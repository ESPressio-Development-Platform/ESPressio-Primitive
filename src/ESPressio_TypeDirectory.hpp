#pragma once
#include <array>
#include "ESPressio_PrimitiveTypeDescriptor.hpp"

namespace ESPressio::Primitive {
enum class TypeDirectoryRegistrationStatus { Success, Full, DuplicateKey, DuplicateCanonicalName, InvalidDescriptor, Frozen };
enum class TypeDirectoryInitializationStatus { Success, InvalidDescriptor, DuplicateKey, DuplicateCanonicalName, AlreadyFrozen };
template<std::size_t Capacity> class TypeDirectory;

/// <summary>Read-only view issued only by a frozen directory. Owner must outlive every view.</summary>
class TypeDirectoryView final {
    const PrimitiveTypeDescriptor* entries_{};
    std::size_t count_{};
    bool frozen_{};
    template<std::size_t> friend class TypeDirectory;
    constexpr TypeDirectoryView(const PrimitiveTypeDescriptor* entries, std::size_t count) noexcept
        : entries_(entries), count_(count), frozen_(true) {}
public:
    /// <summary>Creates an unavailable view, distinct from a valid frozen empty directory.</summary>
    constexpr TypeDirectoryView() noexcept = default;
    constexpr bool IsFrozen() const noexcept { return frozen_; }
    constexpr std::size_t Size() const noexcept { return count_; }
    constexpr const PrimitiveTypeDescriptor* begin() const noexcept { return entries_; }
    constexpr const PrimitiveTypeDescriptor* end() const noexcept { return count_ ? entries_ + count_ : entries_; }
    /// <summary>Allocation-free logarithmic lookup in deterministic family/Type order.</summary>
    const PrimitiveTypeDescriptor* Find(PrimitiveTypeKey key) const noexcept {
        std::size_t first = 0, last = count_;
        while (first < last) {
            const auto mid = first + (last - first) / 2;
            if (entries_[mid].Key < key) first = mid + 1; else last = mid;
        }
        return first < count_ && entries_[first].Key == key ? &entries_[first] : nullptr;
    }
    /// <summary>Bounded family-qualified, exact case-sensitive name lookup.</summary>
    const PrimitiveTypeDescriptor* Find(PrimitiveFamilyId family, PrimitiveTypeNameView name) const noexcept {
        for (std::size_t i = 0; i < count_; ++i)
            if (entries_[i].Key.Family == family && entries_[i].CanonicalName == name) return &entries_[i];
        return nullptr;
    }
};

/// <summary>Caller-owned fixed-capacity metadata directory. Configuration is owner-serialized.</summary>
/// <remarks>Initialize validates before sorting/publishing; all subsequent reads are immutable,
/// lock-free and allocation-free. No copying/moving may invalidate published entry addresses.
/// Name and extension storage must be immutable and have static lifetime.</remarks>
template<std::size_t Capacity>
class TypeDirectory final {
    std::array<PrimitiveTypeDescriptor, Capacity> entries_{};
    std::size_t count_{};
    bool frozen_{};
public:
    TypeDirectory() noexcept = default;
    TypeDirectory(const TypeDirectory&) = delete;
    TypeDirectory& operator=(const TypeDirectory&) = delete;
    /// <summary>Resolves family-supplied traits; does not construct an instance of T.</summary>
    template<class T> TypeDirectoryRegistrationStatus Register() noexcept {
        static_assert(noexcept(PrimitiveTypeTraits<T>::Descriptor()), "Primitive descriptor must be noexcept");
        return Register(PrimitiveTypeTraits<T>::Descriptor());
    }
    /// <summary>Copies common metadata. Every failed registration leaves all state unchanged.</summary>
    TypeDirectoryRegistrationStatus Register(const PrimitiveTypeDescriptor& descriptor) noexcept {
        using R = TypeDirectoryRegistrationStatus;
        if (frozen_) return R::Frozen;
        if (!descriptor.IsValid()) return R::InvalidDescriptor;
        for (std::size_t i = 0; i < count_; ++i) {
            if (entries_[i].Key == descriptor.Key) return R::DuplicateKey;
            if (entries_[i].Key.Family == descriptor.Key.Family && entries_[i].CanonicalName == descriptor.CanonicalName)
                return R::DuplicateCanonicalName;
        }
        if (count_ == Capacity) return R::Full;
        entries_[count_++] = descriptor;
        return R::Success;
    }
    /// <summary>Validates the entire candidate set then freezes sorted entries without extra storage.</summary>
    TypeDirectoryInitializationStatus Initialize() noexcept {
        using R = TypeDirectoryInitializationStatus;
        if (frozen_) return R::AlreadyFrozen;
        for (std::size_t i = 0; i < count_; ++i) {
            if (!entries_[i].IsValid()) return R::InvalidDescriptor;
            for (std::size_t j = 0; j < i; ++j) {
                if (entries_[i].Key == entries_[j].Key) return R::DuplicateKey;
                if (entries_[i].Key.Family == entries_[j].Key.Family && entries_[i].CanonicalName == entries_[j].CanonicalName)
                    return R::DuplicateCanonicalName;
            }
        }
        // No operation after this validation can fail. Insertion sort needs one descriptor scratch.
        for (std::size_t i = 1; i < count_; ++i) {
            const auto entry = entries_[i];
            auto j = i;
            while (j && entry.Key < entries_[j - 1].Key) { entries_[j] = entries_[j - 1]; --j; }
            entries_[j] = entry;
        }
        frozen_ = true;
        return R::Success;
    }
    /// <summary>Returns unavailable until Initialize succeeds. Publish to readers with normal synchronization.</summary>
    TypeDirectoryView View() const noexcept { return frozen_ ? TypeDirectoryView(entries_.data(), count_) : TypeDirectoryView{}; }
    constexpr std::size_t Size() const noexcept { return count_; }
    constexpr bool IsFrozen() const noexcept { return frozen_; }
};
} // namespace ESPressio::Primitive
