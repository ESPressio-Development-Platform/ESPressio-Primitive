#!/usr/bin/env bash
set -euo pipefail

root="${1:?usage: run_v11_provider_validation.sh <checked-out ESPressio graph root>}"
radio="$root/ESPressio-Radio"

compile_and_run() {
    local output="$1"
    shift
    c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti "$@" -o "/tmp/${output}"
    "/tmp/${output}"
}

# The provider contract itself: finite ingress declaration, non-zero contention domain,
# finite conservative cost, synchronous/deferred TransmissionCompletion ownership and
# infrastructure-only lifecycle notifications. No Primitive family is visible here.
compile_and_run v11-11-managed-provider \
    -fno-exceptions \
    -I"$radio/src" \
    -I"$root/ESPressio-Timing/src" \
    "$radio/tests/radio_managed_provider_contract_tests.cpp"

# Provider-proximate capture/evidence remains separate from distributed clock discipline.
# Wire/capture and coordinator tests prove timestamp provenance/quality is preserved and
# that only qualified evidence may drive the clock path.
compile_and_run v11-11-clock-wire \
    -fno-exceptions \
    -I"$radio/src" \
    -I"$root/ESPressio-Timing/src" \
    "$radio/tests/radio_clock_wire_v1_tests.cpp"

compile_and_run v11-11-clock-coordinator \
    -pthread \
    -I"$radio/tests/host_arduino" \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Timing/src" \
    -I"$root/ESPressio-Units/src" \
    "$radio/tests/radio_clock_coordinator_tests.cpp"

# One owner drains the provider's finite ingress quantum. Readiness/Busy transitions and
# provider wakes feed Radio infrastructure, never application/family callbacks directly.
compile_and_run v11-11-ingress-router \
    -pthread \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Timing/src" \
    "$radio/tests/radio_ingress_router_tests.cpp"

# R3 consumes provider cost/readiness/completion. Scheduler/domain tests prove Busy is a
# progress state rather than provider-local semantic retry ownership, and that physical
# completion/reclamation remains correlated to the Radio transfer lifecycle.
compile_and_run v11-11-scheduler \
    -pthread \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Timing/src" \
    "$radio/tests/radio_scheduler_redesign_tests.cpp"

compile_and_run v11-11-domain-runtime \
    -pthread \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Task/src" \
    -I"$root/ESPressio-Timing/src" \
    "$radio/tests/radio_domain_runtime_tests.cpp"

# Final facade remains family-opaque while binding the provider/domain runtime together.
compile_and_run v11-11-radio-runtime \
    -pthread \
    -I"$radio/tests/host_arduino" \
    -I"$radio/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Task/src" \
    -I"$root/ESPressio-Timing/src" \
    -I"$root/ESPressio-Units/src" \
    "$radio/tests/radio_runtime_tests.cpp"

echo "V11-11 provider completion/readiness/cost/timestamp validation passed."
