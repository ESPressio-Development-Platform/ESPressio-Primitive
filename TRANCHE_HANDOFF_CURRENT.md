# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest user time reference: **15:55 Europe/Prague**
Continuation state: **Structural Tranches 2–10 CLOSED/GREEN; Tranche 11 ACTIVE; V11-01 through V11-10 CLOSED/GREEN; V11-11 ACTIVE.**

This is the canonical living continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for architecture, governance, dependency order, locked contracts, tranche gates and historical decisions. Live `primitives_redesign` branch tips are implementation truth and MUST be re-queried before every mutation.

## Authorization boundary

Implementation remains continuously authorized through structural Tranche 11; no permission pause is required between validation items. **Tranche 12/release preparation is NOT authorized.** Do not change versions, finalize release CHANGELOGs, reintegrate to `main`, tag/release, publish Wiki release material, force-push or add backward-compatibility shims.

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
- Dynamic Web/Lua/Serial tooling independently authorizes operations, bounds input before parse/construction and enters final family APIs.
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

All D10-01 through D10-20 are closed. Late closure evidence:

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

## V11-01 through V11-06 — CLOSED/GREEN

Cross-graph validators are live and green for:

- production-source removed-symbol eradication across 26 repositories / 711 production/public source files;
- active examples/demos/live Markdown/API/workflow surfaces;
- exact final dependency DAG: 16 locked repositories / 57 direct ESPressio edges;
- forbidden dependency and redesign-branch guards across 26 repositories / 177 build/package/workflow surfaces;
- semantic classification of the entire current test/workflow corpus across all 26 semantic domains.

Important remediation retained from these gates:

- Radio `29c62486482521a13d0c28378ea380fc1a6871c3`: Radio-owned local monotonic coordinate.
- RadioAdapters `f4cf090a49af1cc6cf5e6236039661f9e90e7710` and `4ebeeafb960b0eb93f55cba41a34f4b02ebe3463`: removed direct System clock/synchronization coupling while preserving exact-M1/4-byte-envelope semantics.
- Threads `7d40e5260bf4e2420c90bb3aef448ac4dd45104b`: locked Observable edge consistently restored.
- Mesh `fdea7a04749f7138485a310ecfdc770298a9d0b2`: predecessor runtime worker contract migrated to final bare `Threads::Thread` + direct work-signal/fixed-thunk architecture.

## V11-07 — CLOSED/GREEN

Restricted public-header compilation and ASAN+UBSAN real capability composition drove the final Mesh/Task migrations:

- Mesh `94b7222e5cedf9a480ba2eccdf3747a3355db394`: final `RadioRuntime` forwarding/terminal correlation/physical-peer lifecycle.
- Mesh `05b644dddf005a6da0cd90203503043c9ecce4af`: liveness on final Radio runtime and six neutral relay service classes.
- Mesh `dd917577635f098f133b266c7e1ded67fc7eac76`: managed Mesh→Radio submission result aligned to `{Status, TransferId}`.
- Mesh `11381a110209e43e3332722468cf2fa857234690`: neighbour discovery moved to `RadioInboundTransferHandle` while retaining physical-peer/semantic-source separation.
- Mesh `f7b7694a530e84466c53ab1accf3c9f40510d5e3`: protected destination delivery uses final `PrimitiveAdmissionDisposition`; only `Accepted`/`AlreadyAccepted` establishes admission.
- Mesh `2ed4fbb6089831a393c5825afc8fc066813f6f96`: integrity repair restored complete M2 implementation after an accidental shortened replacement.
- Mesh `4b6662972ab2dd42a6873690d5e80f37129c7a8a`: final M2 fake/scheduler-result semantics; exact-tip Mesh workflow GREEN.
- Task `6808f84503bb41935e5f11fd3f9dd22985eff8dd` and `c6bd4df69c074c1fcbce7b2d006771aad18c81fc`: C++17-portable optional member-pointer binding while retaining fixed non-owning thunks/no heap/no alternate task mechanism.
- Task run `34976816646`: host contracts + ESP32 PlatformIO GREEN.
- Primitive Platform rerun `34969584258`, job `104407017114`: restricted headers, sanitizer four-capability composition, dynamic tooling and normal Thread composition GREEN.

## V11-08 — CLOSED/GREEN

`tests/platform_wire_malformed_property.cpp` provides deterministic ASAN+UBSAN Event/Command/State malformed/property coverage: all shorter lengths, relevant family/protocol/kind/reliability/version/length corruptions, deterministic byte mutations and bounded valid round-trips for Event, Command request/response and all four State V1 shapes.

