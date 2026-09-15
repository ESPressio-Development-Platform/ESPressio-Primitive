# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest continuation update: **after successor re-baseline and first V11-15 Labs validator migration**
Continuation state: **Structural Tranches 0–10 CLOSED/GREEN; Tranche 11 ACTIVE; V11-01 through V11-14 CLOSED/GREEN; V11-15 ACTIVE; V11-16 CLOSED/GREEN; V11-17 CLOSED; V11-18 ACTIVE/BLOCKED; V11-19/V11-20 PENDING.**

This is the canonical living continuation card. The complete Primitive Platform Redesign architecture/design handoff remains authoritative for locked architecture, ownership, dependency boundaries, wire contracts, resource rules, lifecycle/admission semantics, tranche ordering and completion gates. Live branch tips are implementation truth and MUST be re-queried immediately before every mutation.

## Authorization boundary

Implementation is continuously authorized through structural Tranche 11. Do not pause between V11 steps to request permission.

**Structural Tranche 12 / release preparation is NOT authorized.** Do not change versions, finalize release-version CHANGELOGs, reintegrate to `main`, create tags/releases, publish release material, or force-push. Do not introduce compatibility shims, aliases or predecessor facades merely to keep stale Labs/tests/examples compiling.

## Mandatory non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission. Only `Accepted` / `AlreadyAccepted` establishes destination Primitive admission.
- Radio/R3 owns physical fragmentation, reassembly and contention arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer which understands both Radio and Primitive-family contracts; generic Adapters remains Radio-neutral.
- Direct-Radio Primitive envelope remains exactly four bytes: 2-byte LE family id + 2-byte LE protocol version.
- Immediate physical peer/address and authenticated semantic `OriginalSource` are distinct facts. Never infer semantic provenance from a Radio peer/address/handle.
- Mesh remains family-neutral and must not regain direct Event/Command/State ownership.
- No family-local fragmentation engine, retry worker/queue, duplicate family runtime or bespoke transport manager may return.
- Registration/topology freezes before Running; runtime work is bounded and ingress nonblocking.
- TypeDirectory/P3/descriptors/schema/factory metadata are discovery/constructibility metadata, not authorization.
- Generic State tooling is read/inspect only; owner-authoritative mutation remains owner-path only.
- State remote admission cross-checks encoded owner/requester identity against adapter-validated semantic OriginalSource.
- Unauthenticated Radio service-class claims cannot grant protected capacity. Untrusted ingress remains quarantined until a higher trust layer validates the complete logical payload and explicitly promotes the validated service class.
- Threads has one root task/stack/common Wake per `ThreadWith<TCapabilities...>` composition; no reusable specialized Thread flavors.
- Timing owns final clock reliability/evidence vocabulary (`TimeReliability`).
- System remains free of Persistence. Persistence points downward to System/Serializable/Security.
- Threads does not depend upward on Event/Command/State; Timing does not depend upward on Threads; Command does not depend on Event; Radio does not know Primitive families; Mesh does not directly depend on Event/Command/State.
- No structural-tranche version changes.

## Tranche 11 gate status

1. V11-01 exact-tip freeze — CLOSED
2. V11-02 branch-specific removed-symbol/source/include scan — CLOSED
3. V11-03 examples/demos/Labs/wiki/README/generated-CI-fixture scan — CLOSED as audit; Labs remediation carried into V11-15/V11-18
4. V11-04 final dependency DAG — CLOSED
5. V11-05 forbidden dependency/branch guards — CLOSED
6. V11-06 semantic classification of existing tests — CLOSED
7. V11-07 host/public-header/no-RTTI/no-exception/sanitizer validation — CLOSED/GREEN
8. V11-08 codecs/fuzz/malformed/property validation — CLOSED/GREEN
9. V11-09 capacity/exhaustion/no-hidden-heap validation — CLOSED/GREEN
10. V11-10 shutdown/restart/generation/stale-handle validation — CLOSED/GREEN
11. V11-11 provider physical completion/readiness/cost/timestamp validation — CLOSED/GREEN
12. V11-12 multi-device Mesh broadcast/relay/congestion/failover validation — CLOSED/GREEN
13. V11-13 qualified Clock load/uncertainty/reference-switch validation — CLOSED/GREEN
14. V11-14 Command/Persistence crash/reboot/exactly-once-evidence validation — CLOSED/GREEN
15. **V11-15 Web/Lua/Serial/WiFi/ESP32/Demos/Labs integration — ACTIVE because Labs remains incomplete**
16. V11-16 deterministic memory/resource reports — CLOSED/GREEN
17. V11-17 unavailable automation/fallback evidence — CLOSED
18. **V11-18 final live-doc/API/example eradication scan — ACTIVE/BLOCKED by live Labs predecessor surfaces**
19. V11-19 repository-by-repository validation matrix + exact evidence — PENDING
20. V11-20 release-preparation blocker audit — PENDING

