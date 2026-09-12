# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-12

This file is the current cross-repository continuation card for the Primitive Platform redesign. It supplements the historical `TRANCHE_HANDOFF.MD`; when they differ on current implementation state, this file is authoritative for the latest published tranche position. The uploaded architecture handoff remains authoritative for locked contracts, ordering, completion gates and prohibited compatibility shortcuts.

## Standing authorization

The user has explicitly authorized implementation through **all remaining tranches** without any further tranche-by-tranche authorization pause. Do not stop to request permission at the historical authorization boundaries in Sections 27–32. Preserve the locked dependency order and do not begin a later tranche until the predecessor completion gate is executable-evidence green. No version changes, tags, releases, force pushes, `main` integration or backward-compatibility shims are authorized unless separately requested.

## Completed tranches

Foundation F01–F08, Tranche 2 Task/Timing/Threads, Tranche 3 Event, Tranche 4 Command and Tranche 5 State are complete.

### State final gate

`ESPressio-State/primitives_redesign` final Tranche-5 head:

`25637a7555e3a03f1d709bd8e37340bc4d545b6e` — `Close State redesign tranche`

GitHub Actions run `34703052958` completed both `host-contracts` and `esp32-typed-surface` successfully. The immediately preceding executable-evidence head `0d5c3d3a9b03ad3e6272bc8f0744e404ca1c53f7` ran 37/37 host CTest cases successfully, including the twelve required V1 examples, three intended compile-failure contracts, exact State V1 wire vectors, persistence/session/provenance/convergence/continuity/resource/tooling tests and no-RTTI coverage. `STATE_TRANCHE_IMPLEMENTATION_REPORT.md` and `STATE_CONTINUATION_CHECKPOINT.md` in ESPressio-State contain the formal closure evidence.

State predecessor Publisher/Manager/Availability/Epoch/ObserverThread/StateCodec architecture has been removed. State direct package/build metadata is Observable-free; Observable appears only in the raw host harness because ESPressio-Timing still declares it as its own transitive dependency. Package version remains unchanged.

Known later-platform gaps remain explicitly open and are not hidden by State success: the current ESP32 provider still lacks the required joinable execution implementation and the ESP32 storage provider does not yet establish the complete P4 hardware-durability contract.

## Current next tranche — Tranche 6 generic ESPressio-Adapters

Before first adapter source write, branch readiness was rechecked:

- `ESPressio-Adapters/primitives_redesign` = `ef64f117258155387f0908707e09618500a8cb93` (untouched bootstrap)
- `ESPressio-RadioAdapters/primitives_redesign` = `8b660acaa4f6c93d363364c596cf2bcbbda9c044` (untouched bootstrap)
- `ESPressio-State/primitives_redesign` = `25637a7555e3a03f1d709bd8e37340bc4d545b6e`

The immediate-pre-write branch prerequisite from Section 27 is therefore satisfied. Do not write redesign work to either repository's `main` branch.

Tranche 6 scope is only the family-neutral A1/A2/Q1 substrate in `ESPressio-Adapters`. Direct dependencies must be exactly System + Primitive + Task. It must not directly depend on Event, Command, State, Mesh, Radio, Threads, Timing, Serializable, Persistence, Observable, Security or any transport/family library.

Implementation order remains A6-01 through A6-24 from Section 27.26: scaffold/dependency boundary; neutral vocabulary; generation-safe lease primitives; A1 byte arena and immutable commit; Q1 complete directional bundles/private/shared/untrusted domains; deterministic protected fit; capacity-generation wake; bounded records/queues; frozen family binding table; transactional runtime initialization; shared T1 worker pools with rotating class/family fairness; trusted inbound M1 boundary; quarantine/promotion; outbound direct encode handoff; bounded P2 campaign state; lower-transport completion seam; evidence/provenance; shutdown; full host/negative/no-heap/no-RTTI/no-exception validation; manifests/resource accounting; README/examples/docs; final tranche integration report.

Do not copy EventMeshTransport or other family-specific code into generic Adapters. Physical ingress performs ownership only; family execution is deferred. DestinationPrimitiveAdmission can be published only from family M1 Accepted/AlreadyAccepted, never from link/transport completion. P2 uses monotonic finite campaign state and no polling timer Task.

## After Tranche 6

Because standing authorization now covers all tranches, after Tranche 6 passes its formal completion gate and implementation report, continue immediately into Tranche 7 Radio/provider work rather than asking permission. Then continue through all later locked tranches in the architecture document in dependency order, always final-gating each predecessor first.

Only pushed commits plus repository handoffs/reports count as recoverable progress. Keep this current handoff synchronized before any interruption or usage-limit exit.
