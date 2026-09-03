# ESPressio Primitive

Dependency-neutral conceptual-message vocabulary for the ESPressio Development Platform.

**Release target:** `1.0.0`

ESPressio Primitive contains the small set of identities and compatibility types that are shared by conceptual primitive families such as Command, Event, State, Mesh control and future application-defined families. It deliberately does **not** define transport, routing, destinations, payload schemas, application semantics or a common polymorphic base class for every primitive.

## When to use it

Consume ESPressio Primitive when a library or application needs to refer to conceptual messages without coupling itself to Command, Event, State or Mesh semantics. Typical uses include carrying a transport-independent message identity, correlating later asynchronous messages, advertising a primitive-family protocol range or comparing a family-level semantic contract fingerprint.

## Conceptual message identity

```cpp
#include <ESPressio_Primitive.hpp>

using ESPressio::Primitive::ConceptualMessageId;
using ESPressio::Primitive::CorrelationId;

const ConceptualMessageId messageId(42);
const CorrelationId correlation = CorrelationId::FromMessage(messageId);
```

`ConceptualMessageId` identifies one conceptual message occurrence. That identity remains stable when the same message is serialized, transported, retried or routed differently. A genuinely new conceptual message receives a new identity.

`CorrelationId` is a different semantic type. It may intentionally carry the scalar value of an earlier message when associating later work, but it does not create request/response, waiting, completion or RPC semantics.

Both values use zero as Invalid/Unspecified.

## Primitive family namespace

`PrimitiveFamilyId` is an exact 16-bit wire/API value. The namespace is permanently partitioned as follows:

| Range | Meaning |
| --- | --- |
| `0x0000` | Invalid / Unspecified |
| `0x0001`–`0x7FFF` | ESPressio-defined families |
| `0x8000`–`0xFFFE` | Application/private families |
| `0xFFFF` | Reserved sentinel |

The constants and range helpers live in `ESPressio_PrimitiveFamilyRegistry.hpp`.

ESPressio-defined families are allocated individually from this central registry. Repositories are not given arbitrary numeric blocks, and application/private identifiers are not derived from names or hashes.

## Protocol-version compatibility

`PrimitiveProtocolVersion` is a compact scalar revision that evolves independently for each primitive family. `PrimitiveProtocolVersionRange` represents one inclusive supported range and can select the highest mutually supported revision between two peers.

```cpp
PrimitiveProtocolVersionRange local{1, 3};
PrimitiveProtocolVersionRange remote{2, 4};
PrimitiveProtocolVersion selected{};

if (local.TrySelectHighestMutual(remote, selected)) {
    // selected == 3
}
```

Family protocol versioning is separate from payload/schema versioning. A CommandType, EventType, StateType or Mesh control message may evolve its own schema without redefining the primitive-family identity.

## Contract fingerprint

`ContractFingerprint` is the exact 32-byte SHA-256 compatibility digest used to identify a family-level semantic contract. It is compatibility metadata only; it is not authentication, a credential, a signature or proof of identity.

The digest must be produced from a deterministic, versioned and domain-separated canonical semantic encoding owned by the corresponding contract. Compiler ABI/layout, RTTI/type names and incidental C++ representation must never be fingerprint inputs.

## Design guarantees

- No Arduino, ESP-IDF, FreeRTOS or hardware dependency.
- No dependency on Command, Event, State, Radio or Mesh.
- No RTTI requirement.
- Fixed-width bounded identity and fingerprint representations.
- Distinct semantic types for message identity and correlation.
- No transport or destination semantics.
- No giant common primitive base class.

## Installation during coordinated development

```ini
lib_deps =
    https://github.com/ESPressio-Development-Platform/ESPressio-Primitive.git#structural_realignment
```

During this coordinated Mesh implementation tranche, downstream propagation branches that depend on Primitive are repinned to `structural_realignment_propagation_ESPressio-Mesh` as required by the platform propagation policy.
