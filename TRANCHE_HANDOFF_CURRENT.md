# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-14
Last synchronized continuation reference: user timestamp 08:28 Europe/Prague

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for CLOSED/LOCKED architecture and governance. Live `primitives_redesign` branch tips are implementation truth and MUST be rebaselined before every new implementation step.

## Authorization boundary

Implementation remains authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags/releases, Wiki publication, force pushes and backward-compatibility shims remain outside authorization. Tranche 12 release preparation remains separate.

The user additionally requires this living handoff to remain present on `ESPressio-Primitive/primitives_redesign` and to be mirrored as an up-to-date downloadable conversation artifact whenever progress is reported.

## Locked non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning.
- Only `Accepted` / `AlreadyAccepted` establishes `DestinationPrimitiveAdmission`.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Direct-Radio family envelope remains exactly 4 bytes before unchanged family representation: 2-byte LE family + 2-byte LE protocol.
- Immediate physical peer and validated semantic `OriginalSource` remain distinct provenance facts.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Every neutral non-Mesh transport has finite lifecycle/generation; restart invalidates prior handles/correlation and stale completions cannot become current work.
- Temporary backpressure/disconnection/restart must not create unbounded retry.
- No structural-Tranche-9 version changes.

## Closed foundation / structural work

Foundation F01–F08 and structural Tranches 2–8 are CLOSED.

Key Tranche-8 promoted checkpoints:
- Mesh `5f36b51f6ce570e97e4f95f975f039d61e2287cd`; workflows `34753038491`, `34753038532`, `34753038454` SUCCESS.
- Mesh closure report `a832ce41c7ebd6174c7a06835ea24a871f843dcc`.
- MeshAdapters `ce0a745498216248279aafc70d6603e49b10a6ab`; combined `34753328372`, State `34753328259`, recovered Command `34753328297` SUCCESS.

## Tranche 9 status

### R9-02..R9-07 direct-Radio substrate — CLOSED; GREEN

- R9-02/03 RadioAdapters `3d3f1ed6a9bfdcc52fec2df385d37c71578d9bf2`; workflow `34753638473` SUCCESS.
- R9-04/05 RadioAdapters `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`; ingress `34755161807`, redesign `34755161844` SUCCESS.
- Neutral A2 metadata seam: Adapters `4c22db73063041a488e497b75be903a98a89196a`.
- R9-06 RadioAdapters `819a2cd5e6f3dcec589d3dd586e5cc5ba1c54525`; outbound `34755755309`, ingress `34755755291`, redesign `34755755273` SUCCESS.
- R9-07 Radio correlation substrate: Radio `84c6bbcac36d959378dcc69366bc18921298c257`; redesign `34764194951`, transfer-ID lease `34764194938` SUCCESS.
- R9-07 exact M1: RadioAdapters `0e72a10f0034820e8bc8e0e72166bee9731b972e`; redesign `34768426144`, exact-M1 `34768426012`, ingress `34768426030`, outbound `34768426102` SUCCESS.

### R9-08 Event direct-Radio — CLOSED; GREEN
RadioAdapters `a8092a2d914f7a0abf1a35c005e105f3c7d5a650`; ingress `34769579671`, outbound `34769579684`, redesign `34769579653`, exact-M1 `34769579682`, Event `34769579729` SUCCESS.

### R9-09 Command direct-Radio — CLOSED; GREEN
RadioAdapters `984731e214affdfb1152e0d9cf9bdb01b0e36a75`; ingress `34771857945`, outbound `34771857991`, redesign `34771857946`, exact-M1 `34771857903`, Event `34771858014`, Command `34771857995` SUCCESS.

### R9-10 State direct-Radio — CLOSED; GREEN
RadioAdapters `285b184ffd84ddb1e97c4292154010c613eaa735`; ingress `34772597924`, outbound `34772597753`, redesign `34772597861`, exact-M1 `34772597866`, Event `34772597831`, Command `34772597748`, State `34772597901` SUCCESS.

### R9-11 generation-safe lifecycle — CLOSED; GREEN
RadioAdapters `fd34d0e91f5aed61476792e2bad39bbcacaed39b`; ingress `34774777059`, outbound `34774777129`, redesign `34774777106`, exact-M1 `34774777090`, Event `34774777107`, Command `34774777045`, State `34774777083`, lifecycle `34774777147` all SUCCESS.

### R9-12..R9-16 ESP-NOW consolidation — SOURCE COMPLETE; AUTOMATION FALLBACK ACTIVE

Final provider-boundary source checkpoint before the R9-24 guard: `9792c5cc7f10aa00bdf5830d4e973a26b3eb7128`.

