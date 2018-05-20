#if !defined(TYPENAME_HPP)
#define TYPENAME_HPP

#include "Common.hpp"
#include "String.hpp"

namespace mp
{
namespace detail
{

template <unsigned N, typename = void>
struct ParseUInt
{
    constexpr static auto name = ParseUInt<N / 10>::name + std::integer_sequence<char, N % 10 + '0'>{};
};
template <unsigned N>
struct ParseUInt<N, std::enable_if_t<(N < 10)>>
{
    constexpr static auto name = std::integer_sequence<char, N + '0'>{};
};

using namespace mp::literals;
template <typename T, typename = void> //for SFINAE
struct TypeNameImpl
{
    constexpr static auto name = "undefined"_str;
};

#define BasicTypeName(Type)                       \
    template <>                                   \
    struct TypeNameImpl<Type>                     \
    {                                             \
        constexpr static auto name = #Type##_str; \
    };

BasicTypeName(int)
BasicTypeName(char)
BasicTypeName(double)
BasicTypeName(float)
BasicTypeName(void)

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
    constexpr static auto name = "array["_str + ParseUInt<N>::name +
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
    constexpr static auto name = "function ("_str + TypeNames<Args...>::name +
                                 " return ("_str + TypeNameImpl<Ret>::name;
};

} // namespace detail

template <typename T>
using TypeName = detail::TypeNameImpl<T>;

} // namespace mp

#endif // TYPENAME_HPP
