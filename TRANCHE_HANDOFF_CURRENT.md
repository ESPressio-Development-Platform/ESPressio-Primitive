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

### R9-12..R9-16 ESP-NOW consolidation — SOURCE COMPLETE; HOSTED EXECUTION BLOCKED AT LAST CHECK

Current source checkpoint: `ESPressio-ESP-Now/primitives_redesign` `9792c5cc7f10aa00bdf5830d4e973a26b3eb7128` (`Complete ESP-NOW provider boundary migration`).

- R9-12: `ESPNowRadio : Radio::IRadio` owns bounded physical ESP-NOW mechanics only. One native TX is outstanding; completion is deferred; handles are generation-separated; six-byte addressing, MTU/capabilities, shared Wi-Fi contention-domain identity, peer/channel/interface mechanics and PMK/LMK remain provider-owned. Successful unicast native completion is direct-link MAC acknowledgement only, never Primitive admission.
- R9-13: removed `ESPNowEventTransport`, duplicate Event fragmentation/reassembly/TaskExecutor path and predecessor Event examples.
- R9-14: removed `ESPNowCommandTransport`, endpoint/protocol stack and transport-specific Command tests/examples.
- R9-15: removed fixed-cadence `ESPNowClockSynchronizer`; `ESPNowRadioTimingCapture` now exposes callback monotonic coordinate + immutable Timing model snapshot + uncertainty with no local estimator/cadence/historical reconstruction.
- R9-16: production `src/` reduced to `ESPressio_ESPNow.hpp`, `ESPressio_ESPNowRadio.hpp`, `ESPressio_ESPNowRadioTiming.hpp`; predecessor Observable/PrecisionThread/AsyncProtocolHandler/Event/Command/State/Security/WiFi-coordinator surfaces removed. Direct package dependencies are System + Radio. Version remains `0.8.3`.
- Last exact-tip hosted runs were infrastructure-blocked before runner allocation: Tests `34805336304`, provider `34805336457`; do not call these code failures or successes unless a runner later executes them.

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

Sockets hardening checkpoint `4ebc172bd3d797a16b169e2c9f46bdccb4909d04`:
- Host Tests `34811393426` SUCCESS.
- Socket Adapter neutral transport contracts `34811393280` SUCCESS.
- Security Integration `34811393283` SUCCESS.
- Deterministic adversarial coverage mutates every bit of a live M1 receipt header, rejects all non-domain M1 bytes, verifies all exact non-success dispositions remain non-establishing, churns session generations repeatedly, proves stale receipt rejection, and exercises bounded stream recovery under deterministic pseudo-random chunking.

RadioAdapters hardening checkpoint `29b7889bc1c1527b5830b223e8ae880c6c27e1ab`:
- lifecycle `34811500875` SUCCESS.
- Command `34811500964` SUCCESS.
- exact M1 `34811500882` SUCCESS.
- State `34811500883` SUCCESS.
- outbound `34811500894` SUCCESS.
- ingress `34811500967` SUCCESS.
- redesign `34811500932` SUCCESS.
- Event `34811500917` SUCCESS.
- Adversarial exact-M1 coverage proves all seven dispositions round-trip and share the same establishment predicate as Sockets; malformed control-prefix/reserved/admission values fail closed; wrong route/domain/transfer IDs cannot alias current correlation; `CompletedAndAcknowledged` direct-link evidence alone cannot complete A2; quiesce/rebind preserves stale suppression and transfer-ID exclusion.

No production semantic change was needed by R9-23.

## Active continuation — R9-24 manifests/workflows/dependency/resource accounting

### Source-first rebaseline recorded at user continuation 08:28

- Primitive `5ecd87a55e6838f71d9d5715c10308a09029f7e1` before this handoff refresh.
- RadioAdapters `29b7889bc1c1527b5830b223e8ae880c6c27e1ab`.
- Adapters `4c22db73063041a488e497b75be903a98a89196a`.
- Radio `84c6bbcac36d959378dcc69366bc18921298c257`.
- ESP-NOW `9792c5cc7f10aa00bdf5830d4e973a26b3eb7128`.
- Sockets `60e9af5f06423bc2307e05201884f434f3d3fd5e`; this is already an R9-24 metadata commit after the R9-23 hardening checkpoint.
- Serial `3ef07be4252908458110682291fd6b1c1d181262`.
- WiFi `8f959f19fbf4f7c3af42223ccc27521a4728f5dd`.

### R9-24 audit findings already confirmed

1. ESP-NOW package metadata is aligned to the final provider boundary: `library.json` and `library.properties` expose only ESPressio-System + ESPressio-Radio; no Event/Command/State/Observable/Threads package dependency remains. No version change is required or authorized.
2. Radio `library.json` remains Primitive-family-neutral and depends only on System, Task, Timing and Units. Radio has no `library.properties`; do not invent one merely for symmetry.
3. Adapters `library.json` / `library.properties` correctly expose System + Primitive + Task and remain Radio-neutral.
4. RadioAdapters intentionally has neither `library.json` nor `library.properties`; do not manufacture a package manifest unless repository packaging policy later explicitly requires one.
5. Sockets `library.json` description/keywords were partially modernized by commit `60e9af5f06423bc2307e05201884f434f3d3fd5e`, but `library.properties` is still stale: it advertises removed Event/Command/State responsibilities and `PubSubClient` despite the final source tree containing only neutral Adapter transport, generic socket worker/session support, Security session mechanics and K1/K2 Timing evidence. This is the immediate metadata defect to correct.
6. Sockets workflow dependency checkouts are already on `primitives_redesign`. The neutral Adapter workflow correctly compiles against Adapters + Primitive + System + Task, and host/security/timing workflows compile the genuine optional surfaces separately.
7. ESP-NOW bounded resource accounting evidence: default fixed RX ring depth 16 (`ESPRESSIO_ESPNOW_RADIO_RX_QUEUE_DEPTH`), exactly one outstanding native TX, six-byte addresses, explicit finite lifecycle generation plus bounded per-generation handle sequence, fixed native ESP-NOW payload bound, no provider-local retry queue/application worker, and conservative cost/evidence only when explicitly characterized.

### Mandatory continuation sequence

1. Correct Sockets Arduino/package metadata without reintroducing removed family dependencies or changing version numbers.
2. Audit/record final bounded resource surfaces for Sockets neutral transport and direct-Radio/Adapter composition, and strengthen automated dependency/resource guards where useful.
3. Recheck manifest/workflow branch references after any writes and run/resolve exact-tip workflows. Infrastructure failures before runner allocation must be recorded distinctly from code/test failures.
4. Promote R9-24 only when package/workflow/dependency/resource accounting is coherent at exact branch tips.
5. Continue directly into R9-25 documentation/integration closure, then authorized structural Tranches 10–11. Tranche 12 remains separate and unauthorized.
