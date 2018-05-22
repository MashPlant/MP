#if !defined(TYPENAME_HPP)
#define TYPENAME_HPP

#include "Common.hpp"
#include "String.hpp"

namespace mp
{
namespace detail
{
template <int N>
constexpr auto parseInt()
{
    if constexpr (N < 0)
        return CharSeq<'-'>{} + parseInt<-N>();
    else if constexpr (N < 10)
        return CharSeq<N + '0'>{};
    else
        return parseInt<N / 10>() + CharSeq<N % 10 + '0'>{};
}

using namespace mp::literals;
template <typename T, typename = void> //for SFINAE
struct TypeNameImpl
{
    constexpr static auto name = "undefined"_str;
};

template <>
struct TypeNameImpl<int>
{
    constexpr static auto name = "int"_str;
};
template <>
struct TypeNameImpl<char>
{
    constexpr static auto name = "char"_str;
};
template <>
struct TypeNameImpl<double>
{
    constexpr static auto name = "double"_str;
};
template <>
struct TypeNameImpl<float>
{
    constexpr static auto name = "float"_str;
};
template <>
struct TypeNameImpl<void>
{
    constexpr static auto name = "void"_str;
};

template <typename T>
struct TypeNameImpl<const T, typename std::enable_if<!std::is_array<T>::value>::type>
{
    constexpr static auto name = "const "_str + TypeNameImpl<T>::name;
};

template <typename T>
struct TypeNameImpl<T *>
{
    constexpr static auto name = "pointer to "_str + TypeNameImpl<T>::name;
};
template <typename T>
struct TypeNameImpl<T &>
{
    constexpr static auto name = "l-reference of "_str + TypeNameImpl<T>::name;
};
template <typename T>
struct TypeNameImpl<T &&>
{
    constexpr static auto name = "r-reference of "_str + TypeNameImpl<T>::name;
};
template <typename T, int N>
struct TypeNameImpl<T[N]>
{
    constexpr static auto name = "array["_str + parseInt<N>() +
                                 "] of "_str + TypeNameImpl<T>::name;
};

template <typename...>
struct TypeNames;
template <typename First, typename... Rests>
struct TypeNames<First, Rests...>
{
    constexpr static auto name = TypeNameImpl<First>::name + ", "_str + TypeNames<Rests...>::name;
};
template <typename First>
struct TypeNames<First>
{
    constexpr static auto name = TypeNameImpl<First>::name;
};
template <>
struct TypeNames<>
{
    constexpr static auto name = ""_str;
};

template <typename Ret, typename... Args>
struct TypeNameImpl<Ret(Args...)>
{
    // C++17 folding expression
    constexpr static auto name = "function ("_str + TypeNames<Args...>::name +
                                 ") return "_str + TypeNameImpl<Ret>::name;
};

} // namespace detail

template <typename T>
using TypeName = detail::TypeNameImpl<T>;

} // namespace mp

#endif // TYPENAME_HPP