## Closed evidence highlights

- Structural Tranche 10 close: Primitive `243014060ce19ad783d59bc742110f8af12894a5` (D10-19) and `670ad84b37d5cd3cd4d2c4f0ec522b80604495a5` (D10-20); Platform runs `34946740550` and `34947850970` GREEN.
- V11-07 Platform `34969584258`, job `104407017114` SUCCESS.
- V11-08 Platform `34978625033`, job `104412783040` SUCCESS.
- V11-09 Primitive `b72d34a972d93c2d1e9fdace477983ba8985877f`; Platform `34979178551`, job `104414679441` SUCCESS.
- V11-10 Primitive `45346226b3af35f66453591f61cabfc0b1e460c3`; Platform `34979811958`, job `104416871448` SUCCESS.
- V11-11 Platform `34981104491`, job `104421331248` SUCCESS.
- V11-12 Mesh repair `7f58cd03f9e32c9db0eda2ef5d59b76ff3bc1442`; Mesh `34982501502` SUCCESS; Platform retry job `104426279651` SUCCESS.
- V11-13 validation runner `e86120cb5484f27d90e6bd4e89b96b17f79b606a`; closed on successful Platform retry.
- V11-14 Primitive `a6371668cdf2ed8659e95191fdd9e568d6dde333` + `af72ed65acaada50a5415c58cf2ce5401387ed5f`; Persistence `cf310f2f00673ecc63720b604a7dd4a336ba80f5`; Platform retry job `104432647092` SUCCESS.
- V11-16 Primitive `a726256cccf2032d1cb5ed761d5cc8a09e2a9d78` + execution `523924b461fa75ff3a41dbeb1e6dcfa7c1fe3f4e`; exact V11-16 run `34987271889` GREEN.
- V11-17 Primitive `3fdc769797d4e061ae0be92a0726009d03b97179`; classification vocabulary: `AUTOMATION_EXECUTED`, `AUTOMATION_UNAVAILABLE_PRE_EXECUTION`, `FALLBACK_SUFFICIENT`, `FALLBACK_INSUFFICIENT`. A no-step job is never relabelled as successful.

## Radio provider progression already completed for Labs

Radio `primitives_redesign` exact resume anchor before any later change: `42094fadfd641e3d65bf6ec177b8221e527832ec` — `Prove provider Clock ingress routing through Radio runtime`; exact-tip redesign workflow `34998922399` SUCCESS.

The final family-neutral provider contract now includes:

- bounded `CopyCompleteForValidation(...)` / runtime `CopyInboundForValidation(...)` for complete quarantined logical transfers;
- readiness notification for trusted or quarantined completion;
- explicit trust state on inbound transfer handles;
- explicit promotion only after higher-layer validation;
- exact discard for completed invalid/unusable records;
- provider Clock ingress through the same final Radio-owned ingress/domain path.

Security semantics remain: untrusted service claims stay quarantined, higher layer copies into bounded caller-owned validation storage, validates/authenticates, then explicitly promotes validated service class or discards. Radio remains Mesh/family-neutral.

## V11-15 public integrations already green

