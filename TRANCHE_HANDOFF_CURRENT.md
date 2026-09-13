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
- Radio `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`.

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

The family-neutral lease/correlation seam protects outstanding direct-Radio semantic campaigns from transfer-ID reuse within one live Radio runtime. It does not interpret correlation as Primitive admission and does not claim restart-incarnation protection.

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
- `RadioAdapters ingress contracts` `34771857945` — SUCCESS;
- `RadioAdapters outbound contracts` `34771857991` — SUCCESS;
- `RadioAdapters redesign contracts` `34771857946` — SUCCESS;
- `RadioAdapters exact M1 contracts` `34771857903` — SUCCESS;
- `RadioAdapters Event direct-Radio contracts` `34771858014` — SUCCESS;
- `RadioAdapters Command direct-Radio contracts` `34771857995` — SUCCESS.

Implemented Command direct-Radio composition:

1. `src/ESPressio_CommandRadioAdapterBinding.hpp`
   - one frozen Command family binding through real A2;
   - fixed per-Type configuration only;
   - canonical Command request/response wire remains Command-owned;
   - inbound execution, durable terminal ledger, replay/idempotency and response semantics remain in the real Command runtime;
   - no second executor/runtime/ledger, response worker, retry queue or alternate wire format.

2. Semantic route boundary
   - `RadioAdapterSemanticRouteBinding` resolves `DeviceIdentifier -> AdapterRouteToken` at composition scope;
   - route tokens remain opaque transport facts and are never hashes/truncations of semantic identity;
   - the same seam is intentionally reusable by State R9-10.

3. Provenance
   - trusted Radio ingress resolves a validated `OriginalSource` before A2 handoff;
   - Command family parses the wire-carried request origin / response executor and requires exact equality with that validated source;
   - physical Radio peer is never treated as Command semantic identity;
   - family descriptor intentionally does **not** falsely claim lower-transport `ProvidesValidatedOriginalSource`, because Radio outbound lower transport does not authenticate ingress.

4. Response-bearing delivery / exact M1
   - bounded generation-safe request campaign retains only `CommandRequestDeliveryToken` + required-evidence fact;
   - Radio terminal failure without required M1 produces `RequestDeliveryFailed`;
   - exact `Accepted` M1 preserves the requester until the actual response arrives;
   - generated executor response returns through A2/direct Radio;
   - duplicate-terminal request maps `AlreadyAccepted` without a second handler execution.

5. Durable recovered response
   - `ReserveRecoveredResponse<TCommand>()` reserves the semantic return route before freeze/A2 start;
   - recovery test seeds a persistent terminal result, starts a new local runtime incarnation, and proves the persisted result is emitted through direct Radio to the original requester without handler re-execution.

6. Host contracts
   - `command_radio_adapter_contract_test.cpp`: local request egress, trusted remote request execution, wrong service and forged source rejection;
   - `command_radio_adapter_m1_test.cpp`: real R9-07 M1 controller, terminal delivery failure, exact M1 success, remote response, generated response and duplicate/idempotency;
   - `command_radio_adapter_recovered_response_test.cpp`: durable recovered-response route and payload proof.

7. Public surface / dependency proof
   - `ESPressio_RadioAdapters.hpp` exports the Command binding alongside Event;
   - umbrella-consuming workflows explicitly include both family dependency graphs instead of succeeding only through narrow private-header includes;
   - RadioAdapters currently has no `library.json` / `library.properties` manifest at repo root, so no metadata was invented during R9-09.

## Active continuation — R9-10 State direct-Radio binding

Source-first State baseline:
- `ESPressio-State/primitives_redesign` `25637a7555e3a03f1d709bd8e37340bc4d545b6e`.

Confirmed current State transport lifecycle:
- `StateTransportBinding` exposes semantic-only `StateOutboundMessage<TState>` plus immutable `StateTransportContract` and bounded `Admit/Validate/Wake` thunks;
- `Runtime::Initialize()` prepares Type runtimes, but transport validation occurs at `Runtime::Start()` through `StateTypeRuntime::ValidateStart()`;
- therefore direct-Radio `ValidateTransport` must remain valid **after family freeze**; freeze controls mutation/admission, not validity of the immutable configured transport contract;
- `Wake()` must only coalesce service work and must never service inline during State mutation;
- State remains sole owner of sessions, versions, baseline/resync, convergence/NeedsConvergence and latest-truth semantics.

R9-10 implementation direction:
- port only the proven composition shape from `StateMeshAdapterFamilyBinding`, replacing Mesh route/service facts with `RadioAdapterSemanticRouteBinding` and `AdapterServiceClass`;
- inbound direct-Radio State must validate wire-carried semantic source against trusted Radio `OriginalSource` before `Runtime::AdmitRemote`;
- outbound destination Device resolves to an opaque Radio route token; canonical State V1 encoding remains State-owned;
- bounded convergence campaign retains only generation/type/`StateConvergenceHandle`; A2 owns pursuit;
- terminal insufficient evidence reports exhaustion back through the real State runtime and allows State to enter its own `NeedsConvergence` behavior;
- no broadcast semantics, second State runtime, replica/session table, family-local retry worker or duplicate convergence engine in RadioAdapters;
- generic exact M1 path supplies `DestinationPrimitiveAdmission` when the State convergence policy requires it.

## Remaining Tranche-9 order

- R9-08 Event direct-Radio — CLOSED;
- R9-09 Command direct-Radio — CLOSED;
- R9-10 State direct-Radio — ACTIVE;
- R9-11 restart/shutdown/stale-completion hardening;
- R9-12..R9-16 ESP-NOW migration/predecessor removal;
- R9-17..R9-19 Sockets neutral transport/session migration;
- R9-20 Serial classification/migration;
- R9-21..R9-22 WiFi migration;
- R9-23 hardening;
- R9-24 dependency/manifests/accounting;
- R9-25 documentation/integration closure.

## Immediate continuation

1. Reuse the proven Mesh State binding only as a composition reference; source truth is current State `25637a7555e3a03f1d709bd8e37340bc4d545b6e` and current RadioAdapters.
2. Implement `ESPressio_StateRadioAdapterBinding.hpp` with fixed per-Type entries, semantic route resolution, trusted-source validation, canonical State V1 encode/decode and bounded convergence campaign feedback.
3. Add focused real-State inbound/outbound host contracts before exporting State through the public umbrella.
4. Prove destination-admission failure drives real State convergence exhaustion / `NeedsConvergence`; prove trusted inbound State mutates only through the real State runtime and forged source fails closed.
5. Once focused State gates are green, export State through `ESPressio_RadioAdapters.hpp`, make umbrella workflow dependency graphs explicit, then promote only an exact-tip all-green R9-10 checkpoint.
6. Maintain this file after every material checkpoint and regenerate the synchronized downloadable handoff with every user response.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
