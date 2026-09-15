# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest user time reference: **16:46 Europe/Prague**
Continuation state: **Structural Tranches 2–10 CLOSED/GREEN; Tranche 11 ACTIVE; V11-01 through V11-14 CLOSED/GREEN; V11-15 ACTIVE.**

This is the canonical living continuation card. The complete Primitive Platform Redesign Architecture Handoff / Revision 102 remains authoritative for architecture, governance, dependency order, locked contracts, tranche gates and historical decisions. Live branch tips are implementation truth and MUST be re-queried before every mutation.

## Authorization boundary

Implementation remains continuously authorized through structural Tranche 11; no permission pause is required between validation items. **Tranche 12 / release preparation is NOT authorized.** Do not change versions, finalize release CHANGELOGs, reintegrate to `main`, tag/release, publish release Wiki material, force-push, or add backward-compatibility shims.

Deprecated ESP-NOW-era functionality outside the active Mesh-based redesign remains excluded from the active completion path. ESPressio-ESP-Now hosted automation has repeatedly failed before runner execution (`steps=[]` / no usable runner evidence); do not mutate valid provider code merely to turn infrastructure failure green.

## Mandatory continuation protocol

Before changing a repository:

1. re-query the exact target branch tip;
2. inspect manifest/dependency boundaries before implementation source;
3. consume closed provider contracts rather than restoring predecessor APIs;
4. classify tests/examples/demos semantically before migration;
5. keep mutations small/coherent and validate the exact resulting tip;
6. update this handoff after substantive progress.

## Locked non-regression rules

- Primitive TypeDirectory/P3 is immutable discovery/schema/constructibility metadata after freeze; it is not authorization or a semantic registry.
- Dynamic Web/Lua/Serial tooling independently authorizes operations, bounds input before parse/construction and enters final family APIs.
- Commands use final typed descriptor/schema/factory/admission semantics; no Event fabrication or Command registry revival.
- Generic State tooling is read/inspect only; owner-authoritative State remains writable only through the bound owner path.
- Event delivery/admission policy remains Event-owned; tools cannot recreate Event transport/runtime ownership.
- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission. Only `Accepted`/`AlreadyAccepted` establishes destination Primitive admission.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Direct-Radio Primitive envelope remains exactly 4 bytes: 2-byte LE family + 2-byte LE protocol.
- Mesh remains family-neutral. Immediate physical peer and validated semantic `OriginalSource` remain distinct provenance facts.
- No family-local retry worker/queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Threads uses one root task/stack/common Wake. `ThreadWith<TCapabilities...>` is the sole generic non-empty capability host; bare `Thread` is the zero-capability spelling.
- Reusable specialized Thread flavours including `PrecisionThread` remain removed. Precision is a resident capability and owns no private task/scheduler/Wake.
- Timing owns clock discipline and final reliability/evidence vocabulary: `TimeReliability`, not predecessor `ClockSynchronizationState` in cross-domain timestamp records.
- System remains free of Persistence. Persistence depends on System/Serializable/Security.
- Threads does not depend upward on Event/Command/State. Timing does not depend on Threads. Command does not depend on Event. Radio has no Primitive-family knowledge. Mesh has no direct Event/Command/State edge.
- State remote admission cross-checks encoded owner/requester against adapter-validated semantic OriginalSource.
- Unauthenticated Radio service-class claims cannot grant protected capacity; quarantine/trusted promotion remains required.
- No structural-tranche version changes.

# Structural Tranche 10 — CLOSED/GREEN

All D10-01 through D10-20 are closed. Key late evidence:

- Serial final Event tooling examples: `2275bae54b8be8457a2bb032b97a3781423a8ff9`; exact-tip Host/ownership/diagnostics/ESP32 monitor/Command Console checks GREEN.
- Primitive full real Thread composition proof exercises Event reception + Precision + Command response + State observation on one `ThreadWith` / one root task.
- D10-19 close: Primitive `243014060ce19ad783d59bc742110f8af12894a5`; CI `34946740606` SUCCESS; Platform `34946740550` SUCCESS.
- D10-20 close: Primitive `670ad84b37d5cd3cd4d2c4f0ec522b80604495a5`; CI `34947850953` SUCCESS; Platform `34947850970` SUCCESS.

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

## V11-01 through V11-10 — CLOSED/GREEN

Earlier gates remain green. Notable exact evidence:

