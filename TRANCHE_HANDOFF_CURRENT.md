# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest user time reference: **13:32 Europe/Prague**
Continuation state: **Structural Tranches 2–10 CLOSED/GREEN; Tranche 11 ACTIVE with V11-01 through V11-06 CLOSED/GREEN; V11-07 is next.**

This is the living continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for architecture, governance, dependency order, locked contracts, tranche gates and historical decisions. Live `primitives_redesign` branch tips are implementation truth and MUST be re-queried before every mutation.

## Authorization boundary

Implementation remains authorized continuously through structural Tranche 11; no permission pause is required between validation items. **Tranche 12/release preparation is NOT authorized.** Do not change versions, finalize release CHANGELOGs, reintegrate to `main`, tag/release, publish Wiki release material, force-push or add backward-compatibility shims.

Deprecated ESP-NOW-era functionality outside the active Mesh-based redesign remains excluded from the active completion path. ESPressio-ESP-Now hosted automation has repeatedly failed before runner execution (`steps=[]`/no usable runner evidence) and must not be mutated merely to turn infrastructure failure green.

## Mandatory continuation protocol

Before changing a repository:

1. re-query its exact `primitives_redesign` tip;
2. inspect manifest/dependency boundaries before implementation source;
3. consume closed provider contracts rather than restoring predecessor APIs;
4. classify tests/examples semantically before migration;
5. keep mutations small/coherent and validate the exact resulting tip;
6. update this handoff after substantive progress.

## Locked non-regression rules

- Primitive TypeDirectory/P3 is immutable discovery/schema/constructibility metadata after freeze; it is not authorization or a semantic registry.
- Dynamic Web/Lua/Serial tooling must independently authorize operations, bound input before parse/construction and enter final family APIs.
- Commands use final typed descriptor/schema/factory/admission semantics; no Event fabrication or Command registry revival.
- Generic State tooling is read/inspect only; owner-authoritative State remains writable only through the bound owner path.
- Event delivery/admission policy remains Event-owned; tools cannot recreate Event transport/runtime ownership.
- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission. Only `Accepted`/`AlreadyAccepted` establishes destination Primitive admission.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Direct-Radio Primitive envelope remains exactly 4 bytes: 2-byte LE family + 2-byte LE protocol.
- Mesh remains family-neutral. Immediate physical peer and validated semantic OriginalSource remain distinct provenance facts.
- No family-local retry worker/queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Threads uses one root task/stack/common Wake. `ThreadWith<TCapabilities...>` is the sole generic non-empty capability host; bare `Thread` is the zero-capability spelling.
- Reusable specialized Thread flavours including `PrecisionThread` remain removed. Precision is a resident capability and owns no private task/scheduler/wake.
- Timing owns clock discipline and final reliability/evidence vocabulary (`TimeReliability`).
- System remains free of Persistence. Persistence depends on System/Serializable/Security.
- Threads does not depend upward on Event/Command/State. Timing does not depend on Threads. Command does not depend on Event. Radio has no Primitive-family knowledge. Mesh has no direct Event/Command/State edge.
- State remote admission cross-checks encoded owner/requester against adapter-validated semantic OriginalSource.
- Unauthenticated Radio service-class claims cannot grant protected capacity; quarantine/trusted promotion remains required.
- No structural-tranche version changes.

# Structural Tranche 10 — CLOSED/GREEN

All D10-01 through D10-20 are closed. Important late closure evidence:

- Serial final Event tooling examples: `2275bae54b8be8457a2bb032b97a3781423a8ff9`; exact-tip Host/ownership/diagnostics/ESP32 monitor/Command Console checks GREEN.
- Primitive full real Thread composition proof: `tests/platform_thread_capability_integration.cpp`, exercising Event reception + Precision + Command response + State observation on one `ThreadWith`/one root task.
- D10-19 Primitive close: `243014060ce19ad783d59bc742110f8af12894a5`; CI `34946740606` SUCCESS; Platform Redesign Boundaries `34946740550` SUCCESS.
- D10-20 final Primitive close tip before Tranche 11: `670ad84b37d5cd3cd4d2c4f0ec522b80604495a5`; CI `34947850953` SUCCESS; Platform Redesign Boundaries `34947850970` SUCCESS.

# Structural Tranche 11 — ACTIVE

Authoritative order:

1. V11-01 exact-tip freeze
2. V11-02 branch-specific removed-symbol/source/include scan
3. V11-03 examples/demos/Labs/wiki/README/generated-CI-fixture scan
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

Post-D10-20 live graph frozen as the Tranche-11 architectural baseline. Later V11 commits are validation/remediation and do not redefine locked architecture.

