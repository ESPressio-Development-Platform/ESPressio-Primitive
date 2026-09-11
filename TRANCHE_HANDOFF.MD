# Primitive platform implementation checkpoint

Scope: implement the complete authorized primitive platform reset described by the uploaded Revision 079 architecture handoff, in Sections 21–32 dependency order. Release preparation is inventory only. No versions, tags, releases or main integration are authorized.

Rules: the architecture handoff and current user authorization govern. Policy documents reviewed: ABSTRACTION_POLICY, CIRCULAR_DEPENDENCY_POLICY, CROSS_LIBRARY_CHANGES, DEMO_POLICY, DOCUMENTATION_POLICY, GITHUB_TASK_RESULT_POLICY, LOGGING_INSTRUMENTATION_POLICY, OBSERVER_CALLBACK_POLICY, TRANCHE_TIMEOUT_OR_INTERRUPTION_POLICY, WORKING_BRANCHES. The handoff supersedes older propagation-branch and Observable/bridge rules wherever it explicitly replaces them. Work directly on primitives_redesign. No compatibility code. Semantic test review precedes execution. Record capacity, ownership, lifecycle, wire and persistence evidence; do not mistake unavailable automation for a pass.

## Status

2026-09-11T10:57:12.590327+00:00 — Full 1,215,633-character handoff read, including revision ledger. Both new adapter branches verified, created from their current main tips; existing source tips checked out without resetting unrelated work. Foundation underway; no tranche complete.

Primitive starting SHA: d01a3657e67feb29a5695faf2e5fde0e76948d4e.
Adapters starting SHA: ef64f117258155387f0908707e09618500a8cb93.
RadioAdapters starting SHA: 8b660acaa4f6c93d363364c596cf2bcbbda9c044.

## Initial test classification

primitive_types_test.cpp: family allocation, protocol ranges, fingerprint and message scalar tests remain valid. Generic correlation and resettable Event message generator assertions are superseded; replace with directory, family-type identity, normalized policy and admission tests. Event-only generator moves to Event in its tranche.

## Expected dependent migrations

Event and Command still use generic correlation; EventTransportManager uses the predecessor message generator. Their scheduled family tranches remove these paths. Do not restore compatibility declarations to make them compile.

2026-09-11T11:04:29.495265+00:00 — Primitive F01/F02 implementation and local validation complete: three CMake/CTest suites, standalone no-RTTI/no-exception public headers, two intended negative compile diagnostics, directory allocation denial/concurrent reads, normalized semantic vectors and compiled README examples passed. No dependencies added; version unchanged. Current Primitive source has no removed generic correlation/resettable generator or stale structural branch references. Whole-platform eradication remains pending downstream tranches. GitHub automation not yet classified.
