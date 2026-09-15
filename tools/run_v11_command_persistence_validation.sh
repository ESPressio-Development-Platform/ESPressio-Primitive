#!/usr/bin/env bash
set -euo pipefail

root="${1:-${GITHUB_WORKSPACE:-$PWD}/repos}"

required=(
  ESPressio-System ESPressio-Primitive ESPressio-Task ESPressio-Threads
  ESPressio-Timing ESPressio-Serializable ESPressio-Units ESPressio-Observable
  ESPressio-Persistence ESPressio-Security ESPressio-Command ESPressio-Logging
)
for repository in "${required[@]}"; do
  test -d "$root/$repository/src" || { echo "missing V11-14 checkout: $repository" >&2; exit 1; }
done

# Command owns durable execution/replay semantics. Execute the final persistence and
# recovery contracts together so a durable Started record, terminal result replay,
# sparse remote replay and ambiguous power-loss handling cannot drift independently.
rm -rf /tmp/v11-14-command
cmake -S "$root/ESPressio-Command/tests" -B /tmp/v11-14-command \
  -DESPRESSIO_DEPENDENCIES="$root"
cmake --build /tmp/v11-14-command --parallel 2
ctest --test-dir /tmp/v11-14-command --output-on-failure \
  -R 'command_(persistence|persistent_results|remote_replay|recovery|fault_injection)'

# Persistence owns atomic storage and runtime-incarnation recovery. Reuse its coordinated
# host build configuration and execute atomic records plus every incarnation/power-loss
# case, including ambiguous old/new records and failed writes.
rm -rf /tmp/v11-14-persistence
cmake -S "$root/ESPressio-Persistence" -B /tmp/v11-14-persistence \
  -DESPRESSIO_SYSTEM_SOURCE_DIR="$root/ESPressio-System" \
  -DESPRESSIO_TIMING_SOURCE_DIR="$root/ESPressio-Timing" \
  -DESPRESSIO_UNITS_SOURCE_DIR="$root/ESPressio-Units" \
  -DESPRESSIO_LOGGING_SOURCE_DIR="$root/ESPressio-Logging" \
  -DESPRESSIO_TASK_SOURCE_DIR="$root/ESPressio-Task"
cmake --build /tmp/v11-14-persistence --parallel 2
ctest --test-dir /tmp/v11-14-persistence --output-on-failure \
  -R '(espressio_atomic_record_tests|incarnation_.*)'

echo "V11-14 Command/Persistence crash/reboot/exactly-once evidence validation passed."
