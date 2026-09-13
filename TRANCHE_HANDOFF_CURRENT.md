# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The authoritative architecture handoff remains controlling for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. This file records current implementation truth and the exact next continuation point.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases and Wiki publication remain outside this authorization.

## Locked ownership and non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Mesh owns authenticated membership, topology, routing/forwarding/Broadcast and Mesh application lifecycle.
- Radio/R3 owns physical fragmentation/reassembly/arbitration.
- Timing owns clock estimation/discipline/uncertainty/reliability; Mesh owns only clock root/parent/reference topology selection.
- Primitive family runtimes own exact M1 semantics.
- Only family `Accepted`/`AlreadyAccepted` establishes `DestinationPrimitiveAdmission`.
- Adapter queue ownership is never M1 `Accepted`.
- Immediate transport peer and original semantic source are independent provenance facts.
- Never derive System runtime incarnation from Mesh membership incarnation.
- Never pack/truncate semantic identity into route tokens.
- No family-local retry worker, retry queue or fragmentation architecture.
- Direct-link transmission/peer ACK evidence never becomes destination Primitive admission.
- Radio core remains Primitive-family-neutral; generic Adapters remains Radio-neutral.
- No version change in structural Tranche 9.

## Closed structural tranches

Foundation F01–F08 and structural Tranches 2–8 are CLOSED.

### Tranche 8 final evidence

Mesh M8-23 green checkpoint: `5f36b51f6ce570e97e4f95f975f039d61e2287cd`.
- Tranche-8 Mesh closure workflow `34753038491` — SUCCESS.
- Mesh redesign workflow `34753038532` — SUCCESS.
- Mesh clock/runtime workflow `34753038454` — SUCCESS.

Formal Mesh closure report: `ESPressio-Mesh/TRANCHE_8_CLOSURE.md` at `a832ce41c7ebd6174c7a06835ea24a871f843dcc`.

Final MeshAdapters integration checkpoint: `ce0a745498216248279aafc70d6603e49b10a6ab`.
- combined workflow `34753328372` — SUCCESS;
- State workflow `34753328259` — SUCCESS;
- recovered Command workflow `34753328297` — SUCCESS.

## Tranche 9 — ACTIVE: RadioAdapters and non-Mesh transports

Authoritative implementation sequence is R9-01..R9-25 from Architecture section 30.

Source-first baseline heads before Tranche-9 writes:
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

Service class remains out-of-band and explicitly mapped. Physical/direct peer is distinct from validated semantic original source.

### R9-02 / R9-03 — CLOSED; GREEN

Exact four-byte RadioAdapter codec and explicit six-way `AdapterServiceClass` <-> `RadioServiceClass` mapping are implemented. The codec is policy-free; unsupported family/version is a frozen-registry concern.

Foundation checkpoint:
- RadioAdapters `3d3f1ed6a9bfdcc52fec2df385d37c71578d9bf2`;
- workflow `34753638473` — SUCCESS.

### R9-04 / R9-05 — CLOSED; GREEN

Promoted RadioAdapters ingress checkpoint:
- `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`;
- ingress workflow `34755161807` — SUCCESS;
- redesign workflow `34755161844` — SUCCESS.

Implemented frozen Radio-specific demux/policy registry and trusted Radio -> A2 handoff. Radio owns the complete trusted logical-message lease until bridge entry; RadioAdapters strips only the four-byte prefix, resolves policy/provenance, and A2 synchronously copies accepted family bytes. Trusted physical peer creates `ImmediatePeer` only and never automatically creates semantic `OriginalSource`.

### Neutral A2 lower-transport metadata seam — CLOSED; INTEGRATION GREEN

Current Adapters tip:
- `4c22db73063041a488e497b75be903a98a89196a`.

`LowerTransportSubmitThunk` now carries neutral A2-owned metadata required by direct transports:
- `AdapterRecordIdentity`;
- `PrimitiveFamilyId`;
- `PrimitiveProtocolVersion`;
- immutable `PrimitivePolicyDescriptor`;
- `AdapterServiceClass`;
- `AdapterByteView`;
- `AdapterRouteToken`.

