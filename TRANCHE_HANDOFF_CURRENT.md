# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff. Mesh owns authenticated membership, topology, routing/forwarding/Broadcast and Mesh application lifecycle. Radio/R3 owns physical fragmentation/reassembly/arbitration. Timing owns clock estimation/discipline/uncertainty/reliability. Mesh owns only clock root/parent/reference topology selection. Primitive family runtimes own exact M1 semantics.

Only family `Accepted`/`AlreadyAccepted` establishes `DestinationPrimitiveAdmission`. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens are opaque transport facts and never encode/truncate `DeviceIdentifier`. No family-local retry worker/queue/fragmentation architecture is permitted.

## Tranches 2–7

Foundation F01–F08 and structural Tranches 2–7 remain closed.

## Tranche 8 — current status

Tranche 8 is at the final cross-repository integration gate.

### Mesh M8-23 — GREEN

M8-23 is fully green at Mesh implementation checkpoint `5f36b51f6ce570e97e4f95f975f039d61e2287cd`.

Exact successful workflows:
- `Tranche 8 Mesh closure` — `34753038491` SUCCESS.
- `Mesh redesign contracts` — `34753038532` SUCCESS.
- `Mesh clock and runtime redesign` — `34753038454` SUCCESS.

Those exact runs prove:
- dependency boundary and unchanged Mesh version `1.0.0`;
- exact seven-disposition M1 admission/evidence semantics;
- complete relay record + byte + workspace ownership;
- relay-capacity compatibility;
- finite/non-increasing remaining residence;
- forward-once Broadcast plus bounded `DeferredLocal` retry without re-fan;
- family Broadcast legality;
- source no-feedback / no own-family redispatch loop;
- logical Mesh-to-Radio handoff with no physical-fragment ownership leakage;
- Mesh v1 authentication/replay/security behavior;
- deterministic codec fuzz coverage;
- three-node A -> B -> C forwarding with authenticated original-source knowledge but no invented A-C direct session/link;
- clock ownership/failover;
- generic Thread runtime worker with predecessor mechanisms absent;
- deterministic Mesh-owned resource accounting.

The three-node fixture was corrected without weakening security: C records A as an Active authenticated Mesh member but `Unreachable`, while B remains C's only direct authenticated sender/session for the forwarded frame.

The legacy worker guard was corrected to strip comments before testing forbidden executable patterns; it still rejects `PrecisionThread`, `std::function`, `<functional>`, maintenance-period polling and catch-all exception wrappers in code.

The Mesh memory-accounting test no longer imports deleted Radio reassembly/logical-transfer macros. Radio-owned R3 resources remain Radio-owned and separately published; Mesh accounts only Mesh-owned resources.

### Mesh M8-24 — DOCUMENTATION/REPORT IMPLEMENTED; FINAL INTEGRATION PENDING

Current Mesh live tip is `f496359526fcdf88fb140e67cd0e5b40cbdc691b`.

After the green M8-23 implementation checkpoint:
- README was rewritten at `5153c10319149e15c76164a3f37d917f3ff78cf2` to describe the current `primitives_redesign` ownership/dependency/runtime/clock/resource model and remove predecessor `RadioTransport`/propagation-branch wording.
- `TRANCHE_8_CLOSURE.md` was added at `f496359…` as the formal closure-candidate report.
- `library.json` remains `1.0.0` and depends only on System, Threads, Primitive, Radio, Timing and Security on `primitives_redesign`; Mesh core still has no Event/Command/State/Observable/Adapters dependency.

The report is intentionally marked closure-candidate until the final MeshAdapters family integration rerun executes against this finalized Mesh tip.

### MeshAdapters M8-21/M8-22 — IMPLEMENTED; PRIOR GREEN; FINAL RERUN ACTIVE

Prior promoted MeshAdapters checkpoint is `fbef3eedb8d4396461e7d02e8073eccea982d99a` (`Retire predecessor Event-only MeshAdapter architecture`). Exact successful evidence at that checkpoint:
- combined contracts `34750952418` SUCCESS;
- State outbound A2 `34750952358` SUCCESS;
- Command recovered-response A2 `34750952335` SUCCESS.

This covers:
- neutral Mesh -> A2 ingress correlation;
- neutral A2 -> Mesh lower transport;
- Event ingress/outbound and remote-origin no re-egress;
- Command ingress/idempotency/no-response egress/response-bearing delivery failure/durable recovered response;
- State ingress/outbound convergence feedback;
- opaque route-token and authenticated semantic provenance rules;
- removal of predecessor Event-only Mesh transport/submission architecture with no compatibility shim.

