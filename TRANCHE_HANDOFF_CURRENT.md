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
- Tranche 7 Radio/providers: Radio `364f083c297e2072f7972f2fd63fcfa79cb6c1dd`, executable evidence `2a33d86c782ef25a25750ccd2b50b28191abd161`, CI `34719879383` SUCCESS; ESP32 closure `b29b53bc438a0d5013075ce58a501424c689c0a0`, CI `34716648904`; NRF24 closure `a641199da7d4e5101e4d2c871715a9c870bdc531`, CI `34716303385`. Provider source contracts did not drift in later README-only commits.

Tranche-7 physical qualification nonclaims remain explicit: Raw80211 RX capture stays Estimated until characterized; BLE cannot carry the exact 32-byte Clock response; NRF24 has no bounded/certified RX timestamp.

## Current tranche — Tranche 8 Mesh / MeshAdapters

### Current branch truth

- `ESPressio-Mesh/primitives_redesign` = `e21a4a7d7f527db59171477e27e12263231a7069`, redesign CI `34742545719` SUCCESS.
- `ESPressio-Adapters/primitives_redesign` = `77e034ec8d3efa4a8c8e6df0ef2f6a405f8dd98a`. A brief attempted family-admission signature expansion was reverted; the existing `AdapterSemanticProvenance::ImmediatePeer.Token` remains the correct opaque transport-peer fact.
- `ESPressio-MeshAdapters/primitives_redesign` = **`f09d5a1e9db6bf069216e37057d8167f6600bd07`** (`Correct Command contract provenance probe in validation`).
- exact MeshAdapters redesign workflow **`34747588394` — SUCCESS**.
- therefore the current **green MeshAdapters checkpoint is now `f09d5a1e9db6bf069216e37057d8167f6600bd07`**.

Do NOT call Tranche 8 complete yet. State family validation, full outbound family composition, predecessor removal, M8-23/M8-24 gates, manifests/workflows/docs/umbrella audit and formal Tranche-8 closure remain open.

### Mesh core checkpoint

The Mesh tip already contains major M8 core work: neutral M1 receiver semantics, six-class relay Q1/profile, non-increasing remaining residence, authenticated Seen/Forwarded separated from DeferredLocal admission, generic NoRemoteEvidence broadcast policy, managed-Radio next-hop submission, Mesh-only reference/topology orchestration, runtime-worker migration away from PrecisionThread/std::function, fixed lifecycle sinks and resource accounting.

### Green MeshAdapters integration contract at `f09d5a1…`

Validated together by workflow `34747588394`:

- bounded Mesh -> A2 ingress correlation;
- neutral A2 -> Mesh lower-transport composition;
- real Event family MeshAdapter binding;
- real Command family MeshAdapter binding, including real Command runtime, persistence, response reservation/routing, replay/idempotency and broadcast-policy semantics.

`src/ESPressio_MeshLowerTransportBinding.hpp` remains a thin lifecycle adapter: A2 owns logical pursuit/retry, Mesh owns routing/forwarding/application lifecycle, and Radio R3 owns physical fragmentation/arbitration. No duplicate worker, queue, route engine, retry engine or fragmentation engine was introduced.

### Mesh -> A2 ingress correlation — current contract

`src/ESPressio_MeshAdapterIngress.hpp` preserves the asynchronous M1/M2 boundary:

- correlation key = authenticated Mesh source device + Mesh membership incarnation + Mesh message ID;
- first Mesh `Receive()` transfers complete bytes to A2 and returns retryable; A2 ownership is NEVER destination Primitive admission;
- exact family M1 returned later by `AdapterInboundCompletionTarget` is retained;
- generation wake drives Mesh `DeferredLocal` retry, which consumes stored M1 without re-enqueueing A2;
- pending duplicate local retries do not duplicate A2 work;
- only exact family `Accepted`/`AlreadyAccepted` establishes destination Primitive admission;
- try-lock behavior keeps remote ingress bounded/nonblocking.

The bridge never converts Mesh `MembershipIncarnation` into Primitive/System `RuntimeIncarnationId`. A family may validate a runtime identity carried by authenticated family bytes only after proving its `DeviceIdentifier` equals the authenticated Mesh source.

### Event M8-21 status

Event remains green. The real Event family binding uses fixed pre-freeze per-Type entries, real `Event::Runtime` inbound admission, Event receipt/idempotency/source-loop semantics and authenticated Mesh service validation. Generic broadcast rejects `DestinationPrimitiveAdmission`; only `NoRemoteEvidence` is allowed. Historical Event checkpoint `bb1c1ff1fe6f6bd60c3f79deb3183f7961198841`, run `34744901323` SUCCESS.

### Command M8-22 status — GREEN

`src/ESPressio_CommandMeshAdapterBinding.hpp` is now validated against the real Command/Persistence/Task runtime at `f09d5a1…`, workflow `34747588394` SUCCESS.

Validated semantics include:

