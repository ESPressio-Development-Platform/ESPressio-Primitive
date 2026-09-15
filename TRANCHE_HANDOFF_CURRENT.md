# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Continuation state: structural Tranches 2–9 CLOSED; Tranche 10 ACTIVE at D10-15
Latest user time reference: 08:24 Europe/Prague

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical decisions. `TRANCHE_8_CLOSURE.md`, `TRANCHE_9_RESOURCE_ACCOUNTING.md` and `TRANCHE_9_CLOSURE.md` remain formal closure evidence. Live source branch tips are implementation truth and MUST be re-queried before every mutation.

## Authorization boundary

Implementation remains authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags/releases, Wiki publication, force pushes and backward-compatibility shims remain outside authorization. Tranche 12 release preparation remains separate and unauthorized.

The user requires continuous implementation rather than status-only pauses. This handoff must remain current on `ESPressio-Primitive/primitives_redesign` so a successor agent can resume without reconstructing the tranche.

## Mandatory continuation protocol

Before changing any repository:

1. re-query the exact `primitives_redesign` branch tip wherever that branch exists;
2. inspect the manifest/dependency boundary before implementation source;
3. consume already-closed provider contracts rather than reintroducing predecessor APIs;
4. classify tests/examples semantically before migrating them;
5. keep mutations small/coherent and validate exact-tip workflows;
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
- Dynamic/common consumers consume final TypeDirectory/P3/family descriptors/factories/diagnostics and do not become semantic owners.
- Generic State tooling remains read/inspect only; no generic mutation surface may be invented.
- TypeDirectory/schema availability is discovery metadata, never authorization.
- Dynamic input is bounded before parse/construction; no unbounded heap fallback or exception-driven retry path.
- Threads uses one root Thread task/stack/common Wake. `ThreadWith<TCapabilities...>` is the sole generic capability composition host; bare `Thread` is the sole zero-capability spelling.
- Reusable specialized Thread flavours including `PrecisionThread` are removed, not retained as aliases/wrappers/facades. Concrete domain workers may remain by composing final capabilities.
- Precision is a resident capability over the root Thread. It owns cadence/telemetry semantics but no private task, private scheduler loop, private wake signal or `Iterate()` callback. `DesiredIterationPeriod` is replaced by explicit execution-budget semantics.
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
14. D10-14 WiFi Command/Event integration -> final family APIs — **CLOSED/GREEN**
15. D10-15 WiFiWorker away from PrecisionThread — **ACTIVE**
16. D10-16 Logging bounded diagnostics validation
17. D10-17 ESP32 non-Radio downstream cleanup
18. D10-18 prove Units remains dependency-neutral
19. D10-19 tests/examples/manifests/workflows/dependency guards/security tests
20. D10-20 docs/schema examples/cross-tool integration validation

## Closed D10 evidence summary

- D10-01 focused run `34820218599` SUCCESS.
- D10-02 Web schema run `34823200466` SUCCESS.
- D10-03 Web typed Command run `34823927243` SUCCESS.
- D10-04 Event dynamic-dispatch run `34825328341` SUCCESS.
- D10-05 generic State read-only run `34827626308` SUCCESS.
- D10-06 WebSocket focused run `34830311993` SUCCESS; aggregate Web Host `34830311963` SUCCESS.
- D10-07 Timing evidence focused run `34831049103` SUCCESS; aggregate `34831049006` SUCCESS.
- D10-08 Lua Primitive discovery focused run `34831877208` SUCCESS at Lua `d15ad661a9da41224670f2b30d7be357a598ac6b`.
- D10-09 Lua Command closure tip `ce1e7a5cb83b150f52e99160d5c6c8e97e90c457`; focused `34834072387` SUCCESS; aggregate `34834072357` SUCCESS.
- D10-10 Lua Event closure tip `8eeff358a862391856b70903b42c074ebf2c25f1`; focused `34834794887` SUCCESS; aggregate `34834794904` SUCCESS.
- D10-11 Lua State closure tip `e09f01755b8ebf4094f66270e7cce13a6399c06b`; focused `34847762946` SUCCESS; aggregate `34847763087` SUCCESS.
- D10-12 Serial closure tip `a86612d78b57501870195c9d954d8993a8f25f97`; focused Command run `34859791114` SUCCESS.
- D10-13 Serial `Final Diagnostics Contract` run `34859791169` SUCCESS. Aggregate Serial run `34859791064` remains red only for independently-owned Logging/Timing migration debt reserved for D10-16.

## D10-14 — WiFi final Command/Event integration — CLOSED/GREEN

