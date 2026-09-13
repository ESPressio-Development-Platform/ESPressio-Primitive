# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The authoritative architecture handoff remains controlling for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. Branch tips remain implementation truth.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases, Wiki publication, force pushes and backward-compatibility shims remain outside this authorization. Tranche 12 remains separately consequential.

## Locked ownership / non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning.
- Only family `Accepted` / `AlreadyAccepted` establishes `DestinationPrimitiveAdmission`; adapter ownership, Radio transmit completion and peer ACK never do.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio composition layer that simultaneously understands Radio and Primitive families.
- Generic Adapters remains Radio-neutral.
- Immediate physical peer and validated semantic `OriginalSource` are independent provenance facts.
- Never hash, pack or truncate semantic identity into `AdapterRouteToken`.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology is fixed before Running; bounded storage and nonblocking ingress remain mandatory.
- Every neutral non-Mesh transport binding has a finite lifecycle/generation. Restart invalidates prior handles/correlation; late callbacks/completions must never become current work.
- Shutdown rejects new work, quiesces ingress, releases volatile transport capacity, waits only already-executing bounded work and never force-kills application execution.
- Temporary backpressure/disconnection/restart must not create unbounded retry.
- No structural-Tranche-9 version changes.

## Closed structural tranches

Foundation F01–F08 and structural Tranches 2–8 are CLOSED.

### Tranche 8 closure evidence

- Mesh closure checkpoint `5f36b51f6ce570e97e4f95f975f039d61e2287cd`; workflows `34753038491`, `34753038532`, `34753038454` — SUCCESS.
- Formal Mesh report `ESPressio-Mesh/TRANCHE_8_CLOSURE.md` at `a832ce41c7ebd6174c7a06835ea24a871f843dcc`.
- Final MeshAdapters checkpoint `ce0a745498216248279aafc70d6603e49b10a6ab`; combined `34753328372`, State `34753328259`, recovered Command `34753328297` — SUCCESS.

## Tranche 9 — ACTIVE: RadioAdapters and non-Mesh transports

Authoritative sequence is R9-01..R9-25 from Architecture section 30.

Source-first baseline heads before Tranche-9 writes:
- RadioAdapters `8b660acaa4f6c93d363364c596cf2bcbbda9c044`;
- ESP-Now `56e4f4023c68468c49229fcff85e55a7cbc6b8e6`;
- Sockets `8c5322aa03e1e3b6408e1ed999f00263afbe159e`;
- Serial `3ef07be4252908458110682291fd6b1c1d181262`;
- WiFi `8f959f19fbf4f7c3af42223ccc27521a4728f5dd`;
- Radio pre-R9 baseline `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`.

Direct-Radio Primitive envelope remains exactly:

```text
Offset 0..1: PrimitiveFamilyId, canonical little-endian
Offset 2..3: PrimitiveProtocolVersion, canonical little-endian
Offset 4..N: unchanged family representation
```

Service class is out-of-band and explicitly mapped.

### R9-02 / R9-03 — CLOSED; GREEN

Exact four-byte codec and six-way `AdapterServiceClass` <-> `RadioServiceClass` mapping.
- RadioAdapters `3d3f1ed6a9bfdcc52fec2df385d37c71578d9bf2`;
- workflow `34753638473` — SUCCESS.

### R9-04 / R9-05 — CLOSED; GREEN

Frozen direct-Radio demux/policy registry and trusted Radio -> A2 handoff.
- RadioAdapters `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`;
- ingress `34755161807`, redesign `34755161844` — SUCCESS.

Radio owns the complete trusted logical-message lease until bridge entry; RadioAdapters strips only the four-byte prefix, resolves policy/provenance and hands family bytes synchronously to A2. Physical peer produces `ImmediatePeer` only and never automatically produces semantic `OriginalSource`.

### Neutral A2 lower-transport metadata seam — CLOSED; GREEN

Adapters `4c22db73063041a488e497b75be903a98a89196a` carries neutral record/family/protocol/policy/service/bytes/route metadata to lower transports while remaining Radio-neutral.

MeshAdapters compatibility checkpoint `f861d96ecddb14a9242f444174fb0248da9bab88`; State `34756179342`, recovered Command `34756179358`, combined `34756179363` — SUCCESS.

### R9-06 outbound — CLOSED; GREEN

RadioAdapters `819a2cd5e6f3dcec589d3dd586e5cc5ba1c54525`; outbound `34755755309`, ingress `34755755291`, redesign `34755755273` — SUCCESS.

`ESPressio_RadioAdapterLowerTransport.hpp` resolves opaque route tokens to generation-safe Radio peers, resolves finite Radio service/timing policy, frames the four-byte prefix, submits one logical Radio transfer and owns no retry/fragmentation worker.

### R9-07 Radio correlation substrate — CLOSED; GREEN

Radio `84c6bbcac36d959378dcc69366bc18921298c257`; redesign `34764194951`, transfer-ID lease `34764194938` — SUCCESS.

The family-neutral lease/correlation seam protects outstanding direct-Radio semantic campaigns from transfer-ID reuse within one live Radio runtime. It does not interpret correlation as Primitive admission and did not yet claim restart-incarnation protection.

