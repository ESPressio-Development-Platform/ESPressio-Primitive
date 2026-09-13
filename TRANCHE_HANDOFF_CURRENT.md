# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical pursuit/retry; Mesh owns routing/forwarding/application lifecycle; Radio R3 owns physical fragmentation/arbitration. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens remain opaque transport facts and never encode/truncate DeviceIdentifier. No family-local retry worker/queue/fragmentation architecture may be introduced.

## Green baseline and current promoted evidence

Foundation F01–F08 and Tranches 2–7 remain closed. Mesh baseline remains `e21a4a7d7f527db59171477e27e12263231a7069` (workflow `34742545719` SUCCESS).

Current MeshAdapters promoted tip is `fbef3eedb8d4396461e7d02e8073eccea982d99a` (`Retire predecessor Event-only MeshAdapter architecture`). All workflows at this exact cleanup tip are SUCCESS:
- combined MeshAdapters redesign contracts `34750952418`;
- focused State outbound A2 contract `34750952358`;
- focused Command recovered-response A2 contract `34750952335`.

The exact cleanup tip therefore re-proves the neutral Mesh/A2 boundaries, Event ingress/outbound, Command ingress/idempotency/no-response egress/response-bearing delivery failure, State ingress/outbound convergence, and durable Command recovered-response routing after predecessor removal.

Adapters live tip remains `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Native workflow `34748737223` remains queued without job allocation. This is native-CI pending, not a failure; the exact Adapters tip is compiled and exercised by all current green MeshAdapters workflows.

Do not call Tranche 8 complete until M8-23/M8-24 and the formal closure gate are complete.

## Event replacement path — IMPLEMENTED; GREEN; PREDECESSOR RETIRED

The canonical Event path is now `ESPressio_EventMeshAdapterBinding.hpp` plus `ESPressio_EventMeshAdapterOutboundTarget.hpp` over neutral A2/Mesh integration. Event remains owner of Event semantics and remote-to-local dispatch; local outbound Event data is synchronously copied into A2 ownership and remote-origin Event occurrences do not re-egress.

The predecessor Event-only architecture has been removed with no compatibility shim, as required by the clean 1.0.0 reset:
- `ESPressio_EventMeshTransport.hpp`;
- `ESPressio_EventMeshNodeSubmission.hpp`;
- `ESPressio_EventMeshSelectiveSubmission.hpp`;
- `ESPressio_EventMeshBroadcastSubmission.hpp`;
- their four predecessor-specific tests.

`ESPressio_MeshAdapters.hpp` now exports only the neutral ingress/lower-transport/route surfaces and current Event/Command/State family bindings. README has been rewritten around the locked family-neutral ownership model. Combined/focused validation is fully green at `fbef3ee…`.

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

## Locked Tranche-8 completion checks still being audited

M8-23/M8-24 must close the remaining security/resource/fuzz/multi-node/dependency/documentation evidence and the formal integration gate. In particular the closure audit must explicitly prove or map existing tests for:
- exact seven-disposition M1 family admission and evidence promotion;
- forward-once plus bounded DeferredLocal without re-fan;
- no source feedback loop;
- finite/non-increasing remaining residence under duplicate/retry;
- family broadcast legality, including response-bearing Command and invalid/stateless State rejection;
- compatible minimum relay-capacity admission and complete relay record+byte+workspace ownership;
- R3 physical-fragment ownership;
- Timing/Radio/Mesh clock ownership and conservative failover;
- no predecessor worker/polling dependencies in canonical Mesh runtime;
- dependency guards preventing family runtimes/Observable from leaking into Mesh core;
- deterministic published resource accounting;
- semantic classification of existing tests before execution;
- no version change.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Never derive runtime incarnation from Mesh membership.
- Never pack/truncate DeviceIdentifier into a route token.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken fail-closed provenance or broadcast restrictions to satisfy tests.

## Immediate continuation

1. Classify existing Mesh/MeshAdapters tests and workflows against every M8-23/Tranche-8 completion-gate item.
2. Add only missing focused host/security/resource/fuzz/multi-node/dependency-guard evidence; preserve locked architecture.
3. Update manifests/workflows/README/source comments/resource-accounting evidence required by M8-24 and run tranche integration validation.
4. Re-check Adapters native workflow `34748737223`; retain native-CI-pending versus integration-green distinction if no runner is allocated.
5. Produce the formal Tranche-8 implementation/closure report and update this living handoff before moving to Tranche 9.

After Tranche 8, continue authorized structural Tranches 9–11. Tranche 12 release preparation remains separate.
