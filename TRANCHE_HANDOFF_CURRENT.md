# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED design, dependency order, tranche gates and historical evidence. This file records the current implementation position and immediate continuation state.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this standing authorization.

## Last fully green baseline

Foundation F01–F08 and Tranches 2–7 are closed per the architecture handoff. Mesh remains `e21a4a7d7f527db59171477e27e12263231a7069` (CI `34742545719` SUCCESS).

Last fully green combined MeshAdapters checkpoint remains `fcec9570287cc12455c285f5c074491a3ebf215c`, workflow `34747763059` SUCCESS. It validates Mesh->A2 ingress correlation, A2->Mesh lower transport, real Event ingress, real Command ingress/executor-response routing with Persistence/replay/idempotency, and real State ingress/session/version mutation with role-correct provenance.

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. `ImmediatePeer.Token` is only an opaque transport route fact.

## Live branch truth — UNDER VALIDATION

- MeshAdapters `primitives_redesign`: `0f010e967c8db30f3f8975ae5d824b206a815137` (`Stabilize Command duplicate contract fixture`). Combined workflow `34748653783` is queued at this update.
- Adapters `primitives_redesign`: `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). This tip is under validation.

Do not call Tranche 8 complete.

## Event outbound — IMPLEMENTED; dedicated steps GREEN

`ESPressio_EventMeshAdapterBinding.hpp` now has a real A2 outbound encoder for every frozen Event Type/format entry. Encoding is synchronous from a borrowed `EventLease` into Adapter-owned bytes; neither A2 nor MeshAdapters retains the Event object or lease.

`ESPressio_EventMeshAdapterOutboundTarget.hpp` provides a normal Event `ExternalAdapter` target which submits through `AdapterRuntime::SubmitOutbound` using the frozen Event service/policy and one composition-owned opaque `AdapterRouteToken`. Route selection is binding topology, not occurrence-local state. Generic broadcast rejects policies requiring destination Primitive admission. `EventTypeRuntime` itself suppresses `ExternalAdapter` delivery for remote-origin Event occurrences, so the replacement does not recreate source-local/remote redispatch.

`tests/event_mesh_adapter_outbound_test.cpp` uses the real A2 runtime. Workflow `34748517373` proved both new Event outbound compile/runtime steps GREEN: local Event dispatch reached A2/lower transport as correctly encoded Event V1 bytes with local runtime identity, conceptual message identity, service and opaque route preserved; remote-origin Event admission did not re-egress through the external target. That workflow failed later in the existing Command duplicate test, so the combined branch still awaits a fully green rerun.

## Command combined-test correction — UNDER VALIDATION

The Command failure in `34748517373` was a test timing assumption, not a production regression. Command commits its terminal durable ledger before the first response slot necessarily finishes routing/release. An exact terminal duplicate arriving during that bounded slot-retention interval may correctly return `TemporarilyUnavailable`; once the slot releases, the same duplicate must converge to `AlreadyAccepted` and may replay the response without rerunning the handler.

MeshAdapters workflow at `0f010e9…` now patches the fixture to assert that transient->idempotent transition. It also narrows the Serializable include and removes the temporary `-Wno-error=misleading-indentation` compile suppression. These fixture changes still need to be committed directly into `tests/command_mesh_adapter_binding_test.cpp`, after which the workflow-side patch step must be removed.

Locally-originated Command request egress through `CommandOutboundBinding` remains open.

## A2 mixed-policy correction — IMPLEMENTED; UNDER VALIDATION

Adapters live tip `b8a1722…` fixes a family-neutral bug in `AdapterRuntime::SubmitOutbound`.

A frozen family binding may contain both Types whose P2 policy requires `DestinationPrimitiveAdmission` and Types using `NoRemoteEvidence`. The binding-level `RequiresDestinationAdmissionEvidence` flag means the configured lower transport must be capable of producing the strongest evidence needed by any bound occurrence; it must not mean every occurrence in the family requires that evidence.

The fix preserves the Initialize-time fail-closed proof (`RequiresDestinationAdmissionEvidence` without a destination-admission-capable transport -> `EvidenceUnavailable`) but removes the incorrect per-submission rejection of a `NoRemoteEvidence` occurrence merely because another Type in the family requires stronger evidence. Per-occurrence submission still rejects an evidence-requiring policy if the active transport cannot provide it.

New regression `tests/test_adapter_mixed_policy.cpp` proves both sides: Initialize fails without the strongest advertised capability; with that capability present, both `NoRemoteEvidence` and destination-evidence submissions from the same family are accepted. `tests/CMakeLists.txt` includes the new contract.

## State

Inbound State remains green. Locally-originated `StateTransportBinding` -> A2 encoding/routing remains open, together with convergence-exhaustion feedback and non-polling service wake composition. State session/version/baseline/resync/convergence state remains family-owned.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into the 64-bit route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken fail-closed provenance or broadcast restrictions to satisfy tests.

## Immediate continuation

1. Validate Adapters `b8a1722…`; if green, promote exact run/commit here.
2. Inspect MeshAdapters workflow `34748653783`; if green, promote `0f010e9…` and Event outbound combined state here. If not, fix only the exact failing contract.
3. Persist Command fixture cleanup directly into source and remove the workflow mutation step.
4. Implement locally-originated Command request egress through `CommandOutboundBinding`.
5. Implement locally-originated State transport egress and convergence feedback.
6. Remove predecessor Event-only MeshAdapter submission/transport files only after replacement inbound/outbound coverage is green.
7. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency/documentation gates, then formal Tranche-8 closure.
8. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue through authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
