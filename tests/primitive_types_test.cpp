#include <array>
#include <cassert>
#include <cstdint>
#include <type_traits>

#include "ESPressio_Primitive.hpp"

int main() {
    using namespace ESPressio::Primitive;

    static_assert(sizeof(PrimitiveFamilyId) == 2);
    static_assert(sizeof(PrimitiveProtocolVersion) == 2);
    static_assert(sizeof(ConceptualMessageId) == 8);
    static_assert(sizeof(CorrelationId) == 8);
    static_assert(sizeof(ContractFingerprint) == 32);
    static_assert(std::is_trivially_copyable<ConceptualMessageId>::value);
    static_assert(std::is_trivially_copyable<CorrelationId>::value);
    static_assert(std::is_trivially_copyable<ContractFingerprint>::value);

    assert(FamilyIds::Invalid == 0x0000U);
    assert(FamilyIds::ESPressioDefinedFirst == 0x0001U);
    assert(FamilyIds::ESPressioDefinedLast == 0x7FFFU);
    assert(FamilyIds::ApplicationPrivateFirst == 0x8000U);
    assert(FamilyIds::ApplicationPrivateLast == 0xFFFEU);
    assert(FamilyIds::ReservedSentinel == 0xFFFFU);
    assert(FamilyIds::MeshControl == 0x0001U);
    assert(FamilyIds::Command == 0x0002U);
    assert(FamilyIds::Event == 0x0003U);
    assert(FamilyIds::State == 0x0004U);
    assert(FamilyIds::IsESPressioDefined(FamilyIds::MeshControl));
    assert(FamilyIds::IsESPressioDefined(FamilyIds::Command));
    assert(FamilyIds::IsESPressioDefined(FamilyIds::Event));
    assert(FamilyIds::IsESPressioDefined(FamilyIds::State));
    assert(FamilyIds::IsESPressioDefined(0x0001U));
    assert(!FamilyIds::IsESPressioDefined(0x8000U));
    assert(FamilyIds::IsApplicationPrivate(0x8000U));
    assert(!FamilyIds::IsUsable(FamilyIds::Invalid));
    assert(!FamilyIds::IsUsable(FamilyIds::ReservedSentinel));

    const ConceptualMessageId message(99U);
    assert(static_cast<bool>(message));
    assert(message.Value() == 99U);

    const CorrelationId correlation = CorrelationId::FromMessage(message);
    assert(static_cast<bool>(correlation));
    assert(correlation.Value() == message.Value());

    PrimitiveProtocolVersion selected = 0;
    const PrimitiveProtocolVersionRange local{1, 3};
    const PrimitiveProtocolVersionRange remote{2, 4};
    assert(local.TrySelectHighestMutual(remote, selected));
    assert(selected == 3);

    const PrimitiveProtocolVersionRange incompatible{4, 5};
    assert(!local.TrySelectHighestMutual(incompatible, selected));

    ContractFingerprint::Storage digest{};
    digest[31] = 1U;
    const ContractFingerprint fingerprint(digest);
    assert(!fingerprint.IsZero());
    assert(fingerprint.Bytes() == digest);

    return 0;
}
