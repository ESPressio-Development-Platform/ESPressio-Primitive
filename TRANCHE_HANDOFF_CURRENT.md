# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-14

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for CLOSED/LOCKED architecture and governance. Live `primitives_redesign` branch tips are implementation truth and MUST be rebaselined before every new implementation step.

## Authorization boundary

Implementation remains authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags/releases, Wiki publication, force pushes and backward-compatibility shims remain outside authorization. Tranche 12 release preparation remains separate.

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

## Tranche 9 — ACTIVE

### R9-02..R9-07 direct-Radio substrate — CLOSED; GREEN

- R9-02/03 RadioAdapters `3d3f1ed6a9bfdcc52fec2df385d37c71578d9bf2`; workflow `34753638473` SUCCESS.
- R9-04/05 RadioAdapters `8a3d1cf9506357fe90937d6bcf1d19d4f1091da2`; ingress `34755161807`, redesign `34755161844` SUCCESS.
- Neutral A2 lower metadata seam: Adapters `4c22db73063041a488e497b75be903a98a89196a`.
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

RadioAdapters `fd34d0e91f5aed61476792e2bad39bbcacaed39b`.
Exact-tip workflows all SUCCESS: ingress `34774777059`, outbound `34774777129`, redesign `34774777106`, exact-M1 `34774777090`, Event `34774777107`, Command `34774777045`, State `34774777083`, lifecycle `34774777147`.

R9-11 provides explicit active/quiesced generations, finite recent `(contention-domain, transfer-id)` exclusion across controlled restart, stale Radio/M1/A2 completion suppression, bounded quiesce and restart rebinding without wire changes.

## R9-12..R9-16 ESP-NOW provider consolidation — SOURCE COMPLETE; HOSTED EXECUTION BLOCKED

Current exact ESP-NOW source checkpoint:
- `ESPressio-ESP-Now/primitives_redesign` `9792c5cc7f10aa00bdf5830d4e973a26b3eb7128` (`Complete ESP-NOW provider boundary migration`).

### R9-12 final provider

`ESPNowRadio : Radio::IRadio` now owns only provider-specific physical mechanics: six-byte hardware addressing; ESP-NOW MTU/capabilities; stable shared Wi-Fi contention-domain identity; fixed bounded RX ring; finite provider resource profile; exactly one outstanding native TX with deferred terminal completion; generation-separated handles; explicit conservative cost characterization (otherwise `RelativeOnly`); peer/channel/interface mechanics and PMK/LMK encryption.

Successful unicast native completion maps only to direct-link MAC peer acknowledgement; broadcast success maps to transmission completion without peer acknowledgement. Neither native submission nor link acknowledgement is Primitive admission.

### R9-13 Event predecessor removal

Removed `ESPNowEventTransport`, its duplicate Event fragmentation/reassembly protocol, TaskExecutor ownership and predecessor EventTransportManager examples. Event-over-ESP-NOW now composes through Radio + RadioAdapters + final Event family binding.

### R9-14 Command predecessor removal

Removed `ESPNowCommandTransport`, `ESPNowCommandEndpoint`, `ESPNowCommandProtocol`, transport-specific tests/examples and the predecessor remote Command path. Command semantics remain solely in final Command + A2/direct-Radio composition.

### R9-15 clock migration

Removed `ESPNowClockSynchronizer` and fixed-cadence clock examples. Added `ESPNowRadioTimingCapture`, which captures provider-callback monotonic coordinates, an immutable Timing clock-model snapshot and explicit conservative uncertainty. It owns no estimator, cadence or historical System-time reconstruction; Radio/Timing K1/K2 remains the direct-neighbour exchange owner.

### R9-16 dependency/family/worker cleanup

At `9792c5cc...`, production `src/` is reduced to `ESPressio_ESPNow.hpp`, `ESPressio_ESPNowRadio.hpp` and `ESPressio_ESPNowRadioTiming.hpp`. Predecessor `ESPNowTransport`, Observable graph, PrecisionThread worker, AsyncProtocolHandler, Event bridge/events, Command coupling, bespoke State/Security transports, peer-liveness legacy surface and old WiFi coordinator are removed. Direct package dependencies are System + Radio only. Manifest version remains `0.8.3`; no version number changed.

Hosted CI remains infrastructure-blocked at this exact tip: Tests `34805336304` and ESP-NOW Radio provider `34805336457` both terminate before runner allocation with no executed steps. Do not misclassify those as compiler/test failures or successes.

## R9-17 Sockets neutral A2 transport/session binding — CLOSED; GREEN

Promoted Sockets checkpoint `675fd906ddf0d1aa8a079287031983cfa275541e`; dedicated neutral-transport workflow `34809102690` SUCCESS.

`SocketAdapterTransport` is fixed-capacity and family-neutral. It owns bounded socket envelope/session framing, immutable route/session topology, nonblocking writer admission, finite stream assembly, per-session availability/generation, transport lifecycle generation, exact M1 receipt carriage and bounded correlation. It does not parse Event/Command/State representations.

