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

`ESPNowRadio : Radio::IRadio` now owns only provider-specific physical mechanics:
- six-byte hardware addressing, ESP-NOW MTU/capabilities and stable shared Wi-Fi contention-domain identity;
- fixed bounded RX ring and finite provider resource profile;
- exactly one outstanding native TX with deferred terminal completion;
- successful unicast native send callback maps to direct-link MAC peer acknowledgement only; broadcast success maps to transmission completion without peer acknowledgement;
- neither native submission nor link acknowledgement is Primitive admission;
- generation-separated transmission handles;
- explicit conservative cost characterization, otherwise `RelativeOnly`;
- native peer/channel/interface operations plus PMK/LMK ESP-NOW encryption mechanics.

Dual-IDF provider contracts compile the actual header against IDF 5.4- and 5.5-style callback ABIs. An independent local executable harness passed both variants with `-Wall -Wextra -Werror` before hosted-runner failure began.

### R9-13 Event predecessor removal

Removed the bespoke `ESPNowEventTransport`, its second Event fragmentation/reassembly runtime, TaskExecutor ownership and predecessor EventTransportManager examples. Event-over-ESP-NOW now composes through Radio + RadioAdapters + the final Event family binding.

### R9-14 Command predecessor removal

Removed `ESPNowCommandTransport`, `ESPNowCommandEndpoint`, `ESPNowCommandProtocol`, their transport-specific tests and CommandPeer predecessor example. Command request/response semantics remain solely in the final Command family/A2 direct-Radio path.

### R9-15 clock migration

Removed `ESPNowClockSynchronizer` and fixed-cadence clock examples. Added `ESPNowRadioTimingCapture`, which captures provider-callback monotonic coordinates plus an immutable Timing clock-model snapshot and explicit conservative uncertainty. It owns no estimator/cadence/System reconstruction.

Radio `84c6bbcac36d959378dcc69366bc18921298c257` remains the direct-neighbour K1/K2 exchange owner through `RadioClockCoordinator`: cadence comes only from Timing, T1/T3 are late captures, T2/T4 use provider capture-time evidence, and there is no current-System-minus-elapsed historical reconstruction.

### R9-16 dependency/family/worker cleanup

At `9792c5cc...`, production `src/` is reduced to:
- `ESPressio_ESPNow.hpp`
- `ESPressio_ESPNowRadio.hpp`
- `ESPressio_ESPNowRadioTiming.hpp`

Removed predecessor `ESPNowTransport`, Observable observer graph, PrecisionThread worker, AsyncProtocolHandler, Event bridge/events, Command administrative coupling, bespoke State transport, bespoke Security fragmentation transport/protocol, peer-liveness legacy surface and old WiFi coordinator. Native ESP-NOW peer encryption/channel/interface mechanics remain in the provider. WiFi shared-radio consumer composition is intentionally revisited in ordered R9-21/R9-22 against the final provider, not by preserving `ESPNowTransport`.

Direct package dependencies are now System + Radio only. Manifest version remains `0.8.3`; no version number changed.

### Hosted CI status — IMPORTANT

GitHub Actions is currently failing before runner allocation, not during source execution. At exact tip `9792c5cc...`:
- Tests run `34805336304`: both jobs have `runner_id=0`, empty runner name and `steps=[]`.
- ESP-NOW Radio provider run `34805336457`: both jobs have `runner_id=0`, empty runner name and `steps=[]`.

Therefore R9-12..R9-16 are **source-complete with durable tests present, but not claimed hosted-CI-green**. Do not misclassify these infrastructure failures as compiler/test failures or successes.

## Active continuation — R9-17 Sockets neutral A2 transport/session binding

Mandatory next sequence:
1. Rebaseline `ESPressio-Sockets/primitives_redesign` live tip against planned baseline `8c5322aa03e1e3b6408e1ed999f00263afbe159e`.
2. Audit concrete stream/datagram/WebSocket connection/session ownership, ingress buffering, backpressure, reconnect and generation behavior.
3. Expose a bounded family-neutral byte/session lower-transport binding to A2; do not put Event/Command/State semantics into that binding.
4. Preserve transport-specific stream/datagram framing, endpoint addressing, connection/session lifecycle, reconnect/backpressure and TLS/security-session mechanics.
5. Then execute R9-18 removal/reduction of parallel Event/Command/State stacks and Event bridges.
6. R9-19 migrates socket/network clock evidence to the same K1/K2 quality/source model.
7. Continue R9-20 Serial, R9-21/22 WiFi, R9-23 hardening, R9-24 manifests/workflows/accounting and R9-25 documentation/integration closure without permission pauses.

After Tranche 9, continue authorized structural Tranches 10–11. Tranche 12 remains separate and unauthorized.
