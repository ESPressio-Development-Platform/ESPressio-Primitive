# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Continuation state: structural Tranches 2–9 CLOSED; Tranche 10 ACTIVE at D10-14
Latest user time reference: 07:29 Europe/Prague

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical decisions. `TRANCHE_8_CLOSURE.md`, `TRANCHE_9_RESOURCE_ACCOUNTING.md` and `TRANCHE_9_CLOSURE.md` remain formal closure evidence. Live source branch tips are implementation truth and MUST be rebaselined before every implementation step.

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

## Structural Tranche 10 — ACTIVE

Locked work order:

1. D10-01 Primitive TypeDirectory discovery — **CLOSED/GREEN**
2. D10-02 P3 schema/constructibility metadata — **CLOSED/GREEN**
3. D10-03 Web typed Command construction/admission — **CLOSED/GREEN**
4. D10-04 Web Event discovery/final Event APIs — **CLOSED/GREEN**
5. D10-05 Web generic State read/inspect surface — **CLOSED/GREEN**
6. D10-06 WebSocket family bridges/transports onto Sockets/A2/family bindings — **CLOSED/GREEN**
7. D10-07 retained Web clock helper -> final Timing evidence/quality contract — **CLOSED/GREEN**
8. D10-08 Lua Primitive descriptor discovery adapter — **CLOSED/GREEN**
9. D10-09 Lua typed Command construction/admission adapter — **CLOSED/GREEN**
10. D10-10 Lua Event operations through final Event APIs — **CLOSED/GREEN**
11. D10-11 generic Lua State read/inspect only — **CLOSED/GREEN**
12. D10-12 Serial Command/Event/State consoles/monitors -> final descriptors/diagnostics — **CLOSED/GREEN**
13. D10-13 Serial Thread/Timing/transport/WiFi monitors -> final diagnostics seams — **CLOSED/GREEN**
14. D10-14 WiFi Command/Event integration -> final family APIs — **ACTIVE**
15. D10-15 WiFiWorker away from PrecisionThread — **BLOCKED UNTIL D10-14 GREEN**
16. D10-16 Logging bounded diagnostics validation
17. D10-17 ESP32 non-Radio downstream cleanup
18. D10-18 prove Units remains dependency-neutral
19. D10-19 tests/examples/manifests/workflows/dependency guards/security tests
20. D10-20 docs/schema examples/cross-tool integration validation

## Closed D10 evidence summary

### D10-01 through D10-05

- D10-01: final fixed-capacity frozen Primitive `TypeDirectory` / immutable `TypeDirectoryView` consumed by Web; focused run `34820218599` SUCCESS.
- D10-02: P3 remains Serializable-owned; dynamic construction remains family-owned. Event provider `532d04e1200b04b5734b68467018c597ae996223`; Command provider `658a9f9064a8ef58a0016d041a29be0c8ca3da7f`; State provider `25637a7555e3a03f1d709bd8e37340bc4d545b6e`; Web schema run `34823200466` SUCCESS.
- D10-03: Web raw `CommandRequestEnvelope` / `InboundCommandEvent` path replaced with bounded TypeDirectory/P3/family-owned `Command::SubmitDynamicCommand`; run `34823927243` SUCCESS.
- D10-04: obsolete HTTP `IEventTransport` path removed; bounded descriptor-driven `Event::DispatchDynamicEvent` with explicit authorization; run `34825328341` SUCCESS.
- D10-05: Web State tooling is GET/HEAD read-only through immutable State descriptors + `ReadDynamicState()`, including exact `TruthTime`; run `34827626308` SUCCESS. No generic mutation was added.

### D10-06 — WebSocket final transport composition

Web composes binary WebSocket sessions into final Sockets/A2 through `ESPressio_WebSocketSocketAdapter.hpp`; route slots freeze before Sockets start and Web owns no Primitive-family transport semantics. Predecessor WebSocket Event bridge/events/transport artifacts were removed with no shim. Exact post-deletion focused run `34830311993` SUCCESS; aggregate Web Host Tests `34830311963` SUCCESS.

### D10-07 — Web clock helper final Timing evidence

Web clock synchronization now composes Sockets V2 K1/K2 evidence with final `Timing::IClockSynchronizationTarget`; Web owns no fixed cadence, estimator, historical timestamp reconstruction or clock worker. Exact focused `WebSocket Timing Evidence Contract` run `34831049103` SUCCESS; aggregate Web Host Tests `34831049006` SUCCESS.

### D10-08 — Lua Primitive discovery

