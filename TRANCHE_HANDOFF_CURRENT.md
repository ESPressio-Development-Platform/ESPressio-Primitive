# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. The Revision 102 architecture handoff remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical evidence. Live `primitives_redesign` branch tips are implementation truth and MUST be rebaselined before every new implementation tranche.

## Authorization boundary

Implementation is authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags, releases, Wiki publication, force pushes and backward-compatibility shims remain outside this authorization. Tranche 12 remains separately consequential.

## Locked non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning.
- Only family `Accepted` / `AlreadyAccepted` establishes `DestinationPrimitiveAdmission`; adapter ownership, Radio transmit completion and peer ACK never do.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio composition layer that simultaneously understands Radio and Primitive families; generic Adapters remains Radio-neutral.
- Immediate physical peer and validated semantic `OriginalSource` are distinct provenance facts.
- Never hash, pack or truncate semantic identity into `AdapterRouteToken`.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology is fixed before Running; bounded storage and nonblocking ingress remain mandatory.
- Every neutral non-Mesh transport binding has a finite lifecycle/generation. Restart invalidates prior handles/correlation; late callbacks/completions must never become current work.
- Shutdown rejects new work, quiesces ingress, releases volatile transport capacity, waits only already-executing bounded work and never force-kills application execution.
- Temporary backpressure/disconnection/restart must not create unbounded retry.
- RadioTransport-v3 wire and the exact four-byte RadioAdapters Primitive prefix remain locked.
- No structural-Tranche-9 version changes.

## Closed structural tranches

Foundation F01–F08 and structural Tranches 2–8 are CLOSED.

Tranche 8 final evidence remains:
- Mesh closure `5f36b51f6ce570e97e4f95f975f039d61e2287cd`; workflows `34753038491`, `34753038532`, `34753038454` SUCCESS.
- Mesh formal report `TRANCHE_8_CLOSURE.md` at `a832ce41c7ebd6174c7a06835ea24a871f843dcc`.
- MeshAdapters final `ce0a745498216248279aafc70d6603e49b10a6ab`; combined `34753328372`, State `34753328259`, recovered Command `34753328297` SUCCESS.

## Tranche 9 — ACTIVE

Authoritative sequence is Architecture §30 R9-01..R9-25.

Original non-Mesh baseline tips before R9 implementation:
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

Service class remains out-of-band and explicitly mapped.

### R9-02 / R9-03 — CLOSED; GREEN

Exact four-byte codec and six-way `AdapterServiceClass` <-> `RadioServiceClass` mapping.
- RadioAdapters `3d3f1ed6a9bfdcc52fec2df385d37c71578d9bf2`;
- workflow `34753638473` SUCCESS.

### R9-04 / R9-05 — CLOSED; GREEN

Frozen direct-Radio demux/policy registry and trusted Radio -> A2 handoff.
- RadioAdapters `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`;
- ingress `34755161807`, redesign `34755161844` SUCCESS.

### Neutral A2 lower-transport metadata seam — CLOSED; GREEN

Adapters `4c22db73063041a488e497b75be903a98a89196a` carries neutral record/family/protocol/policy/service/bytes/route metadata to lower transports while remaining Radio-neutral.

MeshAdapters compatibility checkpoint `f861d96ecddb14a9242f444174fb0248da9bab88`; State `34756179342`, recovered Command `34756179358`, combined `34756179363` SUCCESS.

### R9-06 outbound — CLOSED; GREEN

RadioAdapters `819a2cd5e6f3dcec589d3dd586e5cc5ba1c54525`; outbound `34755755309`, ingress `34755755291`, redesign `34755755273` SUCCESS.

### R9-07 Radio correlation substrate — CLOSED; GREEN

Radio `84c6bbcac36d959378dcc69366bc18921298c257`; redesign `34764194951`, transfer-ID lease `34764194938` SUCCESS.

### R9-07 exact M1 — CLOSED; GREEN

RadioAdapters `0e72a10f0034820e8bc8e0e72166bee9731b972e`; redesign `34768426144`, exact M1 `34768426012`, ingress `34768426030`, outbound `34768426102` SUCCESS.

`ESPressio_RadioAdapterM1.hpp` owns the bounded exact-M1 control path `{Family=0, Protocol=1}`. Radio completion/peer ACK remains direct-link evidence only.

### R9-08 Event direct-Radio — CLOSED; GREEN

