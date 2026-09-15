#!/usr/bin/env bash
set -euo pipefail

root="${1:-${GITHUB_WORKSPACE:-$PWD}/repos}"

required=(
  ESPressio-System ESPressio-Task ESPressio-Timing ESPressio-Threads
  ESPressio-Units ESPressio-Radio ESPressio-Mesh
)
for repository in "${required[@]}"; do
  test -d "$root/$repository/src" || { echo "missing V11-13 checkout: $repository" >&2; exit 1; }
done

# Timing owns qualification, uncertainty and evidence/deadline vocabulary. Re-run the
# final qualification/regression/sample contracts against the current System substrate.
rm -rf /tmp/v11-13-timing
cmake -S "$root/ESPressio-Timing/tests" -B /tmp/v11-13-timing \
  -DESPRESSIO_SYSTEM_SOURCE_DIR="$root/ESPressio-System"
cmake --build /tmp/v11-13-timing --parallel 2
ctest --test-dir /tmp/v11-13-timing --output-on-failure \
  -R '(ClockSynchronization|ClockSampleValidation|SynchronizedSystemClock|clock_qualification|clock_affine_regression)'

# Radio must prioritize promoted Clock work under queued application load while keeping
# bounded fairness, and timestamp/capture evidence must remain tied to physical send/RX.
radio="$root/ESPressio-Radio"
c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti -pthread \
  -I"$radio/src" \
  -I"$root/ESPressio-System/src" \
  -I"$root/ESPressio-Timing/src" \
  "$radio/tests/radio_scheduler_redesign_tests.cpp" \
  -o /tmp/v11-13-radio-scheduler
/tmp/v11-13-radio-scheduler

c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti -pthread \
  -I"$radio/tests/host_arduino" \
  -I"$radio/src" \
  -I"$root/ESPressio-System/src" \
  -I"$root/ESPressio-Timing/src" \
  -I"$root/ESPressio-Units/src" \
  "$radio/tests/radio_clock_coordinator_tests.cpp" \
  -o /tmp/v11-13-radio-clock
/tmp/v11-13-radio-clock

# Mesh owns reference/parent selection only. Use final-architecture tests that carry
# qualified evidence and authenticated direct-peer usability; explicitly reject the
# predecessor RadioTransport seam in this V11-13 evidence set.
mesh="$root/ESPressio-Mesh"
mesh_tests=(
  mesh_clock_reference_orchestration_test.cpp
  clock_parent_usability_test.cpp
  clock_reachability_coordinator_test.cpp
)
for source in "${mesh_tests[@]}"; do
  if grep -qE 'ESPressio_RadioTransport|Radio::RadioTransport' "$mesh/tests/$source"; then
    echo "V11-13 selected Mesh clock test still uses removed RadioTransport: $source" >&2
    exit 1
  fi
  output="/tmp/v11-13-${source%.cpp}"
  c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti -pthread \
    -I"$mesh/src" \
    -I"$root/ESPressio-System/src" \
    -I"$root/ESPressio-Primitive/src" \
    -I"$root/ESPressio-Timing/src" \
    -I"$root/ESPressio-Radio/src" \
    -I"$root/ESPressio-Task/src" \
    -I"$root/ESPressio-Threads/src" \
    -I"$root/ESPressio-Units/src" \
    -I"$root/ESPressio-Units/tests/stubs" \
    "$mesh/tests/$source" -o "$output"
  "$output"
done

echo "V11-13 qualified Clock load/uncertainty/reference-switch validation passed."