- V11-07 final Mesh/Task migrations culminated in Platform rerun `34969584258`, job `104407017114` SUCCESS.
- V11-08 deterministic ASAN+UBSAN Event/Command/State malformed/property matrix: Platform run `34978625033`, job `104412783040` SUCCESS.
- V11-09 real capacity/exhaustion/no-hidden-heap matrix: Primitive `b72d34a972d93c2d1e9fdace477983ba8985877f`; Platform run `34979178551`, job `104414679441` SUCCESS.
- V11-10 lifecycle/generation/restart matrix: Primitive `45346226b3af35f66453591f61cabfc0b1e460c3` + workflow attachment `150260e4cffce3b262adf7e9c9c27911b2982e48`; Platform run `34979811958`, job `104416871448` SUCCESS.

## V11-11 — CLOSED/GREEN

Provider physical completion/readiness/cost/timestamp validation is closed on the live Radio/ESP32/NRF24 graph.

- Primitive provider gate tip: `0dceb30b...` / commit message `Execute V11-11 provider contracts` in the progression history.
- Exact Platform run `34981104491`, job `104421331248`: **SUCCESS** through V11-11 plus dynamic tooling and final Thread composition.
- Provider tips used at the audit frontier included Radio `29c62486482521a13d0c28378ea380fc1a6871c3`, ESP32 `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f`, NRF24 `0c62ee73...`; re-query before any provider mutation.

## V11-12 — CLOSED/GREEN

Final Mesh multi-device broadcast/relay/congestion/failover contracts are closed.

- Primitive V11-12 gate commit: `dcf915e8a3fa00b9f7db792c7e9e306d5fbd1963`.
- The first run exposed only a stale three-node test fake returning predecessor `{bool, transferId}` instead of final `{RadioSchedulerStatus, transferId}`.
- Mesh test-only repair: `7f58cd03f9e32c9db0eda2ef5d59b76ff3bc1442`, `Align three-node forwarding fixture with final Radio result`.
- Mesh exact-tip runtime run `34982501502`, job `104426106473`: SUCCESS.
- Primitive Platform rerun `34981810933`, attempt-2 job `104426279651`: **SUCCESS**, including V11-12, dynamic tooling and final Thread composition.
- Production Mesh behavior was not changed by the repair.

## V11-13 — CLOSED/GREEN

Qualified Clock load/uncertainty/reference-switch validation is closed.

- Primitive runner commit `e86120cb5484f27d90e6bd4e89b96b17f79b606a` added `tools/run_v11_clock_validation.sh`.
- The gate uses final Timing qualification/regression/sample evidence, Radio scheduler/clock arbitration under queued load, and final Mesh reference-orchestration/parent-usability/reachability contracts.
- Stale `mesh_system_clock_synchronization_test.cpp` was deliberately excluded because it still instantiates removed predecessor `RadioTransport`; it is not authoritative final evidence.
- V11-13 step is GREEN on the successful Platform retry recorded under V11-14 below.

## V11-14 — CLOSED/GREEN

Command/Persistence crash/reboot/exactly-once-evidence validation is closed.

- Primitive `a6371668cdf2ed8659e95191fdd9e568d6dde333`: `Add V11-14 Command persistence validation runner`.
- Primitive `af72ed65acaada50a5415c58cf2ce5401387ed5f`: `Execute V11-14 Command persistence recovery validation`.
- Initial Platform job `104429611323` exposed only stale Persistence test vocabulary: `Timing::ClockSynchronizationState::Synchronized` in `persistent_log_sink_tests.cpp`.
- Persistence migrated to final `Timing::TimeReliability::Synchronized`: `cf310f2f00673ecc63720b604a7dd4a336ba80f5`, `Migrate persistence logging test reliability vocabulary`.
- Persistence exact-tip run `34984149187`: host tests SUCCESS, Serializable-host tests SUCCESS, ESP32 compile SUCCESS.
- Primitive Platform run `34983510494`, retry job `104432647092`: **SUCCESS** through V11-14 plus dynamic tooling and final real Thread composition.

## V11-15 — ACTIVE

Target: Web/Lua/Serial/WiFi/ESP32/Demos/Labs integration builds on final contracts.

### Public integration evidence already green

- Web tip `585956879ad212dca6a4cf428d3dc16b255f0cdc`; Host Tests run `34946822615`: SUCCESS.
- Lua tip `2fd32036cabfc91e80393cda1ce7b4fb255d792e`; `Lua bindings` run `34950638082`: SUCCESS, including both ESP32 demo variants.
- Serial tip `efbc9063089937832efc7b63774affbeef301b23`; exact-tip Command Console Final Contract run `34947116406`: SUCCESS. Re-query the other exact-tip Serial workflows if additional matrix evidence is needed.
- WiFi tip `937a27f977bd77003f2b9a3fd3896ac61ffafe4e`; architecture-contract run `34947205392`: SUCCESS.
- ESP32 tip `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f`; CI run `34938975315`, attempt 2: SUCCESS.