## R9-18 Sockets family-stack / Event-bridge removal — CLOSED; GREEN

Implementation checkpoint `e0b7c995cfda61ae8189e23e2fb0b954121e4ca8` (`Remove parallel socket family transports`), validated at final exact Sockets tip `89876b27ad647be842ade71163f4e7a95053c6fd`.

Removed the parallel socket-owned family runtimes and their predecessor consumers: Command protocol/session/types and TCP Command server; Event frame/events and Event bridge surfaces; State frame/session/client/server; obsolete family examples/docs/tests; socket/security worker Event bridges. Genuine socket/session/TLS mechanics remain below the neutral A2 binding.

## R9-19 socket/network clock evidence — CLOSED; GREEN

Clock migration checkpoint `37499d978287a1393cf765dc763b26cd4dbfb117` (`Migrate socket clock evidence to K1 K2`), final exact Sockets tip `89876b27ad647be842ade71163f4e7a95053c6fd`.

The old TCP/UDP/SNTP synchronizers are removed. `SocketClockSynchronizationProtocol` now carries a bounded one-outstanding-exchange K1/K2 request/response seam with explicit T1/T2/T3/T4 captures, capture quality, conservative uncertainty, reference identity/reliability and continuity reset. `EvidenceDue()` is driven from Timing's synchronization deadline; the socket layer owns no fixed cadence, estimator, discipline or historical-current-System reconstruction.

Exact final-tip workflows all SUCCESS:
- Host Tests `34810378919`
- Socket Adapter neutral transport contracts `34810378909`
- Security Integration `34810378901`

## R9-20 Serial transport classification — CLOSED; NEGATIVE TRANSPORT CLASSIFICATION

Source baseline: `ESPressio-Serial/primitives_redesign` `3ef07be4252908458110682291fd6b1c1d181262`.

No genuine device-to-device Primitive byte transport exists in current Serial source. The repository is explicitly the terminal/operator layer: Console consumes `System::IO::IByteInput`/`IByteOutput`/`IByteStream`; platform/framework byte transport belongs below Serial; Serial owns consoles, logging sink and diagnostics/monitors. `EventConsole` is an operator tooling consumer, not an `IEventTransport` or A2 lower transport.

Therefore R9-20 intentionally creates no Serial wire protocol and makes no Serial source mutation. Stale Command/Event/State/Timing/Thread/WiFi/ESP-NOW/socket console/monitor consumers are handed to Tranche 10 D10-12/D10-13 for final descriptor/diagnostics migration.

## R9-21 WiFi remote family bridge/handler classification — CLOSED; NO DIRECT REMOTE TRANSPORT PATH

Source baseline: `ESPressio-WiFi/primitives_redesign` `8f959f19fbf4f7c3af42223ccc27521a4728f5dd`.

WiFi is a platform/service manager, not an ESPressio physical Radio data plane. Its current family integrations are local consumers:
- `WiFiEventBridge` converts `IWiFiObserver` callbacks into local Event emissions; it owns no remote byte/session transport.
- `WiFiCommandHandler` is a local administrative CommandRegistry consumer; it owns no remote Command transport.

No WiFi-owned predecessor Event/Command remote transport or family-specific byte delivery path exists to migrate to A2 in R9-21. No synthetic WiFi Primitive transport is introduced. Migration of these local family consumer surfaces to final typed family APIs remains explicitly assigned to Tranche 10 D10-14.

## R9-22 WiFiWorker/specialized-thread cleanup handoff — CLOSED AS EXPLICIT TRANCHE-10 HANDOFF

`WiFiWorker` at the same WiFi baseline derives directly from the predecessor `PrecisionThread`, with mutable iteration-period/budget configuration and `Bump()` signalling. R9-22 does not prematurely redesign this consumer inside the transport tranche; the architecture explicitly hands it into common consumer migration. Tranche 10 D10-15 must move it to bare Thread + generic composition or a lower bounded Task worker as appropriate.

## Active continuation — R9-23 cross-transport hardening

Mandatory next sequence:
1. Rebaseline current RadioAdapters, Adapters, Radio, Sockets and ESP-NOW tips before any hardening mutation.
2. Add/verify congestion, restart, stale-handle/stale-completion, evidence-separation and family cross-transport tests/fuzz coverage without inventing new semantic owners.
3. Preserve exact M1 meaning and generation-safe shutdown/restart contracts across direct Radio and Sockets; keep link/peer evidence distinct from destination Primitive admission.
4. Treat ESP-NOW hosted-runner failure as infrastructure-blocked until a runner actually executes source; do not fake green evidence.
5. Continue R9-24 manifests/workflows/dependency guards/resource accounting and R9-25 README/source-comment/tranche-wide integration validation without permission pauses.
6. After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 remains separate and unauthorized.