Lua has explicit `primitives_redesign`. `ESPressio_LuaPrimitiveDiscovery.hpp` borrows one frozen TypeDirectory view and exposes common metadata only; no second mutable registry and no FamilyExtension authorization handle. Lua core manifest remains System-only, version `1.0.0`. Focused run `34831877208` SUCCESS at Lua `d15ad661a9da41224670f2b30d7be357a598ac6b`.

### D10-09 — Lua typed Command admission

Lua opt-in `ESPressio_LuaCommand.hpp` uses final Command descriptors and bounded P3 bytes with application-owned authorization. Fire-and-forget submission delegates to `Command::SubmitDynamicCommand`; response-bearing Commands remain requester-required and are rejected by the generic Lua path. Lua owns no Command registry/pool/retry/transport/worker lifecycle. Closure tip `ce1e7a5cb83b150f52e99160d5c6c8e97e90c457`; focused run `34834072387` SUCCESS; aggregate `34834072357` SUCCESS.

### D10-10 — Lua Event dispatch

Lua opt-in `ESPressio_LuaEvent.hpp` uses frozen TypeDirectory + immutable Event descriptors, explicit application authorization and bounded P3. Family-owned `Event::DispatchDynamicEvent` owns decode/construction/occurrence/pool/lane/dispatch; Lua owns no listener topology, occurrence identity lifecycle, retry, transport or worker. Closure tip `8eeff358a862391856b70903b42c074ebf2c25f1`; focused run `34834794887` SUCCESS; aggregate `34834794904` SUCCESS.

### D10-11 — Lua State read/inspection — CLOSED/GREEN

Provider checkpoint: State `25637a7555e3a03f1d709bd8e37340bc4d545b6e`. Lua exact closure tip `e09f01755b8ebf4094f66270e7cce13a6399c06b`.

Lua added opt-in `ESPressio_LuaState.hpp` over the final immutable `StateTypeDescriptor`, frozen TypeDirectory and family-owned `ReadDynamicState()`. An application-owned `ILuaStateAuthorizer` is required before family read. A compile-time fixed-capacity result owns one bounded DirectBinary/CBOR/JSON representation long enough to push it into Lua; successful results expose exact immutable `TruthTime` as high/low 32-bit nanoseconds plus reliability. No State owner, mutation, convergence/session, retry, routing, transport or worker capability is exposed.

Validation uses a real final State runtime and typed owners owned only by the test application. It proves no-value, current value `42`, canonical DirectBinary/CBOR/JSON bytes, exact `TruthTime`, authorization-before-read, non-Serializable/local State rejection, invalid index, finite output capacity and unchanged authoritative typed State after all Lua reads. The focused workflow guard rejects mutation/lifecycle names from production Lua State integration.

Initial focused failures were test-fixture-only: a guessed generic Serializable helper, then the wrong DirectBinary helper name, then an invalid assumption that strict Lua modules return `nil` for unexposed members. No State provider/runtime semantic change was made. Final exact-tip `Lua State Inspection Contract` run `34847762946` SUCCESS and exact-tip aggregate `Lua bindings` run `34847763087` SUCCESS. Lua core manifest remains System-only; no version change was made.

### D10-12 — Serial final Primitive-family tooling — CLOSED/GREEN

Serial remains operator/terminal tooling, not a device-device Primitive transport. Its core manifest remains version `0.8.1` with only System + Logging dependencies; Command/Event/State integrations remain opt-in surfaces.

The predecessor family architecture was removed rather than shimmed. Command console/monitor now use frozen TypeDirectory + final Command descriptors and family-owned dynamic submission, including requester-required rejection where the generic console has no requester. Event console/monitor use frozen TypeDirectory + final Event descriptors and family-owned dynamic dispatch. State monitor performs descriptor-driven read/inspection only and never obtains owner/mutation/convergence capability. Operator P3 input is bounded before family decode/construction and action authorization remains application-owned.

Stale Command regression fixtures were migrated from `CommandRegistry`, `CommandRequestEnvelope`, `InboundCommandEvent` and response-route registry assumptions to the final descriptor/P3 contract. Obsolete Event transport formatter/payload machinery, predecessor `EventTransportManager` stubs and old Command Event stubs were removed with no compatibility layer. The orphaned production `ESPressio_SerialTypes.hpp` transport-oriented Event monitor configuration (`EventMonitorMode`, payload/transport/hop/acceptance controls) was also removed and guarded against reintroduction.

Exact closure Serial tip: `a86612d78b57501870195c9d954d8993a8f25f97`. Exact-tip `Command Console Final Contract` run `34859791114` SUCCESS. The migrated family targets also compile in aggregate Host Tests; that aggregate build stops only on the independently-owned Logging/Timing mismatch reserved for D10-16.

