# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth only.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership

A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff. Mesh owns authenticated membership, topology, routing/forwarding/Broadcast and Mesh application lifecycle. Radio/R3 owns physical fragmentation/reassembly/arbitration. Timing owns clock estimation/discipline/uncertainty/reliability. Mesh owns only clock root/parent/reference topology selection. Primitive family runtimes own exact M1 semantics.

Only family `Accepted`/`AlreadyAccepted` establishes `DestinationPrimitiveAdmission`. Mesh membership incarnation is never a System runtime incarnation. Adapter route/peer tokens are opaque transport facts and never encode/truncate `DeviceIdentifier`. No family-local retry worker/queue/fragmentation architecture is permitted.

## Closed structural tranches

Foundation F01–F08 and structural Tranches 2–8 are CLOSED.

## Tranche 8 — CLOSED

### Mesh implementation evidence

M8-23 is green at Mesh implementation checkpoint `5f36b51f6ce570e97e4f95f975f039d61e2287cd`:
- `Tranche 8 Mesh closure` workflow `34753038491` — SUCCESS.
- `Mesh redesign contracts` workflow `34753038532` — SUCCESS.
- `Mesh clock and runtime redesign` workflow `34753038454` — SUCCESS.

Those exact runs prove dependency/version guards, exact seven-disposition M1 admission/evidence, complete relay record+byte+workspace ownership, relay-capacity compatibility, finite remaining residence, forward-once Broadcast + bounded DeferredLocal without re-fan, family Broadcast legality, source no-feedback, logical Mesh-to-Radio handoff, Mesh v1 security/replay, deterministic codec fuzz, three-node forwarding, clock ownership/failover, generic Thread worker behavior and deterministic Mesh-owned resource accounting.

The three-node fixture preserves the security contract: C knows A as an Active authenticated Mesh member but Unreachable; B remains C's only direct authenticated sender/session for the forwarded frame. No fake A-C direct link/session was introduced.

The worker guard strips comments before checking forbidden executable predecessor mechanisms. The Mesh accounting test no longer imports deleted Radio reassembly/logical-transfer macros; Radio-owned R3 resources remain Radio-owned.

### Mesh M8-24 documentation/closure

Mesh README was aligned to the current `primitives_redesign` ownership/dependency/runtime/clock/resource model at `5153c10319149e15c76164a3f37d917f3ff78cf2`.

`ESPressio-Mesh/TRANCHE_8_CLOSURE.md` is formally CLOSED at Mesh commit `a832ce41c7ebd6174c7a06835ea24a871f843dcc`.

`library.json` remains version `1.0.0` and family-neutral: System, Threads, Primitive, Radio, Timing and Security only.

### Final MeshAdapters integration evidence

Final integration checkpoint: `ESPressio-MeshAdapters/primitives_redesign` commit `ce0a745498216248279aafc70d6603e49b10a6ab`.

Exact successful workflows:
- combined MeshAdapters redesign contracts `34753328372` — SUCCESS;
- State outbound A2 contract `34753328259` — SUCCESS;
- Command recovered-response A2 contract `34753328297` — SUCCESS.

These final runs resolved the live finalized Mesh `primitives_redesign` branch and the live Adapters branch, proving the Event/Command/State replacement contracts against the completed Mesh M8-23/M8-24 state.

### Adapters native-runner caveat

Adapters live tip used by final integration is `b8a17228bb3d5e87ae622dbab782a308326bf543` (`Allow mixed outbound evidence policies per family`). Native workflow `34748737223` has remained queued without job allocation. This is an infrastructure/native-runner caveat, not an integration failure: the exact Adapters tip is compiled and exercised by the successful final MeshAdapters workflows above.

## Family replacement state after Tranche 8

### Event — GREEN; predecessor retired

Canonical path is `ESPressio_EventMeshAdapterBinding.hpp` + `ESPressio_EventMeshAdapterOutboundTarget.hpp` over neutral A2/Mesh integration. Remote-origin Event occurrences do not re-egress.

Removed without compatibility shims: predecessor Event Mesh transport/node/selective/broadcast submission surfaces and their predecessor-specific tests.

### Command — GREEN

Two-stage MeshAdapter composition supports Command startup ordering. Local requests copy synchronously into A2-owned bytes. Response-bearing request delivery tokens are bounded/generation-safe; terminal A2 failure without required destination admission publishes exactly one `RequestDeliveryFailed`. Durable recovered executor responses preserve execution key/executor/payload/route semantics.

Exact terminal duplicates may be transiently `TemporarilyUnavailable` while response-slot release is in progress, then converge to `AlreadyAccepted` without handler re-execution.

### State — GREEN

State egress uses real `StateTransportBinding<TState,TFormat>`. MeshAdapters validates role-specific semantic source, resolves the opposite semantic role through `MeshRouteBinding`, synchronously encodes canonical State V1 into A2-owned bytes and retains no payload/route/retry/deadline state. Terminal A2 exhaustion reports through the existing State convergence handle; State alone owns dormant `NeedsConvergence`, sessions, versions, baselines, resync and rearm.

Canonical State V1 generic Broadcast remains rejected.

## Tranche 9 — ACTIVE: RadioAdapters and non-Mesh transports

