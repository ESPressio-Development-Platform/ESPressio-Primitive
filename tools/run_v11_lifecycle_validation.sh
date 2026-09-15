#!/usr/bin/env bash
set -euo pipefail

root="${1:?usage: run_v11_lifecycle_validation.sh <checked-out ESPressio graph root>}"

configure_and_run() {
    local repo="$1"
    local build="$2"
    local regex="$3"
    shift 3
    rm -rf "$build"
    cmake -S "$root/ESPressio-${repo}/tests" -B "$build" "$@"
    cmake --build "$build" --parallel 2
    ctest --test-dir "$build" --output-on-failure -R "$regex"
}

# T1: generation-safe handles, Ready cancellation/drop, Executing join, self-join,
# reinitialization without stale-token revival, plus executor shutdown/quiescence.
configure_and_run Task /tmp/v11-10-task \
    '(idle_worker|executor|configuration|rejected_contracts)' \
    -DESPRESSIO_SYSTEM_SOURCE_DIR="$root/ESPressio-System"

# TH3/TH12: one-root lifecycle, common Wake termination races, capability quiescence
# and deterministic initialization rollback/finalization.
configure_and_run Threads /tmp/v11-10-threads \
    '(thread_lifecycle|common_wake_and_deadlines|composition)' \
    -DESPRESSIO_DEPENDENCIES="$root"

# Event shutdown/freeze: topology cannot reopen after freeze; failed Initialize rolls
# back; pause/quiesce releases retained references without callbacks after teardown.
configure_and_run Event /tmp/v11-10-event \
    'event_(runtime_freeze|initialization_rollback|thread_pause_quiesce)' \
    -DESPRESSIO_DEPENDENCIES="$root"

# Command lifecycle: bounded runtime and requester capability terminate/cancel without
# reviving completed/stale work or invoking application callbacks after quiescence.
configure_and_run Command /tmp/v11-10-command \
    'command_(runtime|response_capability)' \
    -DESPRESSIO_DEPENDENCIES="$root"

# State shutdown closes mutation/admission before waiting for in-flight work, tears down
# sessions/transports deterministically, and preserves the installed System incarnation.
configure_and_run State /tmp/v11-10-state \
    'state_(shutdown|initialization|remote_sessions|runtime_identity_projection)' \
    -DESPRESSIO_DEPENDENCIES="$root"

# A1/A2: generation-safe leases, deferred retry wake, bounded runtime teardown, no generic
# drain/replay, and lower transport quiescence/cancel before Shutdown returns.
configure_and_run Adapters /tmp/v11-10-adapters \
    'adapter_(shutdown|deferred_retry_wake|binding|runtime)' \
    -DESPRESSIO_DEPENDENCIES="$root"

# Radio lifecycle stays family-neutral. Domain/runtime tests exercise cooperative stop,
# readiness ownership, restart-safe runtime state and provider/resource reclamation.
radio="$root/ESPressio-Radio"
c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti -pthread \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Task/src" \
    -I"$root/ESPressio-Timing/src" \
    "$radio/tests/radio_domain_runtime_tests.cpp" \
    -o /tmp/v11-10-radio-domain
/tmp/v11-10-radio-domain

c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti -pthread \
    -I"$radio/tests/host_arduino" \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Task/src" \
    -I"$root/ESPressio-Timing/src" \
    -I"$root/ESPressio-Units/src" \
    "$radio/tests/radio_runtime_tests.cpp" \
    -o /tmp/v11-10-radio-runtime
/tmp/v11-10-radio-runtime

# The neutral Socket A2 transport explicitly proves generation increments on Restart,
# stale receipts/completions are rejected across generations, and Quiesce rejects work.
sockets="$root/ESPressio-Sockets"
for test in socket_adapter_transport_test socket_adapter_hardening_test; do
    c++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -fno-rtti -pthread \
        -I"$sockets/src" \
        -I"$root/ESPressio-Adapters/src" \
        -I"$root/ESPressio-Primitive/src" \
        -I"$root/ESPressio-System/src" \
        -I"$root/ESPressio-Task/src" \
        "$sockets/tests/${test}.cpp" \
        -o "/tmp/v11-10-${test}"
    "/tmp/v11-10-${test}"
done

echo "V11-10 lifecycle/generation/restart validation passed."
