#pragma once
#include <array>
#include <cstdint>
#include <exception>
#include <string_view>
#include "ESPressio_PrimitiveTypes.hpp"
namespace ESPressio::Primitive {
/// Fixed-storage SHA-256 sink for complete family contract semantics. Families
/// supply domain-separated canonical bytes; this is compatibility metadata and
/// never authentication, a credential, or a runtime policy decision.
class ContractFingerprintBuilder final {
    std::array<std::uint32_t,8> _state{0x6a09e667U,0xbb67ae85U,0x3c6ef372U,0xa54ff53aU,
        0x510e527fU,0x9b05688cU,0x1f83d9abU,0x5be0cd19U};
    std::array<std::uint8_t,64> _block{};
    std::size_t _used=0;
    std::uint64_t _bytes=0;
    inline static constexpr std::array<std::uint32_t,64> Rounds{
        0x428a2f98U,0x71374491U,0xb5c0fbcfU,0xe9b5dba5U,0x3956c25bU,0x59f111f1U,0x923f82a4U,0xab1c5ed5U,
        0xd807aa98U,0x12835b01U,0x243185beU,0x550c7dc3U,0x72be5d74U,0x80deb1feU,0x9bdc06a7U,0xc19bf174U,
        0xe49b69c1U,0xefbe4786U,0x0fc19dc6U,0x240ca1ccU,0x2de92c6fU,0x4a7484aaU,0x5cb0a9dcU,0x76f988daU,
        0x983e5152U,0xa831c66dU,0xb00327c8U,0xbf597fc7U,0xc6e00bf3U,0xd5a79147U,0x06ca6351U,0x14292967U,
        0x27b70a85U,0x2e1b2138U,0x4d2c6dfcU,0x53380d13U,0x650a7354U,0x766a0abbU,0x81c2c92eU,0x92722c85U,
        0xa2bfe8a1U,0xa81a664bU,0xc24b8b70U,0xc76c51a3U,0xd192e819U,0xd6990624U,0xf40e3585U,0x106aa070U,
        0x19a4c116U,0x1e376c08U,0x2748774cU,0x34b0bcb5U,0x391c0cb3U,0x4ed8aa4aU,0x5b9cca4fU,0x682e6ff3U,
        0x748f82eeU,0x78a5636fU,0x84c87814U,0x8cc70208U,0x90befffaU,0xa4506cebU,0xbef9a3f7U,0xc67178f2U
    };
    static constexpr std::uint32_t Rotate(std::uint32_t x,unsigned n) noexcept { return (x>>n)|(x<<(32-n)); }
    constexpr void Compress() noexcept {
        std::array<std::uint32_t,64> words{};
        for(std::size_t i=0;i<16;++i)
            for(std::size_t j=0;j<4;++j) words[i]=(words[i]<<8)|_block[i*4+j];
        for(std::size_t i=16;i<64;++i) {
            const auto x=words[i-15],y=words[i-2];
            const auto s0=Rotate(x,7)^Rotate(x,18)^(x>>3);
            const auto s1=Rotate(y,17)^Rotate(y,19)^(y>>10);
            words[i]=words[i-16]+s0+words[i-7]+s1;
        }
        auto a=_state[0],b=_state[1],c=_state[2],d=_state[3],e=_state[4],f=_state[5],g=_state[6],h=_state[7];
        for(std::size_t i=0;i<64;++i) {
            const auto s1=Rotate(e,6)^Rotate(e,11)^Rotate(e,25);
            const auto t1=h+s1+((e&f)^(~e&g))+Rounds[i]+words[i];
            const auto s0=Rotate(a,2)^Rotate(a,13)^Rotate(a,22);
            const auto t2=s0+((a&b)^(a&c)^(b&c));
            h=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2;
        }
        _state[0]+=a;_state[1]+=b;_state[2]+=c;_state[3]+=d;
        _state[4]+=e;_state[5]+=f;_state[6]+=g;_state[7]+=h;
    }
    constexpr void Push(std::uint8_t byte) noexcept {
        _block[_used++]=byte;
        if(_used==64) { Compress();_used=0; }
    }
public:
    /// Appends one canonical byte. Input length cannot wrap SHA-256's bit count.
    constexpr void Byte(std::uint8_t byte) noexcept {
        if(_bytes==UINT64_MAX/8) std::terminate();
        ++_bytes;Push(byte);
    }
    /// Canonical schema/policy scalars use exactly eight little-endian bytes.
    constexpr void Integer(std::uint64_t value) noexcept {
        for(unsigned i=0;i<8;++i) { Byte(static_cast<std::uint8_t>(value));value>>=8; }
    }
    /// Unambiguous length-prefixed text; neither C++ names nor pointers are hashed implicitly.
    constexpr void Text(std::string_view value) noexcept {
        Integer(value.size());for(char byte:value) Byte(static_cast<std::uint8_t>(byte));
    }
    /// Finalizes a copy. The original builder remains usable and no heap is involved.
    constexpr ContractFingerprint Finish() const noexcept {
        auto hash=*this;
        const auto bits=_bytes*8;
        hash.Push(0x80);
        while(hash._used!=56) hash.Push(0);
        for(unsigned i=0;i<8;++i) hash.Push(static_cast<std::uint8_t>(bits>>(56-8*i)));
        ContractFingerprint::Storage bytes{};
        for(std::size_t i=0;i<8;++i)
            for(std::size_t j=0;j<4;++j) bytes[4*i+j]=static_cast<std::uint8_t>(hash._state[i]>>(24-8*j));
        return ContractFingerprint{bytes};
    }
};
}
