#pragma once
#include <string_view>
#include "ESPressio_PrimitiveTypeId.hpp"

namespace ESPressio::Primitive {
/// <summary>Local is inherent; transmission additionally requires serialization.</summary>
enum class PrimitiveTypeCapability : std::uint8_t { Serializable = 1, Transmissible = 2 };
/// <summary>Compact tier facts, not runtime routing or permission flags.</summary>
class PrimitiveTypeCapabilities final {
    std::uint8_t bits_{};
public:
    constexpr PrimitiveTypeCapabilities() noexcept = default;
    constexpr explicit PrimitiveTypeCapabilities(std::uint8_t bits) noexcept : bits_(bits) {}
    constexpr bool Contains(PrimitiveTypeCapability flag) const noexcept {
        return (bits_ & static_cast<std::uint8_t>(flag)) != 0;
    }
    constexpr bool IsValid() const noexcept {
        return (bits_ & ~3U) == 0 && (!Contains(PrimitiveTypeCapability::Transmissible) || Contains(PrimitiveTypeCapability::Serializable));
    }
};
/// <summary>Maximum complete family representation over all allowed formats, excluding lower framing.</summary>
struct PrimitiveSerializedSizeSummary final { std::size_t MaximumCompletePrimitiveWireBytes{}; };
/// <summary>Static immutable family-owned metadata. Primitive never interprets or invokes it.</summary>
struct PrimitiveFamilyExtensionRef final { const void* Data{}; };
/// <summary>Human-readable static-lifetime text; not a wire identity or a name hash.</summary>
using PrimitiveTypeNameView = std::string_view;
/// <summary>Copied common metadata with immutable static-lifetime name/extension references.</summary>
struct PrimitiveTypeDescriptor final {
    PrimitiveTypeKey Key{};
    PrimitiveTypeNameView CanonicalName{};
    PrimitiveTypeCapabilities Capabilities{};
    PrimitiveProtocolVersionRange Versions{};
    ContractFingerprint Contract{};
    PrimitiveSerializedSizeSummary SerializedSize{};
    PrimitiveFamilyExtensionRef FamilyExtension{};
    /// <summary>Checks neutral invariants only; family-specific contracts remain family-owned.</summary>
    constexpr bool IsValid() const noexcept {
        return Key.IsValid() && !CanonicalName.empty() && Capabilities.IsValid() && Versions.IsValid()
            && (!Capabilities.Contains(PrimitiveTypeCapability::Serializable) || SerializedSize.MaximumCompletePrimitiveWireBytes != 0);
    }
};
/// <summary>Family customization point. Descriptor() returns immutable common metadata by value.</summary>
template<class T> struct PrimitiveTypeTraits;
} // namespace ESPressio::Primitive