RadioAdapters `a8092a2d914f7a0abf1a35c005e105f3c7d5a650`; ingress `34769579671`, outbound `34769579684`, redesign `34769579653`, exact M1 `34769579682`, Event `34769579729` SUCCESS.

Event uses one frozen family binding, canonical Event V1, real Event runtime admission/idempotency/source-loop semantics and the generic A2/M1 lower path. No second Event runtime.

### R9-09 Command direct-Radio — CLOSED; GREEN

RadioAdapters `984731e214affdfb1152e0d9cf9bdb01b0e36a75`; ingress `34771857945`, outbound `34771857991`, redesign `34771857946`, exact M1 `34771857903`, Event `34771858014`, Command `34771857995` SUCCESS.

Command direct-Radio includes exact provenance checks, bounded response-bearing request correlation, existing `RequestDeliveryFailed`, duplicate `AlreadyAccepted` without handler re-execution, and durable recovered-response routing through the same A2/direct-Radio lane.

### R9-10 State direct-Radio — CLOSED; GREEN

RadioAdapters `285b184ffd84ddb1e97c4292154010c613eaa735`.

Exact-tip workflows all SUCCESS:
- ingress `34772597924`;
- outbound `34772597753`;
- redesign `34772597861`;
- exact M1 `34772597866`;
- Event `34772597831`;
- Command `34772597748`;
- State `34772597901`.

State direct-Radio uses one frozen A2 family binding, canonical State V1, post-freeze-valid transport validation, semantic route resolution, trusted semantic provenance, exact duplicate `AlreadyAccepted`, and real State convergence exhaustion/`NeedsConvergence`. Full Radio -> RadioAdapters -> A2 -> State ingress is proven. State is exported through the public umbrella.

### R9-11 generation-safe restart/shutdown/stale completion — CLOSED; GREEN

Final promoted RadioAdapters checkpoint:
- `fd34d0e91f5aed61476792e2bad39bbcacaed39b` (`Add RadioAdapters lifecycle restart gate`).

Exact-tip workflows — all SUCCESS:
- ingress `34774777059`;
- outbound `34774777129`;
- redesign `34774777106`;
- exact M1 `34774777090`;
- Event `34774777107`;
- Command `34774777045`;
- State `34774777083`;
- lifecycle restart `34774777147`.

Implemented R9-11 lifecycle contract:

1. `RadioAdapterM1Controller`
   - explicit active/quiesced lifecycle;
   - non-wrapping lifecycle generation;
   - fixed-capacity recent `(contention-domain, RadioTransferId)` exclusion window retained across controlled restart;
   - all volatile attempts cleared on quiesce;
   - old A2 completion target detached;
   - late Radio terminal result and late M1 receipt while inactive are diagnostic/no-op;
   - replacement Radio/A2 may be rebound only while quiesced;
   - no wire-generation field, heap state, retry worker or polling loop was added.

2. `RadioAdapterLowerTransport`
   - explicit non-zero lifecycle generation;
   - quiesce publishes rejection first, waits only any current synchronous workspace holder, then quiesces M1;
   - submit rechecks quiesce after workspace acquisition so a shutdown race cannot enter a replacement lifecycle;
   - restart is legal only from Quiesced, requires an already-running replacement Radio runtime, validates immutable route/policy bindings, advances generation without wrap and owns no retry.

3. `RadioAdapterReassemblyIngress`
   - explicit lifecycle generation and quiesce boundary;
   - quiesce waits only the currently executing bounded bridge quantum and clears all volatile pending-receipt records while preserving their slot generations;
   - restart rebinds A2 and advances generation;
   - old A2 completion after restart cannot emit an M1 receipt into the replacement lifecycle;
   - completed reassembly arriving after quiesce is released without entering family/A2 execution.

4. Transfer-ID safety without wire changes
   - exact four-byte Primitive prefix unchanged;
   - exact eight-byte direct-Radio M1 receipt unchanged;
   - RadioTransport-v3 unchanged;
   - a fresh Radio scheduler may restart its local uint16 issuer, but the persistent finite M1 exclusion window rejects recently used old-lifecycle IDs until they age out of the configured bounded window;
   - active attempts remain protected independently of the recent window.

5. Dedicated permanent workflow
   - `.github/workflows/lifecycle.yml` compiles/runs lower-transport lifecycle, M1 stale correlation and ingress stale-receipt contracts under `-Wall -Wextra -Werror -fno-rtti`.

