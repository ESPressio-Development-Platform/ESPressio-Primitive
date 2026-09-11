#pragma once
#include <array>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace ESPressio::Primitive {
/// <summary>Structural policy categories and evidence/terminal markers. Never stored per occurrence.</summary>
struct OccurrenceDeliveryPolicyTag {};
struct StateConvergencePolicyTag {};
struct NoRemoteEvidence {};
struct DestinationPrimitiveAdmission {};
struct DiagnosticOnlyAfterBudget {};
struct ReportTerminalFailureToFamily {};
struct LatestAuthoritativeValue {};
struct DormantNeedsConvergence {};

/// <summary>Normalized descriptive metadata, derived exclusively from a compile-time policy.</summary>
/// <remarks>These numeric codes belong to the canonical fingerprint input only, not packet
/// policy selection, scheduler priorities, or a runtime mutable policy registry.</remarks>
struct PrimitivePolicyDescriptor final {
    std::uint8_t Category{}; // 1 occurrence, 2 convergence
    std::uint8_t Evidence{}; // 0 no remote evidence, 1 destination family admission
    std::uint8_t Terminal{}; // 0 diagnostic, 1 report to family (occurrence only)
    std::uint8_t Supersession{}; // 1 latest authoritative truth (convergence only)
    std::uint8_t Exhaustion{}; // 1 dormant needs convergence (convergence only)
    std::uint64_t MaximumResidenceNanoseconds{};
    std::uint16_t MaximumAttempts{};
    std::uint64_t MaximumAdapterAdmissionWaitNanoseconds{};
    std::uint64_t MinimumRetrySpacingNanoseconds{};
    std::uint64_t MaximumRetrySpacingNanoseconds{};

    /// <summary>Versioned fixed-width little-endian input to the family semantic fingerprint.</summary>
    /// <remarks>The family hash additionally domain-separates this input from schema and other
    /// semantic fields. No C++ names, layout, addresses, route or QoS fields are included.</remarks>
    constexpr std::array<std::uint8_t, 40> CanonicalBytes() const noexcept {
        std::array<std::uint8_t, 40> out{};
        out[0] = 1; out[1] = Category; out[2] = Evidence;
        out[3] = Terminal; out[4] = Supersession; out[5] = Exhaustion;
        std::size_t p = 6;
        const auto append = [&](std::uint64_t v, std::size_t n) constexpr {
            for (std::size_t i = 0; i < n; ++i) { out[p++] = static_cast<std::uint8_t>(v); v >>= 8; }
        };
        append(MaximumResidenceNanoseconds, 8); append(MaximumAttempts, 2);
        append(MaximumAdapterAdmissionWaitNanoseconds, 8);
        append(MinimumRetrySpacingNanoseconds, 8); append(MaximumRetrySpacingNanoseconds, 8);
        return out;
    }
};

namespace Detail {
template<class T, class = void> struct PolicyBounds : std::false_type {};
template<class T> struct PolicyBounds<T, std::void_t<
    typename T::PolicyCategory, typename T::RequiredEvidence,
    decltype(std::integral_constant<std::uint64_t, T::MaximumResidenceNanoseconds>{}),
    decltype(std::integral_constant<std::uint16_t, T::MaximumAttempts>{}),
    decltype(std::integral_constant<std::uint64_t, T::MaximumAdapterAdmissionWaitNanoseconds>{}),
    decltype(std::integral_constant<std::uint64_t, T::MinimumRetrySpacingNanoseconds>{}),
    decltype(std::integral_constant<std::uint64_t, T::MaximumRetrySpacingNanoseconds>{})>> : std::bool_constant<
        std::is_empty_v<T> && !std::is_polymorphic_v<T> &&
        (std::is_same_v<typename T::RequiredEvidence, NoRemoteEvidence> || std::is_same_v<typename T::RequiredEvidence, DestinationPrimitiveAdmission>) &&
        T::MaximumAttempts >= 1 && T::MaximumAttempts < std::numeric_limits<std::uint16_t>::max() &&
        T::MaximumResidenceNanoseconds < std::numeric_limits<std::uint64_t>::max() &&
        T::MaximumAdapterAdmissionWaitNanoseconds < std::numeric_limits<std::uint64_t>::max() &&
        T::MaximumRetrySpacingNanoseconds < std::numeric_limits<std::uint64_t>::max() &&
        T::MinimumRetrySpacingNanoseconds <= T::MaximumRetrySpacingNanoseconds &&
        ((T::MaximumResidenceNanoseconds > 0 && T::MaximumAdapterAdmissionWaitNanoseconds <= T::MaximumResidenceNanoseconds) ||
         (T::MaximumResidenceNanoseconds == 0 && T::MaximumAttempts == 1 &&
          std::is_same_v<typename T::RequiredEvidence, NoRemoteEvidence> &&
          T::MaximumAdapterAdmissionWaitNanoseconds == 0 && T::MinimumRetrySpacingNanoseconds == 0 && T::MaximumRetrySpacingNanoseconds == 0))> {};
} // namespace Detail