Current MeshAdapters live tip is `ce0a745498216248279aafc70d6603e49b10a6ab`, which adds `TRANCHE_8_INTEGRATION.md` and deliberately triggers the final family contract workflows against the finalized live Mesh `primitives_redesign` branch. Do not promote Tranche 8 to closed until those new exact runs are SUCCESS.

### A2 mixed-policy correction

Adapters live tip remains `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). It preserves Initialize-time strongest-capability proof while allowing a `NoRemoteEvidence` occurrence in a family that also contains Types requiring `DestinationPrimitiveAdmission`. Per-occurrence evidence remains fail-closed.

Native Adapters workflow `34748737223` has remained queued without job allocation. This is tracked as native-CI pending rather than failure; exact-tip integration has been green through MeshAdapters, and the final MeshAdapters rerun must again compile against this exact Adapters tip.

## Family replacement state

### Event — GREEN; predecessor retired

Canonical path is `ESPressio_EventMeshAdapterBinding.hpp` + `ESPressio_EventMeshAdapterOutboundTarget.hpp` over neutral A2/Mesh integration. Remote-origin Event occurrences do not re-egress.

Removed without compatibility shims:
- `ESPressio_EventMeshTransport.hpp`;
- `ESPressio_EventMeshNodeSubmission.hpp`;
- `ESPressio_EventMeshSelectiveSubmission.hpp`;
- `ESPressio_EventMeshBroadcastSubmission.hpp`;
- predecessor-specific tests.

### Command — GREEN

Two-stage MeshAdapter composition supports Command startup ordering: configure Type/format/policy before Command Runtime initialization, bind outbound/recovered-response transport during initialize, attach inbound Runtime afterwards, then freeze before start.

Local requests are synchronously copied into A2-owned bytes. Response-bearing request delivery tokens are held only in a bounded generation-safe correlation table. Terminal A2 failure without required destination admission publishes exactly one existing `RequestDeliveryFailed` completion. Durable recovered executor responses use the same A2 encoder and preserve original execution key/executor/payload/route semantics.

Exact terminal duplicates may be transiently `TemporarilyUnavailable` while response-slot release is in progress, then converge to `AlreadyAccepted` without handler re-execution.

### State — GREEN

State egress uses real `StateTransportBinding<TState,TFormat>`. MeshAdapters validates role-specific semantic source, resolves the opposite semantic role through `MeshRouteBinding`, synchronously encodes canonical State V1 into A2-owned bytes and retains no payload/route/retry/deadline state.

Only the existing immutable `StateConvergenceHandle` is correlated for terminal feedback. Terminal A2 exhaustion enters bounded `ExhaustionPending`; service context reports exact exhaustion to State, which alone owns dormant `NeedsConvergence`, sessions, versions, baselines, resync and rearm.

Canonical State V1 generic Broadcast remains rejected.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Only `Accepted`/`AlreadyAccepted` establishes destination Primitive admission.
- Never derive System runtime incarnation from Mesh membership incarnation.
- Never pack/truncate `DeviceIdentifier` into route tokens.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- No predecessor Event node/selective/broadcast transport runtimes under new names.
- Do not weaken authenticated-source, provenance, replay or Broadcast restrictions to satisfy tests.
- Radio/R3 remains sole physical fragmentation/reassembly/arbitration owner.
- Timing remains sole estimator/discipline/uncertainty/reliability owner.
- Mesh core remains family-neutral and Observable-free.
- No version change in this tranche.

## Immediate continuation

1. Resolve the workflows triggered by MeshAdapters `ce0a745…` and record exact run IDs/results.
2. If all final MeshAdapters combined/focused workflows are green against Mesh `f496359…` and Adapters `b8a1722…`, update `ESPressio-Mesh/TRANCHE_8_CLOSURE.md` from closure-candidate to CLOSED and record the exact final integration evidence.
3. Update this live handoff immediately with the exact closed Tranche-8 tips and workflow IDs.
4. Re-check Adapters native workflow `34748737223`; retain a clearly stated native-runner caveat if GitHub still has not allocated a job, without confusing it with integration failure.
5. Once Tranche 8 is formally closed, continue authorized structural Tranche 9 according to the authoritative redesign handoff, source-first and without permission pause.
6. Maintain this file after every material checkpoint and before every stop; regenerate the synchronized downloadable handoff for the user with every response.

Tranche 12 release preparation remains separate and unauthorized.