- fixed frozen per-Type binding; no dynamic registry/worker/retry loop;
- role-correct authenticated semantic provenance;
- response-bearing inbound requests receive a bounded pre-reserved `CommandRemoteResponseDestination`;
- retained typed response is synchronously offered to A2, after which A2 owns the P2 delivery campaign;
- response-bearing request broadcast rejected;
- no-response `NoRemoteEvidence` request may use generic broadcast;
- responses never use generic broadcast;
- exact duplicate terminal request is family-idempotent and does not rerun the handler;
- opaque route tokens remain transport facts and are never packed/truncated Device identifiers.

M1 mapping remains:

- `Admitted` -> `Accepted`;
- `DuplicateTerminal`, `StaleOriginRuntime`, `ExecutionHistoryExpired` -> `AlreadyAccepted`;
- `InProgress`, `TemporarilyUnavailable` -> `TemporarilyUnavailable`;
- `LedgerCapacityUnavailable` -> `ResourceUnavailable`;
- `UnknownType`, `UnsupportedProtocol` -> `Unsupported`;
- `NoActiveRequester` -> `Rejected`;
- invalid/schema/decode failure -> `Malformed`.

The previous runtime failure in `34747352450` was proven to be a test sequencing defect: a negative broadcast resolution correctly cleared a reused provenance object. The green workflow uses a distinct `broadcastProvenance` in the runner checkout, preserving production `ResolvePolicy` fail-closed clearing. Do not weaken that behavior.

Two test-harness cleanups remain explicitly open because the connector rejected direct replacement of the ~20 KB test source during this session:

1. commit the separate `broadcastProvenance` source edit directly into `tests/command_mesh_adapter_binding_test.cpp` when a suitable write path is available;
2. replace broad `ESPressio_Serializable.hpp` with `ESPressio_SerializationMacros.hpp`, then remove the Command-only workflow `-Wno-error=misleading-indentation` workaround. The warning comes from pre-existing `ESPressio_Migration.hpp`, not MeshAdapters production code.

These harness cleanups do not weaken the green production/runtime result, but should be completed before formal Tranche-8 closure.

### State M8-22 status — IMPLEMENTED, NOT YET VALIDATED

`src/ESPressio_StateMeshAdapterBinding.hpp` exists but still requires a real State host contract/workflow step.

Locked integration semantics already confirmed:

- `StateValidatedIngressContext` carries full `System::DeviceRuntimeIdentity` semantic source;
- State V1 message kind determines whether Owner or Requester is semantic source;
- `ValidateStateSemanticSource` requires exact role-specific runtime-identity equality;
- `State::Runtime::AdmitRemote<TState,Format>` is the family security/session/convergence boundary;
- Transmissible State descriptors expose canonical convergence policy and bounded V1 wire maxima;
- MeshAdapters may parse enough authenticated State wire to determine role/type and validate `DeviceIdentifier`, but MUST NOT reproduce State session/version/baseline/resync/convergence mutation;
- generic State broadcast is rejected;
- Mesh membership incarnation is never substituted for State/System runtime incarnation.

### Exact integration rules — do not regress

Mesh `IPrimitiveReceiver::Receive` is synchronous; A2 family admission is asynchronous. Never collapse Adapter queue acceptance into M1 `Accepted`.

A2 route tokens remain opaque transport-integration values. `AdapterSemanticProvenance::ImmediatePeer.Token` is the physical/logical-peer fact; `OriginalSource` is semantic provenance.

Command response-bearing requests must preserve real Command persistence/replay/response capability semantics.

State semantic provenance is full `DeviceRuntimeIdentity` derived from authenticated State bytes after matching its Device to Mesh-authenticated source. Delegate all State session/convergence mutation to the family runtime.

### Immediate continuation steps

1. Add real State host contract and workflow dependency closure for `ESPressio_StateMeshAdapterBinding.hpp`; validate Owner/Requester semantic-source role handling, Device/source mismatch rejection, generic broadcast rejection, service mismatch rejection and delegation to real State admission.
2. On State green, update this handoff immediately with exact MeshAdapters SHA/workflow run.
3. Complete locally-originated/outbound family integration through the neutral A2 lower-transport seam and bounded Mesh route-token composition without family-local retry/worker/fragmentation systems.
4. Remove predecessor Event-only MeshAdapter transport/submission files only after replacement inbound/outbound coverage is green; no shims.
5. Complete M8-23/M8-24 security/resource/fuzz/multi-node/dependency gates, manifests/workflows/README/source comments, canonical Mesh/MeshAdapters umbrella audit and formal Tranche-8 report.
6. Complete the two Command test-harness cleanups before formal closure.
7. Update this file after every material checkpoint and before any session/usage stop with exact SHAs and CI run IDs. **Never leave unvalidated live-tip work absent from this card.**

## Remaining authorized structural work

After Tranche 8, continue without permission pause through Tranche 9 RadioAdapters/non-Mesh transports, Tranche 10 dynamic tooling/platform consumers and Tranche 11 platform-wide eradication/final structural validation. Tranche 12 release preparation remains outside the standing structural authorization.
