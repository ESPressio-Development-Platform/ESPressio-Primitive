#include <ESPressio_CommandResponseCapability.hpp>
#include <ESPressio_Event.hpp>
#include <ESPressio_EventThreadCapability.hpp>
#include <ESPressio_Precision.hpp>
#include <ESPressio_State.hpp>
#include <ESPressio_StateObserverCapability.hpp>
#include <ESPressio_ThreadWith.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>

using namespace ESPressio;
namespace C = ESPressio::Command;
namespace E = ESPressio::Event;
namespace S = ESPressio::State;
namespace T = ESPressio::Threads;

namespace {

struct ResourceEvent final : E::Event<ResourceEvent> {
    static constexpr E::EventTypeId TypeId{0x7B01};
    static constexpr std::size_t MaximumLiveInstances = 4;
    static constexpr std::size_t MaximumPendingInstances = 2;
};

struct ResourceState final : S::State<ResourceState, std::uint32_t> {
    static constexpr S::StateTypeId TypeId{0x7B02};
    static constexpr std::string_view CanonicalName = "Test.Platform.ResourceState";
};

using EventCapability = E::ThreadCapability<E::SharedPendingCapacity<1>, ResourceEvent>;
using PrecisionCapability = T::Precision<4>;
using ResponseCapability = C::ResponseCapability<2>;
using StateCapability = S::ObserverCapability<ResourceState>;

class ResourceWorker final
    : public T::ThreadWith<EventCapability, PrecisionCapability, ResponseCapability, StateCapability> {
public:
    ResourceWorker() : T::ThreadWith<EventCapability, PrecisionCapability, ResponseCapability, StateCapability>(Configuration()) {}

private:
    static T::ThreadConfiguration Configuration() {
        T::ThreadConfiguration configuration{};
        configuration.Execution.Name = "v11Resource";
        configuration.Execution.StackSize = 4096;
        configuration.ApplicationStackFloorBytes = 1536;
        return configuration;
    }
};

} // namespace

int main() {
    static_assert(EventCapability::FrameworkStackFloorBytes == 1024);
    static_assert(PrecisionCapability::FrameworkStackFloorBytes == 1024);
    static_assert(ResponseCapability::FrameworkStackFloorBytes == 0);
    static_assert(StateCapability::FrameworkStackFloorBytes == 512);

    static_assert(EventCapability::ExternalStorageBytes == 0);
    static_assert(PrecisionCapability::ExternalStorageBytes == 0);
    static_assert(ResponseCapability::ExternalStorageBytes == 0);
    static_assert(StateCapability::ExternalStorageBytes == 0);

    static_assert(EventCapability::PendingCapacity == 3);
    static_assert(EventCapability::PendingPointerBytes == 3 * sizeof(void*));
    static_assert(ResponseCapability::Capacity == 2);
    static_assert(StateCapability::ObservationCount == 1);
    static_assert(StateCapability::PendingBitmapBytes == sizeof(std::uint64_t));

    ResourceWorker worker;
    const auto profile = T::GetThreadResourceProfile(worker);

    const auto frameworkMaximum = std::max({
        EventCapability::FrameworkStackFloorBytes,
        PrecisionCapability::FrameworkStackFloorBytes,
        ResponseCapability::FrameworkStackFloorBytes,
        StateCapability::FrameworkStackFloorBytes
    });
    const auto externalStorageTotal =
        EventCapability::ExternalStorageBytes +
        PrecisionCapability::ExternalStorageBytes +
        ResponseCapability::ExternalStorageBytes +
        StateCapability::ExternalStorageBytes;

    assert(frameworkMaximum == 1024);
    assert(externalStorageTotal == 0);
    assert(profile.ResidentBytes == sizeof(ResourceWorker));
    assert(profile.ResidentAlignment == alignof(ResourceWorker));
    assert(profile.ExternalStorageBytes == externalStorageTotal);
    assert(profile.ExternalStorageAlignment == 1);
    // The application declares a 1536-byte worst active path. The one shared stack
    // therefore uses max(framework=1024, application=1536), never a sum of capability floors.
    assert(profile.FrameworkStackFloorBytes == 1536);
    assert(profile.FrameworkStackFloorBytes !=
           EventCapability::FrameworkStackFloorBytes +
           PrecisionCapability::FrameworkStackFloorBytes +
           StateCapability::FrameworkStackFloorBytes);
    assert(profile.ConfiguredStackBytes == 4096);
    assert(profile.ExecutionContexts == 1);
    assert(profile.CommonWorkSignals == 1);
    assert(!profile.PlatformControlBytesKnown);
    assert(profile.PlatformControlBytes == 0);

    std::printf("V11_RESOURCE_PROFILE resident_bytes=%zu resident_alignment=%zu\n",
                profile.ResidentBytes, profile.ResidentAlignment);
    std::printf("V11_RESOURCE_PROFILE external_storage_bytes=%zu external_storage_alignment=%zu\n",
                profile.ExternalStorageBytes, profile.ExternalStorageAlignment);
    std::printf("V11_RESOURCE_PROFILE framework_floor_bytes=%u configured_stack_bytes=%u execution_contexts=%u common_work_signals=%u\n",
                static_cast<unsigned>(profile.FrameworkStackFloorBytes),
                static_cast<unsigned>(profile.ConfiguredStackBytes),
                static_cast<unsigned>(profile.ExecutionContexts),
                static_cast<unsigned>(profile.CommonWorkSignals));
    std::printf("V11_RESOURCE_PROFILE platform_control_bytes=%s\n",
                profile.PlatformControlBytesKnown ? "known" : "platform-defined/unknown");
    std::printf("V11_RESOURCE_EVENT pending_slots=%zu pending_pointer_bytes=%zu\n",
                EventCapability::PendingCapacity, EventCapability::PendingPointerBytes);
    std::printf("V11_RESOURCE_COMMAND response_slots=%zu\n", ResponseCapability::Capacity);
    std::printf("V11_RESOURCE_STATE observations=%zu pending_bitmap_bytes=%zu\n",
                StateCapability::ObservationCount, StateCapability::PendingBitmapBytes);
    std::printf("V11_RESOURCE_PRECISION retained_samples=%u\n", 4U);

    return 0;
}
