# Tranche 2 implementation evidence

All repositories use `primitives_redesign`. User authorization covers subsequent tranches; implementation continues in dependency order.

| Repository | Commit | GitHub Actions run |
|---|---|---|
| Task | 1e52c71181e9539d53641ae9ed5a1e1c84a3f4f5 | 34601294744 success |
| Timing | d59d4585cf3da37884e9d72b6a9a9542fc2f2a0c | 34605257490 success |
| Threads | 1c92912c19dcfc3159ee9cf8193898602c84b49c | 34608718921 success |

Task implements the one-slot IdleWorkerTask and fixed FIFO TaskExecutor with cooperative join, explicit ownership, cancellation generations, bounded overflow behavior and no hidden queue fallback. Four native gates, race and allocation-denial checks, eight independent headers and three README examples pass.

Timing implements bounded uncertainty-aware synchronization, immutable continuous clock models, strict qualification and holdover, fixed regression windows, four-timestamp validation and monotonic adaptive deadlines. Fourteen native suites, five README snippets, eleven independent headers, negative compile checks and real System/Units/Observable integration pass. Tests include more than two million nanosecond monotonicity steps and heap-denied reads.

Threads replaces the capability-combination hierarchy with one root and ThreadWith static composition. Precision is a cadence capability on the common worker/wake context. Five native suites cover lifecycle, rollback, fatal faults, admission/quiesce, round-robin service, wake coalescing, deadlines, Precision and Timing independence. Four README snippets, seven independent headers and nine negative compile checks pass. ESP32 examples and the WiFi SDK/TLS coexistence consumer compile without RTTI.

Threads direct dependencies are System, Task, Timing and Units. Observable is only a transitive Timing dependency and a test-only direct include for integration. Task and Timing retain their permitted dependency boundaries. System prerequisite c28065089422ccd1b48f0ee45630c592c23ce787 adds CreateJoinable/Join; Persistence consumer 3e9aff700a88764c383da5f18546e7e3f56cfcf8 migrates to fixed TaskExecutor configuration.

The first Threads ESP32 fixture failed because Arduino WiFi.h could not locate Network.h. Replacing that wrapper with the actual esp_wifi SDK station-list probe retained the intended coexistence check; the complete rerun passed. No automation budget or quota limitation was observed.

Physical ESP32 cooperative execution and durable-storage providers remain scheduled platform work. Hardware power-loss, temperature, saturated-radio and multi-device timing qualification remain later validation requirements; host and compile results are not hardware certification. Platform-wide predecessor eradication remains pending dependent tranches. No version changes, tags, releases, publication or main integration were performed.
