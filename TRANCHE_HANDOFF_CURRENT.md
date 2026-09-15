# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Continuation state: structural Tranches 2–9 CLOSED; Tranche 10 ACTIVE at D10-17
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
- Timing owns clock discipline and final reliability/evidence vocabulary. Downstream diagnostics consume `TimeReliability` / final status fields and do not restore predecessor synchronization-state APIs.
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
15. D10-15 WiFiWorker away from PrecisionThread — **CLOSED/GREEN**
16. D10-16 Logging bounded diagnostics validation — **CLOSED/GREEN**
17. D10-17 ESP32 non-Radio downstream cleanup — **ACTIVE**
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
- D10-13 focused Serial `Final Diagnostics Contract` run `34859791169` SUCCESS; D10-16 subsequently closed the aggregate downstream gaps that this compile-focused evidence did not exercise.

## D10-14 — WiFi final Command/Event integration — CLOSED/GREEN

WiFi Command/Event integration consumes final family APIs and owns no duplicate Command/Event runtime.

- Serializable `9bec7caa4fb515e564ea0146bd44f77610e9aebc`; run `34936398752`: host `104275135814` SUCCESS, ESP32 `104275136043` SUCCESS.
- Task test infrastructure `db7380e7b247cace222a96bebae056205efc0963`; run `34936630325`: host `104275852921` SUCCESS, ESP32 `104275852749` SUCCESS.
- Final WiFi D10-14 run `34931486431`: host `104276459857` SUCCESS, ESP32 `104276461079` SUCCESS.

## D10-15 — WiFiWorker final Thread/Precision composition — CLOSED/GREEN

Implementation commits on `ESPressio-WiFi/primitives_redesign`:

- `9411436244787d6332686d054b2d1c3f25448dbf` — `WiFiWorker` -> `ThreadWith<Precision<8>>`, final `OnLoop()`/cadence/execution-budget/Bump semantics.
- `727880476d13c8c7c3ae635cdd1521d2babe6136` — final worker contract test.
- `9aa7d5ace928fe71b206a741e53c4d6a183880ec` — worker contract wired into host CTest.
- `48a2bca844245cf08e5b4e3ff2c603f865bfa914` — anti-legacy CI guard and ESP32 final worker compilation surface.

Final run `34937355325` at head `48a2bca844245cf08e5b4e3ff2c603f865bfa914`: host `104278069924` SUCCESS; ESP32 `104278069751` SUCCESS.

## D10-16 — Logging bounded diagnostics validation — CLOSED/GREEN

Logging was migrated from removed Timing synchronization-state vocabulary to final bounded `Timing::TimeReliability` semantics without restoring compatibility aliases.

Logging commits on `ESPressio-Logging/primitives_redesign`:

- `0e9ff772d8e7079aa6b6d33431482f86f7d56cb6` — `LogTimestamp` now stores `Timing::TimeReliability SystemReliability`.
- `9d7ac007d450b572103b56cb38e91bb93124670b` — `Logger::CaptureTimestamp()` now consumes `ClockSynchronizationStatus::Reliability`.
- `e875c37899515f902b980c2196b667cc058b82e3` — host contract validates final reliability vocabulary.
- `10b5209fd05a9c61c95deda9176f45584d8b6459` — workflow rejects predecessor Timing diagnostics and validates final host/ESP32 surface.

Logging run `34937769272` at head `10b5209fd05a9c61c95deda9176f45584d8b6459`:

- host `104279337186`: **SUCCESS**.
- ESP32 `104279336967`: **SUCCESS**.

Downstream Serial aggregate revalidation exposed and closed two stale consumers rather than weakening provider APIs:

- `0ac974568e1e5e63260072672b56891442400004` — Serial Logging test migrated to `TimeReliability::Synchronized`.
- `a89261887fd13997bba03061db48806933b97ff0` — aggregate Serial CI rejects predecessor Timing diagnostic vocabulary.
- `342b71ddf76a4c233c4748528bec53e7053bce0e` — completed the final `IWiFiObserver`-based WiFi monitor diagnostic facts (client/scan/AP-until-client/selection/IP/MAC) that aggregate behavioral testing exposed as incomplete. No WiFi runtime ownership or predecessor family bridge was reintroduced.

Final Serial head `342b71ddf76a4c233c4748528bec53e7053bce0e` validation:

- Host Tests run `34938272919`, job `104280871049`: **SUCCESS** including configure/build/all aggregate CTest.
- Final Diagnostics Contract run `34938272888`:
  - ownership-boundaries `104280871089`: **SUCCESS**;
  - host-diagnostic-aggregator `104280871093`: **SUCCESS**;
  - esp32-wifi-monitor `104280870895`: **SUCCESS**.
- Command Console Final Contract run `34938273002`: **SUCCESS**.

D10-16 is therefore **CLOSED/GREEN**.

## D10-17 — ESP32 non-Radio downstream cleanup — ACTIVE

Current baseline before D10-17 mutation must be re-queried. Last observed `ESPressio-ESP32/primitives_redesign` head was `53d67b9f9099094bd8818a518567578fede1c941`.

Scope is explicitly **non-Radio** downstream cleanup. Do not reopen or restructure the Radio/R3 architecture under this item. Audit the ESP32 manifest first, then concrete System/Persistence/Timing/WiFi/platform glue, tests, examples and workflows for stale provider contracts or removed Thread/Timing/Event/Command/State APIs. Consume final provider contracts; do not add compatibility façades.

### Immediate next action

1. Re-query the exact ESP32 `primitives_redesign` head and manifest.
2. Inventory non-Radio production/test/workflow paths separately from Radio implementation paths.
3. Search for stale final-provider API references and dependency drift, classifying every hit before mutation.
4. Apply only confirmed non-Radio migration fixes and add anti-regression validation.
5. Validate exact ESP32 head and relevant downstream consumers before closing D10-17.
6. Record closure here and proceed directly to D10-18 Units dependency-neutral proof.