## V11-02 — CLOSED/GREEN

`tools/validate_v11_source_eradication.py` scans active production/public source across the 26 redesign repositories and rejects predecessor APIs. Current platform attempt confirms V11-02 GREEN across **711 production/public source files**.

## V11-03 — CLOSED/GREEN

`tools/validate_v11_live_surfaces.py` separately checks active examples/demos, live Markdown/API material and workflows. Earlier remediation included coordinated branch guidance, final `Timing::TimeReliability` vocabulary and Lua Serial console removal of obsolete `CommandRegistry` usage. Current platform attempt confirms V11-03 GREEN across **98 example/demo sources, 53 live Markdown/API files and 68 workflows**.

## V11-04 — CLOSED/GREEN

Primitive `a7e2841595f5db7d858213b54dd19b6ede141637` hardened exact-DAG validation so manifest-less adapter repositories are validated from direct public includes rather than invented package metadata.

A live DAG failure correctly exposed residual `RadioAdapters -> System` coupling. It was fixed provider-first without changing family/M1 semantics:

- **Radio** `29c62486482521a13d0c28378ea380fc1a6871c3`
  - added/exported `RadioMonotonicNowNanoseconds()` as the Radio-owned canonical local monotonic coordinate;
  - preserves duration/deadline semantics only; it is not synchronized System Time or timestamp evidence;
  - exact-tip Radio redesign contract run `34964716772`: SUCCESS.
- **RadioAdapters** `f4cf090a49af1cc6cf5e6236039661f9e90e7710`
  - lower transport removed direct System synchronization/clock use; switched local synchronization to `std::mutex` and monotonic time to the Radio-owned boundary.
- **RadioAdapters** `4ebeeafb960b0eb93f55cba41a34f4b02ebe3463`
  - exact-M1 controller removed the final direct `ESPressio_Synchronization.hpp` / `ESPressio_SystemPlatformClock.hpp` coupling in the same way;
  - constructor, M1 correlation, generation, finite capacity, nonblocking hot paths, exact admission evidence and 4-byte envelope are unchanged;
  - all eight exact-tip RadioAdapters workflows completed GREEN.

Current platform evidence: V11-04 passes **16 locked repositories / 57 exact direct ESPressio edges; 14 manifest-backed, 2 public-include-backed**.

## V11-05 — CLOSED/GREEN

Current platform evidence: forbidden dependency/branch validation passes across **26 repositories and 177 build/package/workflow surfaces**.

Threads dependency remediation completed before this pass:

- **Threads** `7d40e5260bf4e2420c90bb3aef448ac4dd45104b`
- locked Observable edge consistently restored in `library.json`, `library.properties`, ESP-IDF CMake, legacy component metadata, README and dependency chart; no version change.

## V11-06 — CLOSED/GREEN

The semantic test classifier exposed one real stale contract:

- `ESPressio-Mesh/tests/mesh_runtime_worker_contract_test.cpp` still asserted the removed `PrecisionThread` hierarchy and obsolete std::function/configuration contracts.

Remediation:

- **Mesh** `fdea7a04749f7138485a310ecfdc770298a9d0b2`
- test now asserts the actual final worker architecture: bare `Threads::Thread` root, direct `IMeshRuntimeWorkSignal`, fixed noexcept owner/thunk service binding, bounded `WorkQuantum`, and explicit monotonic deadline publication.
- no production code/version change.
- all three exact-tip Mesh workflows GREEN, including Mesh clock/runtime redesign.

Final cross-graph evidence for V11-01..06:

- Primitive workflow run `34952785742`, latest successful attempt/job `104369045514`
- locked dependency/migration validation: SUCCESS
- V11-02: SUCCESS
- V11-03: SUCCESS
- V11-04: SUCCESS
- V11-05: SUCCESS
- V11-06: SUCCESS
- final dynamic tooling contracts: SUCCESS
- real four-capability Thread composition: SUCCESS

## Current live frontier / immediate continuation

**V11-07 is next.** Continue without a permission pause:

1. re-query exact live tips before any mutation;
2. implement/collect V11-07 host/public-header/no-RTTI/no-exception/sanitizer evidence without weakening existing contracts;
3. proceed in authoritative order through V11-20, fixing genuine implementation/test/docs defects as exposed;
4. update this handoff after each substantive frontier change;
5. keep ESPressio-ESP-Now and deprecated ESP-NOW-era Labs out of the active redesign completion path unless separately re-authorized/rebaselined;
6. **do not begin Tranche 12/release preparation without separate authorization.**
