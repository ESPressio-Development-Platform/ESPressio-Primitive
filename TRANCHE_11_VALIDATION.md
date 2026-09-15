# Structural Tranche 11 — Validation Evidence

Date: 2026-09-15
Initial Tranche-11 reference time supplied by the user: 09:38 Europe/Prague
Latest continuation reference time supplied by the user: 10:44 Europe/Prague
Status: **V11-01 and V11-02 CLOSED/GREEN; V11-03 ACTIVE**

This file records validation evidence for Structural Tranche 11 of the Primitive Platform Redesign. The architecture and completion gates remain defined by `ESPressio_Primitive_Platform_Redesign_Architecture_Handoff_Revision_102`; this file does not alter those contracts.

## Scope rule

The active validation graph is the public `primitives_redesign` graph listed below. Deprecated functionality explicitly excluded by the user is outside this validation scope and must not consume implementation or validation effort.

`ESPressio-Demos` and `Labs` are **not** promoted into the core redesign DAG by this freeze. The authoritative architecture handoff gives Demos no authorized redesign baseline and treats Labs as downstream/validation context only. Their current branches are recorded separately for V11-03/V11-15.

No release preparation, version change, tag, `main` reintegration or release publication is authorized by this validation tranche.

# V11-01 — Exact-tip freeze — CLOSED

The following exact `primitives_redesign` tips are the frozen active public graph at the start of Tranche 11 validation:

| Repository | Frozen tip |
|---|---|
| ESPressio-Primitive | `3f9d36e9800a79628009b317333a0b8c27910be0` |
| ESPressio-System | `c28065089422ccd1b48f0ee45630c592c23ce787` |
| ESPressio-Serializable | `9bec7caa4fb515e564ea0146bd44f77610e9aebc` |
| ESPressio-Persistence | `3e9aff700a88764c383da5f18546e7e3f56cfcf8` |
| ESPressio-Task | `db7380e7b247cace222a96bebae056205efc0963` |
| ESPressio-Timing | `f94e82459ebbca42e74e210e306be0861cc8d73b` |
| ESPressio-Threads | `1c92912c19dcfc3159ee9cf8193898602c84b49c` |
| ESPressio-Event | `532d04e1200b04b5734b68467018c597ae996223` |
| ESPressio-Command | `658a9f9064a8ef58a0016d041a29be0c8ca3da7f` |
| ESPressio-State | `25637a7555e3a03f1d709bd8e37340bc4d545b6e` |
| ESPressio-Adapters | `8a9dc6ce5f4c57361824637a1d614f7699e5dc73` |
| ESPressio-Radio | `a43e700cd20b287217f805cebedc6e9fc126ca48` |
| ESPressio-Mesh | `a832ce41c7ebd6174c7a06835ea24a871f843dcc` |
| ESPressio-MeshAdapters | `f861d96ecddb14a9242f444174fb0248da9bab88` |
| ESPressio-RadioAdapters | `337859721246ab613c354a8073943e2d5c588946` |
| ESPressio-Sockets | `3c0d23255295bc9b6609af1390b5c47ed6750641` |
| ESPressio-Serial | `efbc9063089937832efc7b63774affbeef301b23` |
| ESPressio-WiFi | `937a27f977bd77003f2b9a3fd3896ac61ffafe4e` |
| ESPressio-ESP32 | `1b19c94a85aaac6fdf71935a78fbd7a0a4d4333f` |
| ESPressio-Logging | `10b5209fd05a9c61c95deda9176f45584d8b6459` |
| ESPressio-Security | `08cda2dddcd59cc8efc5c3c532e0e14efdff4c21` |
| ESPressio-Units | `738da6833955ddd0d491cbfac8942ec3ed3bc4f0` |
| ESPressio-Observable | `d2bc585891a99172cb3654999b5840dd239207fa` |
| ESPressio-Web | `585956879ad212dca6a4cf428d3dc16b255f0cdc` |
| ESPressio-Lua | `1cac393ec64c38b12903d083e973bebcb8c4f3de` |
| ESPressio-NRF24 | `0c62ee73c2deaf7d7955ff1f04f2e88695c81b6a` |

The freeze found no unexplained core/public branch drift after the green Tranche-10 closure.

## Separate integration/validation surfaces

### ESPressio-Demos

No `primitives_redesign` branch exists and no fallback branch is authorized by the architecture handoff. Current branches observed during V11-01:

- `main`: `ed23f62e2392f97f05a8b1b619161ccdf1869bc8`
- `structural_realignment`: `c0607b3cca44a7c54200720be3a5b36ec5abc3bf`

Demos remains provisional validation context. V11-03 must inspect the live demo content and classify stale paths; V11-15 must use only an explicitly justified validation baseline and must not silently establish a new source-of-truth branch.

### Labs

Repository: `ESPressio-Development-Platform/Labs` (private). It has no `primitives_redesign` branch and remains validation/downstream context only.

Observed branches relevant to current validation:

- `main`: `6df31fba01a382fbb5a6ead0dd72c9d5df4a8e41`
- `structural_realignment_propagation_ESPressio-Mesh`: `f662e645ab62fe893731253055f4f9b456b19ce4`

The latter is recorded because it is the existing Mesh-lab working lineage; recording it does not authorize promotion to the redesign source branch. V11-03/V11-15 will classify the live Lab fixtures against the frozen redesign contracts.

# V11-02 — Production source/include eradication — CLOSED/GREEN

V11-02 is deliberately separate from the examples/documentation scan in V11-03. Commit `c01c4a37a14249ca5caac945804c40e92bd9a1fe` added `tools/validate_v11_source_eradication.py`; commit `16934b01949aa0c52ed56d831999dfec33e37ba7` wired it into the public redesign-graph workflow.

The gate:

- checks only `src/` and `include/` production/public C/C++ source surfaces;
- strips C/C++ comments before matching so explanatory architecture comments may accurately name removed APIs;
- checks all 26 active redesign repositories and omits deprecated out-of-scope functionality;
- rejects the removed Precision/Event/Command/State/Radio/Thread predecessor manager/worker hierarchy, including `PrecisionThread`, `EventTransportManager`, `EventManager`, `CommandRegistry`, `RemoteStateObserverThread`, `RadioWorker`, `ThreadManager`, `ThreadTerminationDispatcher`, `DesiredIterationPeriod`, and related removed identifiers.

Exact validation evidence:

- workflow: `Platform Redesign Boundaries`
- run: `34948846099`
- job: `104314675007`
- head: `16934b01949aa0c52ed56d831999dfec33e37ba7`
- result: **SUCCESS**
- production/public files scanned: **710** across **26** repositories
- existing locked-DAG guard: SUCCESS
- V11-02 production-source eradication: SUCCESS
- final dynamic-tooling contracts: SUCCESS
- real multi-capability `ThreadWith` composition: SUCCESS

No production remediation was required by V11-02.

# V11 continuation

- V11-01 exact-tip freeze: **CLOSED/GREEN**
- V11-02 branch-specific removed-symbol/source/include scan: **CLOSED/GREEN**
- V11-03 examples/demos/Labs/wiki/README/generated-CI-fixture scan: **ACTIVE**
- V11-04 through V11-20: pending in the authoritative order

Any repair commit made during Tranche 11 necessarily advances a branch beyond the immutable V11-01 baseline. Such movement must be recorded as validation remediation, not silently folded back into the original freeze.
