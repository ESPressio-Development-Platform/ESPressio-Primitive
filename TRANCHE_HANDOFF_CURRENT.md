# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live cross-repository continuation card. The uploaded `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff(20260912-141121).md` remains authoritative for CLOSED/LOCKED architecture, exact contracts, dependency order and tranche completion gates. This file is authoritative for the latest implementation position.

## Standing authorization

The user explicitly authorizes implementation through all remaining **structural** tranches without additional tranche-by-tranche permission pauses. Continue dependency-correctly and do not stop at historical authorization gates.

Still NOT authorized unless separately requested: version changes, CHANGELOG/release finalization, `main` reintegration, tags, releases, Wiki publication, force pushes or backward-compatibility shims. Tranche 12 release preparation remains separately consequential.

## Closed tranches

- Foundation F01–F08 and Tranche 2 Task/Timing/Threads: closed per architecture handoff.
- Tranche 3 Event: closed.
- Tranche 4 Command: closed.
- Tranche 5 State: `ESPressio-State/primitives_redesign` `25637a7555e3a03f1d709bd8e37340bc4d545b6e`; CI `34703052958` SUCCESS.
- Tranche 6 Adapters: `ESPressio-Adapters/primitives_redesign` `e43076c6c158b9036da4a3424b77043bb5910975`; CI `34708547392` SUCCESS; direct deps exactly System + Primitive + Task.
- Tranche 7 Radio/providers: Radio `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`, executable evidence `2a33d86c782ef25a25750ccd2b50b28191abd161`, CI `34719879383` SUCCESS; ESP32 `b29b53bc438a0d5013075ce58a501424c689c0a0`, CI `34716648904`; NRF24 `a641199da7d4e5101e4d2c871715a9c870bdc531`, CI `34716303385`. Radio direct deps exactly System + Task + Timing + Units. Predecessor v2 transport/PrecisionThread/Event/Observable/control-clock paths were eradicated.

Tranche-7 physical qualification nonclaims remain explicit: Raw80211 RX capture stays Estimated until characterized; BLE cannot carry the exact 32-byte Clock response; NRF24 has no bounded/certified RX timestamp.

## Current tranche — Tranche 8 Mesh / MeshAdapters

### Mesh core checkpoint

`ESPressio-Mesh/primitives_redesign` = `e21a4a7d7f527db59171477e27e12263231a7069` (`Restore Clock reference regression semantics`). Mesh redesign CI `34742545719` SUCCESS.

This tip is 52 fast-forward commits beyond the Section-29 planning baseline and already contains major M8 core work: neutral M1 receiver semantics, six-class relay Q1/profile, non-increasing remaining residence, authenticated Seen/Forwarded separated from DeferredLocal admission, generic NoRemoteEvidence broadcast policy, managed-Radio next-hop submission, Mesh-only reference/topology orchestration, runtime-worker migration away from PrecisionThread/std::function, fixed lifecycle sinks and resource accounting.

Do NOT call Tranche 8 complete yet. Final Mesh umbrella/manifests, cross-repo integration and formal M8 closure remain open.

### MeshAdapters live tip

`ESPressio-MeshAdapters/primitives_redesign` = **`b44997b448b29105cfc5a8021eb59633c9538148`** (`Fix strict ingress correlation build`).

Exact redesign workflow run **`34744393741` — SUCCESS**.

The new `src/ESPressio_MeshAdapterIngress.hpp` establishes the bounded asynchronous Mesh -> A2 ingress correlation required by the locked M1/M2 semantics:

- explicit `MeshRelayServiceClass` -> `AdapterServiceClass` mapping; no numeric enum ABI shortcut;
- correlation key = authenticated Mesh source device + Mesh membership incarnation + Mesh message ID;
- first Mesh `Receive()` transfers complete bytes to A2 and returns `TemporarilyUnavailable`; A2 ownership is NEVER represented as destination Primitive admission;
- exact family M1 returned later by `AdapterInboundCompletionTarget` is retained;
- completion advances a saturating/non-wrapping admission generation and emits a fixed wake;
- Mesh `DeferredLocal` retries only after that generation changes, then consumes the stored M1 without re-enqueueing A2;
- pending duplicate local retries do not duplicate A2 work;
- only exact family `Accepted`/`AlreadyAccepted` can establish destination Primitive admission;
- Mesh `MembershipIncarnation` is deliberately NOT forged into Primitive `RuntimeIncarnationId`; stronger A2 original-source provenance remains unset unless genuinely validated by the family/runtime;
- `Receive()` now uses `std::try_to_lock`; correlation-lock contention returns retryable `TemporarilyUnavailable` and never blocks remote ingress. The earlier blocking-ingress follow-up is therefore CLOSED.