- `7be225bc965541c6addca28439089d49213488f6`: restored complete harness after accidental connector-created empty-file commit `537fc1c52f9ce6af8631dc7421e21e8b5fcee047`.
- `46a750f57db72bdf805e3618ffb9ef228d14022b`: attached V11-08 sanitizer gate.
- `243c7bea3917675ab07a2c1d2e14915e090de76b`: corrected one harness over-specification around State wrapper diagnostic-status propagation; production codecs were not changed.
- Platform run `34978625033`, job `104412783040`: V11-08 and all preceding/following platform gates GREEN.

Do not rewrite history solely to remove the harmless intermediate `537fc1c...` commit.

## V11-09 — CLOSED/GREEN

V11-09 executes real behavioral capacity/no-hidden-heap suites rather than a lexical surrogate. Primitive commit `b72d34a972d93c2d1e9fdace477983ba8985877f` added the cross-graph gate covering:

- Event pool/inbox/blocking admission/remote receipt-contention capacities;
- Command runtime/response/critical-execution/no-heap paths;
- Adapters byte arena, capacity, rollback, fit, no-heap/runtime-no-heap, resource and stress contracts;
- Task worker/executor/configuration/rejected contracts;
- Threads composition/common-wake tests, including heap denied after initialization;
- Radio capacity/resource-accounting/reassembly/quarantine-validation/scheduler contracts.

Exact Platform run `34979178551`, job `104414679441`: **SUCCESS**. V11-09, dynamic tooling and final Thread composition all GREEN. Therefore finite refusal/rollback/protected capacity and no hidden canonical hot-path heap escape are re-proven against one live graph.

## V11-10 — CLOSED/GREEN

Primitive commit `45346226b3af35f66453591f61cabfc0b1e460c3` added `tools/run_v11_lifecycle_validation.sh`; `150260e4cffce3b262adf7e9c9c27911b2982e48` attached it to the platform workflow.

The gate exercises:

- Task generation-safe handles, exact Ready-generation cancellation, Ready-drop on Shutdown, Executing join, self-join typing and generation monotonicity across reinitialization;
- Threads lifecycle/common-Wake termination races/composition rollback/quiescence;
- Event runtime freeze, initialization rollback and pause/quiesce teardown;
- Command runtime/response-capability cancellation/quiescence;
- State shutdown admission closure, in-flight mutation/transport drain, session deactivation and retained snapshot readability without changing the System incarnation;
- Adapters shutdown/deferred-retry/binding/runtime generation and quiescence contracts;
- Radio domain/runtime cooperative stop and resource reclamation;
- neutral Socket transport restart generation, stale receipt/completion rejection and quiesced-admission refusal.

Exact Platform run `34979811958`, job `104416871448`: **SUCCESS**. Step-level evidence shows V11-02 through V11-10, final dynamic tooling and real Thread composition all GREEN. Therefore V11-10 is CLOSED/GREEN.

## V11-11 — ACTIVE

Locked target: provider physical completion/readiness/cost/timestamp correctness across the final Radio/provider graph. Validate final Radio provider contract plus actual ESP32/NRF24 physical-provider surfaces. Required semantics include bounded provider ingress/service, explicit readiness/Busy behavior and wake/progress, physical completion ownership, provider cost/airtime model, RX/TX timestamp/evidence semantics, no family knowledge at provider/Radio layer, and no provider-local semantic retry ownership.

Do not infer provider correctness only from Radio core tests: inspect and execute the current provider-specific workflows/tests/examples on the exact live `primitives_redesign` tips. Any failure must be classified as harness/infrastructure versus genuine provider-contract defect before mutation.

## Current live frontier / immediate continuation

Continue without a permission pause:

1. re-query Radio, ESP32 and NRF24 exact `primitives_redesign` tips and manifests before mutation;
2. inspect provider-specific tests/workflows for physical completion/readiness/cost/timestamp coverage;
3. add a V11-11 cross-graph provider validation gate only for missing final evidence, reusing provider-owned tests where possible;
4. remediate genuine provider defects provider-first, then rerun the platform graph;
5. once V11-11 is GREEN, continue immediately through V11-12..V11-20 in authoritative order and keep this handoff current;
6. keep deprecated ESP-NOW-era paths outside the active redesign completion path unless separately re-authorized/rebaselined;
7. **do not begin Tranche 12/release preparation without separate authorization.**
