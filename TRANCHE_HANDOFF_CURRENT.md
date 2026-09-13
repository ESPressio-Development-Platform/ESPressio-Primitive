# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This file is the current cross-repository continuation card. The uploaded architecture handoff remains authoritative for locked contracts, ordering and completion gates. `TRANCHE_HANDOFF.MD` remains historical context; this file is authoritative for the latest pushed tranche position.

## Standing authorization

The user has explicitly authorized implementation through **all remaining structural tranches** without additional tranche-by-tranche authorization pauses. Preserve dependency/completion ordering, but do not stop to request permission at historical gates.

Not authorized unless separately requested: version changes, CHANGELOG release finalization, `main` reintegration, tags, releases, Wiki publication, force pushes or backward-compatibility shims. Tranche 12 release preparation therefore remains outside the current structural authorization.

## Completed structural tranches

Foundation F01–F08, Tranche 2 Task/Timing/Threads, Tranche 3 Event, Tranche 4 Command, Tranche 5 State, Tranche 6 generic Adapters and **Tranche 7 Radio/providers** are complete.

### Tranche 5 State

Final head: `ESPressio-State/primitives_redesign` `25637a7555e3a03f1d709bd8e37340bc4d545b6e`.

Final workflow run `34703052958` succeeded. `STATE_TRANCHE_IMPLEMENTATION_REPORT.md` and `STATE_CONTINUATION_CHECKPOINT.md` contain the formal closure evidence.

### Tranche 6 generic Adapters

Final report head: `ESPressio-Adapters/primitives_redesign` `e43076c6c158b9036da4a3424b77043bb5910975`.

Final workflow run `34708547392` succeeded for host + ESP32 surfaces. `TRANCHE_6_IMPLEMENTATION_REPORT.md` contains the formal A6-01..A6-24 mapping.

Direct Adapters dependencies are exactly System + Primitive + Task. A1/Q1/A2 bounded ownership, fixed capacity, finite pursuit, wake-driven service, frozen family bindings, resource accounting and deterministic shutdown are closed.

### Tranche 7 Radio/providers

Formal Radio closure report commit:

`ESPressio-Radio/primitives_redesign` `364f083c297e2072f7972f2fd63fcfa79cb6c1dd` — `Close Radio redesign tranche`

Executable evidence head:

`2a33d86c782ef25a25750ccd2b50b28191abd161` — `Fix adversarial Radio logical-length mutation`

Radio workflow run **`34719879383` — SUCCESS**. The active suite proves canonical dependency/predecessor eradication, managed-provider contract, exact v3 wire, compact Clock wire/capture, adaptive Clock coordinator, Radio-local Q1 capacity, deterministic resource accounting, bounded v3 reassembly, malformed/truncated/spoofed ingress rejection, quarantine promotion, R3 DRR/deadline scheduling, Clock promotion under saturated BestEffort load, single-owner ingress routing, cooperative single-Task domain runtime and family-opaque `RadioRuntime` lifecycle/peer semantics.

Provider evidence:

- `ESPressio-ESP32/primitives_redesign` `b29b53bc438a0d5013075ce58a501424c689c0a0`, CI run `34716648904` SUCCESS. Raw80211 and BLE implement the managed provider contract; Raw80211 uses ESP-IDF raw-TX completion; BLE is broadcast-only with 26 opaque bytes and bounded deferred advertising completion.
- `ESPressio-NRF24/primitives_redesign` `a641199da7d4e5101e4d2c871715a9c870bdc531`, CI run `34716303385` SUCCESS. Managed finite ingress, exact 3060-byte v3 logical maximum, conservative retry-aware cost, synchronous terminal completion and real unicast peer-ACK evidence are validated.

Radio direct dependencies are exactly System + Task + Timing + Units. Canonical predecessor v2 `RadioTransport`, `RadioWorker`, `RadioControlWorker`, PrecisionThread control path, Event bridge, Observable callbacks and predecessor Clock synchronizer were removed rather than shimmed.

`README.md`, `CLOCK_SYNCHRONIZATION.md` and `RADIO_TRANCHE_IMPLEMENTATION_REPORT.md` on Radio document the managed architecture.

### Explicit Tranche-7 non-claim

Structural Clock architecture is complete, but no software test invents physical timing certification:

- Raw80211 RX timing remains Estimated until conservative on-target capture uncertainty is characterized.
- BLE legacy advertising cannot carry the exact 32-byte Clock response and does not claim Clock-qualified timestamping.
- NRF24 has a 32-byte MTU and strong TX/ACK evidence but no bounded/certified receive timestamp yet.

This is not a blocker for the structural tranche. It is a provider/deployment qualification boundary that later validation must keep explicit.

## Current tranche — Tranche 8 Mesh/MeshAdapters

Continue immediately under standing authorization.

### Live in-progress checkpoint — 2026-09-13

