# Primitive Platform Redesign — Current Continuation Handoff

Date: 2026-09-15
Latest user time reference: **09:38 Europe/Prague**
Continuation state: **structural Tranches 2–10 CLOSED; Tranche 11 ACTIVE at V11-01 exact-tip freeze**

This is the living continuation card. `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102` remains authoritative for architecture, governance, dependency order, locked contracts, tranche gates and historical decisions. Live `primitives_redesign` branch tips are implementation truth and MUST be re-queried before every mutation.

## Authorization boundary

Implementation remains authorized continuously through structural Tranche 11; no permission pause is required between validation items. **Tranche 12/release preparation is NOT authorized.** Do not change versions, finalize release CHANGELOGs, reintegrate to `main`, tag/release, publish Wiki release material, force-push or add backward-compatibility shims.

Per current project scope, deprecated functionality outside the active Mesh-based architecture is excluded from implementation and validation work.

## Mandatory continuation protocol

Before changing a repository:

1. re-query its exact `primitives_redesign` tip;
2. inspect manifest/dependency boundaries before implementation source;
3. consume closed provider contracts rather than restoring predecessor APIs;
4. classify tests/examples semantically before migration;
5. keep mutations coherent and validate the exact resulting tip;
6. update this handoff after substantive progress.

## Locked non-regression rules

- Primitive TypeDirectory/P3 is immutable discovery/schema/constructibility metadata after freeze; it is not authorization or a semantic registry.
- Dynamic Web/Lua/Serial tooling must independently authorize operations, bound input before parse/construction and enter the final family APIs.
- Commands use final typed descriptor/schema/factory/admission semantics; no Event fabrication or Command registry revival.
- Generic State tooling is read/inspect only; owner-authoritative State remains writable only through the bound owner path.
- Event delivery/admission policy remains Event-owned; tools cannot recreate Event transport/runtime ownership.
- A2 owns logical Primitive-family pursuit/retry after synchronous ownership handoff.
- Primitive family runtimes own family semantics and exact M1 admission meaning. Only `Accepted` / `AlreadyAccepted` establishes destination Primitive admission.
- Radio/R3 owns physical fragmentation/reassembly/arbitration and remains Primitive-family-neutral.
- RadioAdapters is the only direct-Radio layer understanding both Radio and Primitive families; generic Adapters remains Radio-neutral.
- Mesh remains family-neutral. Immediate physical peer and validated semantic original source remain distinct provenance facts.
- No family-local retry worker, retry queue, fragmentation engine or duplicate family runtime.
- Registration/topology freezes before Running; bounded resources and nonblocking ingress remain mandatory.
- Threads uses one root Thread task/stack/common Wake. `ThreadWith<TCapabilities...>` is the sole generic non-empty capability composition host; bare `Thread` is the zero-capability spelling.
- Reusable specialized Thread flavours including `PrecisionThread` remain removed. Precision is a resident capability over the root Thread and owns no private task/scheduler/wake.
- Timing owns clock discipline and final reliability/evidence vocabulary.
- Serial remains downstream tooling/diagnostics and cannot force dependencies upstream.
- Units remains dependency-neutral.
- No structural-tranche version changes.

# Structural Tranche 10 — CLOSED/GREEN

All D10-01 through D10-20 are closed.

## D10-01…18

Previously closed provider/family/tooling work remains as recorded in the authoritative architecture handoff and tranche evidence. Important late-Tranche-10 closure tips include:

- ESPressio-ESP32 D10-17 provider cleanup: `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f`, provider and non-Radio provider smoke jobs GREEN.
- ESPressio-Units D10-18 dependency-neutral proof: `738da6833955ddd0d491cbfac8942ec3ed3bc4f0`, host and optional Serializable integration GREEN.

## D10-19 — semantic validation/eradication closure

D10-19 audited the Section 16 validation matrix rather than duplicating already-closed tests. Existing evidence was confirmed for Event lifetime/admission/contention, Command durable/reboot/idempotency paths, State provenance/convergence/races, Threads common-wake/deadline/lifecycle behavior, Radio protected capacity/quarantine/fairness/reassembly, Mesh broadcast Option-B local retry, Timing evidence qualification and bounded/nonblocking ingress.

A genuine missing proof was added: real simultaneous composition of **Event reception + Precision + Command response + State observation on one root `ThreadWith`**.

Primitive integration evidence:

- `tests/platform_thread_capability_integration.cpp`
- one real Event per-Type runtime, State runtime, Command runtime/response router and one `ThreadWith<EventCapability, Precision<4>, ResponseCapability<1>, ObserverCapability<ObservedState>>`
- asserts all four capabilities add exactly one root Thread task and exercises Event, State, Command response and application cadence callbacks.

