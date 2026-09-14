# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-14
Continuation state: structural Tranches 2–9 CLOSED; Tranche 10 ACTIVE at D10-08
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
7. D10-07 retained Web clock helper -> final Timing evidence/quality contract — **CLOSED/GREEN**
8. D10-08 Lua Primitive descriptor discovery adapter — **ACTIVE NEXT**
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

Web replaced the predecessor raw `CommandRequestEnvelope` -> dynamically allocated `Event::InboundCommandEvent` path with bounded descriptor-driven typed Command admission. Frozen TypeDirectory lookup and caller-owned authorization precede bounded family-owned construction; fire-and-forget requests use `Command::SubmitDynamicCommand`; requester-required Commands fail explicitly rather than dropping response semantics. No CommandRegistry, raw envelope, Event wrapper or hidden heap fallback remains. Focused `Primitive Command Ingress Contract` run `34823927243` SUCCESS at Web `eddc6fa57f2f9cdd4dff7035517ee4fbebb27b61`.

### D10-04 — CLOSED/GREEN

Web removed the obsolete HTTP `IEventTransport` / `EventTransportBuffer` receiver and heap-resized packet path. The replacement performs frozen Event descriptor discovery, caller-owned authorization, bounded DirectBinary/CBOR/JSON P3 input and family-owned `Event::DispatchDynamicEvent`. Final Event has no runtime listener registry: listener/target topology is frozen before `Runtime::Start()`. Focused `Primitive Event Web Contract` run `34825328341` SUCCESS at Web `d92f22d85422a0f8156ce533717e696b1bbe9276`.

### D10-05 — CLOSED/GREEN

State already exposed the required immutable tooling seam in `StateTypeDescriptor`: bounded per-format metadata plus family-owned `ReadDynamicState()`. Web replaced codec-era State tooling with fixed-capacity `HttpStateInspection`, GET/HEAD only, caller-owned selection/authorization, bounded DirectBinary/CBOR/JSON, and immutable `TruthTime`. No generic mutation API or `SetByTypeId` was added. Exact-tip `Primitive State Web Contract` run `34827626308` SUCCESS at Web `9690f3da1081fab687744ccabe0cd4a963afe5dc`.

### D10-06 — CLOSED/GREEN

Session references: user time 11:08 through 11:47 Europe/Prague.

Exact provider rebaseline before writes: Web `9690f3da1081fab687744ccabe0cd4a963afe5dc`, Sockets `3c0d23255295bc9b6609af1390b5c47ed6750641`, Adapters `8a9dc6ce5f4c57361824637a1d614f7699e5dc73`, Event `532d04e1200b04b5734b68467018c597ae996223`, Command `658a9f9064a8ef58a0016d041a29be0c8ca3da7f`, State `25637a7555e3a03f1d709bd8e37340bc4d545b6e`.

Final Sockets already owned the complete neutral lower-transport seam: fixed pre-frozen route/session topology, bounded stream/datagram frame storage, finite outbound admission correlations/inbound receipt slots, exact destination-Primitive admission receipt carriage, synchronous accepted-write ownership, generation-safe availability/restart, quiesce and bounded service without a transport-owned polling worker. No Sockets provider expansion was required.

Web outcome:

- `4216d4a8e29066cac24607b91b760c97d3b072db` added `ESPressio_WebSocketSocketAdapter.hpp`, composing WebSocket binary sessions into final Sockets/A2 without family semantics;
- application-composed route slots freeze before Sockets start; dynamic connections only occupy/release those fixed slots and toggle availability/generation;
- server connection-to-route choice is application-owned rather than derived from connection ID;
- binary ingress feeds Sockets; outbound Sockets frames use `SendBinary`; text remains Web presentation traffic;
- `7831a883a1e7d6a196a58ce0aac6241d7b23fbe3` added real Sockets/A2 integration tests; `7153edddbc9f1b3c8cbff5d36def9df10657f4e0` replaced the aggregate predecessor target; `f01a38fa3e0906be48d6a669d42b693ed10d2054` added final provider checkouts; `afad4a8f193f57e014ed9a1ab478db8962f4da8c` added focused validation.

Four predecessor artifacts were removed with no shim:

- `ESPressio_WebSocketEventBridge.hpp` at `d212211b25ea549645ef33ef6aa62f54f977e13b`;
- `ESPressio_WebSocketEvents.hpp` at `1e7da1cf189d9d2c9882d9e2632b8f72edc65278`;
- `ESPressio_WebSocketEventTransport.hpp` at `b141317fee27873406239dd6cce7db867a6d1f93`;
- `test_websocket_event_bridge.cpp` at `6756fe64b94ef1b6cfe063e4daba531920c3db16`.

