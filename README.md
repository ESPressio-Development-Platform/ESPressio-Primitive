# ESPressio Primitive

Dependency-neutral C++17 Type identity, immutable discovery metadata, policy contracts and destination admission vocabulary for the ESPressio Development Platform.

Primitive defines shared facts. Event owns occurrence distribution, Command owns asynchronous execution and State owns authoritative truth. Their runtimes, serialization, persistence, transport and scheduling do not live here. There are no external dependencies, registration tasks, heap registries or static-constructor registration.

## Installation

```ini
lib_deps =
    https://github.com/ESPressio-Development-Platform/ESPressio-Primitive.git#primitives_redesign
```

Include `ESPressio_Primitive.hpp`, or an individual public header. All public headers compile independently in C++17 without RTTI or exceptions.

## Family and Type identity

| Family | Wire value |
| --- | --- |
| Mesh control | `0x0001` |
| Command | `0x0002` |
| Event | `0x0003` |
| State | `0x0004` |

Family `0` is invalid, `0xFFFF` is reserved, `1..0x7FFF` is platform-owned and `0x8000..0xFFFE` is application-private. `FamilyIds::IsUsable`, `IsESPressioDefined` and `IsApplicationPrivate` check those ranges.

```cpp
#include <ESPressio_Primitive.hpp>
namespace P = ESPressio::Primitive;

constexpr P::EventTypeId alarmType{42};
constexpr P::CommandTypeId resetType{42}; // Distinct family, distinct C++ Type.
constexpr P::PrimitiveTypeKey alarmKey{P::FamilyIds::Event, alarmType.Value()};
static_assert(alarmKey.IsValid());
static_assert(P::FamilyIds::IsApplicationPrivate(0x8000));
using PrivateTypeId = P::PrimitiveTypeId<0x8000>;
constexpr PrivateTypeId privateType{7};
```

Strong Type IDs have `Value()`, explicit validity conversion, equality, inequality and scalar ordering. They cannot implicitly convert between families. Zero is invalid. `PrimitiveTypeKey` compares family first, then the 64-bit Type value. Names never determine numeric identity.

`ConceptualMessageId` remains a nonzero 64-bit occurrence value with the same explicit scalar/value/comparison operations. A family owns issuance and exhaustion; Primitive does not reset or restore a family's sequence.

```cpp
constexpr P::ConceptualMessageId occurrence{99};
static_assert(bool(occurrence) && occurrence.Value() == 99);
```

## Explicit directory bootstrap

Each family supplies `PrimitiveTypeTraits<T>::Descriptor() noexcept`, returning a common descriptor by value. Ordinary application code calls `Register<T>()`; it does not construct a T or register a runtime callback.

This self-contained mock family demonstrates the customization point:

```cpp
struct AlarmDefinition {};
namespace ESPressio::Primitive {
template<> struct PrimitiveTypeTraits<AlarmDefinition> {
    static constexpr PrimitiveTypeDescriptor Descriptor() noexcept {
        return {{FamilyIds::Event, 42}, "alarm", {}, {1, 1}, {}, {}, {}};
    }
};
}

P::TypeDirectory<8> types;
auto registration = types.Register<AlarmDefinition>();
if (registration != P::TypeDirectoryRegistrationStatus::Success) {
    // Handle the configuration error; no entry was added on failure.
}
auto initialization = types.Initialize();
if (initialization == P::TypeDirectoryInitializationStatus::Success) {
    auto view = types.View();
    const auto* byId = view.Find({P::FamilyIds::Event, 42});
    const auto* byName = view.Find(P::FamilyIds::Event, "alarm");
    for (const auto& descriptor : view) {
        // Immutable descriptors, ordered by family and Type ID.
        (void)descriptor;
    }
    (void)byId;
    (void)byName;
}
```

Registration statuses are `Success`, `Full`, `DuplicateKey`, `DuplicateCanonicalName`, `InvalidDescriptor` and `Frozen`. Duplicate registration is an error even for identical metadata. The same name/number in two different families is allowed. Names are exact and case-sensitive.

`Initialize()` validates every candidate before an in-place bounded sort, then freezes. Initialization statuses are `Success`, `InvalidDescriptor`, `DuplicateKey`, `DuplicateCanonicalName` and `AlreadyFrozen`. Failed initialization leaves configuration unfrozen. Invalid registration can be corrected and retried. No partial frozen view is published.

