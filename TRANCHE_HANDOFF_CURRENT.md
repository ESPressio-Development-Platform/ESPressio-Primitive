# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens remain opaque transport facts and never encode/truncate DeviceIdentifier. No family-local retry worker/queue/fragmentation architecture may be introduced.

## Green baseline and current promoted evidence

Foundation F01–F08 and Tranches 2–7 remain closed. Mesh baseline is `e21a4a7d7f527db59171477e27e12263231a7069` (CI `34742545719` SUCCESS).

Current MeshAdapters promoted tip is `2a38f8154ebfa36339d9adaf613e4ec3007b79a2` (`Run Command recovered-response contract`). All three workflows at this exact tip are SUCCESS:
- combined MeshAdapters redesign contracts `34750812152`;
- focused State outbound A2 contract `34750812155`;
- focused Command recovered-response A2 contract `34750812173`.

Combined coverage at this tip includes Mesh->A2 bounded ingress correlation, neutral A2->Mesh lower transport, real Event ingress/outbound, real Command ingress/idempotency, local no-response Command->A2 outbound, response-bearing Command terminal-delivery-failure completion, and real State ingress/session/version mutation.

Adapters live tip remains `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Native workflow `34748737223` remains without execution evidence, but this exact tip is the dependency used by all current green MeshAdapters workflows.

Do not call Tranche 8 complete.

## Event replacement path — IMPLEMENTED; GREEN

Event family binding synchronously encodes borrowed `EventLease` data into A2-owned bytes. `ESPressio_EventMeshAdapterOutboundTarget.hpp` is a normal Event `ExternalAdapter` target using frozen service/policy and a composition-owned opaque route token. `EventTypeRuntime` suppresses ExternalAdapter delivery for remote-origin occurrences, preventing re-egress. Event ingress and outbound are green in combined workflow `34750812152`.

Predecessor Event-only MeshAdapter transport/submission files are now eligible for removal, but must be inventoried and reference-checked before deletion.

## Command replacement path — IMPLEMENTED; GREEN

Command ingress/idempotency is repository truth: terminal ledger state may precede response-slot release, so an exact duplicate may transiently return `TemporarilyUnavailable` before converging to `AlreadyAccepted`, never re-running the handler. Workflow-time fixture mutation has been removed.

The two-stage `CommandMeshAdapterFamilyBinding` supports Command startup ordering: configure immutable Type/format/policy metadata before `Command::Runtime::Initialize`, bind outbound transport and recovered-response reservation during initialize, attach the initialized inbound Runtime afterwards, then freeze before start.

Local request leases are synchronously copied into A2-owned bytes and semantic destinations resolve only via `MeshRouteBinding`. Response-bearing request delivery tokens live only in a bounded generation-safe correlation table; no payload, route, deadline, attempt or retry schedule is retained. A2 remains sole pursuit owner.

`tests/command_mesh_adapter_delivery_failure_test.cpp` is green in combined workflow `34750812152`: a real `ResponseCapability` issues a response-bearing Command, A2 receives terminal lower-transport rejection without destination admission, and the caller receives exactly one `RequestDeliveryFailed` completion. A second service pass produces no duplicate completion.

`tests/command_mesh_adapter_recovered_response_test.cpp` is green in focused workflow `34750812173`: a durable completed result from a prior executor incarnation reserves its MeshAdapter destination during `Command::Runtime::Initialize`, emits only after start through the same A2 response encoder, preserves the original execution key/prior executor identity/payload, resolves an opaque route, and does not re-run the handler.

Command replacement coverage is therefore complete for the currently defined M8-22 contract.

## A2 mixed-policy correction — IMPLEMENTED; INTEGRATION GREEN / NATIVE CI PENDING

Adapters `b8a1722…` preserves the Initialize-time strongest-capability proof while allowing a `NoRemoteEvidence` occurrence to coexist in a family containing Types requiring `DestinationPrimitiveAdmission`. Per-occurrence evidence validation remains fail-closed. `tests/test_adapter_mixed_policy.cpp` covers both strongest-capability rejection and valid mixed per-occurrence submissions.

Native Adapters workflow remains pending/unexecuted; current MeshAdapters combined/focused successes compile and execute against this exact Adapters tip.

## State replacement path — IMPLEMENTED; GREEN

State egress uses the real `StateTransportBinding<TState,TFormat>`. MeshAdapters binds A2, `MeshRouteBinding`, and a coalesced service wake. It validates role-specific semantic source identity, resolves the opposite semantic role through `MeshRouteBinding`, synchronously encodes canonical State V1 into A2-owned bytes, and retains no payload/route/retry/deadline state.

Only messages carrying an existing `StateConvergenceHandle` reserve a fixed correlation slot containing Type entry, generation and immutable handle. A2 owns pursuit. Terminal pursuit without required evidence becomes bounded `ExhaustionPending`; service context reports exact exhaustion through the real State Runtime and State alone owns dormant `NeedsConvergence`.

Focused workflow `34750812155` and combined workflow `34750812152` are SUCCESS at current tip.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into a route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken fail-closed provenance or broadcast restrictions to satisfy tests.

## Immediate continuation

1. Inventory all Event-only predecessor MeshAdapter transport/submission files and every source/build/doc reference; remove only paths superseded by the green family-neutral + Event binding architecture.
2. Run full combined/focused validation after predecessor cleanup and correct any exact stale-reference failure.
3. Re-check native Adapters workflow `34748737223`; retain native-CI-pending versus integration-green distinction if GitHub still does not allocate a runner.
4. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency/documentation gates and formal Tranche 8 closure report.
5. Update this file after every material checkpoint and before any stop.

After Tranche 8, continue authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
