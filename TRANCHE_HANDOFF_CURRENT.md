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

Mesh M8-23 is green at `5f36b51f6ce570e97e4f95f975f039d61e2287cd` with workflows `34753038491`, `34753038532`, and `34753038454` all SUCCESS. Formal Mesh closure is recorded in `ESPressio-Mesh/TRANCHE_8_CLOSURE.md` at `a832ce41c7ebd6174c7a06835ea24a871f843dcc`.

Final MeshAdapters integration checkpoint is `ce0a745498216248279aafc70d6603e49b10a6ab` with combined workflow `34753328372`, State workflow `34753328259`, and Command recovered-response workflow `34753328297` all SUCCESS.

## Tranche 9 — ACTIVE: RadioAdapters and non-Mesh transports

Authoritative implementation sequence is R9-01..R9-25 from Architecture section 30.

Source-first baseline heads confirmed before Tranche-9 writes:
- RadioAdapters `8b660acaa4f6c93d363364c596cf2bcbbda9c044`;
- ESP-Now `56e4f4023c68468c49229fcff85e55a7cbc6b8e6`;
- Sockets `8c5322aa03e1e3b6408e1ed999f00263afbe159e`;
- Serial `3ef07be4252908458110682291fd6b1c1d181262`;
- WiFi `8f959f19fbf4f7c3af42223ccc27521a4728f5dd`;
- Radio `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`.

`ESPressio-RadioAdapters` is the only layer that simultaneously understands Radio and Primitive families. Radio core remains Primitive-family-neutral; generic Adapters remains Radio-neutral.

The direct-Radio Primitive envelope is locked to exactly four bytes before the family representation:

```text
Offset 0..1: PrimitiveFamilyId, canonical little-endian
Offset 2..3: PrimitiveProtocolVersion, canonical little-endian
Offset 4..N: family representation
```

Service class is out-of-band and explicitly mapped. Physical/direct peer is distinct from validated semantic original source.

### R9-02 / R9-03 — IMPLEMENTED; GREEN

RadioAdapters exact four-byte codec and explicit six-way neutral-service <-> `RadioServiceClass` mapping are implemented. The codec is intentionally policy-free; unsupported family/version is a frozen binding-registry concern, not a wire-codec concern.

Initial green foundation checkpoint:
- RadioAdapters `3d3f1ed6a9bfdcc52fec2df385d37c71578d9bf2`
- workflow `34753638473` — SUCCESS.

### R9-04 / R9-05 — IMPLEMENTED; GREEN

Promoted RadioAdapters ingress checkpoint: `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`.

Exact green evidence:
- `RadioAdapters ingress contracts` workflow `34755161807` — SUCCESS;
- `RadioAdapters redesign contracts` workflow `34755161844` — SUCCESS.

Implemented surfaces:
- `src/ESPressio_RadioAdapterBinding.hpp` — fixed-capacity Radio-specific demux/policy registry, one binding per family, frozen before lookup; it does not duplicate A2's `AdapterBindingTable` family execution registry.
- `src/ESPressio_RadioAdapterIngress.hpp` — exact prefix validation/stripping, explicit Radio->A2 service mapping, fixed provenance resolver, synchronous trusted ingress handoff, completed-reassembly handoff, and one-quantum reassembly-ready sink with no local retry worker.
- `tests/radio_adapter_ingress_test.cpp` — duplicate/freeze/unsupported/malformed/provenance/service/ownership contract coverage.

Locked inbound ownership now proven:
Radio owns the complete trusted logical-message lease until the bridge call; RadioAdapters validates and strips only the four-byte prefix; family policy resolution sees only family bytes; transport/security provenance supplies immediate peer and optional validated semantic source independently; A2 synchronously copies accepted bytes before return and later executes exactly one family admission thunk on its own worker topology.

A trusted physical Radio peer produces an `ImmediatePeer` fact but does **not** automatically produce `OriginalSource` semantic provenance. Unknown family or unsupported protocol returns `Unsupported` before family decode. Short/malformed envelope returns `Malformed`. No Radio lease, borrowed pointer, family object, retry record or worker is retained by RadioAdapters.

### Neutral A2 lower-transport metadata seam — IMPLEMENTED; INTEGRATION GREEN

R9-06 source-first analysis exposed that the neutral `LowerTransportSubmitThunk` did not carry enough already-owned A2 metadata for a direct Radio transport to construct the locked envelope or derive finite Radio-local timing/evidence requirements without smuggling transport facts into family payloads/routes.

Current `ESPressio-Adapters/primitives_redesign` tip is:
- `4c22db73063041a488e497b75be903a98a89196a`.

The neutral submit seam now carries, in addition to the existing record/service/bytes/route:
- `PrimitiveFamilyId`;
- `PrimitiveProtocolVersion`;
- immutable `PrimitivePolicyDescriptor`.

`AdapterRuntime` passes `record.Family`, `record.Protocol` and `record.Policy` directly to the bound lower transport. Generic Adapters remains Radio-neutral.