/// <summary>C++17 structural recognition; a malformed policy cannot bind to an occurrence Type.</summary>
template<class T, class = void> struct IsOccurrenceDeliveryPolicy : std::false_type {};
template<class T> struct IsOccurrenceDeliveryPolicy<T, std::void_t<typename T::PolicyCategory, typename T::TerminalDisposition>>
    : std::bool_constant<Detail::PolicyBounds<T>::value && std::is_same_v<typename T::PolicyCategory, OccurrenceDeliveryPolicyTag> &&
        (std::is_same_v<typename T::TerminalDisposition, DiagnosticOnlyAfterBudget> || std::is_same_v<typename T::TerminalDisposition, ReportTerminalFailureToFamily>)> {};
/// <summary>Recognizes latest-truth convergence separately from occurrence delivery.</summary>
template<class T, class = void> struct IsStateConvergencePolicy : std::false_type {};
template<class T> struct IsStateConvergencePolicy<T, std::void_t<typename T::PolicyCategory, typename T::Supersession, typename T::ExhaustionDisposition>>
    : std::bool_constant<Detail::PolicyBounds<T>::value && std::is_same_v<typename T::PolicyCategory, StateConvergencePolicyTag> &&
        std::is_same_v<typename T::Supersession, LatestAuthoritativeValue> && std::is_same_v<typename T::ExhaustionDisposition, DormantNeedsConvergence>> {};

/// <summary>Compile-time binding gate and normalized immutable policy metadata.</summary>
template<class T> struct PrimitivePolicyContract final {
    static_assert(IsOccurrenceDeliveryPolicy<T>::value || IsStateConvergencePolicy<T>::value,
                  "Primitive policy must be stateless, structurally valid and have finite pursuit bounds");
    static constexpr PrimitivePolicyDescriptor Descriptor() noexcept {
        PrimitivePolicyDescriptor d{};
        if constexpr (IsOccurrenceDeliveryPolicy<T>::value) {
            d.Category = 1;
            d.Terminal = std::is_same_v<typename T::TerminalDisposition, ReportTerminalFailureToFamily> ? 1 : 0;
        } else { d.Category = 2; d.Supersession = 1; d.Exhaustion = 1; }
        d.Evidence = std::is_same_v<typename T::RequiredEvidence, DestinationPrimitiveAdmission> ? 1 : 0;
        d.MaximumResidenceNanoseconds = T::MaximumResidenceNanoseconds;
        d.MaximumAttempts = T::MaximumAttempts;
        d.MaximumAdapterAdmissionWaitNanoseconds = T::MaximumAdapterAdmissionWaitNanoseconds;
        d.MinimumRetrySpacingNanoseconds = T::MinimumRetrySpacingNanoseconds;
        d.MaximumRetrySpacingNanoseconds = T::MaximumRetrySpacingNanoseconds;
        return d;
    }
};
} // namespace ESPressio::Primitive
