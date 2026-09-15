#include <ESPressio_EventWire.hpp>
#include <ESPressio_CommandWireV1.hpp>
#include <ESPressio_StateWireV1.hpp>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

using namespace ESPressio;
namespace E = ESPressio::Event;
namespace C = ESPressio::Command;
namespace S = ESPressio::State;

namespace {

System::DeviceIdentifier Device(std::uint8_t seed) {
    System::DeviceIdentifier::Storage bytes{};
    for (std::size_t i = 0; i < bytes.size(); ++i)
        bytes[i] = static_cast<std::uint8_t>(seed + i + 1U);
    return System::DeviceIdentifier{bytes};
}

System::DeviceRuntimeIdentity Identity(std::uint8_t seed, std::uint32_t incarnation) {
    return {Device(seed), System::RuntimeIncarnationId{incarnation}};
}

template<std::size_t N, class TDecoder>
void RejectEveryTruncation(const std::array<std::uint8_t, N>& bytes, TDecoder&& decode) {
    for (std::size_t size = 0; size < N; ++size)
        assert(!decode(bytes.data(), size));
}

template<std::size_t N, class TDecoder>
void ExerciseDeterministicMutations(const std::array<std::uint8_t, N>& seed, TDecoder&& decode) {
    constexpr std::array<std::uint8_t, 3> masks{{0x01U, 0x80U, 0xFFU}};
    for (std::size_t offset = 0; offset < N; ++offset) {
        for (const auto mask : masks) {
            auto mutated = seed;
            mutated[offset] ^= mask;
            (void)decode(mutated.data(), mutated.size());
        }
    }
}

void ValidateEventWire() {
    E::EventWireHeader header{};
    header.Key.TypeId = E::EventTypeId{0x0807060504030201ULL};
    header.Key.MessageId = E::ConceptualMessageId{0x1817161514131211ULL};
    header.Key.Origin = Identity(0x20U, 0x34333231U);
    header.OriginDispatchTime = {0x4847464544434241ULL, Timing::TimeReliability::Holdover};
    header.PayloadLength = 3U;

    std::array<std::uint8_t, E::EventWireHeaderSize + 3U> wire{};
    assert(E::EncodeEventWireHeader(header, wire.data(), wire.size()));
    wire[E::EventWireHeaderSize + 0U] = 0xAAU;
    wire[E::EventWireHeaderSize + 1U] = 0xBBU;
    wire[E::EventWireHeaderSize + 2U] = 0xCCU;

    const auto decode = [](const std::uint8_t* data, std::size_t size) {
        E::EventWireHeader output{};
        return E::DecodeEventWireHeader(data, size, output);
    };
    assert(decode(wire.data(), wire.size()));
    RejectEveryTruncation(wire, decode);

    auto bad = wire;
    bad[0] ^= 0x01U;
    assert(!decode(bad.data(), bad.size()));
    bad = wire;
    bad[2] ^= 0x01U;
    E::EventWireHeader eventOutput{};
    assert(E::DecodeEventWireHeader(bad.data(), bad.size(), eventOutput).Status == E::EventWireStatus::UnsupportedProtocol);
    bad = wire;
    bad[48] = 0xFFU;
    assert(!decode(bad.data(), bad.size()));
    bad = wire;
    bad[49] ^= 0x01U;
    assert(E::DecodeEventWireHeader(bad.data(), bad.size(), eventOutput).Status == E::EventWireStatus::InvalidLength);

    ExerciseDeterministicMutations(wire, decode);

    for (std::uint32_t payloadLength = 0; payloadLength <= 8U; ++payloadLength) {
        header.PayloadLength = payloadLength;
        header.OriginDispatchTime.Reliability = static_cast<Timing::TimeReliability>(payloadLength & 0x03U);
        std::array<std::uint8_t, E::EventWireHeaderSize + 8U> property{};
        const auto total = E::EventWireHeaderSize + payloadLength;
        assert(E::EncodeEventWireHeader(header, property.data(), property.size()));
        E::EventWireHeader decoded{};
        assert(E::DecodeEventWireHeader(property.data(), total, decoded));
        assert(decoded.Key == header.Key);
        assert(decoded.PayloadLength == payloadLength);
        assert(decoded.OriginDispatchTime.Reliability == header.OriginDispatchTime.Reliability);
    }
}

void ValidateCommandWire() {
    const auto origin = Identity(0x30U, 0x11223344U);
    const auto executor = Identity(0x50U, 0x55667788U);
    const C::CommandExecutionKey key{
        C::CommandTypeId{0x8877665544332211ULL}, origin.Device, origin.Incarnation, C::CommandId{0x10203040U}};

    C::CommandRequestWireHeader request{
        key, {0x0102030405060708ULL, Timing::TimeReliability::Synchronized}, 3U};
    std::array<std::uint8_t, C::CommandRequestWireHeaderSize + 3U> requestWire{};
    assert(C::EncodeCommandRequestHeader(request, requestWire.data(), requestWire.size()));
    requestWire[C::CommandRequestWireHeaderSize + 0U] = 1U;
    requestWire[C::CommandRequestWireHeaderSize + 1U] = 2U;
    requestWire[C::CommandRequestWireHeaderSize + 2U] = 3U;

    const auto decodeRequest = [](const std::uint8_t* data, std::size_t size) {
        C::CommandRequestWireHeader output{};
        return C::DecodeCommandRequestHeader(data, size, output);
    };
    assert(decodeRequest(requestWire.data(), requestWire.size()));
    RejectEveryTruncation(requestWire, decodeRequest);

    auto badRequest = requestWire;
    badRequest[0] ^= 0x01U;
    assert(!decodeRequest(badRequest.data(), badRequest.size()));
    badRequest = requestWire;
    badRequest[2] ^= 0x01U;
    C::CommandRequestWireHeader requestOutput{};
    assert(C::DecodeCommandRequestHeader(badRequest.data(), badRequest.size(), requestOutput).Status ==
           C::CommandWireStatus::UnsupportedProtocol);
    badRequest = requestWire;
    badRequest[4] = static_cast<std::uint8_t>(C::CommandMessageKind::Response);
    assert(!decodeRequest(badRequest.data(), badRequest.size()));
    badRequest = requestWire;
    badRequest[45] = 0xFFU;
    assert(!decodeRequest(badRequest.data(), badRequest.size()));
    badRequest = requestWire;
    badRequest[46] ^= 0x01U;
    assert(C::DecodeCommandRequestHeader(badRequest.data(), badRequest.size(), requestOutput).Status ==
           C::CommandWireStatus::InvalidLength);
    ExerciseDeterministicMutations(requestWire, decodeRequest);

    C::CommandResponseWireHeader response{
        key, executor, C::CommandResponseDisposition::Succeeded, 3U};
    std::array<std::uint8_t, C::CommandResponseWireHeaderSize + 3U> responseWire{};
    assert(C::EncodeCommandResponseHeader(response, responseWire.data(), responseWire.size()));
    responseWire[C::CommandResponseWireHeaderSize + 0U] = 4U;
    responseWire[C::CommandResponseWireHeaderSize + 1U] = 5U;
    responseWire[C::CommandResponseWireHeaderSize + 2U] = 6U;

    const auto decodeResponse = [](const std::uint8_t* data, std::size_t size) {
        C::CommandResponseWireHeader output{};
        return C::DecodeCommandResponseHeader(data, size, output);
    };
    assert(decodeResponse(responseWire.data(), responseWire.size()));
    RejectEveryTruncation(responseWire, decodeResponse);

    auto badResponse = responseWire;
    badResponse[0] ^= 0x01U;
    assert(!decodeResponse(badResponse.data(), badResponse.size()));
    badResponse = responseWire;
    badResponse[2] ^= 0x01U;
    C::CommandResponseWireHeader responseOutput{};
    assert(C::DecodeCommandResponseHeader(badResponse.data(), badResponse.size(), responseOutput).Status ==
           C::CommandWireStatus::UnsupportedProtocol);
    badResponse = responseWire;
    badResponse[4] = static_cast<std::uint8_t>(C::CommandMessageKind::Request);
    assert(!decodeResponse(badResponse.data(), badResponse.size()));
    badResponse = responseWire;
    badResponse[57] = 0xFFU;
    assert(!decodeResponse(badResponse.data(), badResponse.size()));
    badResponse = responseWire;
    badResponse[58] ^= 0x01U;
    assert(C::DecodeCommandResponseHeader(badResponse.data(), badResponse.size(), responseOutput).Status ==
           C::CommandWireStatus::InvalidLength);
    ExerciseDeterministicMutations(responseWire, decodeResponse);

    for (std::uint32_t payloadLength = 0; payloadLength <= 8U; ++payloadLength) {
        request.PayloadLength = payloadLength;
        request.OriginRequestTime.Reliability = static_cast<Timing::TimeReliability>(payloadLength & 0x03U);
        std::array<std::uint8_t, C::CommandRequestWireHeaderSize + 8U> property{};
        const auto total = C::CommandRequestWireHeaderSize + payloadLength;
        assert(C::EncodeCommandRequestHeader(request, property.data(), property.size()));
        C::CommandRequestWireHeader decoded{};
        assert(C::DecodeCommandRequestHeader(property.data(), total, decoded));
        assert(decoded.Key == request.Key);
        assert(decoded.PayloadLength == payloadLength);
        assert(decoded.OriginRequestTime.Reliability == request.OriginRequestTime.Reliability);
    }
}

void ValidateStateWire() {
    const auto owner = Identity(0x60U, 0x01020304U);
    const auto requester = Identity(0x70U, 0x05060708U);
    const S::StateTypeId type{0x0102030405060708ULL};
    const S::StateSessionToken session{0x11223344U};

    S::StatePublicationWireHeader publication{
        type, owner, requester, session, {false, 7U},
        {0x1112131415161718ULL, Timing::TimeReliability::Acquiring}, 3U};
    std::array<std::uint8_t, S::StatePublicationWireHeaderSize + 3U> publicationWire{};
    assert(S::EncodeStatePublicationHeader(publication, publicationWire.data(), publicationWire.size()));
    publicationWire[S::StatePublicationWireHeaderSize + 0U] = 7U;
    publicationWire[S::StatePublicationWireHeaderSize + 1U] = 8U;
    publicationWire[S::StatePublicationWireHeaderSize + 2U] = 9U;

    const auto decodePublication = [](const std::uint8_t* data, std::size_t size) {
        S::StatePublicationWireHeader output{};
        return S::DecodeStatePublicationHeader(data, size, output);
    };
    assert(decodePublication(publicationWire.data(), publicationWire.size()));
    RejectEveryTruncation(publicationWire, decodePublication);

    auto badPublication = publicationWire;
    badPublication[0] ^= 0x01U;
    assert(!decodePublication(badPublication.data(), badPublication.size()));
    badPublication = publicationWire;
    badPublication[2] ^= 0x01U;
    S::StatePublicationWireHeader publicationOutput{};
    assert(S::DecodeStatePublicationHeader(badPublication.data(), badPublication.size(), publicationOutput).Status ==
           S::StateWireStatus::UnsupportedProtocol);
    badPublication = publicationWire;
    badPublication[4] = static_cast<std::uint8_t>(S::StateMessageKind::SubscribeRequest);
    assert(!decodePublication(badPublication.data(), badPublication.size()));
    badPublication = publicationWire;
    badPublication[57] = 2U;
    assert(!decodePublication(badPublication.data(), badPublication.size()));
    badPublication = publicationWire;
    badPublication[68] = 0xFFU;
    assert(!decodePublication(badPublication.data(), badPublication.size()));
    badPublication = publicationWire;
    badPublication[69] ^= 0x01U;
    assert(S::DecodeStatePublicationHeader(badPublication.data(), badPublication.size(), publicationOutput).Status ==
           S::StateWireStatus::InvalidLength);
    ExerciseDeterministicMutations(publicationWire, decodePublication);

    S::StateControlWireHeader common{
        S::StateMessageKind::UnsubscribeRequest, type, owner, requester, session, {}, 0U};
    std::array<std::uint8_t, S::StateControlWireHeaderSize> commonWire{};
    assert(S::EncodeStateControl(common, commonWire.data(), commonWire.size()));
    const auto decodeCommon = [](const std::uint8_t* data, std::size_t size) {
        S::StateControlWireHeader output{};
        return S::DecodeStateControl(data, size, output);
    };
    assert(decodeCommon(commonWire.data(), commonWire.size()));
    RejectEveryTruncation(commonWire, decodeCommon);
    auto badCommon = commonWire;
    badCommon[2] ^= 0x01U;
    S::StateControlWireHeader commonOutput{};
    assert(S::DecodeStateControl(badCommon.data(), badCommon.size(), commonOutput).Status ==
           S::StateWireStatus::UnsupportedProtocol);
    badCommon = commonWire;
    badCommon[4] = 0U;
    assert(!decodeCommon(badCommon.data(), badCommon.size()));
    ExerciseDeterministicMutations(commonWire, decodeCommon);

    S::StateControlWireHeader snapshotControl{
        S::StateMessageKind::BaselineSnapshot, type, owner, requester, session, {}, 0U};
    S::StateSnapshotControlWireHeader snapshot{
        snapshotControl, {true, 9U}, {0x2122232425262728ULL, Timing::TimeReliability::Synchronized}, 2U};
    std::array<std::uint8_t, S::StateSnapshotControlWireHeaderSize + 2U> snapshotWire{};
    assert(S::EncodeStateSnapshotControlHeader(snapshot, snapshotWire.data(), snapshotWire.size()));
    snapshotWire[S::StateSnapshotControlWireHeaderSize + 0U] = 0xA1U;
    snapshotWire[S::StateSnapshotControlWireHeaderSize + 1U] = 0xA2U;
    const auto decodeSnapshot = [](const std::uint8_t* data, std::size_t size) {
        S::StateSnapshotControlWireHeader output{};
        return S::DecodeStateSnapshotControlHeader(data, size, output);
    };
    assert(decodeSnapshot(snapshotWire.data(), snapshotWire.size()));
    RejectEveryTruncation(snapshotWire, decodeSnapshot);
    auto badSnapshot = snapshotWire;
    badSnapshot[2] ^= 0x01U;
    S::StateSnapshotControlWireHeader snapshotOutput{};
    assert(S::DecodeStateSnapshotControlHeader(badSnapshot.data(), badSnapshot.size(), snapshotOutput).Status ==
           S::StateWireStatus::UnsupportedProtocol);
    badSnapshot = snapshotWire;
    badSnapshot[4] = static_cast<std::uint8_t>(S::StateMessageKind::UnsubscribeRequest);
    assert(!decodeSnapshot(badSnapshot.data(), badSnapshot.size()));
    badSnapshot = snapshotWire;
    badSnapshot[62] = 2U;
    assert(!decodeSnapshot(badSnapshot.data(), badSnapshot.size()));
    badSnapshot = snapshotWire;
    badSnapshot[73] = 0xFFU;
    assert(!decodeSnapshot(badSnapshot.data(), badSnapshot.size()));
    badSnapshot = snapshotWire;
    badSnapshot[74] ^= 0x01U;
    assert(S::DecodeStateSnapshotControlHeader(badSnapshot.data(), badSnapshot.size(), snapshotOutput).Status ==
           S::StateWireStatus::InvalidLength);
    ExerciseDeterministicMutations(snapshotWire, decodeSnapshot);

    S::StateControlWireHeader acceptanceControl{
        S::StateMessageKind::PublicationAccepted, type, owner, requester, session, {}, 0U};
    S::StateAcceptanceControlWireHeader acceptance{acceptanceControl, {false, 11U}};
    std::array<std::uint8_t, S::StateAcceptanceControlWireHeaderSize> acceptanceWire{};
    assert(S::EncodeStateAcceptanceControl(acceptance, acceptanceWire.data(), acceptanceWire.size()));
    const auto decodeAcceptance = [](const std::uint8_t* data, std::size_t size) {
        S::StateAcceptanceControlWireHeader output{};
        return S::DecodeStateAcceptanceControl(data, size, output);
    };
    assert(decodeAcceptance(acceptanceWire.data(), acceptanceWire.size()));
    RejectEveryTruncation(acceptanceWire, decodeAcceptance);
    auto badAcceptance = acceptanceWire;
    badAcceptance[2] ^= 0x01U;
    S::StateAcceptanceControlWireHeader acceptanceOutput{};
    assert(S::DecodeStateAcceptanceControl(badAcceptance.data(), badAcceptance.size(), acceptanceOutput).Status ==
           S::StateWireStatus::UnsupportedProtocol);
    badAcceptance = acceptanceWire;
    badAcceptance[4] = static_cast<std::uint8_t>(S::StateMessageKind::SubscribeAccepted);
    assert(!decodeAcceptance(badAcceptance.data(), badAcceptance.size()));
    badAcceptance = acceptanceWire;
    badAcceptance[62] = 2U;
    assert(!decodeAcceptance(badAcceptance.data(), badAcceptance.size()));
    ExerciseDeterministicMutations(acceptanceWire, decodeAcceptance);

    for (std::uint32_t payloadLength = 0; payloadLength <= 8U; ++payloadLength) {
        publication.PayloadLength = payloadLength;
        publication.Version = {bool(payloadLength & 1U), static_cast<std::uint16_t>(payloadLength + 1U)};
        publication.TruthTime.Reliability = static_cast<Timing::TimeReliability>(payloadLength & 0x03U);
        std::array<std::uint8_t, S::StatePublicationWireHeaderSize + 8U> property{};
        const auto total = S::StatePublicationWireHeaderSize + payloadLength;
        assert(S::EncodeStatePublicationHeader(publication, property.data(), property.size()));
        S::StatePublicationWireHeader decoded{};
        assert(S::DecodeStatePublicationHeader(property.data(), total, decoded));
        assert(decoded.TypeId == publication.TypeId);
        assert(decoded.PayloadLength == payloadLength);
        assert(decoded.Version == publication.Version);
        assert(decoded.TruthTime.Reliability == publication.TruthTime.Reliability);
    }
}

} // namespace

int main() {
    ValidateEventWire();
    ValidateCommandWire();
    ValidateStateWire();
    return 0;
}
