# Tranche 9 — Transport / Adapter Resource Accounting

Date: 2026-09-14
Scope: Structural Tranche 9 R9-24 manifest, workflow, dependency and bounded-resource accounting.

This document records the finite-capacity contracts that are already enforced by production Types and tests. It is not a release document and does not change any library version. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for architecture and governance.

## 1. Accounting rules

The Tranche-9 transport plane is accepted only when all canonical hot paths are bounded by construction. A transport/provider may expose a compile-time or composition-time finite capacity, but it may not substitute an unbounded queue, hidden retry worker, growable retained-work collection, compatibility executor, or family-local fragmentation/reassembly runtime.

The ownership split is:

- Primitive families own family semantics, representations and exact admission meaning.
- `ESPressio-Adapters` A2 owns admitted Primitive-family bytes/records, retained pursuit and finite T1 workers.
- `ESPressio-Radio` owns physical scheduling, fragmentation/reassembly, physical transfer identity and direct-link evidence.
- `ESPressio-RadioAdapters` owns only the direct Radio ↔ Primitive composition seam, exact four-byte family prefix, route/provenance/service mapping and exact-M1 correlation.
- `ESPressio-ESP-Now` owns only the ESP-NOW physical provider.
- `ESPressio-Sockets` owns only bounded neutral socket/session framing and exact-M1 carriage, plus genuine socket Security/Timing mechanics.
- Serial and WiFi have no canonical device-to-device Primitive transport in Tranche 9; no artificial capacity table is invented for a transport that does not exist.

## 2. Generic A2 — `ESPressio-Adapters`

Canonical Type:

```text
AdapterRuntime<
  TInboundCapacity,
  TOutboundCapacity,
  TMaximumBindings,
  TQueueDepth,
  TInboundWorkers,
  TOutboundWorkers,
  TMaximumRetained,
  TMaximumRequirements
>
```

Finite resources:

| Resource | Bound / owner |
|---|---|
| Inbound owned bytes/records | `TInboundCapacity` |
| Outbound owned bytes/records | `TOutboundCapacity` |
| Frozen family bindings | `TMaximumBindings` |
| Runtime queue depth | `TQueueDepth` |
| Inbound T1 workers | `TInboundWorkers` |
| Outbound T1 workers | `TOutboundWorkers` |
| Retained pursuit records | `TMaximumRetained` |
| Frozen capacity requirements | `TMaximumRequirements` (default 16) |

A2 owns the admitted byte/record lifetime. Inbound and outbound capacity planes are independent. The canonical runtime requires no post-Initialize heap fallback on its hot paths and exposes nonblocking ownership handoffs to families and lower transports.

Dependency boundary at `Adapters/primitives_redesign` `4c22db73063041a488e497b75be903a98a89196a`:

- package dependencies: System + Primitive + Task;
- no Radio dependency;
- no transport-family dependency.

## 3. Direct-Radio composition — `ESPressio-RadioAdapters`

### 3.1 Lower transport workspace

Canonical Type:

```text
RadioAdapterLowerTransport<TRadioRuntime, TMaximumLogicalMessageBytes>
```

Finite resources:

- exactly one fixed synchronous byte workspace of `TMaximumLogicalMessageBytes`;
- one try-lock protects that workspace;
- workspace contention returns `TemporarilyUnavailable`; it never creates a hidden queue;
- no retained payload, retry queue, family object, fragment table or worker;
- one finite non-wrapping lifecycle generation invalidates prior-lifecycle work across controlled restart.

The workspace adds exactly the locked four-byte direct-Radio prefix before the unchanged family representation.

### 3.2 Exact-M1 correlation

Canonical Type:

```text
RadioAdapterM1Controller<
  TRadioRuntime,
  TMaximumAttempts,
  TRecentTransferIds = TMaximumAttempts
>
```

Finite resources:

| Resource | Bound |
|---|---:|
| Active destination-admission attempts | `TMaximumAttempts` |
| Recent `(contention-domain, transfer-id)` restart exclusion entries | `TRecentTransferIds` |
| A2 completion retained per attempt | at most 1 |
| Local retry workers / queues | 0 |

The recent-ID exclusion window is fixed and allocation-free. Radio terminal/link evidence never completes M1; only an exact destination admission receipt can establish the destination-admission evidence required by policy.

