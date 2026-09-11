#pragma once
#include <cstdint>

namespace ESPressio::Primitive {
/// <summary>Exact synchronous, bounded, nonblocking destination-family ownership result.</summary>
/// <remarks>No result implies application callback/handler completion. Accepted transfers
/// all required semantic ownership out of borrowed ingress bytes; AlreadyAccepted proves
/// idempotent accounting. Transient results are retry candidates only within policy.</remarks>
enum class PrimitiveAdmissionDisposition : std::uint8_t {
    Accepted, AlreadyAccepted, TemporarilyUnavailable, ResourceUnavailable,
    Unsupported, Rejected, Malformed
};
/// <summary>Only family acceptance can establish destination admission evidence.</summary>
constexpr bool EstablishesDestinationAdmission(PrimitiveAdmissionDisposition result) noexcept {
    return result == PrimitiveAdmissionDisposition::Accepted || result == PrimitiveAdmissionDisposition::AlreadyAccepted;
}
/// <summary>Indicates a retry candidate, never permission to extend a finite campaign.</summary>
constexpr bool IsAdmissionRetryCandidate(PrimitiveAdmissionDisposition result) noexcept {
    return result == PrimitiveAdmissionDisposition::TemporarilyUnavailable || result == PrimitiveAdmissionDisposition::ResourceUnavailable;
}
} // namespace ESPressio::Primitive
