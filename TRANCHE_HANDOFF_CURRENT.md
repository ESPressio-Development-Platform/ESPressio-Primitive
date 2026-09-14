# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-14
Continuation state: structural Tranche 9 CLOSED; Tranche 10 ACTIVE at D10-02
Latest user time reference: 09:50 Europe/Prague

This is the live continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for CLOSED/LOCKED architecture, governance, dependency order, tranche gates and historical decisions. `TRANCHE_9_CLOSURE.md` is the formal Tranche-9 closure evidence. Live source branch tips remain implementation truth and MUST be rebaselined before every implementation step.

## Authorization boundary

Implementation remains authorized through structural Tranches 8–11 without further permission pauses. Version changes, release/CHANGELOG finalization, `main` reintegration, tags/releases, Wiki publication, force pushes and backward-compatibility shims remain outside authorization. Tranche 12 release preparation remains separate and unauthorized.

The user requires this living handoff to remain present on `ESPressio-Primitive/primitives_redesign` and to be mirrored as an up-to-date downloadable conversation artifact whenever substantive progress is reported.

## Mandatory continuation protocol

Before changing any repository:

1. re-query the exact source-branch tip;
2. inspect the current manifest/dependency boundary before implementation source;
3. consume already-closed provider contracts rather than reintroducing predecessor APIs for compatibility;
4. classify existing tests/examples semantically before migrating or executing them;
5. keep changes small/coherent and validate exact-tip workflows;
6. update this handoff in the same work session after substantive progression.

Do not infer current implementation state from old tranche checkpoint hashes alone. Later branch tips supersede older implementation snapshots while the architecture handoff continues to own locked design/governance.

## Locked non-regression rules

- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning.
- Only `Accepted` / `AlreadyAccepted` establishes `DestinationPrimitiveAdmission`.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Direct-Radio family envelope remains exactly 4 bytes before unchanged family representation: 2-byte LE family + 2-byte LE protocol.
- Immediate physical peer and validated semantic `OriginalSource` remain distinct provenance facts.
- Mesh membership incarnation is never a System runtime incarnation.
- Adapter route/peer tokens are opaque transport facts and never encode/truncate `DeviceIdentifier`.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Every neutral non-Mesh transport has finite lifecycle/generation; restart invalidates prior handles/correlation and stale completions cannot become current work.
- Temporary backpressure/disconnection/restart must not create unbounded retry.
- Dynamic/common consumers in Tranche 10 consume final descriptors/factories/diagnostics; they do not become new semantic owners.
- Generic State access from dynamic tooling is read/inspect/observe only unless an explicit typed State owner API authorizes mutation.
- TypeDirectory/schema availability is discovery metadata, never authorization.
- All dynamic input is bounded before parse/construction; parse/schema/factory failure is explicit and does not fall back to unbounded heap, reinterpretation or exception-driven retries.
- No structural-tranche version changes.

## Closed foundation / structural work

Foundation F01–F08 and structural Tranches 2–9 are CLOSED.

Key closure artifacts:

- Tranche 8: Mesh closure report `TRANCHE_8_CLOSURE.md`; Mesh closure checkpoint `a832ce41c7ebd6174c7a06835ea24a871f843dcc` with the promoted Mesh/MeshAdapters contract suite already recorded in the architecture history.
- Tranche 9 finite resource accounting: `TRANCHE_9_RESOURCE_ACCOUNTING.md`.
- Tranche 9 formal closure: `TRANCHE_9_CLOSURE.md`, created at Primitive commit `27896d57002e9a4cffa543299fadd4255817727d`.

## Structural Tranche 9 — CLOSED

Tranche 9 consolidated remote transport ownership onto A2 / Radio R3 / final family bindings and retired predecessor parallel Event/Command/State transport stacks.

Final R9-25 checkpoints at closure:

- **Adapters** `8a9dc6ce5f4c57361824637a1d614f7699e5dc73` — final A2 README/example/test/workflow surfaces aligned with the family/protocol/policy-aware lower-transport metadata seam. Exact-tip `Adapters architecture contracts` run `34818506121` SUCCESS across host contracts and ESP32 full-surface compile.
- **RadioAdapters** `337859721246ab613c354a8073943e2d5c588946` — final architecture documentation aligned. Eight exact-tip workflows SUCCESS: exact M1 `34815298447`, outbound `34815298347`, redesign `34815298281`, Event `34815298299`, State `34815298326`, ingress `34815298283`, lifecycle `34815298303`, Command `34815298307`.
- **Radio** `a43e700cd20b287217f805cebedc6e9fc126ca48` — final provider/R3 docs aligned; redesign run `34815347501` SUCCESS.
- **Sockets** `3c0d23255295bc9b6609af1390b5c47ed6750641` — neutral A2/session architecture/docs aligned; neutral transport `34815223517`, Host/package `34815223486`, Security `34815223715` all SUCCESS.
- **ESP-NOW** `a1718047c777a09656fc652be12a3dd99ce69624` — provider-only source/docs aligned. Runs `34815106167` and `34815106156` remain infrastructure-unavailable before runner allocation (`steps=[]`, `runner_id=0` for every job), not code-test failures. The earlier independent dual-IDF local provider harness remains fallback evidence. Hosted ESP32/provider execution at the final tip is a recorded automation uncertainty, not silently treated as green.
- **Serial** `3ef07be4252908458110682291fd6b1c1d181262` — negative transport classification: operator/terminal tooling, no canonical device-to-device Primitive byte transport. Remaining family/tooling migration is D10-12/D10-13.
- **WiFi** `8f959f19fbf4f7c3af42223ccc27521a4728f5dd` — no direct remote Primitive transport. Local Command/Event consumers move in D10-14; `WiFiWorker` moves in D10-15.

