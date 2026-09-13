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

Current reconciled/validated tips:

- `ESPressio-Mesh/primitives_redesign` = `e21a4a7d7f527db59171477e27e12263231a7069` (`Restore Clock reference regression semantics`).
- `ESPressio-MeshAdapters/primitives_redesign` = `93f1092f5bb00e08d314e0ba7a06bc633119ad5f` (`Add bounded Mesh to A2 ingress correlation`).
- `ESPressio-Adapters/primitives_redesign` = `e43076c6c158b9036da4a3424b77043bb5910975` (closed Tranche-6 substrate).
- `ESPressio-Radio/primitives_redesign` = `364f083c297e2072f7972f2fd63fcfa79cb6c1dd` (closed Tranche-7 substrate at reconciliation time; re-query before any later Radio-dependent write).

Mesh is **52 fast-forward commits ahead** of the Section-29 planning baseline `2e55bfb2359b2c80dc3cdbb5917776caca92083f`. The current delta already contains implementation/test work in the locked M8 areas including exact neutral Primitive admission, Mesh-local six-class relay Q1/profile, non-increasing remaining residence, authenticated Seen/Forwarded plus local `DeferredLocal`, family-neutral broadcast policy, managed-Radio next-hop submission, Mesh-only clock-reference orchestration, generic Thread runtime-worker migration, lifecycle fixed sinks and resource-accounting updates.

Exact-head Mesh redesign workflow run **`34742545719` — SUCCESS** at `e21a4a7d7f527db59171477e27e12263231a7069`.

### MeshAdapters checkpoint 1 — async exact-M1 ingress correlation

MeshAdapters was previously the untouched Event-only predecessor at `d29065341cee134120bfe18351c50bcec9bbcdfd`. The first replacement checkpoint is now pushed at:

`93f1092f5bb00e08d314e0ba7a06bc633119ad5f` — `Add bounded Mesh to A2 ingress correlation`

Workflow run **`34744239828` — SUCCESS**.

New `ESPressio_MeshAdapterIngress.hpp` establishes the essential Mesh/A2 semantic bridge:

- explicit `MeshRelayServiceClass` -> neutral `AdapterServiceClass` mapping (no numeric ABI shortcut);
- bounded authenticated-occurrence correlation keyed by Mesh source + membership incarnation + Mesh message ID;
- first Mesh `Receive()` transfers complete bytes into A2 and returns `TemporarilyUnavailable`, **not** destination-admission evidence;
- the exact family M1 later returned by A2 `AdapterInboundCompletionTarget` is retained;
- A2 completion advances a non-wrapping/saturating adapter-admission generation and emits a fixed wake;
- the subsequent Mesh `DeferredLocal` retry returns the retained exact M1 without a second A2 enqueue, then releases the correlation slot;
- pending duplicate retries never duplicate A2 work;
- only exact family `Accepted` / `AlreadyAccepted` can later establish destination Primitive admission;
- Mesh membership incarnation is deliberately **not** forged into Primitive `RuntimeIncarnationId`; stronger A2 validated-original-source provenance stays unset until genuinely established by family/runtime validation.

The checkpoint test proves pending duplicate suppression, Accepted/AlreadyAccepted completion consumption, admission-generation wake and exact service-class mapping against the live Mesh/Adapters/System/Primitive branches.

**Important follow-up:** the current bridge uses a mutex for its bounded correlation table. Before Tranche-8 closure, change the synchronous remote `Receive()` acquisition to a non-blocking try-lock path (completion-side short serialization may block); remote ingress must not become an unbounded blocking path.

Do **not** claim Tranche 8 complete yet. MeshAdapters still needs the frozen Event/Command/State family bindings, neutral Mesh lower-transport seam, predecessor Event-only eradication, complete family policy gates, and tranche-wide M8-23/M8-24 validation/docs/report.

### Exact semantic issue already resolved for continuation

Mesh `IPrimitiveReceiver::Receive` is synchronous, while A2 executes the actual family admission asynchronously on a T1 worker. It is **incorrect** to return `Accepted` merely because A2 owns the bytes. The implemented correlation bridge solves this without changing M1 or polling: the first call returns retryable local admission, A2 completion changes the admission generation/wake, and Mesh's existing `DeferredLocal` table retries only after that generation changes. A successor must preserve this design and must not collapse A2 queue acceptance into destination-family admission evidence.

### Immediate continuation point

1. Make `MeshAdapterIngressBridge::Receive()` use non-blocking correlation-lock acquisition and return a retryable M1 fact on lock contention.
2. Build one frozen family composition layer per Primitive family over A2, with per-Type fixed thunks so family runtime receipt/idempotency/codec logic is preserved rather than bypassed.
3. Rebuild Event binding first (M8-21), using Event `Runtime` inbound semantics and `EventOutboundBinding`/real Event wire policy rather than direct descriptor admission that would bypass family receipt semantics.
4. Add Command and State bindings (M8-22), preserving exact family request/response/convergence semantics. Generic Mesh broadcast remains NoRemoteEvidence-only; reject response-bearing Command broadcast and State broadcast as required by current Mesh policy.
5. Add one neutral A2 `LowerTransportBinding` for Mesh outbound submission. MeshAdapters maps neutral service -> Mesh relay service explicitly; it does not create another transport worker/retry/fragmentation engine.
6. Remove predecessor Event-only MeshAdapter transport/submission files and obsolete tests only after replacement coverage exists; no compatibility shims.
7. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency tests, manifests/workflows/README/source comments and formal Tranche-8 implementation report.
8. Re-audit Mesh core umbrella/manifests during M8-24: current `ESPressio_Mesh.hpp` at `e21a4a7d…` does not yet include several newly added M8 public headers, so final canonical-surface integration still needs an explicit gate.
9. Update this living handoff after every material checkpoint and before any session/usage stop with exact branch heads and CI run IDs.

The locked M8-01..M8-24 sequence and completion gate in Section 29 remain authoritative.

## After Tranche 8

Continue without authorization pause through:

- Tranche 9 — RadioAdapters and non-Mesh transports;
- Tranche 10 — dynamic tooling/platform consumers;
- Tranche 11 — platform-wide eradication and final structural validation.

Tranche 12 is release readiness/preparation only and remains separately consequential/not authorized by the standing structural implementation authorization.