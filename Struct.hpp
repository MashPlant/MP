#if !defined(STRUCT_HPP)
#define STRUCT_HPP

#include "Common.hpp"
#include "Tuple.hpp"

namespace mp
{
namespace detail
{
template <typename T_, typename Mem_>
constexpr auto getMemberPointerInfo(Mem_ T_::*)
{
    struct Info
    {
        using T = T_;
        using Mem = Mem_;
    };
    return Info{};
}

template <auto Ptr>
struct MemberGetter
{
    using T = typename decltype(getMemberPointerInfo(Ptr))::T;
    using Mem = typename decltype(getMemberPointerInfo(Ptr))::Mem;

    template <typename T>
    static constexpr decltype(auto) get(T &&object)
    {
        return static_cast<T &&>(object).*Ptr;
    }
};
} // namespace detail

template <typename Struct>
constexpr auto members(Struct &&object)
{
    using Accessor = typename std::decay_t<Struct>::Accessor;
    constexpr auto tuple = Accessor::get();
    return transform(tuple, [&](auto pair) -> decltype(auto) {
        return pair[IntT<1>{}].get(static_cast<Struct &&>(object));
    });
}

#define FwdConcat(a, b) FwdConcat_(a, b)
#define FwdConcat_(a, b) a##b
#define FwdStaticStr(a) FwdStaticStr_(a)
#define FwdStaticStr_(a) StaticStr(#a)

#define ArgsCount(...) \
    ArgsCountImpl(__VA_ARGS__, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, )

#define ArgsCountImpl(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, N, ...) N

#define ArgsBack(...) \
    FwdConcat(ArgsBackImpl, ArgsCount(__VA_ARGS__))(__VA_ARGS__)

#define ArgsDropBack(...) \
    FwdConcat(ArgsDropBackImpl, ArgsCount(__VA_ARGS__))(__VA_ARGS__)

#define DefineStruct(...) \
    FwdConcat(DefineStructImpl, ArgsCount(__VA_ARGS__))(__VA_ARGS__)

#include "./dirty/StructMacros.hpp"

} // namespace mp

#endif // STRUCT_HPP