R9-25 specifically discovered and corrected stale Adapters test/example/workflow fixtures that still used the predecessor lower-transport callback shape. It also corrected one undersized deterministic test record fixture and one invalid wait-free timing assumption in a nonblocking admission test. Production A2 semantics did not require modification. This is important continuation context: do not resurrect those old fixtures or infer a production defect from the historical failed runs preceding `34818506121`.

The 15-item Tranche-9 completion gate is recorded item-by-item in `TRANCHE_9_CLOSURE.md`; Tranche 9 must not be reopened unless live source contradicts a locked closure condition.

## ACTIVE — Structural Tranche 10: common / dynamic consumer migration

Tranche 10 consumes the final closed Primitive/family/provider surfaces in common tooling and dynamic consumers. It must not add a compatibility layer that recreates retired registries, Event brokers, PrecisionThread inheritance, transport-owned family runtimes, or generic State mutation.

### Locked work order

1. **D10-01** — expose/consume final Primitive `TypeDirectory` discovery surface in dynamic tools. **CLOSED/GREEN.**
2. **D10-02** — consume P3 schema/constructibility metadata for family types. **ACTIVE.**
3. **D10-03** — replace Web raw CommandEnvelope → `InboundCommandEvent` ingress with typed Command construction.
4. **D10-04** — migrate Web Event discovery/subscription to final Event descriptors/APIs.
5. **D10-05** — migrate Web generic State inspection to final read-only descriptor/observation surface.
6. **D10-06** — migrate WebSocket family bridges/transports onto Sockets/A2/family bindings as appropriate.
7. **D10-07** — migrate retained Web clock helper to final Timing evidence/quality contract.
8. **D10-08** — add Lua Primitive descriptor discovery adapter.
9. **D10-09** — add Lua typed Command construction/admission adapter.
10. **D10-10** — expose Lua Event operations only through final Event APIs.
11. **D10-11** — expose generic Lua State as read/inspect only; no arbitrary mutation.
12. **D10-12** — migrate Serial Command/Event/State consoles and monitors to final descriptors/diagnostics.
13. **D10-13** — migrate Serial Thread/Timing/transport/WiFi monitors to final diagnostics seams.
14. **D10-14** — migrate WiFi Command/Event integration to final family APIs.
15. **D10-15** — migrate `WiFiWorker` away from `PrecisionThread` to generic execution composition.
16. **D10-16** — validate Logging as fixed/bounded diagnostics seam; isolate optional Observable convenience.
17. **D10-17** — perform ESP32 non-Radio downstream API cleanup.
18. **D10-18** — prove Units remains dependency-neutral and update only integration references if required.
19. **D10-19** — update tests/examples/manifests/workflows/dependency guards and dynamic-input security tests.
20. **D10-20** — update docs/schema examples and complete cross-tool integration validation.

### D10-01 — CLOSED/GREEN

Session reference: user time 09:50 Europe/Prague.

Exact re-baseline corrected a mistaken SHA from prior assistant prose: immediately before D10-01 writes, `ESPressio-Primitive/primitives_redesign` was and remains based on exact pushed commit `a017017a4d38a7b0067c7b17de4770de112087a7` (`Promote Tranche 9 closure and begin D10-01`). The previously quoted `c53b4b0...` was not a repository tip and MUST NOT be used by a successor. `ESPressio-Web/primitives_redesign` began D10-01 at `814ab4c22eb3429b4bcd924b609e9db8be4ca46f`.

Provider conclusion: Primitive already contained the final locked P1 surface. `TypeDirectory<Capacity>` is caller/platform-composition owned and fixed-capacity; successful `Initialize()` freezes deterministic `{Family, TypeId}` order; `TypeDirectoryView` is immutable/read-only, allocation-free, and supports exact key plus family-qualified case-sensitive name lookup. No Primitive provider expansion was required.

Web implementation:

- `dcb03ff4e85d10a59bd2a3286db1f5d6fe89d396` — added opt-in `src/ESPressio_WebPrimitiveDiscovery.hpp`. `PrimitiveTypeDiscovery` binds only a frozen caller-owned `TypeDirectoryView`, exposes count/deterministic index/key/name lookup, and never interprets `FamilyExtension`, schema, construction, admission, authorization or family behavior.
- `cf58241f167c70c10bbee4d18ff3b91f49a07e76` — added focused discovery contracts covering unavailable-view rejection, deterministic enumeration, exact key lookup, family-qualified/case-sensitive names, and common-descriptor-only behavior.
- `c493820208e1948cbca75daa13b6acb04924172b` — wired the focused target into the Web host CMake graph with Primitive include scope limited to that opt-in test.
- `4572ce1aaf324e08d974c727639ff493cd3ef86c` — enabled the existing host workflow on `primitives_redesign` and added Primitive checkout.
- Exact host run `34819919168` reached a real runner and failed at Configure because the pre-existing Web test graph still referenced removed `ESPressio_ThreadTerminationDispatcher.cpp`. This is a Tranche-10 stale-consumer finding, not infrastructure failure and not a D10-01 adapter defect.
- `68a0445bed4234da34779882dd663e921ac2096c` — removed the obsolete ThreadTerminationDispatcher source reference from the two Web host targets. Follow-up run `34819994786` configured successfully and then failed during aggregate Build, proving additional later-D10 predecessor integration remains in the full Web suite.
- `a66e6a694bbba027cdbcc2944e0480a0bb38ffa1` — made the D10-01 test's standard integer dependency explicit.
- `9ce2297fb4a988d469eec2c219d2484546a0dc35` — added the dedicated `Primitive Discovery Contract` workflow so D10-01 can be validated independently without suppressing the aggregate Web suite's legitimate later-D10 failures.
- Exact-tip focused run `34820218599` SUCCESS: checkout, `-std=c++17 -Wall -Wextra -Wpedantic -Werror` compile and runtime contract all passed.

D10-01 semantic classification: the aggregate Web host suite remains intentionally visible as a migration detector. Do not make it green by restoring removed APIs or compatibility files. Its remaining family/WebSocket failures belong to the ordered D10-03..D10-07 migration; D10-01 is closed because its own final provider/consumer contract is independently exact-tip green.

### Tranche-10 completion gate

Before Tranche 10 can close, prove at minimum:

- Web no longer performs raw `Event::InboundCommandEvent` command execution.
- Dynamic Command construction is descriptor/schema/factory driven.
- Dynamic tools no longer discover Commands through `CommandRegistry` or Events through `EventTransportManager`.
- Generic State dynamic access is non-mutating.
- Lua consumes descriptors and remains a consumer, not a semantic owner.
- Serial consoles/monitors do not force predecessor family/runtime APIs.
- `WiFiWorker` no longer derives from `PrecisionThread` or retains a compatibility inheritance base.
- WiFi family bridge/handler paths use final family contracts.
- Logging remains a fixed/bounded low-level diagnostics seam without upward dependency inversion; any Observable convenience is optional and isolated.
- Units retains zero upward dependencies.
- Dynamic input is bounded and family policy/security checked with explicit parse/factory failure; no heap fallback, raw reinterpretation, exception-driven retry, or unbounded construction path is introduced.
- Existing tests/examples are semantically classified before migration/execution.
- No version number changes.

## Immediate continuation — D10-02

Rebaseline `Serializable`, Event, Command and State family descriptors at exact live tips and determine which final P3 schema/constructibility facts already exist versus which family-owned erased construction/read adapters are genuinely absent.

Current first re-baseline facts:

- `ESPressio-Serializable/primitives_redesign` is `2a0dff001cae91365d90f20a382036bd878f53e4`. `StaticSchemaDescriptor` already exposes bounded immutable version/property/value-shape metadata plus maximum DirectBinary/CBOR/JSON sizes; `SchemaDescriptor<T>()` is static and bounded.
- `ESPressio-Command/primitives_redesign` is `b403ca1bb20162c2c88af1ba3506aeb4958ec7e8`. `CommandTypeDescriptor` already carries `RequestSchema`, optional `ResponseSchema`, family policies, exact wire bounds and runtime/admission thunks, and `GetCommandTypeDescriptor(common)` validates family + TypeId before interpreting the opaque Primitive family extension.
- The removed historical `CommandFactory` MUST NOT return as a registry facade. D10-02/D10-03 may add only final family-owned descriptor/factory capability required for bounded typed construction/admission.

Next safe action: inspect Event and State descriptor extensions and the typed local family admission APIs; then define the smallest family-owned P3/constructibility surface needed by Web/Lua/Serial without putting behavior into Primitive or creating a mutable dynamic semantic registry. Do not begin D10-03 raw Web Command replacement until this prerequisite surface is validated.

After each substantive D10 milestone, update this living handoff and mirror it as a downloadable conversation artifact.