Generic Adapters remains Radio-neutral. MeshAdapters accepts and intentionally ignores the additive family/version/policy fields because Mesh owns its own application framing/lifecycle.

Promoted MeshAdapters compatibility checkpoint:
- `f861d96ecddb14a9242f444174fb0248da9bab88`;
- State workflow `34756179342` — SUCCESS;
- recovered Command workflow `34756179358` — SUCCESS;
- combined workflow `34756179363` — SUCCESS.

### R9-06 — CLOSED; GREEN

Promoted RadioAdapters outbound checkpoint:
- `819a2cd5e6f3dcec589d3dd586e5cc5ba1c54525`;
- outbound `34755755309` — SUCCESS;
- ingress `34755755291` — SUCCESS;
- redesign `34755755273` — SUCCESS.

`ESPressio_RadioAdapterLowerTransport.hpp` provides:
- opaque `AdapterRouteToken` -> generation-safe `RadioPeerHandle` resolution;
- composition-owned finite `RadioServiceProfile` + `RadioTransferTiming` policy resolution;
- bounded synchronous framing workspace;
- exact four-byte prefix + immutable family representation;
- one `RadioRuntime::SubmitPeer(...)` logical-transfer admission;
- no RadioAdapter worker/retry queue/retained payload/fragmentation engine;
- atomic quiesce state.

### R9-07 Radio correlation substrate — CLOSED; GREEN

Radio remains family-neutral. A bounded transfer-ID lease/correlation seam was added only to protect outstanding direct-Radio semantic campaigns from transfer-ID reuse inside one Radio runtime lifetime.

Promoted Radio checkpoint:
- Radio `84c6bbcac36d959378dcc69366bc18921298c257`;
- full redesign `34764194951` — SUCCESS;
- dedicated transfer-ID lease contract `34764194938` — SUCCESS.

The substrate provides:
- optional `RadioTransferIdLeaseTarget` with fixed `IsReserved`, `ReserveIssued`, `ReleaseIssued` thunks;
- scheduler issuance excluding active/recent/external leased IDs;
- optional opaque 64-bit submission correlation;
- reservation of `{contention-domain, transfer-id}` under scheduler mutation lock before queue publication;
- rollback if queue publication fails;
- zero-correlation compatibility with established schedulers;
- non-zero correlation fails closed against a scheduler that does not expose the lease-aware submit.

Radio never interprets the correlation as Primitive admission. Radio terminal/link completion does not release the external lease and never establishes M1.

### R9-07 RadioAdapters exact M1 receipt — CLOSED; GREEN

Final promoted RadioAdapters checkpoint:
- `0e72a10f0034820e8bc8e0e72166bee9731b972e` (`Account saturation M1 receipt sends`).

Exact permanent workflows at that tip:
- `RadioAdapters redesign contracts` `34768426144` — SUCCESS;
- `RadioAdapters exact M1 contracts` `34768426012` — SUCCESS;
- `RadioAdapters ingress contracts` `34768426030` — SUCCESS;
- `RadioAdapters outbound contracts` `34768426102` — SUCCESS.

Implemented exact-M1 surfaces:

1. `src/ESPressio_RadioAdapterM1.hpp`
   - RadioAdapters-owned control namespace `{Family=0, Protocol=1}`; family zero remains invalid for ordinary Primitive dispatch.
   - Fixed eight-byte receipt: four-byte control prefix + little-endian original Radio transfer ID + exact M1 disposition + reserved zero byte.
   - Fixed bounded generation-safe attempt table.
   - Exact route/contention-domain/transfer-ID matching.
   - Implements the Radio transfer-ID lease target so an outstanding semantic attempt keeps its Radio transfer ID excluded from reuse.
   - Radio terminal/link callbacks store bounded completion state and signal a composition wake only; a later bounded `ServiceOne()` completes A2. No callback recursively executes A2 pursuit.
   - Record-keyed cancellation releases outstanding attempt state.

