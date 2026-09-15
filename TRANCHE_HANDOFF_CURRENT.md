# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest user time reference: **11:12 Europe/Prague**
Continuation state: **structural Tranches 2–10 CLOSED; Tranche 11 ACTIVE at V11-03 final rerun**

This is the living continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for architecture, governance, dependency order, locked contracts, tranche gates and historical decisions. Live `primitives_redesign` branch tips are implementation truth and MUST be re-queried before every mutation.

## Authorization boundary

Implementation remains authorized continuously through structural Tranche 11; no permission pause is required between validation items. **Tranche 12/release preparation is NOT authorized.** Do not change versions, finalize release CHANGELOGs, reintegrate to `main`, tag/release, publish Wiki release material, force-push or add backward-compatibility shims.

Per current project scope, deprecated functionality outside the active Mesh-based architecture is excluded from implementation and validation work. In particular, ESPressio-ESP-Now is outside the active redesign validation scope and MUST NOT be used as a completion blocker or mutated as part of Tranche 11.

## Mandatory continuation protocol

Before changing a repository:

1. re-query its exact `primitives_redesign` tip;
2. inspect manifest/dependency boundaries before implementation source;
3. consume closed provider contracts rather than restoring predecessor APIs;
4. classify tests/examples semantically before migration;
5. keep mutations coherent and validate the exact resulting tip;
6. update this handoff after substantive progress.

## Locked non-regression rules

- Primitive TypeDirectory/P3 is immutable discovery/schema/constructibility metadata after freeze; it is not authorization or a semantic registry.
- Dynamic Web/Lua/Serial tooling must independently authorize operations, bound input before parse/construction and enter the final family APIs.
- Commands use final typed descriptor/schema/factory/admission semantics; no Event fabrication or Command registry revival.
- Generic State tooling is read/inspect only; owner-authoritative State remains writable only through the bound owner path.
- Event delivery/admission policy remains Event-owned; tools cannot recreate Event transport/runtime ownership.
- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning. Only `Accepted` / `AlreadyAccepted` establishes destination Primitive admission.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Mesh remains family-neutral. Immediate physical peer and validated semantic original source remain distinct provenance facts.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Threads uses one root Thread task/stack/common Wake. `ThreadWith<TCapabilities...>` is the sole generic non-empty capability composition host; bare `Thread` is the zero-capability spelling.
- Reusable specialized Thread flavours including `PrecisionThread` remain removed. Precision is a resident capability over the root Thread and owns no private task/scheduler/wake.
- Timing owns clock discipline and final reliability/evidence vocabulary.
- Serial remains downstream tooling/diagnostics and cannot force dependencies upstream.
- Units remains dependency-neutral.
- No structural-tranche version changes.

# Structural Tranche 10 — CLOSED/GREEN

All D10-01 through D10-20 are closed.

## D10-01…18

Previously closed provider/family/tooling work remains as recorded in the authoritative architecture handoff and tranche evidence. Important late-Tranche-10 closure tips include:

- ESPressio-ESP32 D10-17 provider cleanup: `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f`, provider and non-Radio provider smoke jobs GREEN.
- ESPressio-Units D10-18 dependency-neutral proof: `738da6833955ddd0d491cbfac8942ec3ed3bc4f0`, host and optional Serializable integration GREEN.

## D10-19 — semantic validation/eradication closure

D10-19 audited the Section 16 validation matrix rather than duplicating already-closed tests. Existing evidence was confirmed for Event lifetime/admission/contention, Command durable/reboot/idempotency paths, State provenance/convergence/races, Threads common-wake/deadline/lifecycle behavior, Radio protected capacity/quarantine/fairness/reassembly, Mesh broadcast Option-B local retry, Timing evidence qualification and bounded/nonblocking ingress.

A genuine missing proof was added: real simultaneous composition of **Event reception + Precision + Command response + State observation on one root `ThreadWith`**.

Primitive integration evidence:

- `tests/platform_thread_capability_integration.cpp`
- one real Event per-Type runtime, State runtime, Command runtime/response router and one `ThreadWith<EventCapability, Precision<4>, ResponseCapability<1>, ObserverCapability<ObservedState>>`
- asserts all four capabilities add exactly one root Thread task and exercises Event, State, Command response and application cadence callbacks.

