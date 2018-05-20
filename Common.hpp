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

#endif // COMMON_HPP