Public integration evidence already recorded GREEN includes Web, Lua, Serial, WiFi and ESP32. `ESPressio-Demos` has no operative redesign build surface and is N/A; do not manufacture work.

## WROOM-32 20-node Mesh Lab — active migration frontier

Historical physical Lab branch remains preserved. All redesign integration work is on `Labs/primitives_redesign`.

Provider-side progression already landed before this continuation:

- `71ba7f455c00433a7150d84b7401bb8170f3be7c` — repoint Lab dependencies to redesign graph.
- `017a5baaa7ef3fd690a4ef02996e24a27007f316` — enable validation workflow on redesign branch.
- `1173bbe3434233f31e5c03e3e4d4c208405ab170` — migrate inbound queue toward final Radio handoff.
- `11a01d5d317a2f37cbc582d5535d8d399a2456bd` — add final RadioRuntime Lab ingress bridge.
- `22d742a13e3babb89d88170c2cc0a45410cac86c` — add bounded final Lab RadioRuntime composition.
- `506849eed80568cacc013def6dbd8c88d7131fbe` — preserve physical source address through ingress.
- `44b53b874478f1adef6c2e1e34cdbc77991850df` — carry exact Radio source into Lab handoff.
- `f57974f048c009658463e48f866fc230dcac888f` — move Lab Clock toward final Radio domain runtime.
- `4623749343d4a0974fddd536eed6f9156f20eda7` — tighten Lab Clock control synchronization.

### Successor work completed after re-baseline

- Re-baselined Primitive, Radio, Labs, Mesh, MeshAdapters, Adapters, Event, Command and State exact `primitives_redesign` tips before mutation; no intervening changes were found relative to the successor handoff anchors.
- `Labs/primitives_redesign` advanced to `6c154651276bc6439d34b32d4c46dbf8ba4be873` — **`Migrate Mesh Lab validator to final architecture`**.
- `Mesh/WROOM32-20Node-Mesh-Lab/scripts/validate_lab.py` is now a target-state positive/negative guard rather than a predecessor-architecture validator. It requires redesign dependency pins and final managed-Radio/Clock composition and rejects active `RadioTransport`, `RadioWorker`, `RadioControlWorker`, predecessor Clock synchronizers, `CommandRegistry`, Event-specific predecessor transport/listener ownership, direct State/Command Mesh receivers and legacy State publisher/remote-manager patterns.
- The validator deliberately remains RED while the source still contains those genuine predecessor surfaces; it was not weakened to obtain a pass.
- The validator's generic inbound marker should use the exact final class name `MeshAdapters::MeshAdapterIngressBridge` during the next edit (the first target-state commit used the shorter textual marker `MeshAdapterIngress`).
- The validator's Broadcast clock check must also be updated to final Mesh broadcast semantics: final `MeshV1BroadcastCoordinator::Submit` consumes monotonic start + finite remaining residence under a validated broadcast policy; the predecessor absolute-deadline expression is not a final API requirement.

### Hosted automation classification after validator commit

Fresh Labs run `35019986717` on the validator commit again has all jobs with no executable steps/no runner. Classify it as **`AUTOMATION_UNAVAILABLE_PRE_EXECUTION`**, not source success or source failure. Independent static/source validation remains required.

### Confirmed current source blockers

Current root/controller source is still genuinely predecessor architecture and must be migrated, including:

- root `Radio::RadioTransport`, `Radio::RadioWorker`, `Radio::RadioControlWorker` and predecessor `RadioClockSynchronizer` ownership;
- old worker/Clock diagnostics tied to those workers;
- controller ownership of `RadioTransport` and `RadioClockSynchronizer` arrays;
- `Command::CommandRegistry` for both remote Ping behavior and local console parsing;
- predecessor Event listener/receiver, `EventTransportManager`, Event-specific Mesh transport/packet/outbound queue ownership;
- direct Command/State Mesh primitive receivers;
- legacy State publisher/remote manager architecture.

The final provider objects already exist (`LabRadioRuntime`, `LabRadioIngress`, `LabClockTransport`); do not duplicate them.

### Canonical final composition target

Physical:

`ESP32 Raw80211/BLE providers -> LabRadioRuntime / final RadioRuntime + Q1/R3/domain task -> bounded readiness/quarantine-copy -> higher-layer validation -> explicit promotion or exact discard -> Mesh ingress`

Inter-domain:

`Mesh (family-neutral) -> generic A2 / MeshAdapters -> typed Event/Command/State runtimes`

Family:

- Event: final serializable Event descriptor/runtime/admission/listener model; no Event-specific Mesh transport manager/queue/receiver service loop.
- Command: final typed `TransmissibleCommand` / runtime / response semantics; no `CommandRegistry`, no Event bridge.
- State: State owns definitive transmissible memory and owner-authoritative write path; remote convergence/admission through final State adapter/runtime; no legacy publisher/remote-manager path.

Execution:

- one Radio domain task per contention domain;
- Clock shares final Radio domain scheduling/ingress;
- no separate Radio/Clock/family workers which recreate predecessor ownership.

### Behaviors that must survive the migration

- twenty-node bounded PlatformIO matrix and existing feature environments;
- Raw Wi-Fi default on, BLE default off, optional WiFi/Web mode;
- device identity/security/admission and authenticated liveness;
- authenticated Mesh broadcast diagnostics and the Lab-owned custom test Primitive;
- Ping/Pong test semantics through final Command/Event contracts;
- State visibility/convergence through final State + MeshAdapters architecture;
- disciplined System Clock and sub-millisecond evidence/telemetry requirements;
- deterministic bounded memory/root task reservation diagnostics;
- request-handling Device Identifier in Web status;
- persistent logging/diagnostics.

## Exact continuation procedure

Proceed continuously inside Tranche 11:

1. re-query `Labs/primitives_redesign` before every mutation;
2. finish physical/root cutover onto `LabRadioRuntime` + `LabClockTransport`; preserve exact physical source and never promote it into semantic OriginalSource;
3. migrate Event/Command/State onto generic A2/MeshAdapters + final typed family runtimes, using current MeshAdapters tests/public headers as canonical composition examples;
4. use final Serial console handlers (or bounded Lab-local parser) for operator commands; do not retain `CommandRegistry` merely for shell parsing;
5. migrate validator/comments/docs to exact final APIs and negative predecessor guards;
6. validate honestly. If hosted jobs still have no steps, retain `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` and obtain static/consumer/focused evidence where execution is available;
7. close V11-15 only when active Labs source is final-architecture clean;
8. run V11-18 full live eradication scan across active source/examples/docs/validator;
9. produce V11-19 repository-by-repository exact-SHA/evidence/fallback matrix;
10. run V11-20 release-preparation blocker audit; unresolved stale paths remain explicit RED;
11. **STOP before Structural Tranche 12 unless separately authorized by the user.**

## Current resume anchors

Re-query these before any write; values below are evidence/resume anchors only:

- Primitive `primitives_redesign`: `3fdc769797d4e061ae0be92a0726009d03b97179` before this handoff-only update; updating this file advances Primitive.
- Radio `primitives_redesign`: `42094fadfd641e3d65bf6ec177b8221e527832ec`.
- Labs `primitives_redesign`: `6c154651276bc6439d34b32d4c46dbf8ba4be873`.
- Mesh `primitives_redesign`: `7f58cd03f9e32c9db0eda2ef5d59b76ff3bc1442`.
- MeshAdapters `primitives_redesign`: `273407ffa4b20a12d5923a918e1db30c348f269d`.
- Adapters `primitives_redesign`: `8a9dc6ce5f4c57361824637a1d614f7699e5dc73`.
- Event `primitives_redesign`: `532d04e1200b04b5734b68467018c597ae996223`.
- Command `primitives_redesign`: `658a9f9064a8ef58a0016d041a29be0c8ca3da7f`.
- State `primitives_redesign`: `25637a7555e3a03f1d709bd8e37340bc4d545b6e`.

Immediate active work: **V11-15/V11-18 WROOM-32 20-node Mesh Lab final root + family migration**. Do not begin release preparation.