WiFi Command/Event integration now consumes final family APIs. WiFi owns WiFi semantics/configuration/persistence/platform behavior but no duplicate Command/Event runtime.

Source closure WiFi tip before D10-15: `da39424ae80195766a8a6ad6a5ab626927618238` (`Complete WiFi Event runtime surface`). The final typed Event bridge includes the complete Event runtime surface needed for `TryDispatch`; typed WiFi Commands use final Command runtime/descriptor contracts.

Exact-tip downstream validation exposed and fixed two independent dependency/test-infrastructure defects rather than weakening WiFi family semantics:

- Serializable `9bec7caa4fb515e564ea0146bd44f77610e9aebc` completes zero-property bounded-schema handling through metadata/schema/deserializer paths. Serializable run `34936398752`: host job `104275135814` SUCCESS; ESP32 job `104275136043` SUCCESS.
- Task `db7380e7b247cace222a96bebae056205efc0963` expands the deterministic test-only `HostRuntime` execution-context capacity so the legitimate 13 WiFi Command lanes plus response router can initialize. Task run `34936630325`: host job `104275852921` SUCCESS; ESP32 job `104275852749` SUCCESS. No production Command/Task capacity semantics were changed.

Final WiFi validation uses run `34931486431` against those live dependency tips:

- `host-contracts` job `104276459857`: **SUCCESS** — predecessor-architecture rejection, configure, build and all host contracts pass.
- `esp32-family-surface` job `104276461079`: **SUCCESS**.

D10-14 is therefore **CLOSED/GREEN**.

## D10-15 — WiFiWorker final Thread/Precision composition — ACTIVE

Architecture target is locked by TH8/TH11/TH14: the concrete `WiFiWorker` remains valid, but must compose the final generic Thread host plus resident Precision capability. It must not derive from or preserve `PrecisionThread`, must not retain `Iterate()`, and must not own another scheduler/task/signal. WiFi work demand continues to use Precision `Bump()` through the one common Thread wake. `DesiredExecutionBudgetMilliseconds` maps to Precision's explicit iteration execution budget, not to a second cadence concept.

Current implementation commits on `ESPressio-WiFi/primitives_redesign`:

- `9411436244787d6332686d054b2d1c3f25448dbf` — `WiFiWorker` migrated from `PrecisionThread<...>` to `ThreadWith<Precision<8>>`; `OnLoop()` returns `ThreadWorkDisposition::IdleReady`; period maps to `SetCadencePeriod`; execution budget maps to `SetIterationExecutionBudget`; manager work signal maps to Precision `Bump()`; no private scheduler/wake/task is introduced.
- `727880476d13c8c7c3ae635cdd1521d2babe6136` — added `tests/test_wifi_worker.cpp`, proving final capability composition, one root execution context/common work signal, immediate first application iteration, runtime tuning/Bump servicing and clean Shutdown.
- `9aa7d5ace928fe71b206a741e53c4d6a183880ec` — wired the worker contract into host CTest.
- `48a2bca844245cf08e5b4e3ff2c603f865bfa914` — CI rejects `PrecisionThread`, `PrecisionThreadTraits`, `SetDesiredIterationPeriod` and `Iterate()` in production WiFiWorker, requires final `ThreadWith<Precision<8>>` plus execution-budget mapping, and compiles the final WiFiWorker surface in the ESP32 consumer.

A WiFi workflow run was automatically started for source commit `9411436244787d6332686d054b2d1c3f25448dbf` as run `34937251796`; later commits trigger successor runs and the latest exact branch-tip run is the D10-15 closure authority. Do not close D10-15 until the latest WiFi head passes both host contracts (including `ESPressioWiFiWorkerContract`) and ESP32 final WiFi Thread/Event/Command compilation.

### Immediate next action

1. Re-query the exact current WiFi head (expected `48a2bca844245cf08e5b4e3ff2c603f865bfa914` unless externally advanced).
2. Inspect the latest WiFi Actions run for that exact head.
3. Fix only compiler/test defects confirmed by the final contracts; do not add a `PrecisionThread` compatibility layer.
4. Once host + ESP32 are green, record D10-15 CLOSED/GREEN here and proceed immediately to D10-16 Logging bounded diagnostics validation.

## Known D10-16 debt

`ESPressio-Logging/primitives_redesign` tip `50bf7ed76698152c97651a75a28a760bb33dcccb` still consumes removed Timing symbols (`ClockSynchronizationState` and `.State` on final `ClockSynchronizationStatus`). This is explicitly reserved for D10-16 and must not be repaired by resurrecting predecessor Timing APIs.
