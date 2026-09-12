# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-12

This file is the current cross-repository continuation card for the Primitive Platform redesign. It supplements the historical `TRANCHE_HANDOFF.MD`; when they differ on current implementation state, this file is authoritative for the latest published tranche position. The uploaded architecture handoff remains authoritative for locked contracts, ordering, completion gates and prohibited compatibility shortcuts.

## Standing authorization

The user has explicitly authorized implementation through **all remaining tranches** without any further tranche-by-tranche authorization pause. Do not stop to request permission at the historical authorization boundaries in Sections 27–32. Preserve the locked dependency order and do not begin a later tranche until the predecessor completion gate is executable-evidence green. No version changes, tags, releases, force pushes, `main` integration or backward-compatibility shims are authorized unless separately requested.

Only pushed commits plus repository handoffs/reports count as recoverable progress. Keep this current handoff synchronized before any interruption or usage-limit exit.

## Completed tranches

Foundation F01–F08, Tranche 2 Task/Timing/Threads, Tranche 3 Event, Tranche 4 Command, Tranche 5 State and Tranche 6 generic Adapters are complete.

### State final gate

`ESPressio-State/primitives_redesign` final Tranche-5 head:

`25637a7555e3a03f1d709bd8e37340bc4d545b6e` — `Close State redesign tranche`

GitHub Actions run `34703052958` completed both `host-contracts` and `esp32-typed-surface` successfully. The immediately preceding executable-evidence head `0d5c3d3a9b03ad3e6272bc8f0744e404ca1c53f7` ran 37/37 host CTest cases successfully, including the twelve required V1 examples, three intended compile-failure contracts, exact State V1 wire vectors, persistence/session/provenance/convergence/continuity/resource/tooling tests and no-RTTI coverage. `STATE_TRANCHE_IMPLEMENTATION_REPORT.md` and `STATE_CONTINUATION_CHECKPOINT.md` in ESPressio-State contain the formal closure evidence.

State predecessor Publisher/Manager/Availability/Epoch/ObserverThread/StateCodec architecture has been removed. State direct package/build metadata is Observable-free; Observable appears only in the raw host harness because ESPressio-Timing still declares it as its own transitive dependency. Package version remains unchanged.

Known later-platform gaps remain explicitly open and are not hidden by State success: the current ESP32 provider still lacks the required complete joinable-execution implementation for target hardware and the ESP32 storage provider does not yet establish the complete P4 hardware-durability contract. Provider-layer work belongs to later ordered tranches.

### Tranche 6 generic Adapters final gate

`ESPressio-Adapters/primitives_redesign` formal Tranche-6 report head:

`e43076c6c158b9036da4a3424b77043bb5910975` — `Record completed Adapter Tranche 6 implementation`

Its exact executable-evidence parent is:

`d946526de08c9fc17582a39a949f5e30d782db4b` — `Make due-service test respect nonblocking Busy`

GitHub Actions run `34708407225` on the executable-evidence head completed both `host-contracts` and `esp32-surface` successfully. The host matrix passed all 18 checks: A1 byte ownership, Q1 complete-bundle/private/shared/quarantine capacity, rollback and deterministic fit, binding/freeze, runtime queues, finite P2 pursuit, wake-driven deferred retry, contract-matrix validation, randomized capacity stress, exact resource accounting, deterministic shutdown, post-Initialize no-heap execution, hot-path `noexcept` assertions, intended compile-failure of `ByteLease` copy, and the dependency-neutral mock integration example. The ESP32 job compiled the complete A1/Q1/A2 public surface with `-fno-rtti` successfully.

The report-only head `e43076c6c158b9036da4a3424b77043bb5910975` re-ran the same workflow as run `34708547392`; both host and ESP32 jobs succeeded again. `TRANCHE_6_IMPLEMENTATION_REPORT.md` in ESPressio-Adapters maps A6-01 through A6-24 and the Section 27.27 completion gate to source/executable/documentation evidence.

Tranche-6 delivered the locked generic substrate:

- A1 compile-time size-class arenas, smallest-fit contiguous slots, move-only generation-safe `ByteLease`, immutable actual-length commit and no chaining/heap fallback/live growth;
- Q1 independent inbound/outbound planes, six private non-lendable service domains, opportunistic SharedOverflow, inbound-only UntrustedIngress, complete same-domain record+byte admission, additive deterministic protected-capacity fit, monotonic capacity generation and fixed wake;
- A2 one frozen binding per `PrimitiveFamilyId`, transactional Initialize/freeze, runtime-owned bounded queues, shared T1 inbound/outbound workers with rotating service/family fairness, trusted ingress ownership-only callback boundary, bounded quarantine classifier/promotion, direct outbound encode-to-owned-bytes, finite monotonic P2 pursuit, generation-correlated lower-transport completion, exact M1 evidence discipline, distinct immediate peer/original semantic source and deterministic shutdown;
- `ESPressio_AdapterResources.hpp` plus `RESOURCE_ACCOUNTING.md`; canonical host profile measured `sizeof(AdapterRuntime)=274096`, `AdapterWorkRecord=328`, each queue bank `13376`, each worker-pool object `504`, SharedOverflow semantic reserve `30720`, inbound UntrustedIngress reserve `15360`, with worker stacks reported separately;
- full README, public/non-trivial ownership/state-machine comments and `examples/MockAdapterRuntime/mock_adapter_runtime.cpp` syntax-compiled in CI.

Direct Adapters dependencies are exactly System + Primitive + Task. There is no family/transport/Threads/Timing/Observable dependency in the generic repository. Package version remains `0.1.0`; no version, tag, release, force push or `main` integration occurred.

## Current next tranche — Tranche 7 Radio core and physical providers

Standing authorization requires continuing immediately into Tranche 7 after the completed Adapters gate; do **not** stop to request another authorization.

Before the first Tranche-7 source write, re-query and reconcile the current `primitives_redesign` tips for at least:

- `ESPressio-Radio`
- `ESPressio-ESP32`
- `ESPressio-NRF24`
- any additional physical Radio provider repository discovered by the current source/dependency audit

Do not trust the old Section-28 planning SHAs if any repository has advanced. Read every intervening commit/source delta and preserve legitimate current work. No force push or branch rewind.

Tranche 7 remains the locked Section-28 R1/R2/R3/Q1/K1/K2 work package. The source-of-truth implementation order is R7-01 through R7-28 from the uploaded architecture handoff. Key completion boundaries include:

- Radio direct deps exactly System + Task + Timing + Units; no Event/Observable/Threads/family/Mesh/Adapters dependency in Radio core;
- remove predecessor PrecisionThread Radio worker/control-worker and canonical Event/Observable bridge paths rather than hiding them behind compatibility defaults;
- exact six wire service-class codes and exact v3 15-byte fixed fragment prefix plus source address, with manual endian-stable codec and non-increasing remaining residence;
- Q1 independent protected inbound/outbound planes, six private classes, SharedOverflow, inbound UntrustedIngress, atomic first-fragment complete reassembly ownership and outbound complete transfer+byte ownership, no embedded maximum payload buffer per reassembly record and no heap fallback/live resize after Running;
- R2/R3 finite positive provider cost and one scheduler per physical contention domain, weighted rotating/work-conserving DRR, one fragment per visit, bounded EDF promotion debt with repayment, at most one scheduler-owned outstanding physical fragment per domain, concurrent independent domains, retained Busy with wake-driven retry and generation-safe deferred completion;
- `TransmissionCompletion` terminally knowable for managed providers; `PeerAcknowledgement` only where the provider proves it; link ACK/completion never becomes DestinationPrimitiveAdmission;
- direct-neighbour Clock/K1/K2 traffic uses the same Q1/R3 scheduler with no privileged control bypass; Timing owns adaptive evidence/deadline policy; certified clock frames do not fragment; nRF24 certified profile remains <=32 bytes; provider capture uncertainty/quality is explicit and unknown/unbounded evidence cannot certify Synchronized/Holdover;
- complete host/provider/fuzz/no-heap/no-RTTI/no-exception/resource validation, manifests/workflows/dependency guards, provider compile integrations and Radio/CLOCK_SYNCHRONIZATION/source documentation before the tranche gate is claimed.

Provider commits must follow the Radio provider-contract commit so compile failures expose every provider that has not migrated. Do not add compatibility default methods that allow an old drain-until-empty/submission-only provider to appear compliant.

## After Tranche 7

Continue through all later locked tranches in architecture dependency order under the same standing authorization, final-gating every predecessor before the next tranche. Tranche 8 is Mesh/MeshAdapters, followed by Tranche 9 RadioAdapters and non-Mesh transports, then the later dynamic-consumer/platform-wide eradication/release-preparation gates specified by the architecture handoff.
