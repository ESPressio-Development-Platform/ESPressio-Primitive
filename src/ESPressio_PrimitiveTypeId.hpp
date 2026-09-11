#pragma once
#include "ESPressio_PrimitiveFamilyRegistry.hpp"

namespace ESPressio::Primitive {

/// <summary>Strong, family-qualified 64-bit semantic Type identity; zero is invalid.</summary>
template<PrimitiveFamilyId Family>
class PrimitiveTypeId final {
    static_assert(FamilyIds::IsUsable(Family), "Primitive Type requires a usable family");
    std::uint64_t value_{};
public:
    /// <summary>Family namespace of this strong Type ID.</summary>
    static constexpr PrimitiveFamilyId FamilyId = Family;
    constexpr PrimitiveTypeId() noexcept = default;
    /// <summary>Constructs from its explicit canonical scalar; never hashes a name.</summary>
    constexpr explicit PrimitiveTypeId(std::uint64_t value) noexcept : value_(value) {}
    /// <summary>Returns the exact wire scalar.</summary>
    constexpr std::uint64_t Value() const noexcept { return value_; }
    constexpr explicit operator bool() const noexcept { return value_ != 0; }
    constexpr bool operator==(PrimitiveTypeId other) const noexcept { return value_ == other.value_; }
    constexpr bool operator!=(PrimitiveTypeId other) const noexcept { return !(*this == other); }
    constexpr bool operator<(PrimitiveTypeId other) const noexcept { return value_ < other.value_; }
};

/// <summary>Event semantic Type identifier, distinct from occurrence identity.</summary>
using EventTypeId = PrimitiveTypeId<FamilyIds::Event>;
/// <summary>Command semantic Type identifier, distinct from execution identity.</summary>
using CommandTypeId = PrimitiveTypeId<FamilyIds::Command>;
/// <summary>State semantic Type identifier, distinct from owner/session identity.</summary>
using StateTypeId = PrimitiveTypeId<FamilyIds::State>;

/// <summary>Family-qualified key for generic, immutable metadata lookup.</summary>
struct PrimitiveTypeKey final {
    PrimitiveFamilyId Family{};
    std::uint64_t TypeValue{};
    constexpr bool IsValid() const noexcept { return FamilyIds::IsUsable(Family) && TypeValue != 0; }
    constexpr bool operator==(PrimitiveTypeKey b) const noexcept { return Family == b.Family && TypeValue == b.TypeValue; }
    constexpr bool operator!=(PrimitiveTypeKey b) const noexcept { return !(*this == b); }
    constexpr bool operator<(PrimitiveTypeKey b) const noexcept {
        return Family < b.Family || (Family == b.Family && TypeValue < b.TypeValue);
    }
};
} // namespace ESPressio::Primitive