Authoritative implementation sequence is R9-01..R9-25 from Architecture section 30.

Repositories:
- `ESPressio-RadioAdapters`
- `ESPressio-ESP-Now`
- `ESPressio-Sockets`
- `ESPressio-Serial`
- `ESPressio-WiFi`

Architecture baseline recorded in Revision 102:
- RadioAdapters `primitives_redesign` bootstrap `8b660acaa4f6c93d363364c596cf2bcbbda9c044`;
- ESP-Now audit tip `56e4f4023c68468c49229fcff85e55a7cbc6b8e6`;
- Sockets audit tip `8c5322aa03e1e3b6408e1ed999f00263afbe159e`;
- Serial audit tip `3ef07be4252908458110682291fd6b1c1d181262`;
- WiFi audit tip `8f959f19fbf4f7c3af42223ccc27521a4728f5dd`.

These are audit baselines only. Source-first branch tips MUST be refreshed before each implementation write.

### Tranche-9 locked target boundary

`ESPressio-RadioAdapters` is the only layer that simultaneously understands Radio and Primitive families. Its direct dependencies are exactly:

```text
Radio
Adapters
Primitive
Event
Command
State
```

It owns the exact direct-Radio Primitive envelope:

```text
2 bytes PrimitiveFamilyId
2 bytes PrimitiveProtocolVersion
N bytes family representation
```

The prefix is exactly four bytes. Radio core must not learn the prefix or family semantics. Generic Adapters must not learn Radio wire/service types.

RadioAdapters must explicitly map neutral A2 service class <-> `RadioServiceClass`; no numeric-equivalence shortcut is allowed.

Inbound direct-Radio:
Radio-owned logical bytes -> validate 4-byte prefix -> map trusted Radio provenance/service/evidence into neutral Adapter ingress -> A2 owns/adopts bounded bytes -> one family admission thunk -> exact M1 result. Immediate physical peer is not automatically original semantic source.

Outbound direct-Radio:
family representation including exact 4-byte prefix -> A1/A2 ownership -> Radio admission. Radio owns physical fragmentation through R3. RadioAdapters must not add family-specific queue/worker/fragmentation/retry engines.

### Tranche-9 implementation order now in force

Start with RadioAdapters R9-02..R9-11:
1. exact 4-byte family/version codec + vectors;
2. explicit neutral-service <-> Radio service mapping;
3. fixed binding registry/configuration freeze;
4. inbound Radio logical-message -> A2 ownership/provenance mapping;
5. outbound family/A1 -> Radio admission handoff;
6. exact P2/evidence mapping without conflating link ACK with destination Primitive admission;
7. direct-Radio Event/Command/State bindings;
8. generation-safe restart/shutdown/stale-completion handling.

Then continue R9-12..R9-25 across ESP-NOW, Sockets, scoped Serial, WiFi, congestion/restart/fuzz/dependency/documentation/integration cleanup.

### Tranche-9 completion gate

- exact 4-byte RadioAdapters prefix fixed vectors;
- Radio core remains free of Primitive-family dependencies; Adapters remains free of Radio dependency;
- Event/Command/State direct-Radio all use A1/A2 + exact M1;
- link/peer ACK never becomes destination Primitive admission;
- ESP-NOW no longer owns second Event fragmentation/reassembly runtime;
- ESP-NOW clock follows K1/K2 with no fixed cadence/historical mutable-System reconstruction;
- Sockets exposes bounded neutral transport/session mechanics without parallel family execution stacks;
- Serial tooling is not misclassified as transport; any genuine Primitive byte transport uses A2;
- WiFi remote family bridges no longer depend on predecessor Command/Event hacks;
- finite congestion/backpressure and generation-safe restart across transports;
- no canonical old EventTransportManager/Event bridge/CommandRegistry transport path;
- no extra transport-owned worker where A2/T1 owns execution;
- locked DAG/manifests/branches, semantically classified tests, no version change.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Only `Accepted`/`AlreadyAccepted` establishes destination Primitive admission.
- Never derive System runtime incarnation from Mesh membership incarnation.
- Never pack/truncate `DeviceIdentifier` into route tokens.
- Keep semantic provenance distinct from immediate route/peer facts.
- No family-local retry worker, retry queue or fragmentation architecture.
- Radio/R3 remains sole physical fragmentation/reassembly/arbitration owner.
- Timing remains sole estimator/discipline/uncertainty/reliability owner.
- Radio core remains Primitive-family-neutral; generic Adapters remains Radio-neutral.
- No version change in structural Tranche 9.

## Immediate continuation

1. Re-query exact `primitives_redesign` heads for RadioAdapters, ESP-Now, Sockets, Serial and WiFi and reconcile any drift before writing.
2. Audit the current Radio public logical-message ingress/admission/evidence/restart surface needed by R9-02..R9-11.
3. Implement RadioAdapters exact four-byte prefix codec + vectors first, then explicit service mapping and frozen registry.
4. Continue inbound/outbound A2<->Radio composition and direct Event/Command/State bindings without duplicate worker/retry/fragmentation systems.
5. Update this file after every material checkpoint and before every stop; regenerate the synchronized downloadable handoff for the user with every response.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
