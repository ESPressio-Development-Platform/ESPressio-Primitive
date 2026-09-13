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
- Tranche 6 Adapters historical closure: `e43076c6c158b9036da4a3424b77043bb5910975`; CI `34708547392` SUCCESS; direct deps exactly System + Primitive + Task.
- Tranche 7 Radio/providers: Radio `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`, executable evidence `2a33d86c782ef25a25750ccd2b50b28191abd161`, CI `34719879383` SUCCESS; ESP32 closure SHA `b29b53bc438a0d5013075ce58a501424c689c0a0`, CI `34716648904`; NRF24 closure SHA `a641199da7d4e5101e4d2c871715a9c870bdc531`, CI `34716303385`. ESP32 and NRF24 later advanced by one README-only documentation commit each; provider source contracts did not drift. Radio direct deps remain exactly System + Task + Timing + Units. Predecessor v2 transport/PrecisionThread/Event/Observable/control-clock paths were eradicated.

Tranche-7 physical qualification nonclaims remain explicit: Raw80211 RX capture stays Estimated until characterized; BLE cannot carry the exact 32-byte Clock response; NRF24 has no bounded/certified RX timestamp.

## Current tranche — Tranche 8 Mesh / MeshAdapters

### Current branch truth

- `ESPressio-Mesh/primitives_redesign` = `e21a4a7d7f527db59171477e27e12263231a7069` (`Restore Clock reference regression semantics`), redesign CI `34742545719` SUCCESS.
- `ESPressio-Adapters/primitives_redesign` = `77e034ec8d3efa4a8c8e6df0ef2f6a405f8dd98a` (`Keep inbound peer routing in transport provenance`). This is a fast-forward integration-era tip after the closed Tranche-6 checkpoint. A brief attempted admission-signature expansion was reverted in favor of the already-existing `AdapterSemanticProvenance::ImmediatePeer.Token`; no intended neutral A2 API expansion remains from that experiment.
- `ESPressio-MeshAdapters/primitives_redesign` = **`ab3d326713390eb5f75769443fd210b402b36472`** (`Isolate known Serializable warning in Command contract`). This tip is **NOT YET A GREEN CHECKPOINT**.
- last fully green MeshAdapters checkpoint remains **`4006ce9881bc75b7231774cb011226de68d56e2a`**, exact redesign workflow **`34746074600` — SUCCESS**.

Do NOT call Tranche 8 complete yet. Final Command/State integration validation, outbound family completion, predecessor removal, M8-23/M8-24 gates, manifests/workflows/docs/umbrella audit and formal Tranche-8 closure remain open.

### Mesh core checkpoint

The Mesh tip already contains major M8 core work: neutral M1 receiver semantics, six-class relay Q1/profile, non-increasing remaining residence, authenticated Seen/Forwarded separated from DeferredLocal admission, generic NoRemoteEvidence broadcast policy, managed-Radio next-hop submission, Mesh-only reference/topology orchestration, runtime-worker migration away from PrecisionThread/std::function, fixed lifecycle sinks and resource accounting.

### Last green MeshAdapters checkpoint

At `4006ce9881bc75b7231774cb011226de68d56e2a`, the following is validated:

- `src/ESPressio_MeshLowerTransportBinding.hpp`: one neutral A2 `LowerTransportBinding` over a fixed `MeshApplicationLifecycleBinding`;
- explicit `AdapterServiceClass` -> `MeshRelayServiceClass` mapping, no numeric-enum ABI shortcut;
- immutable Adapter-owned bytes are handed to the existing Mesh application lifecycle/managed-Radio composition;
- deferred terminal/destination M1 completion is generation-correlated back into `AdapterRuntime::CompleteTransport`;
- no new worker, queue, retry engine, route engine or fragmentation engine exists in the binding;
- A2 remains sole owner of Primitive pursuit/retry state; Mesh remains sole owner of routing/forwarding/application lifecycle; Radio R3 remains sole physical-fragment arbiter;
- fixed validate/cancel/quiesce thunks preserve controlled lifecycle composition;
- Mesh -> A2 family policy resolution receives the complete authenticated `MeshReceiveContext` and may publish normalized A2 provenance;
- Event generic broadcast enforces locked M2: `DestinationPrimitiveAdmission` Events are rejected on generic broadcast; only `NoRemoteEvidence` Event policy is admitted there.

