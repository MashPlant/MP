#if !defined(COMMON_HPP)
#define COMMON_HPP

#include <type_traits>
#include <utility>

namespace mp
{
struct TupleTag
{
};
struct IntegerTag
{
};
struct RangeTag
{
};
struct ListTag
{
};

template <typename T>
using TagOf = typename std::remove_reference_t<T>::MPTag;

} // namespace mp

#include "Make.hpp"
#include "ForEach.hpp"
#include "Transform.hpp"
#include "TypeName.hpp"

// avoid circular dependency
namespace mp::detail
{
template <char... Chars>
struct TypeNameImpl<std::integer_sequence<char, Chars...>>
{
    constexpr static auto name = "\""_str + std::integer_sequence<char, Chars...>{} + "\"_str"_str;
};
} // namespace mp::detail

#endif // COMMON_HPP
