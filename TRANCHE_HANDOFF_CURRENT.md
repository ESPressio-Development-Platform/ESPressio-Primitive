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

Adapters live tip used by final integration is `b8a17228bb3d5e87ae622dbab782a308326bf543`. Native workflow `34748737223` remained queued without job allocation; this is a native-runner caveat, not an integration failure.

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

Current exported-surface regression at the promoted ingress checkpoint is also green:
- workflow `34755161844` — SUCCESS.

### R9-04 / R9-05 — IMPLEMENTED; GREEN

Promoted RadioAdapters tip: `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`.

Exact green evidence:
- `RadioAdapters ingress contracts` workflow `34755161807` — SUCCESS;
- `RadioAdapters redesign contracts` workflow `34755161844` — SUCCESS.

Implemented surfaces:
- `src/ESPressio_RadioAdapterBinding.hpp` — fixed-capacity Radio-specific demux/policy registry, one binding per family, frozen before lookup; it does not duplicate A2's `AdapterBindingTable` family execution registry.
- `src/ESPressio_RadioAdapterIngress.hpp` — exact prefix validation/stripping, explicit Radio->A2 service mapping, fixed provenance resolver, synchronous trusted ingress handoff, completed-reassembly handoff, and one-quantum reassembly-ready sink with no local retry worker.
- `tests/radio_adapter_ingress_test.cpp` — duplicate/freeze/unsupported/malformed/provenance/service/ownership contract coverage.

Locked inbound ownership now proven:
Radio owns the complete trusted logical-message lease until the bridge call; RadioAdapters validates and strips only the four-byte prefix; family policy resolution sees only family bytes; transport/security provenance supplies immediate peer and optional validated semantic source independently; A2 synchronously copies accepted bytes before return and later executes exactly one family admission thunk on its own worker topology.

The host contract explicitly proves that a trusted physical Radio peer produces an `ImmediatePeer` fact but does **not** automatically produce `OriginalSource` semantic provenance.

Unknown family or unsupported protocol returns `Unsupported` before family decode. Short/malformed envelope returns `Malformed`. No Radio lease, borrowed pointer, family object, retry record or worker is retained by RadioAdapters.

### R9-06 / R9-07 — ACTIVE NEXT

Radio public runtime has been revalidated at `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`:
- `RadioRuntime::SubmitDirect(...)` and `SubmitPeer(...)` are the family-opaque bounded logical-transfer admission surfaces;
- scheduler submission copies/owns logical bytes before reporting accepted;
- `RadioRuntimeTransferResult` qualifies terminal results by contention domain;
- direct-link transmission completion / peer acknowledgement remain Radio facts only;
- `RadioRuntime::Shutdown()` is terminal for that concrete instance, detaches ingress, drains domain runtimes, stops providers, invalidates peers and clears retained inbound state.

R9-06 must provide one A2 lower-transport seam that resolves the opaque Adapter route into the configured direct Radio peer/provider fact, maps service/policy to a Radio service profile/timing contract, and submits the immutable A2-owned representation through Radio logical-transfer admission. No family-specific queue/retry/fragmentation engine may be introduced.

R9-07 must map Radio terminal evidence conservatively. `TransmissionCompletion` and `PeerAcknowledgement` can establish only lower-transport/link evidence. They can never become `DestinationPrimitiveAdmission`. Any policy requiring destination admission must remain pending until a separate generation-correlated destination M1 receipt exists, or exhaust according to A2 pursuit policy.

The current ingress sink's use of the 16-bit Radio transfer id as a local diagnostic correlation is provisional and must not be treated as the final restart-safe A2 completion identity. R9-07/R9-11 must use generation-safe correlation across Radio runtime lifetimes.

## Tranche-9 remaining order

After R9-06/R9-07:
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

1. Implement R9-06 A2 outbound -> Radio logical-transfer lower-transport seam over `RadioRuntime::SubmitPeer/SubmitDirect` with explicit route resolution and service/timing mapping.
2. Implement R9-07 bounded generation-safe Radio terminal-result correlation and conservative evidence mapping; destination M1 receipt must remain separate from link evidence.
3. Validate exact host contracts and promote only green workflow evidence here.
4. Continue R9-08..R9-11 Event/Command/State direct Radio and restart lifecycle.
5. Maintain this file after every material checkpoint and before every stop; regenerate the synchronized downloadable handoff with every user response.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
