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

- MeshAdapters `primitives_redesign`: `1d2a2d417020efc97e18759f808bbf2e42f699f6` (`Wire Command outbound contract into CI`). This includes Event outbound plus the new Command local-egress implementation and host contract. It is not yet promoted.
- Adapters `primitives_redesign`: `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Workflow `34748737223` remains queued at this update.
- MeshAdapters workflow `34748653783` for predecessor tip `0f010e9…` ended `startup_failure` with zero jobs. No build or test step ran, so this is infrastructure-only evidence and not a code/test failure.

Do not call Tranche 8 complete.

## Event outbound — IMPLEMENTED; dedicated steps GREEN

`ESPressio_EventMeshAdapterBinding.hpp` has a real A2 outbound encoder for every frozen Event Type/format entry. Encoding is synchronous from a borrowed `EventLease` into Adapter-owned bytes; neither A2 nor MeshAdapters retains the Event object or lease.

`ESPressio_EventMeshAdapterOutboundTarget.hpp` provides a normal Event `ExternalAdapter` target which submits through `AdapterRuntime::SubmitOutbound` using the frozen Event service/policy and one composition-owned opaque `AdapterRouteToken`. Route selection is binding topology, not occurrence-local state. Generic broadcast rejects policies requiring destination Primitive admission. `EventTypeRuntime` suppresses `ExternalAdapter` delivery for remote-origin Event occurrences, so the replacement does not recreate source-local/remote redispatch.

`tests/event_mesh_adapter_outbound_test.cpp` uses the real A2 runtime. Workflow `34748517373` proved both new Event outbound compile/runtime steps GREEN: local Event dispatch reached A2/lower transport as correctly encoded Event V1 bytes with local runtime identity, conceptual message identity, service and opaque route preserved; remote-origin Event admission did not re-egress through the external target. That workflow failed later in the existing Command duplicate fixture; its replacement combined rerun never reached a runner (`startup_failure`, zero jobs).

## Command combined-test correction

The Command failure in `34748517373` was a test timing assumption, not a production regression. Command commits its terminal durable ledger before the first response slot necessarily finishes routing/release. An exact terminal duplicate arriving during that bounded slot-retention interval may correctly return `TemporarilyUnavailable`; once the slot releases, the same duplicate must converge to `AlreadyAccepted` and may replay the response without rerunning the handler.

Workflow tip `0f010e9…` updates the CI fixture to assert that transient->idempotent transition, narrows the Serializable include and removes the temporary `-Wno-error=misleading-indentation` suppression. Those fixture edits still need to be persisted directly into `tests/command_mesh_adapter_binding_test.cpp`, after which the workflow-side mutation step must be deleted.

## Command local egress — IMPLEMENTED; UNDER VALIDATION

MeshAdapters now contains a two-stage `CommandMeshAdapterFamilyBinding` configuration required by Command lifecycle ordering:

1. `ConfigureType<TCommand,TFormat>()` freezes Type/format/policy/wire encoder metadata before `Command::Runtime::Initialize`.
2. The same family object initializes `CommandOutboundBinding`, allowing Command to validate the outbound contract and reserve durable recovered-response destinations during startup.
3. After Command initialization, `AttachRuntime<TCommand,TFormat>()` attaches the real inbound runtime binding.
4. `Freeze()` publishes the A2 family descriptor before either runtime starts.

The binding synchronously encodes locally-originated request leases into A2-owned bytes, resolves destinations only through `MeshRouteBinding`, and never retains a Command request object after `SubmitOutbound` returns. Response-bearing request delivery-failure tokens are retained only in a bounded fixed campaign table keyed by opaque A2 correlation; A2 remains the sole retry/pursuit owner. Terminal feedback publishes Command delivery failure only when the required P2 evidence was not established. Executor responses and durable recovered responses continue through the same A2 outbound encoder; response correlations are disjoint from request-campaign correlations.

`tests/command_mesh_adapter_outbound_test.cpp` exercises the real Command runtime -> MeshAdapter -> real A2 runtime -> lower transport path for a locally-originated no-response Command. It verifies route/service, Command Type/CommandId/local runtime identity, and serialized payload. MeshAdapters `1d2a2d4…` wires this contract into CI. Required next evidence is its compile/runtime result, followed by a response-bearing request failure-correlation/recovered-response contract.

## A2 mixed-policy correction — IMPLEMENTED; UNDER VALIDATION

Adapters `b8a1722…` fixes a family-neutral bug in `AdapterRuntime::SubmitOutbound`.

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

1. Inspect the CI run for MeshAdapters `1d2a2d4…`; fix only exact compile/runtime defects and promote Event/Command outbound evidence when green.
2. Inspect Adapters workflow `34748737223`; promote `b8a1722…` if green or fix only the exact failing contract.
3. Add response-bearing Command local-egress coverage for bounded request-delivery failure correlation and durable recovered-response routing.
4. Persist Command fixture cleanup directly into source and remove the workflow mutation step.
5. Implement locally-originated State transport egress and convergence feedback.
6. Remove predecessor Event-only MeshAdapter submission/transport files only after replacement inbound/outbound coverage is green.
7. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency/documentation gates, then formal Tranche-8 closure.
8. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue through authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