The platform structural validator was hardened to scan the current public redesign graph, include Observable, and remain comment-aware for removed-symbol eradication.

D10-19 close evidence at Primitive `243014060ce19ad783d59bc742110f8af12894a5`:

- CI run `34946740606`: SUCCESS
- Platform Redesign Boundaries run `34946740550`: SUCCESS, including structural validation and real four-capability composition.

## D10-20 — docs/schema examples/cross-tool integration closure

Canonical active documentation was aligned to the final redesign rather than predecessor branches/APIs:

- **Web** `585956879ad212dca6a4cf428d3dc16b255f0cdc`
  - frozen TypeDirectory discovery;
  - P3 schema/constructibility;
  - typed Command admission;
  - final Event APIs;
  - generic State read-only;
  - discovery is not authorization;
  - bounded dynamic input;
  - Sockets/A2 and Timing evidence boundaries.
- **Lua** `1cac393ec64c38b12903d083e973bebcb8c4f3de`
  - README and `docs/Integration.md` target `primitives_redesign`;
  - final discovery/Command/Event/State adapter ownership and security rules documented;
  - mandatory System dependency unchanged; version unchanged.
- **Serial** `efbc9063089937832efc7b63774affbeef301b23`
  - README matches frozen TypeDirectory + application authorization + bounded P3 construction + final Command/Event APIs + read-only State diagnostics;
  - required System/Logging dependency surface unchanged; version unchanged.
- **WiFi** `937a27f977bd77003f2b9a3fd3896ac61ffafe4e`
  - README documents the actual `ThreadWith<Precision<8>>` worker/common-wake architecture and redesign branches;
  - manifest/version unchanged.
- **ESP32** `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f`
  - live README/provider boundary matched the final architecture; no documentation churn was introduced.

Primitive gained `tools/validate_dynamic_tooling.py`, an exact-graph cross-tool guard over the active Web/Lua/Serial/WiFi surfaces. It verifies frozen TypeDirectory discovery, independent application authorization, schema-bounded Command/Event input and final family dispatch/admission, read-only generic State tooling, final WiFi Thread composition, focused workflows and coordinated branch guidance.

**Final Tranche-10 Primitive tip:** `670ad84b37d5cd3cd4d2c4f0ec522b80604495a5`

Exact close evidence:

- Primitive CI run `34947850953`: **SUCCESS**
- Platform Redesign Boundaries run `34947850970`: **SUCCESS**

Therefore **Structural Tranche 10 is CLOSED/GREEN**.

# Structural Tranche 11 — ACTIVE

Authoritative validation order:

1. V11-01 exact-tip freeze
2. V11-02 branch-specific removed-symbol/source/include scan
3. V11-03 examples/demos/Labs/wiki/README/generated-CI-fixture scan as separate surfaces
4. V11-04 final dependency DAG
5. V11-05 forbidden dependency/branch guards
6. V11-06 semantic classification of every existing test
7. V11-07 host/public-header/no-RTTI/no-exception/sanitizer validation
8. V11-08 codecs/fuzz/malformed/property validation
9. V11-09 capacity/exhaustion/no-hidden-heap validation
10. V11-10 shutdown/restart/generation/stale-handle validation
11. V11-11 provider physical completion/readiness/cost/timestamp validation
12. V11-12 multi-device Mesh broadcast/relay/congestion/failover validation
13. V11-13 qualified Clock load/uncertainty/reference-switch validation
14. V11-14 Command/Persistence crash/reboot/exactly-once-evidence validation
15. V11-15 Web/Lua/Serial/WiFi/ESP32/Demos/Labs integration builds
16. V11-16 deterministic memory/resource reports
17. V11-17 classify unavailable automation/fallback evidence
18. V11-18 final live-doc/API/example eradication scan
19. V11-19 repository-by-repository validation matrix + evidence links
20. V11-20 block release preparation on every unresolved stale path

## V11-01 — CLOSED

The Tranche-11 entry graph was frozen before eradication mutation began. The frozen baseline is the post-D10-20 `primitives_redesign` graph; subsequent V11 commits are validation/remediation commits and do not redefine the architectural baseline. Live tips remain authoritative before every mutation.

