#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace ESPressio {
namespace Primitive {

/// <summary>Stable 16-bit identifier for a conceptual primitive family.</summary>
using PrimitiveFamilyId = std::uint16_t;

/// <summary>
/// Scalar protocol revision used to negotiate compatibility within one primitive family.
/// </summary>
using PrimitiveProtocolVersion = std::uint16_t;

/// <summary>Identifies one conceptual message occurrence independently of transport.</summary>
/// <remarks>
/// The same conceptual message keeps this identifier across serialization,
/// transports, Mesh routes and retries. Zero is Invalid/Unspecified.
/// </remarks>
class ConceptualMessageId final {
    std::uint64_t _value{0};

public:
    /// <summary>Creates the Invalid/Unspecified identifier.</summary>
    constexpr ConceptualMessageId() noexcept = default;

    /// <summary>Creates an identifier from its exact scalar representation.</summary>
    constexpr explicit ConceptualMessageId(std::uint64_t value) noexcept : _value(value) {}

    /// <summary>Gets the exact scalar representation.</summary>
    constexpr std::uint64_t Value() const noexcept { return _value; }

    /// <summary>Indicates whether the identifier is non-zero.</summary>
    constexpr explicit operator bool() const noexcept { return _value != 0U; }

    /// <summary>Compares conceptual message identifiers.</summary>
    constexpr bool operator==(ConceptualMessageId other) const noexcept { return _value == other._value; }

    /// <summary>Compares conceptual message identifiers for inequality.</summary>
    constexpr bool operator!=(ConceptualMessageId other) const noexcept { return _value != other._value; }

    /// <summary>Provides deterministic scalar ordering.</summary>
    constexpr bool operator<(ConceptualMessageId other) const noexcept { return _value < other._value; }
};

/// <summary>
/// Optional causal/workflow correlation identity shared by conceptual primitive families.
/// </summary>
/// <remarks>
/// CorrelationId is deliberately a distinct semantic type from ConceptualMessageId,
/// even when an application intentionally copies the numeric value of an originating
/// message into a later message's correlation field. Zero is Invalid/Unspecified.
/// </remarks>
class CorrelationId final {
    std::uint64_t _value{0};

public:
    /// <summary>Creates the Invalid/Unspecified correlation identifier.</summary>
    constexpr CorrelationId() noexcept = default;

    /// <summary>Creates a correlation identifier from its exact scalar representation.</summary>
    constexpr explicit CorrelationId(std::uint64_t value) noexcept : _value(value) {}

    /// <summary>
    /// Explicitly creates a correlation identifier using the scalar value of a conceptual message.
    /// </summary>
    constexpr static CorrelationId FromMessage(ConceptualMessageId messageId) noexcept {
        return CorrelationId(messageId.Value());
    }

    /// <summary>Gets the exact scalar representation.</summary>
    constexpr std::uint64_t Value() const noexcept { return _value; }

    /// <summary>Indicates whether the identifier is non-zero.</summary>
    constexpr explicit operator bool() const noexcept { return _value != 0U; }

    /// <summary>Compares correlation identifiers.</summary>
    constexpr bool operator==(CorrelationId other) const noexcept { return _value == other._value; }

    /// <summary>Compares correlation identifiers for inequality.</summary>
    constexpr bool operator!=(CorrelationId other) const noexcept { return _value != other._value; }

    /// <summary>Provides deterministic scalar ordering.</summary>
    constexpr bool operator<(CorrelationId other) const noexcept { return _value < other._value; }
};

/// <summary>Inclusive protocol-version range advertised by a primitive-family implementation.</summary>
struct PrimitiveProtocolVersionRange final {
    PrimitiveProtocolVersion Minimum{0};
    PrimitiveProtocolVersion Maximum{0};

    /// <summary>Indicates whether the inclusive range is ordered correctly.</summary>
    constexpr bool IsValid() const noexcept { return Minimum <= Maximum; }

    /// <summary>Indicates whether the supplied version belongs to this inclusive range.</summary>
    constexpr bool Contains(PrimitiveProtocolVersion version) const noexcept {
        return IsValid() && version >= Minimum && version <= Maximum;
    }

    /// <summary>
    /// Finds the highest mutually supported version between two ranges.
    /// </summary>
    /// <param name="other">The remote/other supported range.</param>
    /// <param name="selected">Receives the highest mutually supported version on success.</param>
    /// <returns><c>true</c> if the ranges overlap.</returns>
    constexpr bool TrySelectHighestMutual(
        const PrimitiveProtocolVersionRange& other,
        PrimitiveProtocolVersion& selected
    ) const noexcept {
        if (!IsValid() || !other.IsValid()) return false;
        const auto minimum = Minimum > other.Minimum ? Minimum : other.Minimum;
        const auto maximum = Maximum < other.Maximum ? Maximum : other.Maximum;
        if (minimum > maximum) return false;
        selected = maximum;
        return true;
    }
};

/// <summary>
/// Complete 256-bit SHA-256 semantic contract fingerprint for compatibility comparison.
/// </summary>
/// <remarks>
/// This value is compatibility metadata, not authentication or a security credential.
/// The digest must be produced from the canonical versioned/domain-separated semantic
/// encoding owned by the corresponding contract.
/// </remarks>
class ContractFingerprint final {
public:
    /// <summary>Fingerprint width in bytes.</summary>
    static constexpr std::size_t Size = 32;

    /// <summary>Underlying exact digest representation.</summary>
    using Storage = std::array<std::uint8_t, Size>;

private:
    Storage _bytes{};

public:
    /// <summary>Creates the all-zero unspecified fingerprint.</summary>
    constexpr ContractFingerprint() noexcept = default;

    /// <summary>Creates a fingerprint from its complete digest bytes.</summary>
    constexpr explicit ContractFingerprint(const Storage& bytes) noexcept : _bytes(bytes) {}

    /// <summary>Gets the complete immutable digest representation.</summary>
    constexpr const Storage& Bytes() const noexcept { return _bytes; }

    /// <summary>Indicates whether every digest byte is zero.</summary>
    constexpr bool IsZero() const noexcept {
        for (const auto value : _bytes) {
            if (value != 0U) return false;
        }
        return true;
    }

    /// <summary>Compares fingerprints by exact digest equality.</summary>
    constexpr bool operator==(const ContractFingerprint& other) const noexcept {
        for (std::size_t index = 0; index < Size; ++index) {
            if (_bytes[index] != other._bytes[index]) return false;
        }
        return true;
    }

    /// <summary>Compares fingerprints for inequality.</summary>
    constexpr bool operator!=(const ContractFingerprint& other) const noexcept {
        return !(*this == other);
    }
};

static_assert(sizeof(ConceptualMessageId) == sizeof(std::uint64_t),
              "ConceptualMessageId must remain an exact 64-bit scalar wrapper.");
static_assert(sizeof(CorrelationId) == sizeof(std::uint64_t),
              "CorrelationId must remain an exact 64-bit scalar wrapper.");
static_assert(sizeof(ContractFingerprint) == ContractFingerprint::Size,
              "ContractFingerprint must remain an exact 32-byte digest value.");

} // namespace Primitive
} // namespace ESPressio
