# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-14
Continuation state: structural Tranches 2–9 CLOSED; Tranche 10 ACTIVE at D10-07
Latest user time reference: 11:47 Europe/Prague

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
6. D10-06 WebSocket family bridges/transports onto Sockets/A2/family bindings — **CLOSED/GREEN**
7. D10-07 retained Web clock helper -> final Timing evidence/quality contract — **ACTIVE NEXT**
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

Exact-tip `Primitive State Web Contract` run `34827626308` SUCCESS at Web `9690f3da1081fab687744ccabe0cd4a963afe5dc`: predecessor/mutation guard, strict compile and runtime contract all passed. Aggregate `Host Tests` run `34827626303` built the State integration target successfully at 96%; its sole build failure was the still-predecessor `WebSocketEventBridge`, which became the D10-06 work surface.

### D10-06 — CLOSED/GREEN

Session references: user time 11:08 through 11:47 Europe/Prague.

Exact provider rebaseline before D10-06 writes: Web `9690f3da1081fab687744ccabe0cd4a963afe5dc`, Sockets `3c0d23255295bc9b6609af1390b5c47ed6750641`, Adapters `8a9dc6ce5f4c57361824637a1d614f7699e5dc73`, Event `532d04e1200b04b5734b68467018c597ae996223`, Command `658a9f9064a8ef58a0016d041a29be0c8ca3da7f`, State `25637a7555e3a03f1d709bd8e37340bc4d545b6e`.

Architecture classification established that final Sockets already owns the complete neutral lower-transport seam required by WebSocket composition. `SocketAdapterTransport` provides fixed pre-frozen route/session topology, bounded stream/datagram frame storage, finite outbound admission correlations and inbound receipt slots, exact destination-Primitive admission receipt carriage, synchronous accepted-write ownership, generation-safe availability changes/restart, quiesce and bounded service without a transport-owned polling worker. No Sockets provider expansion was required.

Web outcome:

- `4216d4a8e29066cac24607b91b760c97d3b072db` — added `ESPressio_WebSocketSocketAdapter.hpp`, a Web-owned composition seam from WebSocket endpoint/client binary sessions into final Sockets/A2;
- topology remains fixed: application-composed route slots are bound before Sockets `Freeze()`, while dynamic WebSocket connections may only occupy/release those slots and toggle session availability/generation;
- server connection-to-route choice remains application-owned through an explicit selector/authorization seam rather than deriving identity from a connection ID;
- binary ingress feeds the bounded neutral Sockets datagram parser; outbound Sockets writes call WebSocket `SendBinary`; text remains Web presentation traffic and is not reinterpreted as Primitive transport;
- `7831a883a1e7d6a196a58ce0aac6241d7b23fbe3` added the real Sockets/A2 integration contract;
- `7153edddbc9f1b3c8cbff5d36def9df10657f4e0` replaced the aggregate predecessor bridge target; `f01a38fa3e0906be48d6a669d42b693ed10d2054` added final Adapters/Sockets provider checkout to aggregate CI; `afad4a8f193f57e014ed9a1ab478db8962f4da8c` added focused validation;
- focused run `34828624540` and aggregate Host Tests run `34828624383` both succeeded at `afad4a8f...` before predecessor deletion.

Final cleanup discovered one additional predecessor beyond the originally identified Event bridge/events/test: `ESPressio_WebSocketEventTransport.hpp` directly implemented retired `Event::IEventTransport`, allocated/copy-resized Event transport buffers and bypassed A2/Sockets. It was classified as predecessor rather than retained for compatibility.

The following obsolete files were deleted with no shim:

- `ESPressio_WebSocketEventBridge.hpp` at commit `d212211b25ea549645ef33ef6aa62f54f977e13b`;
- `ESPressio_WebSocketEvents.hpp` at `1e7da1cf189d9d2c9882d9e2632b8f72edc65278`;
- `ESPressio_WebSocketEventTransport.hpp` at `b141317fee27873406239dd6cce7db867a6d1f93`;
- predecessor `test_websocket_event_bridge.cpp` at `6756fe64b94ef1b6cfe063e4daba531920c3db16`.

`527ede39aae7ee86f6370be6e604a0fb523b0bdc` strengthened the focused workflow so all four predecessor paths must remain absent and the replacement neutral adapter must remain free of family-owned transport APIs. Exact post-deletion focused run `34830311993` SUCCESS and aggregate Host Tests run `34830311963` SUCCESS. The aggregate suite configured, built and ran all current Web integration targets against final Primitive/Adapters/Sockets/Serializable/Persistence/Security/State/Event/Command/Threads/Task/Timing/Units providers. No structural version change was made.

## Immediate continuation — D10-07

Initial read-only rebaseline already completed after D10-06 validation:

- Web D10-06 exact closure tip is `527ede39aae7ee86f6370be6e604a0fb523b0bdc`;
- Timing remains `f94e82459ebbca42e74e210e306be0861cc8d73b` (`Expose coherent Timing model capture`), depending only on System + Units + Observable;
- Sockets remains `3c0d23255295bc9b6609af1390b5c47ed6750641` and exposes the final V2 `SocketClockSynchronizationProtocol` / bounded K1/K2 wire seam.

The retained Web `ESPressio_WebSocketClockSynchronization.hpp` is still predecessor code. It depends on removed `ESPressio_PrecisionThread.hpp`, owns a fixed synchronization cadence through `SynchronizationIntervalMilliseconds`, uses the old templated `IClockSynchronizationTarget<Tick>`/old Sockets message API, and reconstructs receive timestamps by asking the protocol for a later local timestamp after callback entry.

Final provider contracts require the opposite ownership:

1. Timing owns observation validation, estimator/discipline, reliability, uncertainty and adaptive synchronization deadlines.
2. Sockets V2 owns only bounded request/response wire exchange and exact K1/K2 carriage; it owns no worker, estimator or fixed cadence.
3. Concrete WebSocket/provider integration must provide provider-proximate receive captures with truthful `ClockCaptureQuality` and conservative `ClockUncertainty`; it must not reconstruct historical receive time later from System time.
4. Web must consume `Timing::IClockSynchronizationTarget`, `ClockTimestampCapture`, `ClockSynchronizationStatus` and Sockets V2 `EvidenceDue()` / timeout semantics without reintroducing `PrecisionThread` or a Web-owned cadence worker.

Before D10-07 writes, re-query Web/Sockets/Timing exact branch tips and manifests once more, inspect current WebSocket endpoint/client callback capabilities for where truthful receive captures can enter, and classify whether a small Web observer/capture vocabulary extension is required. Preserve WebSocket presentation ownership and do not move estimator/scheduler ownership out of Timing.

After D10-07 implementation, add focused exact-tip validation, require aggregate Web validation to remain green, update this handoff again, then continue directly to D10-08.