- R9-12: `ESPNowRadio : Radio::IRadio` owns bounded physical ESP-NOW mechanics only. One native TX is outstanding; completion is deferred; handles are generation-separated; six-byte addressing, MTU/capabilities, shared Wi-Fi contention-domain identity, peer/channel/interface mechanics and PMK/LMK remain provider-owned. Successful unicast native completion is direct-link MAC acknowledgement only, never Primitive admission.
- R9-13: removed `ESPNowEventTransport`, duplicate Event fragmentation/reassembly/TaskExecutor path and predecessor Event examples.
- R9-14: removed `ESPNowCommandTransport`, endpoint/protocol stack and transport-specific Command tests/examples.
- R9-15: removed fixed-cadence `ESPNowClockSynchronizer`; `ESPNowRadioTimingCapture` exposes callback monotonic coordinate + immutable Timing model snapshot + uncertainty, with no local estimator/cadence/historical reconstruction.
- R9-16: production `src/` is reduced to `ESPressio_ESPNow.hpp`, `ESPressio_ESPNowRadio.hpp`, `ESPressio_ESPNowRadioTiming.hpp`; predecessor Observable/PrecisionThread/AsyncProtocolHandler/Event/Command/State/Security/WiFi-coordinator surfaces are removed. Direct package dependencies are System + Radio. Version remains `0.8.3`.
- Repository-owned dual-IDF provider contract tests exist and an earlier independent local harness compiled/passed both IDF 5.4- and 5.5-style callback variants with `-Wall -Wextra -Werror`, including deferred unicast ACK, broadcast completion without peer ACK, terminal failure, bounded RX, Busy on second send and lifecycle generation separation.
- R9-24 guard checkpoint `04b21963aa461cd1a5a0ec977e1f60278d2df4b9` adds source/package dependency guards. Hosted Tests `34814293042` and provider `34814293069` terminated before runner allocation; every job reports `steps=null`. Per architecture section 21.1A.4 this is automation unavailable before meaningful execution, not code failure. Recursive source/manifest/workflow review and prior independent local contract execution are the fallback evidence. Outstanding uncertainty: hosted ESP32/provider execution has not run at this exact SHA.

### R9-17 Sockets neutral A2 transport/session binding — CLOSED; GREEN
Sockets checkpoint `675fd906ddf0d1aa8a079287031983cfa275541e`; neutral transport workflow `34809102690` SUCCESS. `SocketAdapterTransport` is fixed-capacity/family-neutral and owns bounded socket envelope/session framing, immutable route/session topology, nonblocking writer admission, finite stream assembly, lifecycle generations, exact M1 carriage and bounded correlation.

### R9-18 family-stack/Event-bridge removal — CLOSED; GREEN
Implementation `e0b7c995cfda61ae8189e23e2fb0b954121e4ca8`, validated through Sockets `89876b27ad647be842ade71163f4e7a95053c6fd`. Parallel Command/Event/State socket runtimes, predecessor Event bridges and obsolete consumers removed; genuine socket/session/TLS mechanics remain.

### R9-19 socket/network clock evidence — CLOSED; GREEN
Migration `37499d978287a1393cf765dc763b26cd4dbfb117`, validated at Sockets `89876b27ad647be842ade71163f4e7a95053c6fd`. One bounded K1/K2 exchange carries T1/T2/T3/T4, capture quality, uncertainty and reference reliability; Timing drives `EvidenceDue()` and owns estimator/discipline. Host `34810378919`, neutral transport `34810378909`, Security `34810378901` SUCCESS.

### R9-20 Serial transport classification — CLOSED; NEGATIVE TRANSPORT CLASSIFICATION
Serial baseline `3ef07be4252908458110682291fd6b1c1d181262`. No genuine device-to-device Primitive byte transport exists. Serial is terminal/operator tooling over `System::IO`; no synthetic wire protocol or A2 lower transport was invented. Stale family consoles/monitors are handed to Tranche 10 D10-12/D10-13.

### R9-21 WiFi remote bridge classification — CLOSED; NO DIRECT REMOTE TRANSPORT PATH
WiFi baseline `8f959f19fbf4f7c3af42223ccc27521a4728f5dd`. `WiFiEventBridge` is local observer→Event and `WiFiCommandHandler` local administrative CommandRegistry consumption; neither owns a remote family byte transport. No synthetic WiFi transport was introduced. Final local family-consumer migration remains D10-14.

### R9-22 WiFiWorker handoff — CLOSED AS TRANCHE-10 HANDOFF
`WiFiWorker` remains a predecessor `PrecisionThread` consumer and is explicitly handed to D10-15 for common consumer migration rather than prematurely redesigned inside the transport tranche.

### R9-23 cross-transport hardening — CLOSED; GREEN