### ESPressio-Demos classification

Private `ESPressio-Demos` has no `primitives_redesign` branch. Its `structural_realignment` branch `c0607b3cca44a7c54200720be3a5b36ec5abc3bf` contains only `.gitignore` and `LICENSE`, with no operative source/build. Revision 069 historically classified Demos out of scope. Treat V11-15 Demos as **N/A / no operative integration surface**; do not create work merely to manufacture a build.

### Labs redesign integration branch

Private `Labs` historical Mesh branch remains preserved at `structural_realignment_propagation_ESPressio-Mesh` / `f662e645ab62fe893731253055f4f9b456b19ce4`.

A downstream integration branch `Labs/primitives_redesign` was created exactly from that tip so the historical physical-lab checkpoint remains untouched.

Changes already on `Labs/primitives_redesign`:

- `71ba7f455c00433a7150d84b7401bb8170f3be7c` — `Repoint Mesh Lab to primitives redesign graph`: all ESPressio PlatformIO dependencies now target `#primitives_redesign`; removed predecessor `ESPRESSIO_EVENT_TRANSPORT_OUTBOUND_TASK_STACK_SIZE` build flag.
- `017a5baaa7ef3fd690a4ef02996e24a27007f316` — `Validate Mesh Lab on primitives redesign branch`: WROOM-32 Mesh 20-node workflow now triggers on `primitives_redesign` as well as the historical branch.

Hosted Labs automation is unavailable before execution: fresh run `34985286586` has all seven jobs failed with `steps=null` (structure plus six ESP32 compile environments). Historical run `34199845637` shows the same condition. **Do not mutate source merely to fix a runner that never executes.** Record this formally under V11-17.

However, the Lab itself still contains genuine predecessor architecture and therefore V11-15 is not yet closed. Confirmed stale surfaces include:

- `ESPressio_EventListener.hpp`, `ESPressio_EventMeshTransport.hpp`, `ESPressio_EventTransport.hpp`, `ESPressio_RadioTransport.hpp`;
- `Command::CommandRegistry`;
- predecessor Event-specific Mesh inbound/outbound ownership interfaces and `EventTransportPacket`;
- predecessor Event listener/receiver plumbing;
- old `Radio::RadioTransport` composition;
- `scripts/validate_lab.py` still requires historical branch pins and predecessor integration identifiers.

Migrate these on `Labs/primitives_redesign` to final MeshAdapters/Event/Command/State/Radio contracts with no aliases/shims. Use final MeshAdapters headers/tests as canonical examples. If a historical physical-lab feature cannot be safely migrated, explicitly quarantine it and carry it as a V11-20 blocker; do not falsely mark green.

## Remaining sequence after V11-15

Continue without a permission pause:

1. close V11-15 legitimately (public integrations green; Demos N/A; Labs final-static integration migrated, with hosted runner limitation separately classified);
2. V11-16 deterministic memory/resource reports;
3. V11-17 unavailable automation/fallback evidence, including Labs `steps=null` and the pre-existing ESP-NOW hosted-runner condition;
4. V11-18 final live-doc/API/example eradication scan;
5. V11-19 repository-by-repository validation matrix with exact evidence links;
6. V11-20 release-preparation blocker audit; every unresolved stale path must remain explicit/red;
7. **do not begin Tranche 12 / release preparation without separate authorization.**

## Exact current resume anchors

At this handoff update:

- Primitive `primitives_redesign`: `af72ed65acaada50a5415c58cf2ce5401387ed5f` before this handoff-only update; re-query after reading because updating this file advances the branch.
- Persistence `primitives_redesign`: `cf310f2f00673ecc63720b604a7dd4a336ba80f5` last verified.
- Mesh `primitives_redesign`: `7f58cd03f9e32c9db0eda2ef5d59b76ff3bc1442` last verified.
- Labs `primitives_redesign`: `017a5baaa7ef3fd690a4ef02996e24a27007f316` last verified.

Immediate active work: **V11-15 Labs final-architecture migration**. Re-query Labs before every mutation; inspect final MeshAdapters tests/headers and family runtime contracts first; preserve the historical Lab branch; do not claim hosted build success while runner jobs remain `steps=null`.
