# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-13

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff(20260912-141121).md` remains authoritative for CLOSED/LOCKED architecture, dependency order and tranche gates. This file is authoritative for the latest implementation position.

## Standing authorization

The user explicitly authorizes implementation through remaining **structural** Tranches 8–11 without further permission pauses. Still NOT authorized unless separately requested: version changes, CHANGELOG/release finalization, `main` reintegration, tags, releases, Wiki publication, force pushes or backward-compatibility shims. Tranche 12 release preparation remains separately consequential.

## Closed tranches

Foundation F01–F08, Tranche 2 Task/Timing/Threads, Tranche 3 Event, Tranche 4 Command and Tranche 5 State are closed per the architecture handoff. Tranche 5 closure: State `25637a7555e3a03f1d709bd8e37340bc4d545b6e`, CI `34703052958` SUCCESS. Tranche 6 Adapters historical closure: `e43076c6c158b9036da4a3424b77043bb5910975`, CI `34708547392` SUCCESS. Tranche 7 Radio/providers closed: Radio `364f083c297e2072f7972f2fd63fcfa79cb6c1dd` / evidence `2a33d86c782ef25a25750ccd2b50b28191abd161`, CI `34719879383`; ESP32 `b29b53bc438a0d5013075ce58a501424c689c0a0`, CI `34716648904`; NRF24 `a641199da7d4e5101e4d2c871715a9c870bdc531`, CI `34716303385`.

Physical nonclaims remain: Raw80211 RX capture Estimated until characterized; BLE cannot carry the exact 32-byte Clock response; NRF24 has no bounded/certified RX timestamp.

## Tranche 8 — current branch truth

- Mesh `primitives_redesign`: `e21a4a7d7f527db59171477e27e12263231a7069`, CI `34742545719` SUCCESS.
- Adapters `primitives_redesign`: `77e034ec8d3efa4a8c8e6df0ef2f6a405f8dd98a`. Existing `AdapterSemanticProvenance::ImmediatePeer.Token` remains the opaque peer-route fact; do not expand family admission merely to pass routes.
- MeshAdapters `primitives_redesign`: **`fcec9570287cc12455c285f5c074491a3ebf215c`** (`Validate real State MeshAdapter binding`).
- exact MeshAdapters redesign workflow **`34747763059` — SUCCESS**.
- therefore the current **green MeshAdapters checkpoint is `fcec9570287cc12455c285f5c074491a3ebf215c`**.

Do NOT call Tranche 8 complete yet. Full locally-originated/outbound family composition, predecessor removal, M8-23/M8-24 gates, manifests/workflows/docs/umbrella audit, Command fixture cleanup and formal Tranche-8 closure remain open.

## Green integration at `fcec957…`

Workflow `34747763059` validates together:

- bounded Mesh -> A2 ingress correlation;
- neutral A2 -> Mesh lower transport;
- real Event family MeshAdapter binding;
- real Command family MeshAdapter binding with actual Command runtime, Persistence, response reservation/routing and replay/idempotency;
- real State family MeshAdapter binding with actual State runtime/session/version mutation and role-correct provenance.

A2 owns logical pursuit/retry, Mesh owns routing/forwarding/application lifecycle, and Radio R3 owns physical fragmentation/arbitration. No duplicate family-local retry, worker, route or fragmentation system was introduced.

### Mesh -> A2 M1 correlation rules

Correlation key is authenticated Mesh source device + Mesh membership incarnation + Mesh message ID. First Mesh receive transfers complete bytes to A2 and remains retryable; Adapter queue ownership is never destination Primitive admission. Exact family M1 is retained later through `AdapterInboundCompletionTarget`; generation wake drives `DeferredLocal` retry without re-enqueueing A2. Only family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission. Try-lock behavior keeps ingress bounded.

Mesh membership incarnation is NEVER a System/Primitive runtime incarnation. Runtime identity may only come from authenticated family bytes after its DeviceIdentifier is proven equal to authenticated Mesh source.

### Event — GREEN

Event binding is frozen/fixed, delegates to real `Event::Runtime`, preserves receipt/idempotency/source-loop behavior and rejects generic broadcast for `DestinationPrimitiveAdmission`. Historical dedicated Event checkpoint `bb1c1ff1fe6f6bd60c3f79deb3183f7961198841`, run `34744901323` SUCCESS.

### Command — GREEN

`ESPressio_CommandMeshAdapterBinding.hpp` is validated at `f09d5a1…`, run `34747588394` SUCCESS and remains green in `34747763059`. Response-bearing inbound requests receive bounded pre-reserved `CommandRemoteResponseDestination`; response delivery is handed synchronously to A2, after which A2 owns pursuit. Response-bearing request broadcast is rejected; no-response `NoRemoteEvidence` request may broadcast; responses never generic-broadcast. Exact terminal duplicate is idempotent and does not rerun the handler. Route tokens remain opaque.

M1 mapping: `Admitted` -> `Accepted`; terminal/history duplicates -> `AlreadyAccepted`; in-progress/busy -> `TemporarilyUnavailable`; ledger pressure -> `ResourceUnavailable`; unknown/protocol -> `Unsupported`; no active requester -> `Rejected`; invalid/schema/decode -> `Malformed`.

Command test harness still has two cleanup items before formal Tranche-8 closure because direct replacement of the ~20 KB file was connector-blocked: commit the separate `broadcastProvenance` variable directly into the test source, and narrow broad `ESPressio_Serializable.hpp` to `ESPressio_SerializationMacros.hpp`, then remove the Command-only `-Wno-error=misleading-indentation` workflow workaround. Production behavior is green and must not be weakened.

### State — GREEN

`src/ESPressio_StateMeshAdapterBinding.hpp` plus `tests/state_mesh_adapter_binding_test.cpp` are validated at `fcec957…`, workflow `34747763059` SUCCESS.

The real host contract uses `State::Runtime` with a normal pre-established remote-owner session and submits a newer owner-origin Publication through MeshAdapters. It validates:

- exact Owner `DeviceRuntimeIdentity` provenance from authenticated State bytes;
- runtime incarnation is retained from State bytes and never sourced from Mesh membership;
- real State session/version mutation through `Runtime::AdmitRemote`;
- exact duplicate -> `AlreadyAccepted`;
- generic State broadcast rejection with fail-closed provenance clearing;
- authenticated Mesh-source Device mismatch rejection;
- frozen service-class mismatch rejection;
- requester-origin `SubscribeRequest` selects Requester, not Owner, as semantic source;
- forged requester Device rejected before State mutation.

The host contract uses a valid finite `NoRemoteEvidence` State convergence policy so Publication mutation can be tested without adding an unrelated acknowledgement transport. State session/version/baseline/resync/convergence state remains family-owned.

Locked State rules: `StateValidatedIngressContext` is full `DeviceRuntimeIdentity`; message kind selects Owner vs Requester; exact role-specific identity equality is required; `State::Runtime::AdmitRemote<TState,Format>` remains the security/session/convergence boundary; generic State broadcast is forbidden.

## Exact rules — do not regress

- Never collapse A2 queue acceptance into M1 `Accepted`.
- Never convert Mesh membership incarnation into runtime incarnation.
- Never pack/truncate DeviceIdentifier into the 64-bit A2 route token.
- `ImmediatePeer.Token` is transport peer/route fact; `OriginalSource` is semantic provenance.
- No family-local retry/worker/fragmentation architecture.
- Do not weaken fail-closed provenance clearing merely to satisfy a test.

## Immediate continuation

1. Complete locally-originated/outbound Event, Command and State family composition through the neutral A2 lower-transport seam and bounded Mesh route-token composition. Preserve family-owned serialization/lease semantics and A2-owned pursuit.
2. Remove predecessor Event-only MeshAdapter submission/transport paths only after replacement inbound/outbound coverage is green; no shims.
3. Complete M8-23/M8-24 security, resource, fuzz, multi-node and dependency gates; audit manifests/workflows/README/comments/umbrella; produce formal Tranche-8 closure report.
4. Complete Command test-harness cleanup before formal closure.
5. Update this file after every material checkpoint and before any stop. Never leave unvalidated live-tip work absent from this card.

## Remaining authorized structural work

After Tranche 8, continue without permission pause through Tranche 9 RadioAdapters/non-Mesh transports, Tranche 10 dynamic tooling/platform consumers and Tranche 11 platform-wide eradication/final structural validation. Tranche 12 release preparation remains outside standing structural authorization.
