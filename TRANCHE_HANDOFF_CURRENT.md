# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-14
Continuation state: structural Tranches 2–9 CLOSED; Tranche 10 ACTIVE at D10-06
Latest user time reference: 11:08 Europe/Prague

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical decisions. `TRANCHE_9_CLOSURE.md` is the formal Tranche-9 closure evidence. Live source branch tips are implementation truth and MUST be rebaselined before every implementation step.

## Authorization boundary

Implementation remains authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags/releases, Wiki publication, force pushes and backward-compatibility shims remain outside authorization. Tranche 12 release preparation remains separate and unauthorized.

The user requires this living handoff to remain present on `ESPressio-Primitive/primitives_redesign` and to be mirrored as an up-to-date downloadable conversation artifact whenever substantive progress is reported.

## Mandatory continuation protocol

Before changing any repository:

1. re-query the exact source-branch tip;
2. inspect the current manifest/dependency boundary before implementation source;
3. consume already-closed provider contracts rather than reintroducing predecessor APIs for compatibility;
4. classify existing tests/examples semantically before migrating or executing them;
5. keep changes small/coherent and validate exact-tip workflows;
6. update this handoff in the same work session after substantive progression.

## Locked non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning.
- Only `Accepted` / `AlreadyAccepted` establishes destination Primitive admission.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Direct-Radio family envelope remains exactly four bytes: 2-byte LE family + 2-byte LE protocol.
- Immediate physical peer and validated semantic `OriginalSource` remain distinct provenance facts.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Dynamic/common consumers consume final TypeDirectory/P3/family descriptors/factories/diagnostics and do not become new semantic owners.
- Generic State access from tooling is read/inspect only; no arbitrary mutation or generic `SetByTypeId` may be invented.
- TypeDirectory/schema availability is discovery metadata, never authorization.
- Dynamic input is bounded before parse/construction; no unbounded heap fallback or exception-driven retry path.
- No structural-tranche version changes.

## Closed structural work

Foundation F01–F08 and structural Tranches 2–9 are CLOSED. Important closure artifacts remain `TRANCHE_8_CLOSURE.md`, `TRANCHE_9_RESOURCE_ACCOUNTING.md` and `TRANCHE_9_CLOSURE.md`. Tranche 9 must not be reopened unless live source contradicts a locked closure condition.

## Structural Tranche 10 — ACTIVE

Locked work order:

1. D10-01 Primitive TypeDirectory discovery — **CLOSED/GREEN**
2. D10-02 P3 schema/constructibility metadata — **CLOSED/GREEN**
3. D10-03 Web typed Command construction/admission — **CLOSED/GREEN**
4. D10-04 Web Event discovery/final Event APIs — **CLOSED/GREEN**
5. D10-05 Web generic State read/inspect surface — **CLOSED/GREEN**
6. D10-06 WebSocket family bridges/transports onto Sockets/A2/family bindings — **ACTIVE NEXT**
7. D10-07 retained Web clock helper -> final Timing evidence/quality contract
8. D10-08 Lua Primitive descriptor discovery adapter
9. D10-09 Lua typed Command construction/admission adapter
10. D10-10 Lua Event operations through final Event APIs
11. D10-11 generic Lua State read/inspect only
12. D10-12 Serial Command/Event/State consoles/monitors -> final descriptors/diagnostics
13. D10-13 Serial Thread/Timing/transport/WiFi monitors -> final diagnostics seams
14. D10-14 WiFi Command/Event integration -> final family APIs
15. D10-15 WiFiWorker away from PrecisionThread
16. D10-16 Logging bounded diagnostics validation
17. D10-17 ESP32 non-Radio downstream cleanup
18. D10-18 prove Units remains dependency-neutral
19. D10-19 tests/examples/manifests/workflows/dependency guards/security tests
20. D10-20 docs/schema examples/cross-tool integration validation

### D10-01 — CLOSED/GREEN

Primitive already exposed the final fixed-capacity frozen `TypeDirectory` / immutable `TypeDirectoryView`; no provider redesign was needed. Web added opt-in deterministic discovery without interpreting family extensions or inventing a registry. Focused `Primitive Discovery Contract` run `34820218599` succeeded. Aggregate Web failures were classified as later Tranche-10 predecessor consumers rather than repaired with compatibility APIs.

### D10-02 — CLOSED/GREEN

P3 remained Serializable-owned and constructibility remained family-owned. Event dynamic construction/dispatch stays inside Event's fixed runtime/pool; Command dynamic fire-and-forget construction stays inside Command's fixed request pool; response-bearing Commands remain requester-required; State generic dynamic access remains read-only. Provider checkpoints: Serializable `2a0dff001cae91365d90f20a382036bd878f53e4`, Event `532d04e1200b04b5734b68467018c597ae996223`, Command `658a9f9064a8ef58a0016d041a29be0c8ca3da7f`, State `25637a7555e3a03f1d709bd8e37340bc4d545b6e`. Web P3 consumer focused run `34823200466` succeeded.

### D10-03 — CLOSED/GREEN

Web replaced the predecessor raw `CommandRequestEnvelope` -> dynamically allocated `Event::InboundCommandEvent` path with bounded descriptor-driven typed Command admission.

Final behavior:

- frozen TypeDirectory lookup by caller-selected canonical Command name;
- caller-owned authorization before body construction/admission;
- family-owned `CommandTypeDescriptor` / P3 schema decides dynamic capability;
- fire-and-forget requests use `Command::SubmitDynamicCommand`;
- requester-required Commands fail explicitly rather than dropping response semantics;
- request bytes are read into caller-chosen fixed storage bounded by the P3 representation maximum;
- no CommandRegistry, raw envelope, Event wrapper or hidden heap fallback.