### R9-07 exact M1 — CLOSED; GREEN

RadioAdapters `0e72a10f0034820e8bc8e0e72166bee9731b972e`.
- redesign `34768426144`;
- exact M1 `34768426012`;
- ingress `34768426030`;
- outbound `34768426102` — all SUCCESS.

`ESPressio_RadioAdapterM1.hpp` owns the bounded exact-M1 control path `{Family=0,Protocol=1}`, generation-safe attempt table, exact route/domain/transfer matching and deferred A2 completion. `{Family=0,Protocol=1}` is intercepted before normal family demux. No Radio callback recursively executes A2 pursuit.

### R9-08 Event direct-Radio — CLOSED; GREEN

RadioAdapters `a8092a2d914f7a0abf1a35c005e105f3c7d5a650`.
- ingress `34769579671`;
- outbound `34769579684`;
- redesign `34769579653`;
- exact M1 `34769579682`;
- Event `34769579729` — all SUCCESS.

Event direct-Radio uses one frozen family binding, canonical Event V1 wire, real Event runtime admission/idempotency/source-loop semantics, per-Type service/evidence facts, normal Event external-adapter target and the already-closed generic A2/M1 lower path. No second Event runtime or family-local queue/retry engine.

### R9-09 Command direct-Radio — CLOSED; GREEN

Final promoted RadioAdapters checkpoint:
- `984731e214affdfb1152e0d9cf9bdb01b0e36a75` (`Compile foundation umbrella with Command dependencies`).

Exact-tip permanent workflows:
- ingress `34771857945` — SUCCESS;
- outbound `34771857991` — SUCCESS;
- redesign `34771857946` — SUCCESS;
- exact M1 `34771857903` — SUCCESS;
- Event `34771858014` — SUCCESS;
- Command `34771857995` — SUCCESS.

Command direct-Radio uses one frozen A2 family binding and real Command runtime semantics. Trusted Radio provenance is cross-checked against wire-carried Command origin/executor identity. Response-bearing request delivery uses bounded generation-safe correlation and exact M1. Terminal delivery failure publishes the existing `RequestDeliveryFailed` outcome exactly once. Duplicate terminal requests map `AlreadyAccepted` without handler re-execution. Durable recovered results reserve their semantic return route before freeze/start and re-enter the same A2/direct-Radio response lane without executing the handler again. `ESPressio_RadioAdapters.hpp` exports Command as a first-class public family binding.

### R9-10 State direct-Radio — CLOSED; GREEN

Final promoted RadioAdapters checkpoint:
- `285b184ffd84ddb1e97c4292154010c613eaa735` (`Compile foundation umbrella with State dependency`).

Exact-tip permanent workflows — all SUCCESS:
- `RadioAdapters ingress contracts` `34772597924`;
- `RadioAdapters outbound contracts` `34772597753`;
- `RadioAdapters redesign contracts` `34772597861`;
- `RadioAdapters exact M1 contracts` `34772597866`;
- `RadioAdapters Event direct-Radio contracts` `34772597831`;
- `RadioAdapters Command direct-Radio contracts` `34772597748`;
- `RadioAdapters State direct-Radio contracts` `34772597901`.

Implemented State direct-Radio composition:

1. `src/ESPressio_StateRadioAdapterBinding.hpp`
   - one frozen State family binding through real A2;
   - canonical State V1 encoding/decoding remains State-owned;
   - State owns authoritative/latest truth, sessions, versions, baselines, resync, convergence and `NeedsConvergence`;
   - no second State runtime, replica/session table, retry worker or convergence engine exists in RadioAdapters.

2. Lifecycle-valid State transport contract
   - current State validates `StateTransportBinding` during `Runtime::Start()` after family freeze;
   - direct-Radio `ValidateTransport` therefore remains valid after freeze; freeze blocks mutation/admission, not validity of the configured immutable transport contract;
   - `Wake()` coalesces State service work and never services inline during mutation.

3. Outbound convergence
   - semantic destination `DeviceIdentifier` resolves through `RadioAdapterSemanticRouteBinding` to an opaque route token;
   - State V1 is synchronously encoded into A2-owned bytes;
   - bounded correlation retains only the existing immutable `StateConvergenceHandle`/generation facts;
   - A2 owns pursuit; terminal insufficient evidence is reported back through the real State runtime and drives its existing exhaustion/`NeedsConvergence` behavior.

4. Trusted inbound provenance
   - policy is resolved from the frozen RadioAdapters family binding;
   - trusted Radio provenance supplies semantic `OriginalSource` independently of immediate peer facts;
   - State V1 wire-carried semantic source must equal validated `OriginalSource` before `Runtime::AdmitRemote`;
   - wrong service and forged semantic source fail closed;
   - exact duplicates return `AlreadyAccepted` without duplicate State mutation.

5. Full integration evidence
   - focused outbound contract proves real State publication -> A2 -> Radio lower transport -> terminal pursuit failure -> service wake -> real convergence exhaustion/`NeedsConvergence`;
   - focused inbound contract proves exact State family admission/provenance/idempotency;
   - trusted ingress integration proves real `AdmitDirectRadioLogicalMessage()` -> provenance resolver -> A2 ownership -> State family runtime, including forged-source rejection.

