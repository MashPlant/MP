#if !defined(STRUCT_HPP)
#define STRUCT_HPP

#include "Common.hpp"
#include "IntegerT.hpp"

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
constexpr auto memberTuple(Struct &&object)
{
    using Accessor = typename std::decay_t<Struct>::Accessor;
    constexpr auto tuple = Accessor::get();
    return transform(tuple, [&](auto pair) -> decltype(auto) {
        return  pair[IntT<1>{}].get(static_cast<Struct &&>(object));
    });
}

} // namespace mp

#endif // STRUCT_HPP
