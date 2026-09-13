# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens remain opaque transport facts and never encode/truncate DeviceIdentifier. No family-local retry worker/queue/fragmentation architecture may be introduced.

## Green baseline and current promoted evidence

Foundation F01–F08 and Tranches 2–7 remain closed.

Historical Mesh checkpoint `e21a4a7d7f527db59171477e27e12263231a7069` (workflow `34742545719` SUCCESS) is no longer the live Mesh tip. Source-first reconciliation on 2026-09-13 found `ESPressio-Mesh/primitives_redesign` advanced to live tip `6cd69a02cab7297ce96b77278d56aecc663fc516` (`Fix three-node forwarding contract fixture`). The intervening M8-23 hardening includes deterministic Mesh V1 codec fuzzing, a three-node forwarding fixture, source-broadcast no-feedback coverage, and a consolidated Tranche-8 closure workflow.

At exact Mesh tip `6cd69a02…`:
- `Mesh redesign contracts` workflow `34751515869` is SUCCESS.
- `Tranche 8 Mesh closure` workflow `34751515696` reaches and passes dependency guards, predecessor-worker guard, exact M1 receiver admission, relay-resource ownership, relay-capacity profile, remaining-residence lifetime, broadcast DeferredLocal, family broadcast policy, source no-feedback, logical-transfer Radio handoff, security, and deterministic codec fuzz; its first failing gate is the new three-node forward-once runtime assertion at C (`atC.Disposition == Completed`). Clock/runtime/memory closure steps are skipped only because of that preceding failure.
- `Mesh clock and runtime redesign` workflow `34751515667` compiles/runs clock-reference ownership and the generic Thread Mesh worker successfully, then fails only because its older grep guard matches forbidden predecessor words present in comments. The consolidated closure workflow already strips comments before applying the same prohibition, so this is a workflow false positive rather than a runtime-worker regression.

Current MeshAdapters promoted tip remains `fbef3eedb8d4396461e7d02e8073eccea982d99a` (`Retire predecessor Event-only MeshAdapter architecture`). All workflows at that exact cleanup tip are SUCCESS:
- combined MeshAdapters redesign contracts `34750952418`;
- focused State outbound A2 contract `34750952358`;
- focused Command recovered-response A2 contract `34750952335`.

The exact MeshAdapters cleanup tip therefore re-proves the neutral Mesh/A2 boundaries, Event ingress/outbound, Command ingress/idempotency/no-response egress/response-bearing delivery failure, State ingress/outbound convergence, durable Command recovered-response routing, and predecessor Event-only architecture removal.