`ESPressio-MeshAdapters` production lower transport accepts these additive neutral fields and intentionally ignores them because Mesh already owns its application framing and lifecycle. All stale test-only lower-transport mocks were migrated to the same neutral signature.

Promoted MeshAdapters compatibility checkpoint:
- MeshAdapters `f861d96ecddb14a9242f444174fb0248da9bab88`.
- State outbound workflow `34756179342` — SUCCESS.
- Command recovered-response workflow `34756179358` — SUCCESS.
- combined `MeshAdapters redesign contracts` workflow `34756179363` — SUCCESS.

This proves the neutral seam extension did not alter Tranche-8 Mesh family semantics.

### R9-06 — IMPLEMENTED; GREEN

Promoted RadioAdapters outbound checkpoint:
- RadioAdapters `819a2cd5e6f3dcec589d3dd586e5cc5ba1c54525`.

Exact green evidence at that tip:
- outbound workflow `34755755309` — SUCCESS;
- ingress workflow `34755755291` — SUCCESS;
- redesign/exported-surface workflow `34755755273` — SUCCESS.

Implemented `src/ESPressio_RadioAdapterLowerTransport.hpp`:
- fixed opaque `AdapterRouteToken` -> generation-safe `RadioPeerHandle` resolver;
- composition-owned transfer-policy resolver producing finite `RadioServiceProfile` plus `RadioTransferTiming` from family/protocol/P2/service facts;
- bounded synchronous framing workspace;
- exact four-byte family/version prefix plus immutable family representation;
- one `RadioRuntime::SubmitPeer(...)` logical-transfer admission;
- no RadioAdapters worker, retry queue, retained payload, route engine or fragmentation engine;
- atomic quiesce state.

At this checkpoint the lower binding deliberately advertises `ProvidesDestinationPrimitiveAdmission=false` and `ProvidesValidatedOriginalSource=false`. Radio accepted/transmitted/peer-acknowledged evidence is therefore never mislabeled as exact family M1.

### R9-07 — ACTIVE NEXT

Radio public runtime remains at `364f083c297e2072f7972f2fd63fcfa79cb6c1dd` and has been re-audited:
- `RadioRuntime::SubmitDirect(...)` / `SubmitPeer(...)` are bounded logical-transfer admission surfaces;
- scheduler admission copies/owns logical bytes before reporting success;
- `RadioRuntimeTransferResult` qualifies terminal results by contention domain;
- scheduler terminal result contains the scheduler-local 16-bit `RadioTransferId`, terminal status and direct-link evidence;
- `RadioRuntime::Shutdown()` is terminal for that concrete instance, drains domains, invalidates peer handles and clears result sinks.

Locked R9-07 rule: `TransmissionCompletion` and `PeerAcknowledgement` can establish only lower-transport/link evidence. They can never establish `DestinationPrimitiveAdmission`. A policy requiring destination admission must remain pending for a **separate exact generation-correlated destination M1 receipt**, or exhaust under A2 pursuit policy.

The provisional use of a raw 16-bit Radio transfer id as ingress diagnostic correlation is not sufficient for restart-safe A2 completion identity. R9-07/R9-11 must use bounded generation-safe correlation across Radio runtime lifetimes and must reject stale terminal/receipt observations.

## Tranche-9 remaining order

After R9-07:
- R9-08 Event direct-Radio binding;
- R9-09 Command direct-Radio binding;
- R9-10 State direct-Radio binding;
- R9-11 restart/shutdown/stale-completion hardening;
- R9-12..R9-16 ESP-NOW migration and predecessor fragmentation/runtime removal;
- R9-17..R9-19 Sockets neutral transport/session migration;
- R9-20 Serial classification/migration;
- R9-21..R9-22 WiFi migration;
- R9-23 hardening;
- R9-24 dependency/manifests/accounting;
- R9-25 documentation/integration closure.

## Locked non-regression rules

- Adapter queue ownership is never M1 `Accepted`.
- Only M1 `Accepted`/`AlreadyAccepted` establishes destination Primitive admission.
- Immediate transport peer and original semantic source are independent provenance facts.
- Never derive System runtime incarnation from Mesh membership incarnation.
- Never pack/truncate semantic identity into route tokens.
- No family-local retry worker, retry queue or fragmentation architecture.
- Radio/R3 remains sole physical fragmentation/reassembly/arbitration owner.
- Direct-link transmission/peer ACK evidence never becomes destination Primitive admission.
- Timing remains sole estimator/discipline/uncertainty/reliability owner.
- Radio core remains Primitive-family-neutral; generic Adapters remains Radio-neutral.
- No version change in structural Tranche 9.

## Immediate continuation

1. Implement R9-07 bounded generation-safe Radio terminal-result correlation and conservative evidence mapping, with exact destination M1 receipt kept separate from link evidence.
2. Prove stale scheduler-local transfer IDs and stale runtime-lifetime observations cannot complete reused A2 records.
3. Validate exact host contracts and promote only green workflow evidence here.
4. Continue R9-08..R9-11 Event/Command/State direct Radio and restart lifecycle.
5. Maintain this file after every material checkpoint and before every stop; regenerate the synchronized downloadable handoff with every user response.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