### 3.3 Reassembly ingress receipt correlation

Canonical Type:

```text
RadioAdapterReassemblyIngress<
  TReassemblyTable,
  TAdapterRuntime,
  TMaximumBindings,
  TMaximumPendingReceipts = TMaximumBindings
>
```

Finite resources:

- `TMaximumPendingReceipts` pending receipt slots;
- each slot has its own generation token plus transport lifecycle generation;
- quiesce clears transport-owned volatile receipt slots;
- stale old-lifecycle completion cannot emit a receipt in a replacement lifecycle.

### 3.4 Validation checkpoint

R9-23 exact RadioAdapters checkpoint:
`29b7889bc1c1527b5830b223e8ae880c6c27e1ab`

All eight permanent gates were SUCCESS:

- lifecycle `34811500875`
- Command `34811500964`
- exact M1 `34811500882`
- State `34811500883`
- outbound `34811500894`
- ingress `34811500967`
- redesign `34811500932`
- Event `34811500917`

The adversarial M1 gate covers all seven exact dispositions, malformed control bytes, wrong route/domain/transfer identity, direct-link ACK non-establishment, stale lifecycle suppression and recent transfer-ID exclusion.

## 4. Radio provider contract — `ESPressio-Radio`

`IRadio` requires every physical provider to expose `RadioProviderResourceProfile`:

```text
MaximumQueuedInboundPackets
MaximumInboundPacketsPerService
MaximumQueuedTransmitPackets
MaximumProviderRetryAttempts
```

`MaximumInboundPacketsPerService != 0` is required for a finite ingress service quantum. `ServiceInbound(0)` means “use the provider's declared finite quantum”; zero never means unbounded.

Every provider also exposes a finite positive physical transmission cost and one non-zero contention-domain identity. An accepted physical transmission must either return terminal completion immediately or one generation-safe deferred handle completed exactly once through the Radio runtime sink.

Radio branch checkpoint:
`84c6bbcac36d959378dcc69366bc18921298c257`

The Radio core remains Primitive-family-neutral.

## 5. ESP-NOW provider — `ESPressio-ESP-Now`

Canonical provider:

```text
ESPNowRadio : Radio::IRadio
```

Provider resource bounds:

| Resource | Bound |
|---|---:|
| Native address bytes | 6 |
| RX queue slots | `ESPRESSIO_ESPNOW_RADIO_RX_QUEUE_DEPTH`, default 16 |
| RX index range | compile-time limited to <=255 slots |
| Outstanding native transmit packets | exactly 1 |
| Provider-local retry queue | 0 |
| Provider application/family worker | 0 |
| Per-generation transmission sequence | 22 bits, finite |
| Lifecycle generation | finite high-bit generation, no wrap acceptance |
| Native physical payload | `ESP_NOW_MAX_DATA_LEN` |
| Radio logical transfer maximum represented by provider contract | 58,395 bytes |

Evidence/cost constraints:

- `esp_now_send()==ESP_OK` is provider submission acceptance only.
- terminal send completion is deferred to the native callback.
- successful unicast callback can establish direct-link/MAC peer acknowledgement only.
- broadcast success cannot establish peer acknowledgement.
- neither physical result establishes Primitive admission.
- receive timing is `Estimated` unless an explicit provider-proximate finite-bounded capture binding supplies a valid immutable Timing model snapshot.
- transmission cost remains RelativeOnly/non-promotable unless composition explicitly supplies a conservative finite native-attempt/cost model.

Final source/package boundary before the R9-24 CI guard:
`9792c5cc7f10aa00bdf5830d4e973a26b3eb7128`

R9-24 manifest/CI guard checkpoint:
`04b21963aa461cd1a5a0ec977e1f60278d2df4b9`

Package dependencies are System + Radio only. Versions remain unchanged (`0.8.3`).

The provider workflow itself contains executable assertions for six-byte addressing, finite ingress service, exactly one queued TX, valid conservative cost shape, non-promotable default cost and the shared ESP32 Wi-Fi contention-domain identity. At the R9-24 guard checkpoint, GitHub Actions still failed before runner allocation (`steps=null`) for Tests `34814293042` and provider `34814293069`; these are infrastructure-blocked runs and are not code-test failures.

