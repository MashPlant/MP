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
struct IntegerSeqTag
{
};
struct RangeTag
{
};
struct ListTag
{
};

template <typename T>
using TagOf = typename std::decay_t<T>::MPTag;

template <typename T>
constexpr inline bool ValueOf = std::decay_t<T>::value;

template <typename T, typename T_>
using DecaySame = std::is_same<std::decay_t<T>, std::decay_t<T_>>;

template <typename T, typename T_>
constexpr inline bool DecaySameV = DecaySame<T, T_>::value;
} // namespace mp

#include "Make.hpp"
#include "ForEach.hpp"
#include "Transform.hpp"
#include "FindIf.hpp"
#include "TypeName.hpp"
#include "IntegerSeq.hpp"

#include "BackWardImpl.hpp"

#endif // COMMON_HPP
