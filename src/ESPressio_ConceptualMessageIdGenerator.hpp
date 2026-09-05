#pragma once

#include <cstdint>
#include <limits>

#include "ESPressio_PrimitiveTypes.hpp"

namespace ESPressio {
namespace Primitive {

/// <summary>
/// Issues non-zero conceptual-message identifiers within one externally owned
/// authenticated source-identity and source-incarnation scope.
/// </summary>
/// <remarks>
/// This dependency-neutral generator does not authenticate a source or own its
/// incarnation. Composition must create or reset one generator per such scope,
/// and persist/restore the high-water value when an incarnation continues.
/// Exhaustion is terminal for the current incarnation: identifiers never wrap.
/// </remarks>
class ConceptualMessageIdGenerator final {
    std::uint64_t _highWater{0};

public:
    /// <summary>Issues the next identifier, or fails when this incarnation is exhausted.</summary>
    bool TryIssue(ConceptualMessageId& issued) noexcept {
        if (_highWater == std::numeric_limits<std::uint64_t>::max()) return false;
        ++_highWater;
        issued = ConceptualMessageId(_highWater);
        return true;
    }

    /// <summary>
    /// Restores a persisted high-water value for the same authenticated source incarnation.
    /// </summary>
    /// <returns><c>false</c> when restoration would regress the current high-water value.</returns>
    bool RestoreHighWater(ConceptualMessageId restored) noexcept {
        if (restored.Value() < _highWater) return false;
        _highWater = restored.Value();
        return true;
    }

    /// <summary>Gets the last issued or restored identifier.</summary>
    ConceptualMessageId HighWater() const noexcept {
        return ConceptualMessageId(_highWater);
    }

    /// <summary>
    /// Begins a newly authenticated source incarnation at the initial empty state.
    /// </summary>
    void ResetForNewSourceIncarnation() noexcept {
        _highWater = 0;
    }
};

} // namespace Primitive
} // namespace ESPressio
