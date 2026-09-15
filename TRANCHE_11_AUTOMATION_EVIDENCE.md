# Primitive Platform Redesign — V11-17 Automation Evidence Classification

Date: 2026-09-15
Status: V11-17 CLOSED

This record classifies hosted automation that did not reach meaningful repository execution during structural Tranche 11. It follows the precedent established by `TRANCHE_9_CLOSURE.md`: a GitHub run that terminates before checkout/build/test execution is automation unavailable before meaningful execution, not evidence that repository code failed.

The classification is deliberately narrow. It does not convert a repository with a separately known source/integration defect into a passing repository, and it does not weaken any architecture, ownership, dependency, resource, lifecycle or validation contract.

## Classification vocabulary

- **AUTOMATION_EXECUTED** — at least one meaningful repository step executed; the resulting pass/fail evidence is code/build/test evidence.
- **AUTOMATION_UNAVAILABLE_PRE_EXECUTION** — the hosted job completed without any recorded steps. No checkout, build, test or repository code executed. This is infrastructure/runner unavailability, with the exact external cause left unspecified unless GitHub provides evidence for it.
- **FALLBACK_SUFFICIENT** — independent source/manifest/test/earlier-target evidence is sufficient for the gate being evaluated.
- **FALLBACK_INSUFFICIENT** — automation unavailability is classified, but independent evidence is not sufficient to close the separate implementation/integration gate.

`AUTOMATION_UNAVAILABLE_PRE_EXECUTION` must never be re-labelled as a successful test run and must never be used as a reason to mutate valid implementation merely to make a non-starting runner appear green.

## ESPressio-ESP-Now

Exact redesign checkpoint: `67b793ab47e95588c3d947d26adb369ca22ab43e` (`Guard private ESP-NOW redesign boundaries`).

Hosted evidence on that exact checkpoint:

| Workflow/run | Job | Job id | Recorded steps | Classification |
|---|---|---:|---|---|
| Redesign Boundaries `34940274478`, attempt 2 | `structural-boundaries` | `104296891035` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| Tests `34940274432` | `dependency-boundaries` | `104296976536` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| Tests `34940274432` | `host-provider-contracts` | `104296976887` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| ESP-NOW Radio provider `34940274554` | `ownership-boundary` | `104297009637` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| ESP-NOW Radio provider `34940274554` | `esp32-provider-contract` | `104297010023` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |

No hosted job reached checkout or repository execution. The exact external allocation/billing/runner cause is therefore intentionally not guessed.

Fallback classification: **FALLBACK_SUFFICIENT for the ESP-NOW provider boundary already closed in Tranche 9 / re-audited in D10-19**.

Relevant independent evidence includes the provider-only System + Radio dependency boundary, redesign source/workflow guard audit, provider contract fixtures, prior dual-IDF harness evidence recorded by Tranche 9, and the unchanged provider-only architecture at the current checkpoint. The hosted uncertainty remains explicitly recorded and does not upgrade physical/link evidence into Primitive M1 admission.

## Labs — WROOM-32 20 Node Mesh Lab

Exact redesign checkpoint: `017a5baaa7ef3fd690a4ef02996e24a27007f316` (`Validate Mesh Lab on primitives redesign branch`).

Hosted evidence on that exact checkpoint: workflow `WROOM-32 Mesh 20 Node Lab`, run `34985286586`.

| Job | Job id | Recorded steps | Classification |
|---|---:|---|---|
| `structure` | `104435701935` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| `compile (mesh_validate_dual)` | `104435702226` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| `compile (mesh_validate_wifi_web)` | `104435702231` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| `compile (mesh_node_20)` | `104435702251` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| `compile (mesh_node_10)` | `104435702256` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| `compile (mesh_node_01)` | `104435702425` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |
| `compile (mesh_validate_ble)` | `104435702440` | none (`steps=null`) | `AUTOMATION_UNAVAILABLE_PRE_EXECUTION` |

Again, no hosted job reached checkout or repository execution, so the exact external cause is not guessed.

Fallback classification: **FALLBACK_INSUFFICIENT for V11-15 integration closure**.

The reason is independent of runner availability: static inspection of the active Lab source proves it still contains predecessor redesign surfaces including the removed monolithic `RadioTransport`, Event-specific Mesh transport/manager/listener architecture, `CommandRegistry`, and legacy State publisher/manager composition. The newly-created `primitives_redesign` branch and redesign dependency pins are useful migration scaffolding, but they do not constitute a completed final-architecture Lab integration.

Therefore:

1. V11-17 itself is CLOSED because the unavailable hosted automation has been explicitly and correctly classified.
2. ESP-NOW remains accepted under its previously established fallback evidence, with hosted uncertainty recorded.
3. Labs remains a genuine V11-15/V11-18 implementation blocker until its operative source is migrated to final RadioRuntime + generic A2 + MeshAdapters + typed Event/Command/State contracts and corresponding integration evidence is obtained.
4. The Labs runner failure must not be described as a source compile failure, and the source migration gap must not be described as merely an infrastructure failure.

## V11-17 closure

All currently known unavailable hosted automation in the active redesign completion graph is now classified without conflating infrastructure state with implementation state. Any newly discovered no-step job must be added here before it can be used as fallback evidence in later closure/release-preparation gates.
