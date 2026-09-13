# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens remain opaque transport facts and never encode/truncate DeviceIdentifier. No family-local retry worker/queue/fragmentation architecture may be introduced.

## Green baseline and current promoted evidence

Foundation F01–F08 and Tranches 2–7 remain closed. Mesh baseline is `e21a4a7d7f527db59171477e27e12263231a7069` (CI `34742545719` SUCCESS).

Current MeshAdapters promoted tip is `bafadf0da761983a6493ef06469bfd77c9601054` (`Use committed Command fixture directly`). Combined workflow `34750545825` is SUCCESS against committed repository contents, including Mesh->A2 ingress, neutral A2->Mesh lower transport, real Event ingress/outbound, real Command ingress/idempotency, local no-response Command->A2 outbound, and real State ingress/session/version mutation.

Focused State outbound workflow `34750472189` is SUCCESS at MeshAdapters `f13049f67847dae6f22468ea4d236cc38ed64884`. It proves real State Runtime -> StateTransportBinding -> MeshAdapter -> A2 -> lower transport, then terminal pursuit failure -> A2 feedback -> coalesced service wake -> exact State convergence exhaustion -> dormant `NeedsConvergence`.

Adapters live tip remains `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Its native workflow `34748737223` remains queued with no execution result. This exact Adapters tip is the dependency used by successful MeshAdapters combined workflow `34750545825` and focused State workflow `34750472189`, providing integration evidence while native Adapters CI remains unavailable.

Do not call Tranche 8 complete.

## Event outbound — IMPLEMENTED; GREEN

Event family binding synchronously encodes borrowed `EventLease` data into A2-owned bytes. `ESPressio_EventMeshAdapterOutboundTarget.hpp` is a normal Event `ExternalAdapter` target using frozen service/policy and a composition-owned opaque route token. `EventTypeRuntime` suppresses ExternalAdapter delivery for remote-origin occurrences, preventing re-egress. Dedicated workflow `34748517373` passed the Event outbound steps and combined workflow `34750545825` passes them again.

Predecessor Event-only MeshAdapter transport/submission paths remain until replacement-family coverage and cleanup gates are complete.

## Command ingress/idempotency — IMPLEMENTED; GREEN

The terminal duplicate contract is now repository truth in `tests/command_mesh_adapter_binding_test.cpp`: terminal ledger state may precede response-slot release, so a duplicate may transiently return `TemporarilyUnavailable` before converging to `AlreadyAccepted`, never re-running the handler. Rejected broadcast policy resolution uses independent provenance storage. Workflow-time fixture mutation has been removed; combined success `34750545825` validates committed source directly.

## Command local egress — IMPLEMENTED; NO-RESPONSE PATH GREEN

The two-stage `CommandMeshAdapterFamilyBinding` supports Command startup ordering: configure Type/format/policy/encoder before `Command::Runtime::Initialize`, bind outbound transport/recovered-response reservation during initialize, attach the inbound Runtime afterwards, then freeze before start.

Local request leases are synchronously copied into A2-owned bytes and semantic destinations resolve only via `MeshRouteBinding`. Response-bearing request-delivery tokens are held only in a bounded fixed correlation table; no payload, route, deadline, attempt or retry schedule is retained. A2 remains sole pursuit owner. Executor and recovered responses use the same A2 encoder with disjoint correlations.

`tests/command_mesh_adapter_outbound_test.cpp` builds and runs green in combined workflow `34750545825`, proving real no-response Command Runtime -> MeshAdapter -> A2 -> lower transport and preservation of route/service, Command Type/Id, local runtime identity and payload.

Still open: response-bearing request terminal-delivery-failure correlation and recovered-response reservation/routing coverage.

## A2 mixed-policy correction — IMPLEMENTED; INTEGRATION GREEN / NATIVE CI PENDING

Adapters `b8a1722…` preserves the Initialize-time strongest-capability proof while allowing a `NoRemoteEvidence` occurrence to coexist in a family containing Types requiring `DestinationPrimitiveAdmission`. Per-occurrence evidence validation remains fail-closed. `tests/test_adapter_mixed_policy.cpp` covers both strongest-capability rejection and valid mixed per-occurrence submissions.

Native Adapters workflow `34748737223` remains queued, but MeshAdapters combined success `34750545825` and focused State success `34750472189` both compile and execute against this exact Adapters tip.

## State outbound/convergence — IMPLEMENTED; GREEN

State egress uses the real `StateTransportBinding<TState,TFormat>`. MeshAdapters binds A2, `MeshRouteBinding`, and a coalesced service wake. It validates role-specific semantic source identity, resolves the opposite semantic role through `MeshRouteBinding`, synchronously encodes canonical State V1 into A2-owned bytes, and retains no payload/route/retry/deadline state.

Only messages carrying an existing `StateConvergenceHandle` reserve a fixed correlation slot containing Type entry, generation and immutable handle. A2 owns pursuit. Required evidence frees the slot. Terminal pursuit without required evidence marks bounded `ExhaustionPending`, wakes service context, and `Service()` reports the handle through real `State::Runtime::ReportConvergenceExhausted<TState>()`; State alone owns dormant `NeedsConvergence`, sessions, versions, baselines, resync and rearm.

Validation resolved two exact defects: the service thunk now returns the real `StateTransportAdmission`, and State Start validation now requires the MeshAdapter family to be frozen. Transport binding is still initialized pre-freeze, while `State::Runtime::Start()` validates the frozen composition. Focused workflow `34750472189` is fully SUCCESS and combined workflow `34750545825` is also SUCCESS with the expanded State header present.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into a route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken fail-closed provenance or broadcast restrictions to satisfy tests.

## Immediate continuation

1. Add response-bearing Command request terminal-delivery-failure coverage through real Command -> MeshAdapter -> A2 feedback and verify exactly one `RequestDeliveryFailed` completion without a second retry engine.
2. Add recovered-response reservation/routing coverage through the same A2 encoder and bounded response-destination table.
3. Re-check native Adapters workflow `34748737223`; if GitHub still does not allocate a runner, retain the distinction between native-CI pending and integration-green evidence.
4. Remove predecessor Event-only MeshAdapter transport/submission paths only after Event/Command/State replacement coverage is fully green.
5. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency/documentation gates and formal Tranche 8 closure report.
6. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