## 6. Neutral Sockets A2 lower transport — `ESPressio-Sockets`

Canonical Type:

```text
SocketAdapterTransport<
  TAdapterRuntime,
  TMaximumSessions,
  TMaximumPendingOutbound,
  TMaximumPendingInboundReceipts,
  TMaximumFrameBytes
>
```

Finite resources:

| Resource | Bound |
|---|---:|
| Frozen socket/session routes | `TMaximumSessions` |
| Pending outbound exact-M1 correlations | `TMaximumPendingOutbound` |
| Pending inbound receipt correlations | `TMaximumPendingInboundReceipts` |
| TX framing workspace | one fixed `TMaximumFrameBytes` array |
| Stream assembly per session | one fixed `TMaximumFrameBytes` array |
| Concurrent TX workspace user | at most 1 (`atomic_flag`) |
| Concurrent parser per session | at most 1 (`atomic_flag`) |
| Transport lifecycle generation | finite `uint64_t`, fail closed at exhaustion |
| Session lifecycle generation | finite `uint64_t`, fail closed at exhaustion |

The Type has compile-time assertions that every slot capacity is non-zero and that frame capacity can hold the fixed neutral header plus admission payload. Correlation counters fail closed at exhaustion. Temporary writer unavailability remains bounded transport backpressure and is not converted into a parallel retry engine.

R9-23 hardening checkpoint:
`4ebc172bd3d797a16b169e2c9f46bdccb4909d04`

R9-24 metadata checkpoint:
`0a8698aaca51ae0c6b9de883f07011917be639e3`

At the R9-24 metadata checkpoint all three workflows are SUCCESS:

- Host Tests `34814161515`
- Socket Adapter neutral transport contracts `34814161657`
- Security Integration `34814161623`

`library.json` / `library.properties` now describe the neutral socket/session boundary. The stale Event/Command/State transport claims and `PubSubClient` dependency were removed from Arduino metadata. Version remains `0.7.3`.

## 7. Serial classification

`ESPressio-Serial/primitives_redesign` baseline:
`3ef07be4252908458110682291fd6b1c1d181262`

No canonical device-to-device Primitive byte transport exists in the current library. Serial is operator/terminal tooling over System IO plus logging/diagnostic integrations. Therefore Tranche 9 does **not** invent a transport queue, wire envelope, A2 lower transport or retry resource model merely to fill a table.

Family-aware console/monitor cleanup remains a Tranche-10 consumer migration concern.

## 8. WiFi classification

`ESPressio-WiFi/primitives_redesign` baseline:
`8f959f19fbf4f7c3af42223ccc27521a4728f5dd`

WiFi currently exposes management/configuration plus local observer/Event and local administrative Command consumers, but no canonical remote Primitive family byte transport. `WiFiWorker` remains a predecessor common-consumer concern handed to Tranche 10. Therefore no synthetic Tranche-9 transport capacity is introduced.

## 9. Manifest / dependency accounting

Current locked package boundaries relevant to R9-24:

| Repository | Direct package dependency boundary |
|---|---|
| Adapters | System + Primitive + Task |
| Radio | System + Task + Timing + Units |
| ESP-NOW | System + Radio |
| Sockets | System + Observable in package core; Security/Timing are separately compiled optional source surfaces |
| Serial | System + Logging; higher-level monitor integrations remain opt-in consumer surfaces |
| WiFi | System + Observable + Serializable + Threads until ordered Tranche-10 consumer migration |

RadioAdapters intentionally has no `library.json` / `library.properties` at this checkpoint. This document does not invent a package manifest simply for symmetry.

All redesign dependency URLs which are present in the audited PlatformIO manifests must remain on `#primitives_redesign` until the separately authorized release/reintegration phase.

## 10. Closure rule

R9-24 may be promoted only when:

1. manifests describe actual final Tranche-9 ownership and do not preserve removed family transport stacks;
2. workflow dependency checkouts point to the current redesign branches rather than stale structural/main refs;
3. executable tests cover each canonical finite resource contract where a real transport exists;
4. infrastructure-blocked CI is explicitly distinguished from code/test failure;
5. no version number is changed;
6. `TRANCHE_HANDOFF_CURRENT.md` records the exact promoted checkpoints and R9-25 becomes the active next work unit.