Focused `Primitive Command Ingress Contract` run `34823927243` SUCCESS at Web `eddc6fa57f2f9cdd4dff7035517ee4fbebb27b61`. The aggregate host run at that checkpoint built `espressio_web_command_integration_tests`; its red status came from still-unmigrated later Event/State/WebSocket targets and did not block D10-03 closure.

### D10-04 — CLOSED/GREEN

Web removed the obsolete HTTP `IEventTransport` / `EventTransportBuffer` receiver and heap-resized packet path. The replacement performs frozen Event descriptor discovery, caller-owned authorization, bounded DirectBinary/CBOR/JSON P3 input and family-owned `Event::DispatchDynamicEvent`.

Important architectural classification: final Event has no runtime listener registry. Listener/target topology is installed before `Runtime::Start()` and frozen. D10-04 therefore does not invent post-start subscription-by-string. Persistent WebSocket Event delivery is explicitly deferred to D10-06, where session/byte transport belongs.

Web commits for the D10-04 cut were `d4528ef4167e2e3d1a9f34509f6f78430ceaff0e`, `0512988221d5ba5860abaafef523445c8db9eacd`, `8fafcecd00b6798417abb19baecd3075ff97111a`, and validation tip `d92f22d85422a0f8156ce533717e696b1bbe9276`. Focused `Primitive Event Web Contract` run `34825328341` SUCCESS. Aggregate host build at that exact tip built `espressio_web_event_integration_tests`; remaining red surfaces were State and WebSocket.

### D10-05 — CLOSED/GREEN

Session reference: user time 11:08 Europe/Prague.

Provider rebaseline before writes: Web `d92f22d85422a0f8156ce533717e696b1bbe9276`, State `25637a7555e3a03f1d709bd8e37340bc4d545b6e`, Primitive `bb505e50c356dca72bbba6520003deb1c6dfac52`.

State already exposed the required final tooling seam in `StateTypeDescriptor`: immutable Type/P3 metadata, bounded per-format maximum sizes and family-owned `ReadValue` thunks surfaced through `ReadDynamicState()`. No mutation thunk exists and no provider expansion was required.

Web outcome:

- `16f83e96471012db6798845cc07629e416e9d997` — replaced codec-era `ESPressio_WebState.hpp` with `HttpStateInspection<MaximumPayloadBytes>` over final State descriptor/TypeDirectory surfaces;
- only GET/HEAD is handled; generic POST/mutation is not implemented;
- caller-owned target selector and authorizer remain separate from discovery metadata;
- local-only/non-serializable State fails explicitly rather than being reinterpreted;
- DirectBinary/CBOR/JSON response representation is selected from bounded State P3 metadata;
- response includes canonical State Type, TypeId and immutable source `TruthTime` facts;
- fixed caller-chosen response storage is checked against the schema maximum before serialization; no heap fallback;
- no `StatePublisher`, `StateCodec`, `StateContract`, `StateEpoch`, generic `StateOwner` or `SetByTypeId` dependency appears in the production Web State surface.

Test/validation commits included `e0d0b0337ee7ddc3ed59ac3b764595a9f6273569`, CMake alignment `a4cdddf44014fc2a774ce624e32a657b8968d4ca`, focused workflow `a9abca9b781d5c0bdcaf49096b5c9f3357643a6d`, guard correction `94cd169094775ba7cd5d9c86f17a7b55608370ca`, namespace/test correction `7de5a6b99db161782bb629187ba788cace638866`, and final bounded-capacity test tip `9690f3da1081fab687744ccabe0cd4a963afe5dc`.

Failure classification retained for successors:

- first focused failure was a lexical guard false-positive on explanatory text containing `StateOwner`; guard was tightened to actual API/include forms;
- next compile failure was only C++ injected-base-name shadowing inside test definitions and was corrected using `namespace S = ESPressio::State`;
- first functional JSON assertion used a deployment buffer smaller than the schema's worst-case P3 representation. Production correctly rejected it before serialization. The final test uses finite adequate storage and separately proves that a deliberately undersized deployment returns explicit 503 rather than overflowing or allocating.

Exact-tip `Primitive State Web Contract` run `34827626308` SUCCESS at Web `9690f3da1081fab687744ccabe0cd4a963afe5dc`: predecessor/mutation guard, strict compile and runtime contract all passed. Aggregate `Host Tests` run `34827626303` built the State integration target successfully at 96%; its sole build failure was the still-predecessor `WebSocketEventBridge`, which is the D10-06 work surface.

## Immediate continuation — D10-06

Before writes:

1. re-query exact Web, Sockets, Adapters, Event, Command and State branch tips;
2. inspect Web `ESPressio_WebSocketEventBridge.hpp`, `ESPressio_WebSocketEvents.hpp`, base WebSocket/session surfaces and their tests/examples;
3. inspect the final Sockets neutral `SocketAdapterTransport` / A2-facing session lifecycle and exact M1 carriage rather than inferring it from Tranche-9 checkpoint hashes;
4. classify which WebSocket responsibilities are presentation/routing (remain Web-owned) versus neutral byte/session transport (Sockets/A2-owned) versus family semantics (Event/Command/State-owned);
5. remove predecessor EventTransportManager/Event bridge style ownership rather than adapting it with a compatibility wrapper;
6. preserve fixed capacities, generation-safe restart, bounded backpressure and family-owned destination-admission semantics;
7. add focused D10-06 validation if the aggregate suite still contains intentionally later D10-07 failures;
8. update this handoff again after D10-06 substantive progression.

Do not start D10-07 until D10-06's exact final contract and migration classification are proven.