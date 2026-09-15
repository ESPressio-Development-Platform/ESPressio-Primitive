#include <ESPressio_Commands.hpp>
#include <ESPressio_EventThreadCapability.hpp>
#include <ESPressio_Precision.hpp>
#include <ESPressio_StateObserverCapability.hpp>
#include <ESPressio_States.hpp>
#include <ESPressio_ThreadWith.hpp>
#include <ESPressio_TypeDirectory.hpp>
#include <HostRuntime.hpp>
#include <ESPressio_SystemPlatformClock.hpp>

#include <atomic>
#include <cassert>
#include <chrono>
#include <thread>

using namespace ESPressio;
namespace C = ESPressio::Command;
namespace E = ESPressio::Event;
namespace S = ESPressio::State;
namespace T = ESPressio::Threads;

class ManualClock final : public System::Clock::IMonotonicClock {
public:
    std::atomic<std::uint64_t> Value{1000};
    std::uint64_t NowNanoseconds() const noexcept override { return Value.load(); }
    std::uint64_t ResolutionNanoseconds() const noexcept override { return 1; }
    bool IsInterruptSafe() const noexcept override { return true; }
};

template<class Predicate>
void Eventually(Predicate&& predicate) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(3);
    while (!predicate()) {
        assert(std::chrono::steady_clock::now() < deadline);
        std::this_thread::yield();
    }
}

struct PulseEvent final : E::Event<PulseEvent> {
    static constexpr E::EventTypeId TypeId{0x7A01};
    static constexpr std::size_t MaximumLiveInstances = 4;
    static constexpr std::size_t MaximumPendingInstances = 1;
    int Value = 0;
    explicit PulseEvent(int value = 0) noexcept : Value(value) {}
};

struct ObservedState final : S::State<ObservedState, int> {
    static constexpr S::StateTypeId TypeId{0x7A02};
    static constexpr std::string_view CanonicalName = "Test.Platform.ComposedState";
};

struct Reply final { int Value = 0; };
struct Query final : C::Command<Query, Reply> {
    static constexpr C::CommandTypeId TypeId{0x7A03};
    static constexpr const char* CanonicalName = "Test.Platform.ComposedCommand";
    static constexpr std::size_t MaximumLiveInstances = 2;
    static constexpr std::size_t MaximumPendingExecutions = 1;
    static constexpr std::size_t MaximumPendingResponses = 1;
    using ExecutionAdmissionPolicy = C::RequiredExecution;
    int Value = 0;
    explicit Query(int value = 0) noexcept : Value(value) {}
};

using EventCapability = E::ThreadCapability<E::SharedPendingCapacity<1>, PulseEvent>;
using PrecisionCapability = T::Precision<4>;
using ResponseCapability = C::ResponseCapability<1>;
using StateCapability = S::ObserverCapability<ObservedState>;

class CombinedWorker final
    : public T::ThreadWith<EventCapability, PrecisionCapability, ResponseCapability, StateCapability> {
public:
    std::atomic<unsigned> EventCallbacks{0};
    std::atomic<unsigned> StateCallbacks{0};
    std::atomic<unsigned> CommandCallbacks{0};
    std::atomic<unsigned> ApplicationLoops{0};
    std::atomic<int> EventValue{0};
    std::atomic<int> CommandValue{0};

    explicit CombinedWorker(ManualClock& clock)
        : T::ThreadWith<EventCapability, PrecisionCapability, ResponseCapability, StateCapability>({}, &clock) {}

    ~CombinedWorker() override { assert(Shutdown() == T::ThreadStatus::Success); }

    void ConfigureCadence(std::uint64_t period) {
        GetCapability<T::PrecisionTag>().SetCadencePeriod(period);
    }

    C::CommandClient CommandClient() {
        return GetCapability<C::ResponseCapabilityTag>().Client(*this);
    }

    void OnCommand(const C::CommandCompletion<Query>& completion) {
        assert(completion.Kind() == C::CommandCallerCompletionKind::Response);
        const auto* response = completion.ResponseValue();
        assert(response != nullptr);
        CommandValue.store(response->Value);
        ++CommandCallbacks;
    }

protected:
    void OnInitialization() override {
        assert(GetCapability<E::ThreadCapabilityTag>().Listen<PulseEvent>(*this, &CombinedWorker::OnPulse));
        assert(GetCapability<S::ObserverCapabilityTag>().OnChange(*this, &CombinedWorker::OnState));
    }

    T::ThreadWorkDisposition OnLoop() override {
        ++ApplicationLoops;
        return T::ThreadWorkDisposition::IdleReady;
    }

private:
    void OnPulse(const PulseEvent& event) {
        EventValue.store(event.Value);
        ++EventCallbacks;
    }

    void OnState(const S::StateChangeSet& changes) {
        assert(changes.Contains<ObservedState>());
        ++StateCallbacks;
    }
};

