#include "ESPressio_Primitive.hpp"
#include <atomic>
#include <cassert>
#include <cstdlib>
#include <new>
#include <thread>
#include <type_traits>
using namespace ESPressio::Primitive;
static std::atomic<bool> forbidAllocation{false};
void* operator new(std::size_t n) { if (forbidAllocation.load()) std::abort(); if (auto* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }
struct Sample {};
struct FamilyDefinition {
 static PrimitiveTypeDescriptor GetPrimitiveTypeDescriptor() noexcept {
  return {{0x8000,17}, "private.static", {}, {1,1}, {}, {}, {}};
 }
};
struct DeclarativeType final : FamilyDefinition {
 DeclarativeType()=delete; // Registration never constructs application payloads.
};
namespace ESPressio::Primitive {
template<> struct PrimitiveTypeTraits<Sample> {
 static constexpr PrimitiveTypeDescriptor Descriptor() noexcept {
  return {{FamilyIds::Event, 9}, "sample", PrimitiveTypeCapabilities{3}, {1, 1}, {}, {53}, {}};
 }
};
}
static PrimitiveTypeDescriptor descriptor(PrimitiveFamilyId family, std::uint64_t id, const char* name) {
 return {{family,id},name,{}, {1,1}, {}, {}, {}};
}
int main() {
 static_assert(!std::is_convertible_v<EventTypeId, CommandTypeId>);
 static_assert(sizeof(EventTypeId)==8 && sizeof(CommandTypeId)==8 && sizeof(StateTypeId)==8);
 using R=TypeDirectoryRegistrationStatus;
 TypeDirectory<4> d;
 assert(!d.View().IsFrozen());
 forbidAllocation=true;
 assert(d.Register<Sample>()==R::Success);
 assert(d.Register<Sample>()==R::DuplicateKey);
 auto x=descriptor(FamilyIds::Command,9,"sample");
 assert(d.Register(x)==R::Success); // Same name and number in another family is legal.
 x=descriptor(FamilyIds::Event,10,"sample");
 assert(d.Register(x)==R::DuplicateCanonicalName);
 x=descriptor(FamilyIds::Event,1,"Sample");
 assert(d.Register(x)==R::Success); // Exact case-sensitive names.
 x=descriptor(0,3,"invalid"); assert(d.Register(x)==R::InvalidDescriptor);
 x=descriptor(FamilyIds::State,3,"invalid"); x.Capabilities=PrimitiveTypeCapabilities{2};
 assert(d.Register(x)==R::InvalidDescriptor);
 x=descriptor(FamilyIds::State,3,"state");
 assert(d.Register(x)==R::Success); x.Key.TypeValue=99; // Common descriptor copied.
 assert(d.Register(descriptor(0x8000,1,"private"))==R::Full);
 assert(d.Size()==4);
 assert(d.Initialize()==TypeDirectoryInitializationStatus::Success);
 assert(d.Initialize()==TypeDirectoryInitializationStatus::AlreadyFrozen);
 assert(d.Register(descriptor(0x8000,1,"private"))==R::Frozen);
 const auto v=d.View();
 assert(v.IsFrozen() && v.Size()==4);
 assert(v.Find({FamilyIds::State,3}) && !v.Find({FamilyIds::State,99}));
 assert(v.Find(FamilyIds::Event,"sample")->Key.TypeValue==9);
 assert(v.Find(FamilyIds::Event,"Sample")->Key.TypeValue==1);
 assert(!v.Find(FamilyIds::Event,"SAMPLE"));
 auto previous=v.begin()->Key;
 for(const auto& entry:v) { assert(!(entry.Key<previous)); previous=entry.Key; }
 TypeDirectory<0> empty;
 assert(empty.Register<Sample>()==R::Full);
 assert(empty.Initialize()==TypeDirectoryInitializationStatus::Success);
 assert(empty.View().IsFrozen() && empty.View().begin()==empty.View().end());
 assert(!empty.View().Find({3,9}));
 // Configuration errors do not freeze or poison later valid registration.
 TypeDirectory<1> retry;
 assert(retry.Register(descriptor(3,0,"bad"))==R::InvalidDescriptor);
 assert(retry.Register<Sample>()==R::Success);
 assert(retry.Initialize()==TypeDirectoryInitializationStatus::Success);
 TypeDirectory<1> declarative;
 assert(declarative.Register<DeclarativeType>()==R::Success);
 assert(declarative.Initialize()==TypeDirectoryInitializationStatus::Success);
 assert(declarative.View().Find({0x8000,17}));
 forbidAllocation=false;
 std::thread readers[4];
 for(auto& reader:readers) reader=std::thread([v]{for(int i=0;i<10000;++i) assert(v.Find({3,9}) && v.Find(2,"sample"));});
 for(auto& reader:readers) reader.join();
 for(unsigned i=0;i<7;++i) {
  auto disposition=static_cast<PrimitiveAdmissionDisposition>(i);
  assert(EstablishesDestinationAdmission(disposition)==(i<2));
  assert(IsAdmissionRetryCandidate(disposition)==(i==2 || i==3));
 }
}
