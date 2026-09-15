# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest user time reference: **15:55 Europe/Prague**
Continuation state: **Structural Tranches 2–10 CLOSED/GREEN; Tranche 11 ACTIVE; V11-01 through V11-08 CLOSED/GREEN; V11-09 ACTIVE.**

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

All D10-01 through D10-20 are closed. Late closure evidence includes:

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

Important provider/consumer remediation retained from these gates:

- Radio `29c62486482521a13d0c28378ea380fc1a6871c3`: Radio-owned local monotonic coordinate.
- RadioAdapters `f4cf090a49af1cc6cf5e6236039661f9e90e7710` and `4ebeeafb960b0eb93f55cba41a34f4b02ebe3463`: removed direct System clock/synchronization coupling while preserving final exact-M1/4-byte-envelope semantics.
- Threads `7d40e5260bf4e2420c90bb3aef448ac4dd45104b`: locked Observable edge consistently restored across manifests/docs without version change.
- Mesh `fdea7a04749f7138485a310ecfdc770298a9d0b2`: stale predecessor-era runtime worker contract test migrated to final bare `Threads::Thread` + direct work-signal/fixed-thunk architecture.

## V11-07 — CLOSED/GREEN

V11-07 used restricted independent public-header compilation plus ASAN+UBSAN real capability composition. Compiler-driven remediation advanced Mesh to final Radio/M1 contracts:

- Mesh `94b7222e5cedf9a480ba2eccdf3747a3355db394`: forwarding/terminal correlation/physical-peer lifecycle migrated to final `RadioRuntime`.
- Mesh `05b644dddf005a6da0cd90203503043c9ecce4af`: liveness migrated to final Radio runtime and six neutral relay service classes.
- Mesh `dd917577635f098f133b266c7e1ded67fc7eac76`: managed Mesh→Radio submission regression aligned to `{Status, TransferId}`.
- Mesh `11381a110209e43e3332722468cf2fa857234690`: neighbour discovery migrated from deleted transport view to `RadioInboundTransferHandle` while retaining physical-peer provenance separation.
- Mesh `f7b7694a530e84466c53ab1accf3c9f40510d5e3`: protected destination delivery migrated to final `PrimitiveAdmissionDisposition`; only `Accepted`/`AlreadyAccepted` establishes destination admission.
- Mesh `2ed4fbb6089831a393c5825afc8fc066813f6f96`: integrity repair restored complete M2 inline implementation after an accidental contents replacement shortened the file.
- Mesh `4b6662972ab2dd42a6873690d5e80f37129c7a8a`: M2 regression fake aligned to final scheduler result semantics; exact-tip Mesh workflow GREEN.

V11-07 then exposed a genuine C++17 portability defect in optional member-function bindings in ESPressio-Task. The architecture was preserved: callbacks remain fixed non-owning thunks; no `std::function`, heap state or alternate task mechanism was introduced.

- Task `6808f84503bb41935e5f11fd3f9dd22985eff8dd`: restored complete documented `IdleWorkerTask` header and changed optional member-pointer binding from rejected `if constexpr` comparison to initialization-time `if`.
- Task `c6bd4df69c074c1fcbce7b2d006771aad18c81fc`: same portable correction for `TaskExecutor` discard binding.
- Task exact-tip run `34976816646`: host contracts GREEN and ESP32 PlatformIO build GREEN.
- Primitive platform run `34969584258`, successful rerun job `104407017114`: V11-02..V11-06 GREEN, 19 restricted headers GREEN, ASAN+UBSAN Event+Precision+CommandResponse+StateObserver composition GREEN, dynamic tooling GREEN, normal real Thread composition GREEN.

Therefore V11-07 is CLOSED/GREEN.

## V11-08 — CLOSED/GREEN

A cross-family deterministic malformed/property harness now validates final Event/Command/State wire decoders under ASAN+UBSAN:

- `tests/platform_wire_malformed_property.cpp`
- every shorter input length is exercised for Event, Command request/response, State publication, State common control, State snapshot control and State acceptance control;
- family/protocol/message-kind/reliability/version/declared-length corruptions are rejected according to each public decoder contract;
- deterministic byte mutations are exercised across complete valid seeds;
- bounded valid payload-length/reliability/version combinations round-trip for the property cases;
- the harness owns no codec semantics and only consumes the final family-owned wire APIs from the checked-out live graph.

Primitive sequence:

- `7be225bc965541c6addca28439089d49213488f6`: restored the complete V11-08 harness after an accidental connector-created empty-file commit.
- `46a750f57db72bdf805e3618ffb9ef228d14022b`: attached the ASAN+UBSAN V11-08 gate to `platform-boundaries.yml`.
- first V11-08 run `34978362035` correctly exposed a harness over-specification: State common/snapshot/acceptance wrappers reject unsupported protocol but do not promise preservation of `UnsupportedProtocol` from their internal prefix decoder. This was not a production defect.
- `243c7bea3917675ab07a2c1d2e14915e090de76b`: harness narrowed to the locked property—safe rejection—while retaining exact status assertions where the public family decoder contract exposes them.
- exact-tip Platform Redesign Boundaries run `34978625033`, job `104412783040`: **SUCCESS**. V11-02..V11-07 all GREEN, V11-08 ASAN+UBSAN malformed/property matrix GREEN, final dynamic tooling GREEN and real Thread composition GREEN.

Integrity note: connector commit `537fc1c52f9ce6af8631dc7421e21e8b5fcee047` exists in branch history because a contents-API operation unexpectedly produced an empty-file `noop` commit. It was detected immediately and repaired without force-pushing; the live file at/after `7be225bc...` is the complete intended harness. Do not rewrite history solely to remove this harmless intermediate commit.

Therefore V11-08 is CLOSED/GREEN.

## V11-09 — ACTIVE

Locked target: prove finite resource accounting and exhaustion behavior across the final graph, including Event live-instance/inbox capacity, Command private/protected request/response capacity, Adapter independent byte/record pool exhaustion and atomic rollback, Thread/Task bounded storage, Radio/Q1 protected capacity/starvation isolation, and **no hidden heap fallback or runtime capacity growth** in canonical hot paths.

Do not reduce V11-09 to a lexical search for `new`/`malloc`: repository-local tests must remain the behavioral evidence for independent exhaustion/refusal/rollback/protected-capacity semantics; the cross-graph gate should additionally prove no canonical hidden heap escape and that required evidence suites remain present/executable.

## Current live frontier / immediate continuation

Continue without a permission pause:

1. re-query exact live tips before every mutation;
2. implement V11-09 as cross-graph capacity/no-hidden-heap validation backed by current family/Adapter/Radio/Threads/Task behavioral suites;
3. remediate only real production/resource-contract defects exposed by V11-09; do not add compatibility shims or relax locked capacities;
4. after V11-09 is GREEN, continue immediately through V11-10..V11-20 in authoritative order, updating this handoff after substantive frontier changes;
5. keep ESPressio-ESP-Now and deprecated ESP-NOW-era Labs out of the active redesign completion path unless separately re-authorized/rebaselined;
6. **do not begin Tranche 12/release preparation without separate authorization.**