Checkpoint history:
- `93f1092f5bb00e08d314e0ba7a06bc633119ad5f` — initial bounded correlation; CI `34744239828` SUCCESS.
- `eb059f298f4e74776260f43cca4421ab2bed8e4f` — introduced try-lock but failed only strict `-Werror=misleading-indentation`.
- `b44997b448b29105cfc5a8021eb59633c9538148` — strict build repair; CI `34744393741` SUCCESS.

### Exact integration rule — do not regress

Mesh `IPrimitiveReceiver::Receive` is synchronous; A2 executes real family admission asynchronously on a T1 worker. Never collapse Adapter queue acceptance into M1 `Accepted`. The current bridge intentionally returns a retry candidate until the real family M1 completion exists, then feeds that completion back through Mesh's existing generation-driven DeferredLocal mechanism. Network Seen/Forwarded state remains independent and is never repeated by this retry.

### Event M8-21 design now in progress

The next binding must preserve Event family's real receipt/idempotency/source-loop semantics, not call `EventTypeDescriptor::AdmitRemote` directly.

Relevant live Event APIs:
- `Event::Runtime::BindInbound<T,Format>()` produces the immutable per-Type inbound binding before family Start.
- `Event::Runtime::TryAdmitRemote(binding,data,size)` decodes exact Event V1, checks configured Type and maximum representation, rejects locally-originated device replay, reserves/commits the family receipt table and returns real `AlreadyAdmitted`/M1 semantics.
- Event V1 header is exact 53 bytes and carries its own `DeviceRuntimeIdentity`, message ID, qualified origin time and payload length.

Planned Event family composition:
1. fixed pre-freeze per-Type entries: Event TypeId + real `EventInboundBinding` + immutable DeliveryPolicy + frozen Mesh relay service + maximum complete wire bytes;
2. Mesh ingress policy resolver decodes only enough Event V1 metadata to select the configured Type, validates the signed Mesh relay service equals that Type's frozen mapping, and returns that Type's immutable Primitive policy;
3. A2 family `AdmitInbound` decodes Type selection then calls real `Event::Runtime::TryAdmitRemote`, preserving family receipts/idempotency/source-loop prevention;
4. no RTTI, heap, `std::function`, dynamic registry or per-occurrence policy object;
5. later outbound path uses the real Event outbound binding/encoder through one neutral Mesh lower-transport seam.

Important current gap to fix before Event landing: `MeshAdapterPolicyResolver` currently receives family/version/bytes but not the authenticated Mesh relay service. Extend it to receive `MeshRelayServiceClass` (or equivalent immutable context) so the local frozen per-Type service mapping can be enforced **before A2 ownership transfer**. A2's family admission thunk intentionally has no service parameter, so this pre-A2 resolver is the correct enforcement point.

### Immediate continuation steps

1. Extend `MeshAdapterPolicyResolver` to receive the Mesh relay service and update the green ingress regression.
2. Implement frozen Event family binding (M8-21) with fixed per-Type entries and real Event Runtime admission.
3. Add one neutral A2 `LowerTransportBinding` for Mesh outbound submission; it must use existing Mesh lifecycle/managed-Radio machinery and must not create another worker/retry/fragmentation engine.
4. Add Command and State frozen bindings (M8-22), preserving exact request/response/convergence semantics. Generic Mesh broadcast remains NoRemoteEvidence-only; response-bearing Command broadcast and State broadcast must be rejected according to the locked policy boundary.
5. Remove predecessor Event-only MeshAdapter transport/submission files only after replacement coverage is green; no shims.
6. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency gates, manifests/workflows/README/source comments, canonical Mesh umbrella audit and formal Tranche-8 report.
7. Update this file after every material checkpoint and before any session/usage stop with exact SHAs and CI run IDs.

## Remaining authorized structural work

After Tranche 8, continue without permission pause through Tranche 9 RadioAdapters/non-Mesh transports, Tranche 10 dynamic tooling/platform consumers and Tranche 11 platform-wide eradication/final structural validation. Tranche 12 release preparation remains outside the standing structural authorization.