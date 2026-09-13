# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED design, dependency order, tranche gates and historical evidence. This file records only the current implementation position and immediate continuation state.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this standing authorization.

## Closed/green baseline

Foundation F01–F08 and Tranches 2–7 are closed per the architecture handoff. Current relevant provider baselines remain Mesh `e21a4a7d7f527db59171477e27e12263231a7069` (CI `34742545719` SUCCESS) and Adapters `77e034ec8d3efa4a8c8e6df0ef2f6a405f8dd98a`.

Last fully green MeshAdapters checkpoint is `fcec9570287cc12455c285f5c074491a3ebf215c`, workflow `34747763059` SUCCESS. That checkpoint validates Mesh->A2 ingress correlation, A2->Mesh lower transport, real Event ingress, real Command ingress/executor-response routing with Persistence/replay/idempotency, and real State ingress/session/version mutation with role-correct provenance.

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. `ImmediatePeer.Token` is only an opaque transport route fact.

## Live branch truth — UNDER VALIDATION

MeshAdapters `primitives_redesign` is now `e235563b822876c7827e79a159a03cb0d1d35430` (`Add Event external target backed by A2`). This tip is not yet promoted to green.

### Event outbound work now present

`ESPressio_EventMeshAdapterBinding.hpp` now includes a real A2 outbound encoder for each frozen Event Type/format entry. Encoding is synchronous from a borrowed `EventLease` into Adapter-owned bytes; neither A2 nor MeshAdapters retains the Event object or lease.

`ESPressio_EventMeshAdapterOutboundTarget.hpp` now provides a normal Event `ExternalAdapter` target. It submits through `AdapterRuntime::SubmitOutbound` using the frozen Event service/policy and a composition-owned opaque `AdapterRouteToken`. Route selection is binding topology, not occurrence-local route state. Broadcast validation rejects policies requiring destination Primitive admission.

`EventTypeRuntime` already suppresses `ExternalAdapter` delivery for remote-origin Event occurrences, so this replacement does not recreate the predecessor remote/local redispatch path. A2 remains sole pursuit/retry owner.

This code is still unvalidated. Required next evidence is a local Event dispatch -> external target -> A2 encode/submission contract, including capacity-unavailable/wake behavior. Capacity recovery must use `EventOutboundBinding::NotifyCapacityChanged`; no polling loop is permitted.

## Command state

Inbound Command and executor-response routing remain green. Locally-originated request egress through `CommandOutboundBinding` is still open. It must provide bounded response-bearing delivery-failure correlation and recovered-response routing without adding a second retry engine.

Command fixture cleanup remains open: persist the separate broadcast provenance object in the source, replace the broad Serializable include with the serialization-macros include, then remove the temporary Command-only warning suppression.

## State state

Inbound State remains green. Locally-originated `StateTransportBinding` -> A2 encoding/routing remains open, together with convergence-exhaustion feedback and non-polling service wake composition. State session/version/baseline/resync/convergence state remains family-owned.

## Newly identified A2 issue to resolve

A family binding may contain both `DestinationPrimitiveAdmission` and `NoRemoteEvidence` outbound policies. Initialization must prove destination-admission capability if any bound outbound policy requires it, but `SubmitOutbound` must not reject a valid `NoRemoteEvidence` occurrence merely because another Type in the same family requires stronger evidence. Preserve the Initialize-time proof while making per-occurrence validation policy-specific.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into the 64-bit route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken fail-closed provenance or broadcast restrictions to satisfy tests.

## Immediate continuation

1. Add/run Event local-dispatch -> A2 outbound validation and promote only if green.
2. Resolve the mixed-policy A2 capability issue without weakening Initialize-time evidence proof.
3. Implement locally-originated Command request egress.
4. Implement locally-originated State transport egress and convergence feedback.
5. Remove predecessor Event-only MeshAdapter submission/transport files only after replacement inbound/outbound coverage is green.
6. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency and documentation gates, then formal Tranche-8 closure.
7. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue through authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