Radio itself remains `84c6bbcac36d959378dcc69366bc18921298c257`; R9-11 required no Radio wire/runtime change.

## Active continuation — R9-12 ESP-NOW final managed-provider role

Source-first ESP-NOW tip at activation remains:
- `ESPressio-ESP-Now/primitives_redesign` `56e4f4023c68468c49229fcff85e55a7cbc6b8e6`.

Authoritative Architecture §30.4 target:

```text
ESP-NOW retained as bearer/provider-specific functionality:
    physical address / MTU / capabilities
    finite ingress
    finite conservative cost
    nonblocking send admission/readiness
    terminal completion and peer-ACK evidence only where genuinely proven
    provider-proximate receive timestamp evidence/uncertainty only where genuinely characterized
    peer/security/channel mechanics specific to ESP-NOW

Radio v3 owns logical fragmentation/reassembly.
RadioAdapters owns family prefix/bindings.
A2 owns family ingress/outbound execution resources.
```

Current live ESP-NOW audit at activation:
- `ESPNowTransport` is still the predecessor protocol-multiplexing transport, not the final Radio `IRadio` provider;
- it owns an ESP-NOW-specific `WireHeader`, protocol-handler graph, dynamic/fixed abstraction storage, Observable surface, `PrecisionThread` worker, receive queue and maintenance handlers;
- `ESPNowEventTransport` still owns a second Event fragmentation/reassembly runtime and dedicated execution;
- bespoke Command transport remains;
- `ESPNowClockSynchronizer` remains predecessor T1/T2/T3/fixed-cadence clock logic;
- `ESPNowTypes.hpp` still directly includes Timing clock synchronization and exposes family protocol identifiers;
- these are migration inputs for R9-12..R9-16, not compatibility contracts to preserve.

R9-12 must introduce/define the final ESP-NOW managed physical-provider contract without yet pretending the predecessor Event/Command/clock stacks are canonical. It must preserve honest physical evidence and finite provider-owned resources. ESP-NOW send acceptance is not automatically peer acknowledgement or Primitive admission.

## Remaining Tranche-9 order

- R9-08 Event direct-Radio — CLOSED;
- R9-09 Command direct-Radio — CLOSED;
- R9-10 State direct-Radio — CLOSED;
- R9-11 restart/shutdown/stale-completion hardening — CLOSED;
- R9-12 ESP-NOW managed-provider role/capabilities/cost/evidence — ACTIVE;
- R9-13 remove ESP-NOW Event-specific fragmentation/reassembly/TaskExecutor transport;
- R9-14 remove ESP-NOW bespoke Command family transport where superseded;
- R9-15 migrate ESP-NOW direct clock exchange to Radio/Timing K1/K2 ownership;
- R9-16 remove superseded ESP-NOW Event/Command/Observable/Thread dependency surfaces;
- R9-17..R9-19 Sockets neutral transport/session migration;
- R9-20 Serial classification/migration;
- R9-21..R9-22 WiFi migration;
- R9-23 hardening/fuzz/congestion/restart/stale-handle/evidence cross-transport tests;
- R9-24 manifests/workflows/dependency guards/resource accounting;
- R9-25 README/source comments/tranche-wide integration closure.

## Immediate continuation

1. Audit the exact live ESP-NOW native callback/send/peer/channel surfaces against current `Radio::IRadio` and provider-contract requirements.
2. Implement the final ESP-NOW managed provider as opaque physical-byte transport, not by carrying the predecessor ESP-NOW protocol header above Radio v3.
3. Publish honest `RadioCapabilities`, one stable non-zero contention-domain identity, finite `RadioProviderResourceProfile`, nonblocking readiness/send admission and conservative finite transmission cost.
4. Treat native `esp_now_send()` acceptance only as deferred physical submission; map native send completion generation-safely and claim peer ACK only if the ESP-NOW native completion semantics genuinely establish it. Otherwise advertise/return only `TransmissionCompletion`.
5. Queue native receive frames into fixed finite ingress ownership; capture receive monotonic time at the provider callback and classify uncertainty conservatively until physically characterized; no false Clock certification.
6. Add focused host/native-boundary contract tests and a permanent provider workflow before calling R9-12 complete.
7. Then continue R9-13..R9-16 predecessor removal and dependency cleanup without permission pauses.
8. Update this file after every material checkpoint and regenerate the synchronized downloadable handoff at stable checkpoints.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 release preparation remains separate and unauthorized.