2. `src/ESPressio_RadioAdapterLowerTransport.hpp`
   - `NoRemoteEvidence` occurrences preserve the R9-06 immediate correlation-zero path.
   - `DestinationPrimitiveAdmission` occurrences reserve an M1 attempt, submit Radio with opaque correlation, and return deferred completion to A2.
   - Radio transmission/peer ACK is lower evidence only; the attempt remains pending until exact M1 receipt or terminal policy/cancellation outcome.

3. `src/ESPressio_RadioAdapterIngress.hpp`
   - `{Family=0,Protocol=1}` receipts are intercepted before family demux and can never recursively create another receipt.
   - Ordinary direct-Radio data reserves a fixed pending-receipt context containing only provider/source/transfer/service/generation facts; no family bytes or retry state are retained.
   - A2 exact family completion emits exactly one receipt carrying the original Radio transfer ID and exact family admission.
   - Immediate Unsupported/Malformed/Rejected/temporary/resource outcomes map to exact M1 receipt without pretending A2 accepted work.
   - Pending-receipt saturation emits `ResourceUnavailable` and does not admit a second occurrence to A2.
   - Ingress diagnostics touched across Radio-ready/A2-completion contexts use relaxed atomics.

4. Host contracts
   - `radio_adapter_m1_test.cpp`: receipt codec/controller, spoof mismatch, terminal failure, duplicate/late receipt rejection, record cancellation, non-recursive receipt send.
   - `radio_adapter_lower_transport_test.cpp`: mixed P2 proof: `NoRemoteEvidence` immediate/correlation-zero versus destination-admission deferred M1.
   - `radio_adapter_m1_ingress_integration_test.cpp`: real Radio reassembly table -> RadioAdapter ingress -> A2 semantic completion -> exact receipt; bounded pending-context saturation; immediate Unsupported; control receipt interception/non-recursion.

R9-07 does **not** claim restart/runtime-incarnation stale-packet safety. That remains R9-11. The current generation/lease proof covers one live Radio runtime lifetime only.

## Active continuation — R9-08 Event direct-Radio binding

R9-08 is next. The implementation must reuse the existing Event family/A2 binding and the generic direct-Radio transport surfaces above. RadioAdapters must not create a second Event runtime, Event retry loop, Event queue, or Event wire protocol.

Required proof direction:
- local Event dispatch -> existing Event external/A2 encoder -> direct-Radio lower transport -> exact four-byte RadioAdapter prefix + canonical Event family wire;
- trusted direct-Radio Event -> RadioAdapter ingress -> A2 -> existing Event runtime admission/dispatch;
- remote-origin Event must retain Event-owned source-loop suppression and must not re-egress;
- Event P2 evidence policy is honored generically: NoRemoteEvidence uses lower evidence; destination-admission policy uses the closed R9-07 exact-M1 path.

## Remaining Tranche-9 order

- R9-08 Event direct-Radio binding — ACTIVE NEXT;
- R9-09 Command direct-Radio binding;
- R9-10 State direct-Radio binding;
- R9-11 restart/shutdown/stale-completion hardening;
- R9-12..R9-16 ESP-NOW migration/predecessor removal;
- R9-17..R9-19 Sockets neutral transport/session migration;
- R9-20 Serial classification/migration;
- R9-21..R9-22 WiFi migration;
- R9-23 hardening;
- R9-24 dependency/manifests/accounting;
- R9-25 documentation/integration closure.

## Immediate continuation

1. Source-first revalidate `ESPressio-Event/primitives_redesign` and current RadioAdapters tip.
2. Read the locked R9-08 architecture package and map Event's existing A2 binding/encoder/admission seams onto the generic RadioAdapter registry/lower transport.
3. Implement only the minimal Event-to-RadioAdapter composition binding required to select frozen service/policy/provenance/topology; do not duplicate Event runtime semantics.
4. Add real host contracts for local Event egress, remote Event ingress/dispatch, source-loop suppression, and evidence-policy selection.
5. Promote only green R9-08 evidence here, then continue R9-09 Command.
6. Maintain this file after every material checkpoint and regenerate the synchronized downloadable handoff with every user response.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
