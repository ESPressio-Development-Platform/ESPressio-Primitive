# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens remain opaque transport facts and never encode/truncate DeviceIdentifier. No family-local retry worker/queue/fragmentation architecture may be introduced.

## Green baseline and newly promoted evidence

Foundation F01–F08 and Tranches 2–7 remain closed. Mesh baseline is `e21a4a7d7f527db59171477e27e12263231a7069` (CI `34742545719` SUCCESS).

Last fully green pre-egress MeshAdapters checkpoint is `fcec9570287cc12455c285f5c074491a3ebf215c`, workflow `34747763059` SUCCESS.

Combined workflow `34749673992` at MeshAdapters `165600415c8fc96000eba1cb0f815c9b2c5d673f` adds material green evidence before its first failure:
- Mesh->A2 ingress build/run GREEN.
- A2->Mesh lower transport build/run GREEN.
- real Event ingress build/run GREEN.
- local Event->A2 outbound build/run GREEN.
- corrected Command fixture preparation GREEN.
- real Command family ingress/idempotency build/run GREEN.
- first failure was only `Build local Command-to-A2 outbound contract`; later State steps were skipped.

Thus Event outbound is now green in the combined suite, and the corrected Command terminal-duplicate behavior is also combined-green.

## Live branch truth — UNDER VALIDATION

- MeshAdapters live tip: `11d5b4ddba22d9a38eaa86e539c85607afe2e273` (`Fix Command outbound contract compile surface`).
- Adapters live tip: `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Its own workflow `34748737223` is still queued; however every executing MeshAdapters workflow is already checking out this exact Adapters tip.
- Repeated earlier MeshAdapters `startup_failure` runs with zero jobs are infrastructure-only and are not code evidence.

Do not call Tranche 8 complete.

## Event outbound — IMPLEMENTED; COMBINED GREEN

Event family binding synchronously encodes borrowed `EventLease` data into A2-owned bytes. `ESPressio_EventMeshAdapterOutboundTarget.hpp` is a normal Event `ExternalAdapter` target using frozen service/policy and a composition-owned opaque route token. `EventTypeRuntime` suppresses ExternalAdapter delivery for remote-origin occurrences, preventing re-egress.

`tests/event_mesh_adapter_outbound_test.cpp` uses the real A2 runtime. Dedicated workflow `34748517373` passed the Event outbound build/run steps, and combined workflow `34749673992` passed them again. Local Event V1 identity/message/service/route are preserved and remote-origin Event does not re-egress.

Predecessor Event-only MeshAdapter transport/submission files are not yet removed; removal remains gated on the remaining replacement-family validation and Tranche-8 cleanup.

## Command ingress/idempotency — COMBINED GREEN

The prior duplicate failure was a test timing assumption. Command commits terminal ledger state before response-slot routing/release necessarily completes. A duplicate in that bounded interval may be `TemporarilyUnavailable`; after release it converges to `AlreadyAccepted` without handler re-execution. Combined run `34749673992` passed the corrected Command fixture build and runtime.

TODO remains: persist those fixture edits directly into `tests/command_mesh_adapter_binding_test.cpp` and remove workflow-time source mutation.

## Command local egress — IMPLEMENTED; UNDER VALIDATION

The two-stage `CommandMeshAdapterFamilyBinding` supports Command startup ordering: configure Type/format/policy/encoder before `Command::Runtime::Initialize`, bind outbound transport/recovered-response reservation during initialize, attach inbound Runtime afterwards, then freeze before start.

Local request leases are synchronously copied to A2 bytes and semantic destinations resolve only via `MeshRouteBinding`. Response-bearing delivery-failure tokens are held only in a bounded fixed correlation table; A2 remains sole pursuit owner. Executor and recovered responses use the same A2 encoder with disjoint correlations.

Combined run `34749673992` isolated three compile-surface defects in the new no-response outbound test: templated assert macro shielding, use of `CommandSubmissionResult` boolean conversion rather than nonexistent `Accepted()`, and `CommandOutboundBinding` requiring a non-const validation-owner member. These are corrected in source at live tip `11d5b4d…`; the test now uses a tiny mutable binding-owner shim that delegates to the family without changing production semantics. The resulting rerun is pending/running.

Response-bearing request-delivery-failure and durable recovered-response coverage remain open.

## A2 mixed-policy correction — IMPLEMENTED; UNDER VALIDATION

Adapters `b8a1722…` preserves the Initialize-time strongest-capability proof while allowing a `NoRemoteEvidence` occurrence to coexist in a family containing Types requiring `DestinationPrimitiveAdmission`. Per-occurrence evidence validation remains fail-closed. `tests/test_adapter_mixed_policy.cpp` proves both sides. The repository workflow remains queued.

## State outbound/convergence — IMPLEMENTED; UNDER VALIDATION

State egress continues to use the real `StateTransportBinding<TState,TFormat>`. MeshAdapters binds a real A2 runtime, `MeshRouteBinding`, and a coalesced service wake. It validates role-specific semantic source identity, resolves the opposite semantic role through `MeshRouteBinding`, synchronously encodes canonical State V1 into A2-owned bytes, and stores no payload/route/retry/deadline state after submission.

Only messages carrying an existing `StateConvergenceHandle` reserve a fixed correlation slot containing only Type entry, generation and immutable handle. A2 owns pursuit. Required evidence frees the slot. Terminal pursuit without required evidence marks bounded `ExhaustionPending`, wakes service context, and `Service()` reports the handle through real `State::Runtime::ReportConvergenceExhausted<TState>()`; State alone owns dormant `NeedsConvergence`, sessions, versions, baselines, resync and rearm.

Focused workflow `34749674043` first exposed a name collision and `-Werror` formatting problems; fixed at `61a715e…`. Focused workflow `34749806892` then isolated one remaining compile mismatch: `State::Runtime::ServiceLatest<TState>()` returns `StateTransportAdmission`, while the type-erased service thunk was declared `bool`. Required fix: make the thunk return `StateTransportAdmission` (or explicitly convert at the thunk) and count only an accepted admission as progress. No State ownership or convergence semantics need changing.

## Immediate continuation

1. Fix the exact State `ServiceLatest` thunk return mismatch and rerun focused State + combined MeshAdapters validation.
2. Promote/fix Command local egress from the `11d5b4d…` rerun result.
3. Persist Command fixture cleanup directly in source and delete the workflow mutation step.
4. Add response-bearing Command failure-correlation and recovered-response contracts.
5. Obtain/resolve Adapters `b8a1722…` native workflow evidence.
6. Remove predecessor Event-only MeshAdapter transport/submission files once replacement coverage is fully green.
7. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency/documentation gates and formally close Tranche 8.
8. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
