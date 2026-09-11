#include <ESPressio_ContractFingerprintBuilder.hpp>
#include <cassert>
#include <cstdlib>
#include <new>
using namespace ESPressio::Primitive;
static bool deny=false;
void* operator new(std::size_t n) { if(deny) std::abort();if(auto* p=std::malloc(n?n:1)) return p;throw std::bad_alloc(); }
void operator delete(void* p) noexcept {std::free(p);}
void operator delete(void* p,std::size_t) noexcept {std::free(p);}
constexpr auto Empty=ContractFingerprintBuilder{}.Finish();
static_assert(Empty.Bytes()[0]==0xe3 && Empty.Bytes()[31]==0x55);
int main() {
 struct Vector {std::size_t Length;const char* Hex;};
 constexpr Vector vectors[]={{0,"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
{1,"e7cf46a078fed4fafd0b5e3aff144802b853f8ae459a4f0c14add3314b7cc3a6"},
{3,"b39fad1a1075f64570b3226d339ea818f9c66ecd2f1c59fd8b9c5a32b54c513f"},
{55,"2900465fcb533e05a158fd2b3be0e5e3b03740d83060aa3580e0d98a96bf2384"},
{56,"31454ff48ef36af2f08fd511bdc37d9d5855ac23e992e5ff5445cb6b7674a674"},
{63,"5f6401b96532c36de4e65beec0409b69b1d181864c8009b7a04f43e5d56350d1"},
{64,"94eb5de4943613fd048dc93393ab06877405faa39c11f53e9386083339833e7e"},
{65,"fc518669b6eb4b4dd91827ecacef86689c725bd5bab888fd3b26dbb196eec954"},
{127,"0fe729ff19257bd6fec853acc2ea355f6b34b58e6c0f684c3e188fcdfcd9baae"},
{128,"0aedd4856f8eba0963627336ad5144a9a7dbe12498e6066f0165fc97d8ddee4c"},
{1000,"57799de80e3dd6e2ac4d40c41a150d1662f7f87d0d994776a2fdc37c39b0ea4e"}};
 const char* digits="0123456789abcdef";
 deny=true;
 for(auto vector:vectors) {
  ContractFingerprintBuilder hash;
  for(std::size_t i=0;i<vector.Length;++i) hash.Byte(static_cast<std::uint8_t>(i*37+11));
  const auto result=hash.Finish();assert(result==hash.Finish());
  for(std::size_t i=0;i<32;++i) { assert(digits[result.Bytes()[i]>>4]==vector.Hex[2*i]);assert(digits[result.Bytes()[i]&15]==vector.Hex[2*i+1]); }
 }
 ContractFingerprintBuilder a,b;a.Text("ab");a.Text("c");b.Text("a");b.Text("bc");assert(a.Finish()!=b.Finish());
 deny=false;
}