## V11-02 — CLOSED/GREEN

Primitive added `tools/validate_v11_source_eradication.py` and wired it into `.github/workflows/platform-boundaries.yml` as a dedicated production/public source pass, separate from V11-03 examples/docs surfaces.

The guard scans `src/` and `include/` across all 26 active redesign repositories, strips C/C++ comments and rejects removed predecessor identifiers including the final Event manager/dispatcher/listener hierarchy, specialized Thread/Precision worker hierarchy, `CommandRegistry`, old State/Timing names and `RadioWorker`.

Exact evidence:

- Platform Redesign Boundaries run `34948846099`
- job `104314675007`
- **SUCCESS** for V11-02
- 26 repositories / 710 production-public source files scanned

No predecessor symbol remained in the active production/public source graph.

## V11-03 — ACTIVE, remediation complete; fresh cross-graph rerun triggered by this handoff commit

Primitive added `tools/validate_v11_live_surfaces.py` and a separate workflow step for examples/demos, live README/docs/wiki/API material and generated CI fixtures. Historical CHANGELOG/tranche/history documents are intentionally excluded. Markdown removal/explanation sections may name predecessor APIs as documentary evidence, but fenced/copyable code remains strict.

The first V11-03 run correctly exposed a finite remediation set rather than being weakened:

- stale coordinated `#main` guidance in Persistence, Security, Units and Observable;
- Logging README using removed `ClockSynchronizationState` vocabulary;
- two executable SerialLuaConsole demo copies using removed `CommandRegistry`;
- State/ESP32 explanatory removed-architecture text, which was classified as documentation evidence and the validator made section-aware rather than deleting useful statements.

Remediation completed:

- **Security** README branch guidance: `9a09983db033df9c4ab7d3af41c7b1725f062a6a`
- **Observable** README branch guidance: `476fd1dd133d11949ee07ffd16b194451d891d5a`
- **Units** README optional Serializable/core branch guidance: `987b500309b3345368a713d467d789f627590b7a`
- **Logging** README final `Timing::TimeReliability` vocabulary: `b1f75fb790e5e96969eb04172d2aab448f32132e`
- **Persistence** README coordinated branches and locked `{System, Serializable, Security}` dependency description: `2f132b048d29bb220ed8447b2116abf44b4f9c5a`
- **Lua** SerialLuaConsole removed the obsolete mutable Command registry from both Arduino and PlatformIO source variants. `lua run` is now explicitly a bounded application-owned local operator grammar, not a Command primitive; PlatformIO dependencies reduce to the actual Lua/System requirements; paired-source validation covers the console files; CI compiles both NativeBindings and SerialLuaConsole on ESP32. Exact Lua tip: `2fd32036cabfc91e80393cda1ce7b4fb255d792e`; Lua bindings run `34950638082`: **SUCCESS**.
- **Primitive** Markdown removal-section classification: `358a4a873c1f7deeb7d4e83712ab9d884603c11e` before this handoff update.

Downstream non-authoritative repository classification:

- **Demos** currently contains scaffolding only; no active demo/API surface exists to migrate.
- **Labs Base/FullStack-Lab** is an ESP-NOW-era deprecated fixture and is outside the active Mesh redesign scope.
- **Labs Mesh lab** still references pre-redesign `structural_realignment*` branches. Because Labs has no authorized `primitives_redesign` baseline, this is recorded as a downstream validation finding, not silently mutated. It must not be used as V11-15 build evidence until an authorized redesign validation baseline exists.

The present handoff commit intentionally triggers a fresh `Platform Redesign Boundaries` run over the current 26-repository redesign graph. Inspect that run next; if V11-03 is green, close V11-03 and proceed immediately to V11-04.

## Immediate continuation

1. Inspect the Platform Redesign Boundaries run triggered by this handoff commit.
2. If V11-03 exposes any remaining live-surface defect, classify and repair the genuine defect without weakening the architecture/guard.
3. Close V11-03 when the current graph is green.
4. Continue V11-04 through V11-20 without a permission pause.
5. Keep ESPressio-ESP-Now and deprecated ESP-NOW-era Labs functionality out of the active redesign completion path.
6. Do **not** begin Tranche 12/release preparation without separate authorization.