Historical green M8-21 Event checkpoint: `bb1c1ff1fe6f6bd60c3f79deb3183f7961198841`, run `34744901323` SUCCESS. Historical bounded ingress checkpoint: `b44997b448b29105cfc5a8021eb59633c9538148`, run `34744393741` SUCCESS.

### Mesh -> A2 ingress correlation — current contract

`src/ESPressio_MeshAdapterIngress.hpp` preserves the asynchronous Mesh -> A2 correlation required by locked M1/M2 semantics:

- correlation key = authenticated Mesh source device + Mesh membership incarnation + Mesh message ID;
- first Mesh `Receive()` transfers complete bytes to A2 and returns `TemporarilyUnavailable`; A2 ownership is NEVER represented as destination Primitive admission;
- exact family M1 returned later by `AdapterInboundCompletionTarget` is retained;
- completion advances a saturating/non-wrapping admission generation and emits a fixed wake;
- Mesh `DeferredLocal` retries only after that generation changes, then consumes the stored M1 without re-enqueueing A2;
- pending duplicate local retries do not duplicate A2 work;
- only exact family `Accepted`/`AlreadyAccepted` can establish destination Primitive admission;
- `Receive()` uses `std::try_to_lock`; correlation-lock contention is retryable and never blocks remote ingress.

The bridge itself still **never** converts Mesh `MembershipIncarnation` into Primitive/System `RuntimeIncarnationId`. Where a family wire carries a full `DeviceRuntimeIdentity`, a family resolver may mark that identity as validated only after proving its `DeviceIdentifier` equals the authenticated Mesh source; the runtime-incarnation field comes from authenticated family bytes, not from Mesh membership state.

### M8-22 work after the last green checkpoint — PRESENT BUT UNVALIDATED

Current changed surface after `4006ce9…`:

- `src/ESPressio_MeshRouteBinding.hpp` — bounded composition-owned Device -> opaque `AdapterRouteToken` resolution seam; route tokens remain transport-integration facts and are never packed/truncated Device identifiers.
- `src/ESPressio_CommandMeshAdapterBinding.hpp` — frozen real Command family binding with real `Command::Runtime` admission, request/response policy distinction and bounded response-destination routing through A2.
- `tests/command_mesh_adapter_binding_test.cpp` plus workflow coverage — real Command/Persistence/Task dependency closure regression.
- `src/ESPressio_StateMeshAdapterBinding.hpp` — frozen State family binding which parses the role-specific full `DeviceRuntimeIdentity` from State V1 bytes, requires its Device to match authenticated Mesh source, publishes that exact semantic source to A2 and delegates typed decode/session/convergence mutation to real State runtime. Canonical State broadcast is rejected.
- `.github/workflows/redesign.yml` at `ab3d326…` isolates one known pre-existing `ESPressio_Serializable/ESPressio_Migration.hpp` `-Wmisleading-indentation` warning from `-Werror` **only for the Command contract compile invocation** (`-Wno-error=misleading-indentation`). All other warnings and workflow steps remain `-Werror`; no Serializable production code was modified.

Relevant commit sequence includes:

- `c1382835ed7f2a3fc067f71c5a6ed74e170b7183` — `Test frozen Command MeshAdapter binding`;
- `9eb4bfcbaa4c526c214e2ec4e6f17c914188d6bb` — `Validate Command MeshAdapter binding`;
- `24bf596ead97b1b210a732ab98955a7afefa4abf` — `Fix Command MeshAdapter fixture serialization setup`;
- `20ffe83bfcf301f26ecfc345b7e6ed4efe898deb` — `Add frozen State MeshAdapter family binding`;
- `ab3d326713390eb5f75769443fd210b402b36472` — `Isolate known Serializable warning in Command contract`.

### Command validation — current exact failure

Workflow **`34747352450`** at `ab3d326…` completed FAILURE, but it advanced materially:

- bounded Mesh->A2 ingress build/run: SUCCESS;
- neutral A2->Mesh lower-transport build/run: SUCCESS;
- real Event binding build/run: SUCCESS;
- real Command binding **build: SUCCESS**;
- real Command binding **run: FAILURE** at test assertion line 280, expecting first response-bearing inbound request M1 `Accepted`.