### D10-13 — Serial final non-family diagnostics seams — CLOSED/GREEN

Serial Thread/Timing/provider diagnostics now consume final caller-owned seams instead of predecessor managers/workers/transports. Thread diagnostics consume final `IThread` snapshots; Timing diagnostics consume the final Timing quality/synchronization model; ESP-NOW diagnostics inspect the final Radio provider; Sockets diagnostics inspect final A2 transport/session state; WiFi diagnostics use the final WiFi observer/state surface.

`DiagnosticMonitor` intentionally does not aggregate D10-12 family tooling: the family tooling uses Serial's platform-neutral byte-output writer while retained Arduino-facing Thread/Timing/provider monitors consume global `::Print`. No compatibility output bridge or duplicate lifecycle owner was introduced. `DiagnosticMonitor` therefore aggregates only compatible final non-family provider diagnostics. Predecessor `ThreadManager`, `ESPNowTransport`, `SocketWorker`, WiFi EventThread/EventTransport ownership paths are structurally rejected.

Exact-tip `Final Diagnostics Contract` run `34859791169` SUCCESS at Serial `a86612d78b57501870195c9d954d8993a8f25f97`, including host aggregate compile, ownership guards and ESP32 WiFi monitor compile.

Aggregate Serial Host Tests run `34859791064` remains RED solely because `ESPressio-Logging` tip `50bf7ed76698152c97651a75a28a760bb33dcccb` still consumes removed Timing symbols (`ClockSynchronizationState` and `.State` on the final `ClockSynchronizationStatus`). Command/Event/family tooling and WiFi monitor targets build successfully in that same run. This is explicit D10-16 Logging migration debt, not a D10-12/D10-13 failure. Serializable warning-as-error noise was subsequently addressed in D10-14 downstream validation at Serializable `512b610eab89724deca680b7e62162e33b5f660f`.

Documentation/examples were classified, not silently treated as final evidence: Serial README and `examples/EventMonitor/EventMonitor.ino` still describe predecessor Event transport/registry surfaces and are reserved for D10-20 documentation/example closure.

## D10-14 — WiFi final Command/Event integration — ACTIVE

D10-14 migrates WiFi Command/Event integrations onto the final family APIs while keeping WiFi-specific configuration, persistence and hardware/platform semantics WiFi-owned.

The source migration is materially implemented. WiFi uses final typed Serializable Commands + `Command::Runtime`; WiFi Event dispatch uses typed final `TryDispatch` with family-owned admission. `WiFiWorker` remains deliberately untouched for separate D10-15 scope.

D10-14 fixes landed during exact-tip validation:

- Added an explicit `WiFiCommandResponse` outcome constructor after CRTP Serializable inheritance made the previous aggregate-style construction invalid.
- Fully qualified Command family metadata in the WiFi typed Command declarations so nested WiFi command names cannot shadow the `::ESPressio::Command` namespace.
- Serializable `primitives_redesign` exact tip `512b610eab89724deca680b7e62162e33b5f660f` (`Clarify migration control flow`) rewrites condensed migration control flow that triggered `-Wmisleading-indentation` under WiFi host warnings-as-errors validation.
- WiFi `primitives_redesign` exact tip `da39424ae80195766a8a6ad6a5ab626927618238` (`Complete WiFi Event runtime surface`) includes the complete final Event provider/runtime surface required when typed `TryDispatch` instantiates `EventTypeRuntime<TEvent>`; it does not invent a WiFi-local Event runtime or compatibility facade.

Exact-tip validation evidence at WiFi `da39424ae80195766a8a6ad6a5ab626927618238`:

- WiFi architecture-contract run `34931486431`.
- `esp32-family-surface` job `104260438988`: **SUCCESS**. The final WiFi Event + Command family surface compiles on ESP32 at the exact WiFi head.
- `host-contracts` job `104260439076`: **FAILURE**, specifically in the `Build host contracts` step. Predecessor-architecture rejection and host configuration both succeed. The exact remaining compiler diagnostic is the current D10-14 blocker and must be recovered/fixed before closure.

D10-14 is therefore **NOT CLOSED** yet. Its completion gate remains: exact same WiFi head (or its compiler-fix successor) must pass both host contracts and ESP32 family-surface validation. D10-15 remains mutation-blocked until that gate is green.

### Immediate next action

Recover the exact compiler path/line from host job `104260439076` (or its check-run annotations), patch only the compiler-confirmed final-contract defect, rerun exact-tip validation, then record D10-14 CLOSED/GREEN and proceed immediately to D10-15 WiFiWorker migration away from `Threads::PrecisionThread`.
