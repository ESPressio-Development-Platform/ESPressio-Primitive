# Primitive Platform Redesign — Structural Tranche 9 Closure

Date: 2026-09-14
Status: CLOSED

`ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for the locked architecture and governance. This report records the implementation and validation evidence used to close structural Tranche 9 (transport and adapter consolidation) after R9-25 documentation/integration closure.

No version number was changed by this closure. No `main` reintegration, release, tag, compatibility shim, or release/CHANGELOG finalization is part of this work.

## 1. Final ownership boundary

The closed Tranche-9 transport plane preserves the following ownership split:

- Primitive family runtimes own family semantics, exact representation, and exact M1 admission meaning.
- `ESPressio-Adapters` A2 owns synchronously-admitted complete Primitive-family bytes/records, bounded retained pursuit, and shared T1 worker execution.
- `ESPressio-Radio` R3 owns physical scheduling, fragmentation/reassembly, physical transfer identity, contention, and physical/direct-link evidence while remaining Primitive-family-neutral.
- `ESPressio-RadioAdapters` is the only direct-Radio composition layer that understands both Primitive-family metadata and Radio. It owns the exact four-byte direct-Radio family prefix, neutral service mapping, provenance/route mapping, and exact-M1 correlation.
- `ESPressio-ESP-Now` is a managed ESP-NOW physical `Radio::IRadio` provider only.
- `ESPressio-Sockets` owns bounded neutral socket/session mechanics and neutral A2 framing/correlation, plus genuine socket Security/Timing mechanics; it does not own parallel Event/Command/State execution stacks.
- Serial and WiFi do not own a canonical device-to-device Primitive byte transport in Tranche 9. Their remaining local tooling/family-consumer migration belongs to Tranche 10.

Only Primitive-family `Accepted` or `AlreadyAccepted` establishes `DestinationPrimitiveAdmission`. Physical/link acceptance, MAC acknowledgement, socket write acceptance, Adapter ownership, or Radio terminal success never substitutes for M1.

## 2. Closure checkpoints

Final source/documentation checkpoints used for R9-25 closure:

| Repository | `primitives_redesign` checkpoint | Closure state |
|---|---|---|
| Adapters | `8a9dc6ce5f4c57361824637a1d614f7699e5dc73` | final A2 docs/example/tests/workflow aligned; exact-tip workflow green |
| RadioAdapters | `337859721246ab613c354a8073943e2d5c588946` | final README/source architecture aligned; eight exact-tip workflows green |
| Radio | `a43e700cd20b287217f805cebedc6e9fc126ca48` | final provider/R3 documentation aligned; exact-tip redesign workflow green |
| ESP-NOW | `a1718047c777a09656fc652be12a3dd99ce69624` | provider-only source/docs aligned; hosted Actions unavailable before runner allocation |
| Sockets | `3c0d23255295bc9b6609af1390b5c47ed6750641` | final neutral socket/A2 docs aligned; three exact-tip workflows green |
| Serial | `3ef07be4252908458110682291fd6b1c1d181262` | negative transport classification retained; tooling migration deferred to D10-12/D10-13 |
| WiFi | `8f959f19fbf4f7c3af42223ccc27521a4728f5dd` | no direct remote Primitive transport; local consumers/worker deferred to D10-14/D10-15 |

The deterministic finite-resource model remains recorded separately in `TRANCHE_9_RESOURCE_ACCOUNTING.md`.

## 3. Exact-tip validation evidence

### 3.1 Adapters

At `8a9dc6ce5f4c57361824637a1d614f7699e5dc73`:

- `Adapters architecture contracts` run `34818506121` — **SUCCESS**.
- The run covers the complete host contract suite plus the ESP32 full A1/Q1/A2 surface compile.
- R9-25 found stale test/example/workflow fixtures that still used the pre-metadata lower-transport callback shape. They were migrated to the final callback carrying family, protocol, Primitive policy, neutral service, immutable bytes, and opaque route metadata.
- One latent fixture configured only 64 bytes for a current `AdapterWorkRecord`; it was corrected to a deterministic fitting record capacity.
- The mixed-policy test was corrected to respect A2's nonblocking admission contract: transient `Busy`/`ResourceUnavailable` may be retried by the test harness, while every non-transient result remains fail-closed.
- No production A2 semantic change was required by these R9-25 corrections.

### 3.2 RadioAdapters

At `337859721246ab613c354a8073943e2d5c588946`, all eight permanent exact-tip workflows are **SUCCESS**:

- exact M1 `34815298447`
- outbound `34815298347`
- redesign `34815298281`
- Event direct-Radio `34815298299`
- State direct-Radio `34815298326`
- ingress `34815298283`
- lifecycle restart `34815298303`
- Command direct-Radio `34815298307`

These gates cover fixed direct-Radio envelope vectors, family bindings, ingress/outbound ownership, all seven exact M1 dispositions, direct-link-vs-M1 separation, lifecycle generation, stale completion suppression, and Event/Command/State integration.

### 3.3 Radio

At `a43e700cd20b287217f805cebedc6e9fc126ca48`:

- `Radio redesign contracts` run `34815347501` — **SUCCESS**.

Radio remains Primitive-family-neutral and owns physical scheduling/fragmentation/reassembly plus provider resource/cost/evidence contracts.

### 3.4 Sockets

At `3c0d23255295bc9b6609af1390b5c47ed6750641`, all exact-tip workflows are **SUCCESS**:

- neutral Socket Adapter transport `34815223517`
- Host Tests / package guard `34815223486`
- Security Integration `34815223715`

The final source exposes bounded neutral session/framing/correlation and K1/K2 clock evidence without retaining predecessor family transport/execution stacks.

### 3.5 ESP-NOW automation fallback classification

At `a1718047c777a09656fc652be12a3dd99ce69624`:

- Tests run `34815106167`
- ESP-NOW Radio provider run `34815106156`

GitHub reports these runs as failed, but every job has `steps=[]` and `runner_id=0`. No checkout, build, test, or repository code executed. Per the architecture's automation-fallback rule, this is **automation unavailable before meaningful execution**, not a code/test failure.

Fallback evidence remains:

- recursive source/manifest/workflow audit proving the production provider-only boundary;
- package dependencies reduced to System + Radio;
- repository-owned provider contract fixtures for both relevant ESP-IDF callback signatures;
- earlier independent local dual-IDF harness execution under `-Wall -Wextra -Werror`, covering deferred unicast completion/ACK, broadcast completion without peer ACK, terminal failure, bounded RX, Busy on a second concurrent send, and lifecycle-generation separation.

The hosted ESP32/provider jobs remain an explicitly recorded automation uncertainty; they do not weaken or reinterpret any contract.

## 4. Architecture completion gate

The R9-25 / Tranche-9 completion gate is closed item-by-item as follows.

1. **Exact four-byte RadioAdapters prefix** — CLOSED. The canonical direct-Radio envelope is exactly two little-endian bytes of `PrimitiveFamilyId` plus two little-endian bytes of `PrimitiveProtocolVersion`; fixed-vector RadioAdapters tests are green.
2. **Dependency neutrality** — CLOSED. Radio has no Primitive-family dependency; Adapters has no Radio dependency. Their manifests/workflow guards preserve the locked DAG.
3. **Event/Command/State direct-Radio use A1/A2 and exact M1** — CLOSED. Dedicated RadioAdapters family bindings and their exact-tip family workflows are green.
4. **Link/peer ACK is never destination admission** — CLOSED. Radio/ESP-NOW physical/direct-link evidence is distinct from M1; RadioAdapters exact-M1 tests enforce that only `Accepted`/`AlreadyAccepted` promotes destination admission.
5. **ESP-NOW duplicate Event fragmentation/reassembly removed** — CLOSED. The former Event transport/runtime/fragmentation stack is absent; physical fragmentation/reassembly belongs to Radio R3.
6. **ESP-NOW clock path obeys K1/K2 ownership** — CLOSED. Fixed-cadence/historical reconstruction was removed; provider-proximate capture supplies monotonic coordinate/model/uncertainty while Timing owns estimation/discipline.
7. **Sockets bounded neutral transport/session** — CLOSED. Parallel Event/Command/State socket stacks and predecessor Event bridges are removed; exact-tip neutral/Security/host gates are green.
8. **Serial correctly classified** — CLOSED as a negative transport classification. Current Serial is operator/terminal tooling, not a canonical remote Primitive byte transport. Family-aware consumer cleanup is handed to D10-12/D10-13; no synthetic Tranche-9 transport was invented.
9. **WiFi correctly classified** — CLOSED as no direct remote Primitive transport. Existing `WiFiEventBridge`/`WiFiCommandHandler` are local consumers rather than remote transport ownership. Their predecessor family-API cleanup is handed to D10-14; `WiFiWorker` to D10-15.
10. **Finite backpressure and generation-safe restart** — CLOSED. A2 retained pursuit, RadioAdapters M1/reassembly/lower-transport correlation, Radio provider scheduling, ESP-NOW provider state, and Sockets session/correlation are all fixed-capacity and generation-bounded; temporary pressure cannot create an unbounded retry engine.
11. **No predecessor family transport broker remains canonical** — CLOSED. `EventTransportManager`, old Event bridge transport stacks, and CommandRegistry-based remote transport paths are not canonical Tranche-9 transport architecture. Remaining local consumer uses are explicitly Tranche-10 migration work, not transport ownership.
12. **No duplicate transport worker where A2/T1 owns execution** — CLOSED. Generic A2 owns the shared family work execution/pursuit responsibilities; provider/transports retain only their genuine bounded physical/session work.
13. **Manifest/DAG/branch-ref compliance** — CLOSED. Audited redesign manifests use the locked downward dependency direction and redesign refs; stale Sockets family metadata was removed; RadioAdapters intentionally has no artificial package manifest.
14. **Existing tests semantically classified before execution** — CLOSED. R9-25 did not blindly accept legacy tests: the Adapters audit identified stale callback fixtures, a stale capacity fixture, and an invalid wait-free timing assumption, corrected them to the final contracts, then re-ran exact-tip validation green.
15. **No version number changed** — CLOSED. Structural Tranche 9 introduced no version bump.

## 5. Documentation / example closure

R9-25 audited the final public README/source-comment/example surfaces for Adapters, RadioAdapters, Radio, ESP-NOW, and Sockets against their actual current APIs.

- RadioAdapters now documents the exact four-byte envelope, A2 ownership, exact M1, lifecycle, provenance, and Event/Command/State bindings.
- Radio documents its family-opaque R3/provider responsibility.
- ESP-NOW documents provider-only ownership and no longer carries the obsolete dependency diagram or predecessor family transport examples.
- Sockets documents the neutral bounded A2/session surface and retains only genuine socket/Security examples.
- Adapters documentation now describes MeshAdapters and RadioAdapters as implemented integrations rather than future work; the mock example and CI fixture compile against the final lower-transport metadata seam.

No compatibility documentation was retained for removed predecessor transport architecture.

## 6. Promotion

Structural **Tranche 9 is CLOSED**.

The next authorized work is structural **Tranche 10 — common/dynamic consumer migration**, beginning with **D10-01: expose/consume the final Primitive TypeDirectory discovery surface in dynamic tools**. Tranche 10 must consume the closed provider/family contracts rather than weakening them for compatibility. Tranche 12 release preparation remains separate and unauthorized.
