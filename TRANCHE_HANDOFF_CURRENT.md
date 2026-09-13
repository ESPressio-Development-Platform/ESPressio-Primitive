# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Green baseline

Foundation F01–F08 and Tranches 2–7 remain closed. Mesh baseline is `e21a4a7d7f527db59171477e27e12263231a7069` (CI `34742545719` SUCCESS).

Last fully green combined MeshAdapters checkpoint remains `fcec9570287cc12455c285f5c074491a3ebf215c`, workflow `34747763059` SUCCESS: Mesh->A2 ingress correlation, A2->Mesh lower transport, real Event ingress, real Command ingress/executor-response routing with Persistence/replay/idempotency, and real State ingress/session/version mutation with role-correct provenance.

Locked ownership remains: A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. Route tokens are opaque transport facts and never encoded DeviceIdentifiers.

## Live branch truth — UNDER VALIDATION

- MeshAdapters: `c035a5e248924c3350dd332aa980faf2d00c13c6` — `Stage State outbound convergence through A2`.
- Adapters: `b8a17228bb3d5e87ae622dbab782a308326bf543` — `Allow mixed outbound evidence policies per family`.
- Adapters workflow `34748737223` remains queued at this update.
- MeshAdapters workflows `34748653783` (`0f010e9…`) and `34749320403` (`1d2a2d4…`) both ended `startup_failure` with **zero jobs**. No build/test step ran. Treat these as GitHub runner/infrastructure failures, not code failures.

Do not call Tranche 8 complete.

## Event outbound — IMPLEMENTED; dedicated evidence GREEN

Event family binding now synchronously encodes borrowed `EventLease` data into A2-owned bytes. `ESPressio_EventMeshAdapterOutboundTarget.hpp` submits as a normal Event `ExternalAdapter` target using frozen service/policy and a composition-owned opaque route token. `EventTypeRuntime` suppresses ExternalAdapter delivery for remote-origin occurrences, preventing re-egress.

`tests/event_mesh_adapter_outbound_test.cpp` uses the real A2 runtime. Workflow `34748517373` proved both new Event outbound compile/runtime steps GREEN: local dispatch reached lower transport with Event V1 identity/message/service/route preserved and remote-origin Event did not re-egress. That workflow failed later in the old Command duplicate timing assertion; subsequent combined reruns never reached runners.

## Command duplicate fixture correction

The old failure was a test timing assumption. Command commits terminal ledger state before the first response slot necessarily finishes routing/release. A duplicate during that interval may validly return `TemporarilyUnavailable`; after release it must converge to `AlreadyAccepted` without handler re-execution.

The workflow fixture at `0f010e9…` models this transient->idempotent transition, narrows the Serializable include and removes the warning suppression. TODO: persist those fixture edits directly into `tests/command_mesh_adapter_binding_test.cpp`, then remove workflow-side mutation.

## Command local egress — IMPLEMENTED; UNDER VALIDATION

MeshAdapters has two-stage Command configuration required by Command startup ordering: configure Type/format/policy/encoder before `Command::Runtime::Initialize`, use the same family as `CommandOutboundBinding` so validation/recovered-response reservation can happen during initialize, attach the real inbound Runtime afterwards, then freeze before start.

Local request leases are synchronously encoded into A2-owned bytes and destinations resolve only through `MeshRouteBinding`. Response-bearing request delivery-failure tokens live only in a bounded fixed correlation table; no request payload or retry state is retained there. A2 remains sole pursuit owner. Terminal A2 feedback publishes Command delivery failure only if required P2 evidence was not established. Executor/recovered responses share the same A2 encoder with disjoint response correlations.

`tests/command_mesh_adapter_outbound_test.cpp` exercises real Command -> MeshAdapter -> real A2 -> lower transport for a local no-response Command and verifies route/service, Command Type/Id, local runtime identity and payload. Run `34749320403` ended startup_failure with zero jobs, so the test has not executed in that run.

Response-bearing delivery-failure/recovered-response coverage is still required. One large test-file creation attempt was blocked by the connector safety layer before reaching GitHub; no mutation occurred.

## A2 mixed-policy correction — IMPLEMENTED; UNDER VALIDATION

Adapters `b8a1722…` preserves the Initialize-time strongest-capability proof while removing the incorrect rule that every occurrence in a family must use the strongest evidence required by any Type in that family. A `NoRemoteEvidence` occurrence can now coexist with a `DestinationPrimitiveAdmission` Type; an actual evidence-requiring occurrence still fails closed if the active transport lacks that capability.

`tests/test_adapter_mixed_policy.cpp` proves both the Initialize rejection without strongest capability and valid mixed per-occurrence submissions when that capability exists.

## State outbound/convergence — STAGED; UNDER VALIDATION

MeshAdapters `c035a5e…` extends `StateMeshAdapterFamilyBinding` while leaving all semantic State ownership in State itself.

The real `StateTransportBinding<TState,TFormat>` remains the State egress seam. MeshAdapters can now bind a real A2 runtime, `MeshRouteBinding`, and a composition-owned `StateMeshAdapterServiceWake`. State `Wake()` only signals/coalesces service work; it never services State inline during canonical mutation.

For outbound `StateOutboundMessage<TState>` the bridge verifies that the role-specific semantic source is the local runtime identity, chooses the opposite role as semantic destination, resolves that DeviceIdentifier through `MeshRouteBinding`, and synchronously encodes canonical State V1 into A2-owned bytes. It retains no payload, route, attempt count, deadline or retry schedule.

Only messages whose existing `GetConvergenceHandle()` represents dormant convergence work reserve a fixed correlation slot. The slot stores only the immutable `StateConvergenceHandle`, Type entry index and nonwrapping generation. A2 owns pursuit. Required evidence releases the slot. Terminal pursuit without required evidence marks `ExhaustionPending` and signals the composition wake. `Service()` reports that handle through the real `State::Runtime::ReportConvergenceExhausted<TState>()`; transient `Busy` remains bounded/pending and is re-signalled. State remains sole owner of `NeedsConvergence`, sessions, versions, baselines, resync and explicit availability rearm.

A real State -> StateTransportBinding -> MeshAdapter -> A2 -> lower-transport host contract is still required before promotion.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into a route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken fail-closed provenance or broadcast restrictions to satisfy tests.

## Immediate continuation

1. Add real State outbound/A2 contract including terminal convergence exhaustion -> dormant State feedback and coalesced service wake.
2. Obtain executable MeshAdapters validation when GitHub allocates runners; fix only exact compile/runtime defects.
3. Inspect/promote or fix Adapters `b8a1722…` when workflow `34748737223` executes.
4. Add response-bearing Command delivery-failure and recovered-response coverage.
5. Persist Command fixture cleanup into source and remove workflow mutation.
6. Remove predecessor Event-only MeshAdapter transport/submission files only after replacement coverage is green.
7. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency/documentation gates and formally close Tranche 8.
8. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