6. Public package
   - `ESPressio_RadioAdapters.hpp` exports State alongside Event and Command;
   - all umbrella-consuming workflows explicitly carry the complete State dependency graph instead of relying on transitive/private-header compilation.

## Active continuation — R9-11 generation-safe restart/shutdown/stale-completion handling

Source-first current heads at activation:
- RadioAdapters `285b184ffd84ddb1e97c4292154010c613eaa735`;
- Radio `84c6bbcac36d959378dcc69366bc18921298c257`.

Locked lifecycle rules from Architecture section 30.11:
- every neutral non-Mesh transport binding has a finite lifecycle and generation;
- restart invalidates old handles/correlation without allowing late callbacks/completions to become current work;
- runtime registration is frozen at Running;
- shutdown rejects new work, resolves/releases transport-owned volatile capacity and does not force-kill application execution;
- temporary backpressure, disconnection or restart does not become unbounded retry.

Current audit truth before R9-11 writes:

1. Generic A2 already has the correct family-neutral lifecycle substrate.
   - `CompleteTransport()` requires exact `AdapterRecordIdentity` plus exact transport generation and counts stale completions diagnostically;
   - `Shutdown()` stops new submissions, quiesces lower transport, drains queues, waits for already-executing workers, cancels/drains retained volatile work and clears bindings;
   - this behavior must be reused, not duplicated in RadioAdapters.

2. Current RadioAdapter lower transport is one-way quiescable but not restart-generation aware.
   - `_quiesced` rejects further submission after shutdown;
   - there is no explicit activation generation/re-arm contract;
   - waiting M1 records can be cancelled by A2, but transport lifecycle identity is not represented independently.

3. Current M1 controller is generation-safe inside one live attempt table, but transport callbacks/receipts identify an attempt externally only by current `(contention-domain, RadioTransferId[, route])`.
   - slot tokens include a generation, but Radio terminal callbacks and the locked M1 control receipt do not carry that internal token;
   - a fresh Radio runtime/scheduler may begin its uint16 transfer-id sequence again;
   - therefore a sufficiently late result/receipt from a prior transport lifecycle must be prevented from aliasing a new attempt without altering the locked RadioTransport-v3 header or four-byte direct-Radio Primitive prefix.

4. Current `RadioRuntime` is terminal after `Shutdown()` and invalidates providers/reassembly/peer handles. A later restart is represented by a freshly configured runtime instance.

5. Current `RadioDomainScheduler::Shutdown()` drains volatile queues and detaches provider sinks but leaves `_stopping=true`; a same-object reinitialize is therefore not currently a valid restart. A fresh scheduler also resets its transfer-id issuer/recent window. R9-11 must make the controlled restart boundary explicit and generation-safe rather than relying on accidental object address/lifetime assumptions.

6. `RadioAdapterReassemblyIngress` uses generation-safe bounded pending-receipt slots but has no explicit quiesce/drain lifecycle. Late A2 completion after transport shutdown must not send a receipt into a replacement transport lifecycle.

R9-11 implementation must preserve the locked wire:
- do not change RadioTransport-v3 layout;
- do not change the exact four-byte RadioAdapters family/version prefix;
- do not reinterpret System `RuntimeIncarnationId` as transport lifecycle generation;
- do not introduce a family retry worker, polling loop, or unbounded stale-correlation store.

## Remaining Tranche-9 order

- R9-08 Event direct-Radio — CLOSED;
- R9-09 Command direct-Radio — CLOSED;
- R9-10 State direct-Radio — CLOSED;
- R9-11 restart/shutdown/stale-completion hardening — ACTIVE;
- R9-12..R9-16 ESP-NOW migration/predecessor removal;
- R9-17..R9-19 Sockets neutral transport/session migration;
- R9-20 Serial classification/migration;
- R9-21..R9-22 WiFi migration;
- R9-23 hardening;
- R9-24 dependency/manifests/accounting;
- R9-25 documentation/integration closure.

## Immediate continuation

1. Define the smallest finite transport-lifecycle/generation seam needed to bind RadioAdapters lower transport, M1 correlation and ingress to one active direct-Radio lifecycle without changing locked wire formats.
2. Make controlled Radio restart preserve or explicitly invalidate transfer-id/recent-correlation state so old `(domain, transfer-id)` facts cannot resolve current M1 attempts.
3. Add explicit quiesce/drain behavior to M1 attempts and pending inbound receipt state; late completions after quiesce must be diagnostic/no-op and must not emit new transport traffic.
4. Prove lower submissions and ingress are rejected after quiesce; prove shutdown releases volatile capacity and never force-kills family/application execution.
5. Add focused restart/stale-result/stale-M1-receipt/provider-completion tests plus a permanent lifecycle workflow; promote R9-11 only at one exact all-green tip.
6. Maintain this file after every material checkpoint and regenerate the synchronized downloadable handoff with user-facing checkpoints.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