The live tips were reconciled before continuing:

- `ESPressio-Mesh/primitives_redesign` = `e21a4a7d7f527db59171477e27e12263231a7069` (`Restore Clock reference regression semantics`).
- `ESPressio-MeshAdapters/primitives_redesign` = `d29065341cee134120bfe18351c50bcec9bbcdfd` (still the audited predecessor/Event-only baseline at this checkpoint).
- `ESPressio-Adapters/primitives_redesign` = `e43076c6c158b9036da4a3424b77043bb5910975` (closed Tranche-6 substrate).
- `ESPressio-Radio/primitives_redesign` = `364f083c297e2072f7972f2fd63fcfa79cb6c1dd` (closed Tranche-7 substrate at reconciliation time; re-query before any later Radio-dependent write).

Mesh is **52 fast-forward commits ahead** of the Section-29 planning baseline `2e55bfb2359b2c80dc3cdbb5917776caca92083f`. The current delta already contains implementation/test work in the locked M8 areas including:

- exact neutral Primitive admission mapping / `PrimitiveReceiverRegistry` migration;
- Mesh-local six-class relay Q1 capacity and deterministic relay-capacity profile;
- non-increasing remaining-residence helpers and v1 broadcast wire migration;
- authenticated broadcast lifecycle with network Seen/Forwarded separated from local `DeferredLocal` admission/retry;
- family-neutral broadcast-policy boundary;
- next-hop submission through managed Radio rather than predecessor direct fragment bursts;
- Mesh-only clock reference/topology orchestration and source-lineage/failover handling;
- `MeshRuntimeWorker` migration away from predecessor `PrecisionThread`/`std::function` execution;
- lifecycle observer replacement with fixed sink mechanics and resource-accounting updates.

Exact-head Mesh redesign workflow run **`34742545719` — SUCCESS** at `e21a4a7d7f527db59171477e27e12263231a7069`.

Do **not** yet claim Tranche 8 complete from this checkpoint. MeshAdapters has not yet been migrated on its live branch, and the full M8 completion gate (including Event/Command/State frozen A2 bindings, cross-repo integration/dependency guards, final resource/security/fuzz/multi-node validation, docs/report) remains to be closed.

### Immediate continuation point

1. Re-read the current Mesh core public handoff surfaces and classify any remaining M8-01..M8-20 gaps against the exact `e21a4a7d…` tree; preserve all 52 existing commits.
2. Migrate `ESPressio-MeshAdapters/primitives_redesign` from `d2906534…` to frozen A2 Event/Command/State family bindings (M8-21/M8-22), with no source-local redispatch.
3. Validate MeshAdapters against the closed Adapters/Event/Command/State/Mesh branch APIs and add exact family policy gates for `NoRemoteEvidence`, response-bearing Command rejection and invalid/stateless State broadcast rejection.
4. Complete M8-23/M8-24 tranche-wide security/resource/fuzz/multi-node/dependency tests, manifests/workflows/docs and a formal implementation report.
5. Update this living handoff after every material checkpoint and before any session/usage stop with exact branch heads and CI run IDs.

The locked M8-01..M8-24 sequence remains authoritative. The decisive completion requirements include:

- exact neutral M1 seven-disposition admission mapping at every Mesh family boundary;
- only Accepted/AlreadyAccepted creates DestinationPrimitiveAdmission;
- network Seen/Forwarded state independent of delayed local admission;
- DeferredLocal retry is local only, wake/capacity-generation driven, never network re-forward;
- source node is never redispatched through its own remote broadcast path;
- finite non-increasing remaining residence that duplicate/retry cannot reset;
- generic NoRemoteEvidence family restrictions, including rejection of response-bearing Command broadcast and invalid/stateless State broadcast;
- complete atomic Mesh relay record+bytes+workspace Q1 ownership and membership compatibility profile;
- all selected next-hop physical work goes through managed Radio Q1/R3; Mesh never becomes a physical fragment arbiter;
- Mesh owns reference topology/trust selection only; Radio owns timestamp exchange; Timing owns estimator/discipline;
- reference failover resets source-specific estimator evidence and propagates conservative uncertainty;
- migrate MeshRuntimeWorker away from PrecisionThread/std::function/polling to generic Thread composition;
- no canonical Observable/Event/Command/State dependency leaks into Mesh core;
- frozen Event/Command/State MeshAdapter family bindings through ESPressio-Adapters;
- deterministic resource accounting, host/security/fuzz/multi-node tests, dependency guards and documentation before claiming completion.

## After Tranche 8

Continue without authorization pause through:

- Tranche 9 — RadioAdapters and non-Mesh transports;
- Tranche 10 — dynamic tooling/platform consumers;
- Tranche 11 — platform-wide eradication and final structural validation.

Tranche 12 is release readiness/preparation only and remains separately consequential/not authorized by the standing structural implementation authorization.