`Size()` and `IsFrozen()` inspect the directory. `View()` returns an unavailable view before successful initialization. A default `TypeDirectoryView` is unavailable; a frozen `TypeDirectory<0>` gives a valid empty view. Views expose `IsFrozen()`, `Size()`, `begin()/end()` and both `Find` overloads. A missing lookup returns null.

Configuration is owner-serialized. Publish the initialized directory/view to other threads using normal synchronization. Thereafter reads are immutable, lock-free and allocation-free. The directory cannot be copied/moved, reopened, removed from or replaced in place. Its owner must outlive every view and dependent runtime.

## Descriptor ownership and serialization bounds

`PrimitiveTypeDescriptor` stores `Key`, `CanonicalName`, `Capabilities`, `Versions`, `Contract`, `SerializedSize` and `FamilyExtension`. Common fields are copied. Name and opaque extension references must point to immutable static-lifetime storage. The raw `Register(descriptor)` overload is intended for family infrastructure.

```cpp
static constexpr unsigned familyMetadata = 7;
P::PrimitiveTypeDescriptor descriptor{
    {P::FamilyIds::Event, 43}, "bounded.alarm",
    P::PrimitiveTypeCapabilities{3}, // Serializable | Transmissible
    {1, 1}, {}, {128}, {&familyMetadata}
};
if (descriptor.IsValid() &&
    descriptor.Capabilities.Contains(P::PrimitiveTypeCapability::Serializable)) {
    P::TypeDirectory<1> directory;
    directory.Register(descriptor);
    directory.Initialize();
}
```

Capability bits are Serializable `1` and Transmissible `2`; transmission requires serialization. Local is inherent. Unknown bits are invalid. Serialized Types require a positive `MaximumCompletePrimitiveWireBytes` summary. This is the conservative maximum across all bindable formats, including the family envelope and excluding Mesh/Radio/security framing. Serializable and each family supply the actual per-format traits; this library does not infer them.

`PrimitiveFamilyExtensionRef::Data` is opaque. Only the owning family may interpret it after checking the descriptor family. The directory invokes no extension functions, performs no serialization and grants no operation permission. There is no binary plugin ABI promise.

## Stateless structural policies

A Transmissible Type explicitly selects a family policy Type. The shared gate recognizes C++17 structural definitions, with no virtual policy, per-message policy override or implicit preset.

```cpp
struct ImportantDelivery {
    using PolicyCategory = P::OccurrenceDeliveryPolicyTag;
    using RequiredEvidence = P::DestinationPrimitiveAdmission;
    using TerminalDisposition = P::ReportTerminalFailureToFamily;
    static constexpr std::uint64_t MaximumResidenceNanoseconds = 2'000'000'000;
    static constexpr std::uint16_t MaximumAttempts = 4;
    static constexpr std::uint64_t MaximumAdapterAdmissionWaitNanoseconds = 5'000'000;
    static constexpr std::uint64_t MinimumRetrySpacingNanoseconds = 25'000'000;
    static constexpr std::uint64_t MaximumRetrySpacingNanoseconds = 250'000'000;
};
static_assert(P::IsOccurrenceDeliveryPolicy<ImportantDelivery>::value);
constexpr auto policy = P::PrimitivePolicyContract<ImportantDelivery>::Descriptor();
constexpr auto fingerprintInput = policy.CanonicalBytes();
```

The initial logical attempt counts as one. Residence begins at the first family-to-adapter attempt and covers all waits, route changes and retries; none reset the deadline. Fragment/link retries do not count as new logical attempts. Retry minimum must not exceed maximum, and admission wait must fit positive residence. Zero residence is allowed only for one immediate `NoRemoteEvidence` attempt with zero wait/retry bounds. All-bits-set infinity sentinels and stateful policy objects are rejected.

Occurrence evidence is `NoRemoteEvidence` or `DestinationPrimitiveAdmission`. Terminal behavior is `DiagnosticOnlyAfterBudget` or `ReportTerminalFailureToFamily`. The latter informs family infrastructure, not an application callback named by the policy.

State has a separate category and terminal meaning:

```cpp
struct LatestTruth {
    using PolicyCategory = P::StateConvergencePolicyTag;
    using RequiredEvidence = P::DestinationPrimitiveAdmission;
    using Supersession = P::LatestAuthoritativeValue;
    using ExhaustionDisposition = P::DormantNeedsConvergence;
    static constexpr std::uint64_t MaximumResidenceNanoseconds = 2'000'000'000;
    static constexpr std::uint16_t MaximumAttempts = 4;
    static constexpr std::uint64_t MaximumAdapterAdmissionWaitNanoseconds = 5'000'000;
    static constexpr std::uint64_t MinimumRetrySpacingNanoseconds = 25'000'000;
    static constexpr std::uint64_t MaximumRetrySpacingNanoseconds = 250'000'000;
};
static_assert(P::IsStateConvergencePolicy<LatestTruth>::value);
constexpr auto convergence = P::PrimitivePolicyContract<LatestTruth>::Descriptor();
```

Latest truth supersedes pending older truth. Exhaustion retains only bounded dormant convergence state; a new commit, availability transition or explicit resynchronization may start another bounded campaign. No periodic retry is implied.

`PrimitivePolicyDescriptor` is immutable descriptive metadata at the binding boundary. `CanonicalBytes()` supplies a versioned 40-byte semantic input to the family's domain-separated fingerprint. Identical semantics have identical bytes regardless of C++ names. These bytes are not a packet policy field. Family fingerprints additionally incorporate the normalized schema/other family semantics; a policy encoding alone is not a complete contract digest.

## Admission evidence

```cpp
P::PrimitiveAdmissionDisposition result = P::PrimitiveAdmissionDisposition::Accepted;
if (P::EstablishesDestinationAdmission(result)) {
    // Destination family has taken semantic responsibility, or already accounted for it.
}
if (P::IsAdmissionRetryCandidate(result)) {
    // Owning policy still must authorize retry within remaining attempts/time.
}
```

| Result | Meaning |
| --- | --- |
| Accepted | Complete bounded family ownership acquired |
| AlreadyAccepted | Exact semantic work already accounted for |
| TemporarilyUnavailable | Transient protocol/lifecycle condition |
| ResourceUnavailable | Finite family resource unavailable |
| Unsupported | Type/schema/version unsupported |
| Rejected | Understood but refused by semantic/security policy |
| Malformed | Structural/bounds/canonical validation failed |

Only the first two establish destination admission. Neither implies listener execution, handler completion or observation. The two transient results are retry candidates; the three definitive results must not retry identical bytes automatically. A link ACK or lower-layer byte copy is not this evidence.

## Protocol compatibility and fingerprints

```cpp
P::PrimitiveProtocolVersionRange local{1, 3}, remote{2, 4};
P::PrimitiveProtocolVersion selected{};
if (local.IsValid() && local.Contains(2) && local.TrySelectHighestMutual(remote, selected)) {
    // selected == 3; family protocol version remains independent of payload schema.
}
P::ContractFingerprint::Storage sha256{}; // Fill from the canonical family semantic digest.
sha256[31] = 1;
P::ContractFingerprint fingerprint{sha256};
const bool specified = !fingerprint.IsZero();
const auto& exactDigest = fingerprint.Bytes();
(void)specified;
(void)exactDigest;
```

`ContractFingerprint` is exactly 32 SHA-256 bytes, with exact equality/inequality. It is compatibility metadata, never authentication. The family owns the deterministic versioned, domain-separated semantic digest input. Compiler layout, type names and pointer values are excluded.

## Memory and validation

Directory resident memory is exactly `sizeof(TypeDirectory<N>)`: N common descriptor slots plus count/freeze bookkeeping and compiler padding. Initialization uses one descriptor-sized sort temporary, with no auxiliary index, allocation, stack recursion or thread. Text/extension static storage is separately owned and accounted by its defining family. Lookup is logarithmic by key and bounded linear by name.

Run `cmake -S . -B build`, `cmake --build build`, `ctest --test-dir build --output-on-failure`, and `python3 tests/check_compile_contracts.py`. Tests cover transactional registration, capacity, freeze, ordering, concurrent reads, allocation denial, family identity, normalized policy equivalence, exact admission semantics, negative compilation and standalone no-RTTI/no-exception headers.