Adapters live tip remains `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Native workflow `34748737223` remains queued without job allocation. This is native-CI pending, not a failure; the exact Adapters tip is compiled and exercised by all current green MeshAdapters workflows.

Do not call Tranche 8 complete until the remaining M8-23 failures are resolved, M8-24 integration/documentation is complete, and the formal closure gate is green.

## Event replacement path — IMPLEMENTED; GREEN; PREDECESSOR RETIRED

The canonical Event path is now `ESPressio_EventMeshAdapterBinding.hpp` plus `ESPressio_EventMeshAdapterOutboundTarget.hpp` over neutral A2/Mesh integration. Event remains owner of Event semantics and remote-to-local dispatch; local outbound Event data is synchronously copied into A2 ownership and remote-origin Event occurrences do not re-egress.

The predecessor Event-only architecture has been removed with no compatibility shim, as required by the clean 1.0.0 reset:
- `ESPressio_EventMeshTransport.hpp`;
- `ESPressio_EventMeshNodeSubmission.hpp`;
- `ESPressio_EventMeshSelectiveSubmission.hpp`;
- `ESPressio_EventMeshBroadcastSubmission.hpp`;
- their predecessor-specific tests.

`ESPressio_MeshAdapters.hpp` exports only the neutral ingress/lower-transport/route surfaces and current Event/Command/State family bindings. README is aligned to the locked family-neutral ownership model.

## Command replacement path — IMPLEMENTED; GREEN

Command ingress/idempotency is repository truth. Exact terminal duplicates may transiently return `TemporarilyUnavailable` while a response slot is still releasing, but converge to `AlreadyAccepted` without handler re-execution.

The two-stage `CommandMeshAdapterFamilyBinding` supports Command startup ordering: configure immutable Type/format/policy metadata before `Command::Runtime::Initialize`, bind outbound transport and recovered-response reservation during initialize, attach the initialized inbound Runtime afterwards, then freeze before start.

Local request leases are synchronously copied into A2-owned bytes. Response-bearing request delivery tokens live only in a bounded generation-safe correlation table; A2 owns pursuit. Terminal A2 failure without required destination admission publishes exactly one existing Command delivery failure. Durable recovered responses reserve a bounded MeshAdapter destination during Command initialization and use the same A2 response encoder after start.

Green evidence includes:
- no-response local Command->A2 path in combined workflow `34750952418`;
- real `ResponseCapability` terminal failure -> exactly one `RequestDeliveryFailed` callback in combined workflow `34750952418`;
- recovered durable response preserving original execution key, prior executor identity, payload and opaque route in focused workflow `34750952335`.

M8-22 Command replacement coverage is complete.

## State replacement path — IMPLEMENTED; GREEN

State egress uses the real `StateTransportBinding<TState,TFormat>`. MeshAdapters validates semantic source, resolves the opposite semantic role through `MeshRouteBinding`, synchronously encodes State V1 into A2-owned bytes and retains no payload/route/retry/deadline state.

Only an existing immutable `StateConvergenceHandle` is correlated for terminal A2 feedback. Terminal pursuit failure becomes bounded `ExhaustionPending`; service context reports exact exhaustion to State, which alone owns dormant `NeedsConvergence`, sessions, versions, baselines, resync and rearm.

Focused workflow `34750952358` and combined workflow `34750952418` are SUCCESS after predecessor cleanup.

## A2 mixed-policy correction — IMPLEMENTED; INTEGRATION GREEN / NATIVE CI PENDING

Adapters `b8a1722…` retains Initialize-time strongest-capability proof while allowing `NoRemoteEvidence` occurrences to coexist with Types requiring `DestinationPrimitiveAdmission`. Per-occurrence evidence checks remain fail-closed. Native workflow `34748737223` remains queued, while current MeshAdapters workflows provide integration evidence against the exact tip.

## M8-23 closure audit — ACTIVE

The consolidated Mesh closure workflow now maps the locked completion gate directly to executable evidence. At `6cd69a02…`, all of these are already GREEN before the first failing multi-node step:
- dependency boundary: Mesh core has no Event/Command/State/Observable dependency leakage and remains version `1.0.0`;
- predecessor worker mechanisms rejected after comments are stripped;
- exact seven-disposition M1 receiver path and evidence semantics;
- relay record + byte + workspace ownership;
- minimum relay-capacity profile admission;
- finite/non-increasing remaining-residence lifetime;
- forward-once/DeferredLocal broadcast lifecycle and bounded local retry;
- generic broadcast policy restrictions;
- source broadcast no-feedback path;
- Mesh-to-managed-Radio logical transfer boundary;
- Mesh V1 security/replay/authentication contract;
- deterministic codec fuzz contract.

Current first M8-23 failure is `tests/mesh_v1_three_node_forwarding_test.cpp` at node C. The fixture currently authenticates direct sender B at C but must also satisfy the locked authenticated original-source requirement for source A before C can accept the forwarded origin. The next implementation action is to verify the exact `UnknownAuthenticatedSource` check and correct the fixture topology if that diagnosis is confirmed; do not weaken source verification.

Separately, `.github/workflows/mesh-runtime-redesign.yml` still uses a raw grep over `ESPressio_MeshRuntimeWorker.hpp`, so predecessor terms in explanatory comments cause a false failure. The fix is to make this older guard comment-insensitive in the same manner as `tranche8-closure.yml`, while preserving the exact forbidden code patterns.

## M8-24 status — NOT YET CLOSED

M8-24 still requires the final manifests/workflows/README/source-comment/resource-accounting audit and tranche integration validation after M8-23 is fully green. The formal Tranche-8 implementation/closure report has not yet been issued.

The closure audit must still end with explicit evidence for:
- three-node forward-once plus DeferredLocal without re-fan;
- clock topology/reference ownership and conservative failover;
- generic Thread worker/no polling predecessor path;
- deterministic Mesh resource accounting;
- full tranche workflow integration after all fixes;
- no version change.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into a route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken authenticated-source, provenance, replay, or broadcast restrictions to satisfy tests.
- Radio/R3 remains sole physical fragmentation/arbitration owner.
- Timing remains sole estimator/discipline/uncertainty owner; Mesh owns only reference/topology orchestration.

## Immediate continuation

1. Verify the three-node C failure against `MeshV1BroadcastCoordinator` authenticated-original-source validation; fix the fixture if it lacks source-A authenticated membership, without inventing an A-C direct link/session.
2. Make the legacy `mesh-runtime-redesign.yml` predecessor-worker guard comment-insensitive while preserving its fail-closed code prohibition.
3. Rerun exact Mesh workflows and promote only genuinely green evidence into this handoff.
4. Complete remaining M8-24 manifest/workflow/README/source-comment/resource-accounting classification and integration validation.
5. Re-check Adapters native workflow `34748737223`; retain native-CI-pending versus integration-green distinction if no runner is allocated.
6. Produce the formal Tranche-8 implementation/closure report and update this living handoff before moving to Tranche 9.

After Tranche 8, continue authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