struct Handler final {
    Reply Handle(const Query& query, const C::CommandExecutionContext&) {
        return {query.Value + 1};
    }
};

static Timing::QualifiedTime CaptureTruthTime() {
    return {1000, Timing::TimeReliability::Synchronized};
}

static Task::TaskExecutorConfiguration RouterConfiguration() {
    Task::TaskExecutorConfiguration configuration{};
    configuration.Execution.Name = "platformCapabilityRouter";
    configuration.Execution.StackSize = 4096;
    configuration.QueueDepth = 1;
    configuration.OverflowPolicy = Task::TaskQueueOverflowPolicy::Reject;
    configuration.QueueMemoryPolicy = Task::TaskMemoryPolicy::Internal;
    return configuration;
}

int main() {
    HostRuntime platform;
    ManualClock clock;

    System::DeviceIdentifier::Storage device{};
    device[0] = 0x7A;
    assert(System::RuntimeIdentity::Install({System::DeviceIdentifier{device}, System::RuntimeIncarnationId{1}})
           == System::RuntimeIdentity::InstallationStatus::Success);

    Primitive::TypeDirectory<3> directory;
    assert(directory.Register<PulseEvent>() == Primitive::TypeDirectoryRegistrationStatus::Success);
    assert(directory.Register<Query>() == Primitive::TypeDirectoryRegistrationStatus::Success);
    assert(directory.Register<ObservedState>() == Primitive::TypeDirectoryRegistrationStatus::Success);
    assert(directory.Initialize() == Primitive::TypeDirectoryInitializationStatus::Success);

    E::Runtime eventRuntime;
    assert(eventRuntime.Initialize(directory.View()) == E::EventRuntimeStatus::Success);

    using StateRuntime = S::Runtime<S::TypeConfiguration<ObservedState>>;
    StateRuntime stateRuntime;
    auto stateOwner = stateRuntime.BindOwner<ObservedState>();
    assert(stateOwner);
    assert(stateRuntime.Initialize(directory.View(), &CaptureTruthTime) == S::StateRuntimeStatus::Success);

    C::CommandResponseRouter<1> router(RouterConfiguration());
    C::RuntimeConfiguration commandConfiguration{};
    commandConfiguration.ExecutionLane.Name = "platformCapabilityCommand";
    commandConfiguration.ExecutionLane.StackSize = 4096;
    commandConfiguration.ResponseRouter = router.Binding();
    C::Runtime commandRuntime(commandConfiguration);
    Handler handler;
    assert(commandRuntime.BindHandler<Query>(handler, &Handler::Handle) == C::CommandRuntimeStatus::Success);
    assert(commandRuntime.Initialize(directory.View()) == C::CommandRuntimeStatus::Success);

    CombinedWorker worker(clock);
    static_assert(CombinedWorker::HasCapability<E::ThreadCapabilityTag>());
    static_assert(CombinedWorker::HasCapability<T::PrecisionTag>());
    static_assert(CombinedWorker::HasCapability<C::ResponseCapabilityTag>());
    static_assert(CombinedWorker::HasCapability<S::ObserverCapabilityTag>());

    const auto tasksBeforeWorker = platform.Created.load();
    assert(worker.Initialize() == T::ThreadStatus::Success);
    assert(platform.Created.load() == tasksBeforeWorker + 1); // exactly one root Task for all four capabilities
    worker.ConfigureCadence(1000000000ULL);

    assert(eventRuntime.Start() == E::EventRuntimeStatus::Success);
    assert(stateRuntime.Start() == S::StateRuntimeStatus::Success);
    assert(commandRuntime.Start() == C::CommandRuntimeStatus::Success);
    assert(worker.Start() == T::ThreadStatus::Success);

    auto client = worker.CommandClient();
    assert(client);

    assert(PulseEvent::Dispatch(17));
    assert(stateOwner.Set(23, {2000, Timing::TimeReliability::Synchronized}) == S::StateSetStatus::Changed);
    const auto command = client.Execute<Query, &CombinedWorker::OnCommand>(std::chrono::milliseconds(500), 41);
    assert(command.Accepted());

    Eventually([&] {
        return worker.EventCallbacks.load() == 1 &&
               worker.StateCallbacks.load() >= 1 &&
               worker.CommandCallbacks.load() == 1 &&
               worker.ApplicationLoops.load() >= 1;
    });

    assert(worker.EventValue.load() == 17);
    assert(worker.CommandValue.load() == 42);
    assert(worker.GetThreadState() == T::ThreadState::Running);

    assert(worker.Shutdown() == T::ThreadStatus::Success);
    assert(commandRuntime.Shutdown() == C::CommandRuntimeStatus::Success);
    assert(stateRuntime.Shutdown() == S::StateRuntimeStatus::Success);
    assert(eventRuntime.Shutdown() == E::EventRuntimeStatus::Success);
    return 0;
}
