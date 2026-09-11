#include "ESPressio_PrimitivePolicy.hpp"
#include <cassert>
using namespace ESPressio::Primitive;
struct Delivery {
 using PolicyCategory=OccurrenceDeliveryPolicyTag;
 using RequiredEvidence=DestinationPrimitiveAdmission;
 using TerminalDisposition=ReportTerminalFailureToFamily;
 static constexpr std::uint64_t MaximumResidenceNanoseconds=2000000000;
 static constexpr std::uint16_t MaximumAttempts=4;
 static constexpr std::uint64_t MaximumAdapterAdmissionWaitNanoseconds=5000000;
 static constexpr std::uint64_t MinimumRetrySpacingNanoseconds=25000000;
 static constexpr std::uint64_t MaximumRetrySpacingNanoseconds=250000000;
};
struct SameMeaning: Delivery {};
struct Changed: Delivery {static constexpr std::uint16_t MaximumAttempts=3;};
struct BadZero: Delivery {static constexpr std::uint16_t MaximumAttempts=0;};
struct BadResidence: Delivery {static constexpr std::uint64_t MaximumResidenceNanoseconds=0;};
struct BadWait: Delivery {static constexpr std::uint64_t MaximumAdapterAdmissionWaitNanoseconds=3000000000;};
struct BadSpacing: Delivery {static constexpr std::uint64_t MinimumRetrySpacingNanoseconds=300000000;};
struct Stateful: Delivery {int state;};
struct Immediate: Delivery {
 using RequiredEvidence=NoRemoteEvidence;
 static constexpr std::uint64_t MaximumResidenceNanoseconds=0;
 static constexpr std::uint16_t MaximumAttempts=1;
 static constexpr std::uint64_t MaximumAdapterAdmissionWaitNanoseconds=0;
 static constexpr std::uint64_t MinimumRetrySpacingNanoseconds=0;
 static constexpr std::uint64_t MaximumRetrySpacingNanoseconds=0;
};
struct Convergent: Delivery {
 using PolicyCategory=StateConvergencePolicyTag;
 using Supersession=LatestAuthoritativeValue;
 using ExhaustionDisposition=DormantNeedsConvergence;
};
static_assert(IsOccurrenceDeliveryPolicy<Delivery>::value);
static_assert(IsOccurrenceDeliveryPolicy<Immediate>::value);
static_assert(IsStateConvergencePolicy<Convergent>::value);
static_assert(!IsOccurrenceDeliveryPolicy<Convergent>::value);
static_assert(!IsStateConvergencePolicy<Delivery>::value);
static_assert(!IsOccurrenceDeliveryPolicy<int>::value);
static_assert(!IsOccurrenceDeliveryPolicy<BadZero>::value);
static_assert(!IsOccurrenceDeliveryPolicy<BadResidence>::value);
static_assert(!IsOccurrenceDeliveryPolicy<BadWait>::value);
static_assert(!IsOccurrenceDeliveryPolicy<BadSpacing>::value);
static_assert(!IsOccurrenceDeliveryPolicy<Stateful>::value);
constexpr auto bytes=PrimitivePolicyContract<Delivery>::Descriptor().CanonicalBytes();
static_assert(bytes.size()==40 && bytes[0]==1 && bytes[1]==1 && bytes[2]==1 && bytes[3]==1);
static_assert(bytes[6]==0 && bytes[7]==0x94 && bytes[8]==0x35 && bytes[9]==0x77);
static_assert(bytes[14]==4 && bytes[15]==0);
int main() {
 assert(bytes==PrimitivePolicyContract<SameMeaning>::Descriptor().CanonicalBytes());
 assert(bytes!=PrimitivePolicyContract<Changed>::Descriptor().CanonicalBytes());
 assert(bytes!=PrimitivePolicyContract<Convergent>::Descriptor().CanonicalBytes());
}
