#!/usr/bin/env bash
set -euo pipefail

root="${1:-${GITHUB_WORKSPACE:-$PWD}/repos}"
mesh="$root/ESPressio-Mesh"

required=(
  ESPressio-Mesh ESPressio-System ESPressio-Primitive ESPressio-Radio
  ESPressio-Task ESPressio-Threads ESPressio-Timing ESPressio-Units ESPressio-Observable
)
for repository in "${required[@]}"; do
  test -d "$root/$repository/src" || { echo "missing V11-12 checkout: $repository" >&2; exit 1; }
done

includes=(
  -I"$mesh/src"
  -I"$root/ESPressio-System/src"
  -I"$root/ESPressio-Primitive/src"
  -I"$root/ESPressio-Radio/src"
  -I"$root/ESPressio-Task/src"
  -I"$root/ESPressio-Threads/src"
  -I"$root/ESPressio-Timing/src"
  -I"$root/ESPressio-Timing/tests/stubs"
  -I"$root/ESPressio-Units/src"
  -I"$root/ESPressio-Observable/src"
)

build_and_run() {
  local source="$1"
  local output="/tmp/v11_mesh_${source%.cpp}"
  echo "V11-12: ${source}"
  c++ -std=c++17 -Wall -Wextra -Werror -fno-rtti -pthread \
    "${includes[@]}" "$mesh/tests/$source" -o "$output"
  "$output"
}

# Multi-node authenticated forwarding, semantic-origin retention and duplicate suppression.
build_and_run mesh_v1_three_node_forwarding_test.cpp

# Locked M2 Option B: forward at most once; retry deferred local admission without re-forwarding.
build_and_run mesh_v1_broadcast_m2_test.cpp

# Broadcast Seen/Forwarded/DeferredLocal lifecycle and family-neutral policy boundaries.
build_and_run mesh_broadcast_lifecycle_test.cpp
build_and_run mesh_broadcast_policy_test.cpp
build_and_run deduplication_window_test.cpp

# Q1 protected relay capacity under congestion: private reservations, shared overflow,
# quarantine isolation, atomic rollback and membership-derived capacity profile.
build_and_run mesh_relay_capacity_test.cpp
build_and_run mesh_relay_capacity_profile_test.cpp

# Route revalidation/failover and generation-safe direct-peer transition semantics.
build_and_run route_planner_attempt_test.cpp
build_and_run direct_peer_forwarding_transition_test.cpp

echo "V11-12 Mesh multi-device broadcast/relay/congestion/failover validation passed."
