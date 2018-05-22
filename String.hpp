#if !defined(STATICSTR_HPP)
#define STATICSTR_HPP

#include "Common.hpp"
#include "IntegerSeq.hpp"

namespace mp
{

namespace detail
{
constexpr int staticStrlen(const char *str)
{
    int len = 0;
    while (*str++)
        ++len;
    return len;
}
} // namespace detail

template <char... Chars>
constexpr bool operator==(CharSeq<Chars...>, const char *s2)
{
    constexpr char s1[] = {Chars..., '\0'};
    int l1 = sizeof...(Chars), l2 = detail::staticStrlen(s2);
    if (l1 != l2)
        return false;
    for (int i = 0; i < l1; ++i)
        if (s1[i] != s2[i])
            return false;
    return true;
}

template <char... Chars>
constexpr bool operator==(const char *s1, CharSeq<Chars...> s2)
{
    return s2 == s1;
}

namespace detail
{
template <typename T, int... N>
constexpr auto getStaticStrImpl(IntSeq<N...>)
{
    return CharSeq<T::get()[N]...>();
}
template <typename T>
constexpr auto getStaticStr(T)
{
    return getStaticStrImpl<T>(make<IntegerSeqTag>(IntT<sizeof(T::get()) - 1>{}));
}
} // namespace detail

// two way to make a type from a string

// way1 : use lambda to convert non-type parameter to type-parameter
#define StaticStr(str)                                            \
    mp::detail::getStaticStr([]() {                               \
        struct Tmp                                                \
        {                                                         \
            constexpr static decltype(auto) get() { return str; } \
        };                                                        \
        return Tmp{};                                             \
    }())

// way2 : g++ extension
namespace literals
{
template <typename Char, Char... Chars>
constexpr auto operator""_str()
{
    return CharSeq<Chars...>{};
}
} // namespace literals

} // namespace mp

#endif // STATICSTR_HPP