The platform structural validator was hardened to scan the current public redesign graph, include Observable, and remain comment-aware for removed-symbol eradication.

D10-19 close evidence at Primitive `243014060ce19ad783d59bc742110f8af12894a5`:

- CI run `34946740606`: SUCCESS
- Platform Redesign Boundaries run `34946740550`: SUCCESS, including structural validation and real four-capability composition.

## D10-20 — docs/schema examples/cross-tool integration closure

Canonical active documentation was aligned to the final redesign rather than predecessor branches/APIs:

- **Web** `585956879ad212dca6a4cf428d3dc16b255f0cdc`
  - frozen TypeDirectory discovery;
  - P3 schema/constructibility;
  - typed Command admission;
  - final Event APIs;
  - generic State read-only;
  - discovery is not authorization;
  - bounded dynamic input;
  - Sockets/A2 and Timing evidence boundaries.
- **Lua** `1cac393ec64c38b12903d083e973bebcb8c4f3de`
  - README and `docs/Integration.md` now target `primitives_redesign`;
  - final discovery/Command/Event/State adapter ownership and security rules documented;
  - mandatory System dependency unchanged; version unchanged.
- **Serial** `efbc9063089937832efc7b63774affbeef301b23`
  - README now matches frozen TypeDirectory + application authorization + bounded P3 construction + final Command/Event APIs + read-only State diagnostics;
  - required System/Logging dependency surface unchanged; version unchanged.
- **WiFi** `937a27f977bd77003f2b9a3fd3896ac61ffafe4e`
  - README now documents the actual `ThreadWith<Precision<8>>` worker/common-wake architecture and redesign branches;
  - manifest/version unchanged.
- **ESP32** `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f`
  - live README/provider boundary already matched the final architecture; no documentation churn was introduced.

Primitive gained `tools/validate_dynamic_tooling.py`, an exact-graph cross-tool guard over the active Web/Lua/Serial/WiFi surfaces. It verifies:

- frozen TypeDirectory discovery rather than mutable replacement registries;
- independent application authorization;
- schema-bounded Command/Event input and final family dispatch/admission;
- read-only generic State dynamic tooling with no owner acquisition;
- final WiFi `ThreadWith<Precision<8>>` composition;
- focused behavioral tests/workflows remain present;
- canonical active documentation does not teach stale coordinated dependency branches.

The predecessor-token part is code-aware so explanatory comments documenting the absence of removed architecture do not create false positives.

**Final Tranche-10 Primitive tip:** `670ad84b37d5cd3cd4d2c4f0ec522b80604495a5`

Exact close evidence:

- Primitive CI run `34947850953`: **SUCCESS**
- Platform Redesign Boundaries run `34947850970`: **SUCCESS**
  - locked dependency/migration boundaries: SUCCESS
  - final dynamic-tooling contracts: SUCCESS
  - real Thread capability composition: SUCCESS

Therefore **Structural Tranche 10 is CLOSED/GREEN**.

# Structural Tranche 11 — ACTIVE

Authoritative validation order:

1. **V11-01 exact-tip freeze — ACTIVE**
2. V11-02 branch-specific removed-symbol/source/include scan
3. V11-03 examples/demos/Labs/wiki/README/generated-CI-fixture scan as separate surfaces
4. V11-04 final dependency DAG
5. V11-05 forbidden dependency/branch guards
6. V11-06 semantic classification of every existing test
7. V11-07 host/public-header/no-RTTI/no-exception/sanitizer validation
8. V11-08 codecs/fuzz/malformed/property validation
9. V11-09 capacity/exhaustion/no-hidden-heap validation
10. V11-10 shutdown/restart/generation/stale-handle validation
11. V11-11 provider physical completion/readiness/cost/timestamp validation
12. V11-12 multi-device Mesh broadcast/relay/congestion/failover validation
13. V11-13 qualified Clock load/uncertainty/reference-switch validation
14. V11-14 Command/Persistence crash/reboot/exactly-once-evidence validation
15. V11-15 Web/Lua/Serial/WiFi/ESP32/Demos/Labs integration builds
16. V11-16 deterministic memory/resource reports
17. V11-17 classify unavailable automation/fallback evidence
18. V11-18 final live-doc/API/example eradication scan
19. V11-19 repository-by-repository validation matrix + evidence links
20. V11-20 block release preparation on every unresolved stale path

## Immediate continuation

1. Freeze and record the exact active public `primitives_redesign` tips for V11-01.
2. Run V11-02 source/include eradication against that frozen graph.
3. Run V11-03 separately over active examples, demos, Labs, README/docs and generated CI fixtures; classify historical material rather than blindly rewriting it.
4. Continue through V11-20 without a permission pause, but do **not** perform any Tranche-12/release action.