The runtime failure has been traced to a **test sequencing defect, not a production Command admission defect**. The test resolves valid unicast request provenance into `provenance`, then intentionally probes rejection of the same request as generic broadcast using that same object. `CommandMeshAdapterFamilyBinding::ResolvePolicy` correctly clears `provenance={}` at entry to prevent stale authenticated facts escaping a rejected resolution. The test then calls the real unicast `AdmitInbound` with that now-cleared object, so the binding correctly returns `Rejected` because `OriginalSource` is absent. The fix is to use a distinct `broadcastProvenance` variable for the negative broadcast probe, preserving fail-closed resolver semantics.

Do **not** weaken `ResolvePolicy` to retain stale provenance on rejection. Do **not** change production M1 mapping to make this test pass.

The broad Serializable include should still eventually be narrowed to `ESPressio_SerializationMacros.hpp`; connector safety checks blocked the large full-file rewrite during this session, so the workflow warning isolation is an explicit temporary validation workaround rather than a production dependency change.

### State validation status

The State binding exists at the live MeshAdapters head but does **not yet have its host contract/workflow step** and therefore must not be claimed green. Closed State semantics confirmed for integration:

- `StateValidatedIngressContext` carries the full `System::DeviceRuntimeIdentity` semantic source;
- State V1 message kind determines whether Owner or Requester is the semantic source;
- `ValidateStateSemanticSource` requires exact role-specific runtime-identity equality;
- `Runtime::AdmitRemote<TState,Format>` is the family security/session/convergence boundary;
- Transmissible State descriptors expose canonical convergence policy and bounded V1 wire maxima.

### Event M8-21 implementation status

The real Event family binding remains green. MeshAdapters contains `ESPressio_EventMeshAdapterBinding.hpp` and its host contract test. It uses fixed pre-freeze per-Type entries, real `Event::Runtime` inbound bindings/admission, Event receipt/idempotency/source-loop semantics, authenticated Mesh relay-service validation before A2 ownership, and no RTTI/heap registry/std::function/dynamic policy registry/per-occurrence policy object.

### Exact integration rules — do not regress

Mesh `IPrimitiveReceiver::Receive` is synchronous; A2 executes real family admission asynchronously on a T1 worker. Never collapse Adapter queue acceptance into M1 `Accepted`. The bridge intentionally returns a retry candidate until the real family M1 completion exists, then feeds that completion back through Mesh's existing generation-driven DeferredLocal mechanism. Network Seen/Forwarded state remains independent and is never repeated by this retry.

A2 route tokens remain opaque transport-integration values. Do not pack/truncate a 16-byte `DeviceIdentifier` into the 64-bit token. `AdapterSemanticProvenance::ImmediatePeer.Token` is the existing opaque physical/logical-peer transport fact; `OriginalSource` is semantic provenance and must remain distinct.

Command response-bearing inbound requests require a real pre-reserved `CommandRemoteResponseDestination`; response-bearing Command broadcast is rejected. Do not bypass Command persistence/replay/response-capability semantics.

State provenance is full `DeviceRuntimeIdentity` derived from authenticated State bytes after matching its DeviceIdentifier to Mesh-authenticated source. Never substitute Mesh membership incarnation. Delegate State session/convergence mutation to the real family runtime.

### Immediate continuation steps

1. Fix the Command contract negative broadcast probe to use a separate provenance object; rerun exact MeshAdapters workflow. Production `ResolvePolicy` fail-closed clearing must remain unchanged.
2. When Command is green, update this handoff immediately with exact MeshAdapters SHA/workflow run and mark the Command M8-22 slice green.
3. Add a real State host contract and workflow dependency closure for `ESPressio_StateMeshAdapterBinding.hpp`; validate semantic-source role handling, device/source mismatch rejection, generic broadcast rejection and delegation to real State admission.
4. Once State is green, update this handoff again immediately.
5. Complete locally-originated/outbound family integration through the neutral A2 lower-transport seam and bounded Mesh route-token composition without creating family-local retry/worker/fragmentation systems.
6. Remove predecessor Event-only MeshAdapter transport/submission files only after replacement inbound/outbound coverage is green; no shims.
7. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency gates, manifests/workflows/README/source comments, canonical Mesh/MeshAdapters umbrella audit and formal Tranche-8 report.
8. Update this file after every material checkpoint and before any session/usage stop with exact SHAs and CI run IDs. **Never leave unvalidated live-tip work absent from this card.**

## Remaining authorized structural work

After Tranche 8, continue without permission pause through Tranche 9 RadioAdapters/non-Mesh transports, Tranche 10 dynamic tooling/platform consumers and Tranche 11 platform-wide eradication/final structural validation. Tranche 12 release preparation remains outside the standing structural authorization.