Sockets `4ebc172bd3d797a16b169e2c9f46bdccb4909d04`: Host `34811393426`, neutral Adapter `34811393280`, Security `34811393283` SUCCESS.

RadioAdapters `29b7889bc1c1527b5830b223e8ae880c6c27e1ab`: lifecycle `34811500875`, Command `34811500964`, exact M1 `34811500882`, State `34811500883`, outbound `34811500894`, ingress `34811500967`, redesign `34811500932`, Event `34811500917` SUCCESS.

No production semantic change was needed by R9-23.

### R9-24 manifests/workflows/dependency/resource accounting — CLOSED

R9-24 was rebaselined from live branch tips rather than replaying the earlier interrupted session.

Final accounting artifacts / evidence:

- `TRANCHE_9_RESOURCE_ACCOUNTING.md` added to Primitive at commit `676a3f6d105b5dbe5f96b148e7f55724c1050df9`. It records exact finite capacities/ownership for A2, direct-Radio M1/ingress/lower transport, the Radio provider contract, ESP-NOW, Sockets, and the negative Serial/WiFi transport classifications.
- Adapters package boundary is System + Primitive + Task and remains Radio-neutral. Its redesign workflow uses only `primitives_redesign` dependency refs and publishes deterministic Adapter resource accounting.
- Radio package boundary is System + Task + Timing + Units and remains Primitive-family-neutral. Its redesign workflows use `primitives_redesign` dependencies and execute deterministic Radio resource-accounting contracts.
- RadioAdapters intentionally has no PlatformIO/Arduino manifest; no artificial manifest was invented.
- ESP-NOW manifests expose only System + Radio. R9-24 guard commit `04b21963aa461cd1a5a0ec977e1f60278d2df4b9` asserts predecessor source eradication, package dependency closure and redesign branch refs. Actions `34814293042` / `34814293069` remain pre-runner infrastructure failures (`steps=null`); fallback evidence is recorded above.
- Sockets stale Arduino metadata was corrected without version change. Final R9-24 Sockets checkpoint is `dda57dbad3f810f74778af7bfa096ca76651a0b7`. It self-guards the neutral package boundary and removal of stale Event/Command/State/PubSubClient claims. Exact-tip workflows are all GREEN: neutral Adapter `34814520351`, Host/package guard `34814520360`, Security `34814520349`.
- Serial/WiFi metadata was not prematurely rewritten because the remaining family/tooling/worker surfaces are real current consumers explicitly handed to Tranche 10.
- No version number changed.

## ACTIVE NEXT — R9-25 README/source-comment and tranche-wide integration closure

Locked purpose: update README/source comments and perform tranche-wide integration validation.

Architecture completion gate to prove item-by-item before R9-25 / Tranche 9 closure:

1. exact four-byte RadioAdapters prefix passes fixed vectors;
2. Radio core has no Primitive-family dependency and Adapters has no Radio dependency;
3. Event/Command/State direct-Radio bindings all use A1/A2 and exact M1 admission;
4. link/peer ACK is never mislabeled destination Primitive admission;
5. ESP-NOW no longer owns a second Event fragmentation/reassembly runtime;
6. ESP-NOW clock path obeys K1/K2 and no fixed cadence/historical System reconstruction remains;
7. Sockets exposes bounded neutral transport/session mechanics without parallel family execution stacks;
8. Serial tooling is not mistaken for a transport; any real Serial byte transport uses A2;
9. WiFi remote family bridges no longer depend on predecessor Command/Event delivery hacks;
10. all transports have finite congestion/backpressure and generation-safe restart semantics;
11. no old EventTransportManager/Event bridge or CommandRegistry transport path remains canonical;
12. no extra transport-owned worker exists where A2/T1 owns that execution responsibility;
13. manifests obey the locked DAG and no stale branch references remain;
14. all existing tests are semantically classified before execution;
15. no version number changed.

Repository completion also requires implementation + aligned documentation comments + README/examples + semantically-reviewed tests and recorded validation evidence. Do not mark Tranche 9 CLOSED until this R9-25 documentation/integration pass is complete.

Immediate continuation:

- audit current READMEs, public source comments and examples in RadioAdapters, ESP-NOW, Sockets, Radio and Adapters against actual final APIs;
- update/remove stale predecessor documentation/examples only where source has already migrated;
- create `TRANCHE_9_CLOSURE.md` in Primitive with itemized completion-gate evidence and ESP-NOW automation fallback classification;
- run/resolve exact-tip workflows triggered by documentation/guard edits;
- promote R9-25 / Tranche 9 CLOSED only after the repository completion gate is satisfied;
- continue automatically into authorized Tranche 10; Tranche 12 remains separate and unauthorized.
