#if !defined(STATICSTR_HPP)
#define STATICSTR_HPP

#include "Common.hpp"

namespace mp
{
namespace detail
{
template <typename T, size_t... N>
constexpr auto getStaticStrImpl(std::index_sequence<N...>)
{
    return std::integer_sequence<char, T::get()[N]...>();
}
template <typename T>
constexpr auto getStaticStr(T)
{
    return getStaticStrImpl<T>(std::make_index_sequence<sizeof(T::get()) - 1>());
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
    return std::integer_sequence<Char, Chars...>{};
}
} // namespace literals

template <typename Str, typename Str_>
struct StrConcat
{
};

template <char... Chars, char... Chars_>
struct StrConcat<std::integer_sequence<char, Chars...>, std::integer_sequence<char, Chars_...>>
{
    constexpr static auto result = std::integer_sequence<char, Chars..., Chars_...>{};
};

template <typename Str, typename Str_, typename = decltype(StrConcat<Str, Str_>::result)>
constexpr auto operator+(Str, Str_)
{
    return StrConcat<Str, Str_>::result;
}

template <typename OS, char... Chars>
constexpr decltype(auto) operator<<(OS &&os, std::integer_sequence<char, Chars...>)
{
    using Dummy = int[];
    static_cast<void>(Dummy{0, (os << Chars, 0)...});
    return os;
}
} // namespace mp

#endif // STATICSTR_HPP