`527ede39aae7ee86f6370be6e604a0fb523b0bdc` strengthened the focused workflow to keep those paths absent. Exact post-deletion focused run `34830311993` SUCCESS and aggregate Host Tests run `34830311963` SUCCESS.

### D10-07 — CLOSED/GREEN

Provider rebaseline: Web `527ede39aae7ee86f6370be6e604a0fb523b0bdc`; Timing `f94e82459ebbca42e74e210e306be0861cc8d73b`; Sockets `3c0d23255295bc9b6609af1390b5c47ed6750641`. Timing still depends only on System + Units + Observable. Sockets V2 remains the bounded socket/network K1/K2 wire seam and explicitly owns no worker, estimator or fixed cadence.

The retained Web `ESPressio_WebSocketClockSynchronization.hpp` was classified as predecessor because it depended on removed `PrecisionThread`, owned `SynchronizationIntervalMilliseconds`/automatic periodic scheduling, used the old templated synchronization target/message API and reconstructed receive time by asking the protocol for a later local timestamp after callback entry.

Final Web outcome:

- `3a489e7a2cccfa40c6562ce808601d9cd1f84fef` replaced the helper with Sockets V2 + final `Timing::IClockSynchronizationTarget` composition;
- Web owns no clock worker and no synchronization cadence. The embedding bounded service context calls one explicit `Service(nowMonotonic)` quantum; Sockets `EvidenceDue()` delegates the due decision to Timing's adaptive `NextRequiredSynchronizationMonotonic`;
- `ServiceTimeout()` records missed evidence deadlines through Timing rather than creating retry/cadence logic in Web;
- client connect/disconnect publishes reference availability and real continuity loss to the final protocol; stale pending evidence is not reused across disconnection;
- provider/composition code may supply an explicit `WebSocketClockReceiveCaptureSource` returning the exact `Timing::ClockTimestampCapture<>` taken near the concrete receive boundary. Quality and uncertainty remain Timing-domain evidence and must be truthful;
- when no provider capture is supplied, the portable helper uses only `SocketClockSynchronizationProtocol::CaptureServiceReceive()`, i.e. an immediate callback-time `SoftwareUnbounded` capture with unknown uncertainty. It never upgrades that evidence or reconstructs historical receive System time;
- a nonblocking atomic gate prevents concurrent service/receive mutation of the one protocol state without introducing an internal blocking worker/queue;
- non-clock WebSocket binary frames are ignored by clock composition rather than reinterpreted.

Validation:

- `e187e1b4527962d69b18f0471aad7ae856bbcacd` added a complete WebSocket K1/K2 exchange contract with caller-supplied T2/T4 captures, exact T1/T2/T3/T4 preservation into Timing, adaptive deadline service, timeout diagnostics, disconnect continuity loss and unrelated-frame rejection;
- `2525fdd6175408abde5aa007243414dd18ff048b` added the clock target to the aggregate host graph;
- `52d0166ed34ebc563a5eef5be214dd1ad7a3476c` added focused validation with a guard rejecting `PrecisionThread`, fixed synchronization interval, automatic cadence, old request-message/broadcast APIs and `GetLocalTimestamp` reconstruction.
- focused `WebSocket Timing Evidence Contract` run `34831049103` SUCCESS on first exact-tip execution;
- aggregate `Host Tests` run `34831049006` SUCCESS: configure, full build and all current Web CTest targets passed against final providers.

No Timing or Sockets provider change and no version change was required.

## Immediate continuation — D10-08

D10-08 adds the Lua Primitive descriptor discovery adapter. It must consume the already-closed Primitive `TypeDirectoryView` rather than create a Lua-owned registry, and discovery must remain metadata-only rather than authorization.

Before writes:

1. inventory `ESPressio-Lua` branches and rebaseline the highest authorized/current redesign source; do not silently treat `main` as a redesign branch if a newer `primitives_redesign` branch now exists;
2. inspect Lua manifest/dependency boundary and all current type/instance registration/public execution surfaces before choosing the integration point;
3. recheck Primitive `TypeDirectoryView` exact public API and D10-01 Web adapter only as a consumer example, not as a dependency;
4. expose bounded deterministic family/type/name discovery into Lua without copying descriptors into a second mutable registry and without exposing family extension pointers as Lua authorization handles;
5. do not pull Command/Event/State semantics into D10-08; those are ordered D10-09/10/11 milestones;
6. add focused host validation against exact Primitive/System/Lua provider tips, preserving Lua's existing constructor/type-registration contracts;
7. after exact-tip green, update this handoff and continue directly to D10-09.
