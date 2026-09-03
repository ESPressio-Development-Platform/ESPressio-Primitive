#pragma once

#include "ESPressio_PrimitiveTypes.hpp"

namespace ESPressio {
namespace Primitive {
namespace FamilyIds {

/// <summary>Invalid/Unspecified primitive-family identifier.</summary>
inline constexpr PrimitiveFamilyId Invalid = 0x0000U;

/// <summary>First identifier available for ESPressio-defined primitive families.</summary>
inline constexpr PrimitiveFamilyId ESPressioDefinedFirst = 0x0001U;

/// <summary>Last identifier available for ESPressio-defined primitive families.</summary>
inline constexpr PrimitiveFamilyId ESPressioDefinedLast = 0x7FFFU;

/// <summary>First identifier available for application/private primitive families.</summary>
inline constexpr PrimitiveFamilyId ApplicationPrivateFirst = 0x8000U;

/// <summary>Last identifier available for application/private primitive families.</summary>
inline constexpr PrimitiveFamilyId ApplicationPrivateLast = 0xFFFEU;

/// <summary>Permanently reserved all-bits-set sentinel.</summary>
inline constexpr PrimitiveFamilyId ReservedSentinel = 0xFFFFU;

/// <summary>Indicates whether an identifier is in the ESPressio-defined namespace.</summary>
constexpr bool IsESPressioDefined(PrimitiveFamilyId id) noexcept {
    return id >= ESPressioDefinedFirst && id <= ESPressioDefinedLast;
}

/// <summary>Indicates whether an identifier is in the application/private namespace.</summary>
constexpr bool IsApplicationPrivate(PrimitiveFamilyId id) noexcept {
    return id >= ApplicationPrivateFirst && id <= ApplicationPrivateLast;
}

/// <summary>Indicates whether an identifier is usable for a concrete primitive family.</summary>
constexpr bool IsUsable(PrimitiveFamilyId id) noexcept {
    return IsESPressioDefined(id) || IsApplicationPrivate(id);
}

// Stable ESPressio-defined family allocations are added here individually as
// they are introduced. Repositories must not invent private blocks or derive
// family identifiers from names/hashes.

} // namespace FamilyIds
} // namespace Primitive
} // namespace ESPressio
