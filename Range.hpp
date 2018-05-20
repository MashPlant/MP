#if !defined(RANGE_HPP)
#define RANGE_HPP

#include "Common.hpp"
#include "IntegerT.hpp"

namespace mp
{
template <typename Int, Int Begin, Int End>
struct Range
{
    static_assert(Begin <= End);
    constexpr static Int begin = Begin;
    constexpr static Int end = End;
    using MPTag = RangeTag;
};

namespace detail
{
template <>
struct MakeImpl<RangeTag>
{
    template <typename Int, Int Begin, Int End>
    constexpr auto operator()(IntegerT<Int, Begin>, IntegerT<Int, End>) const
    {
        return Range<Int, Begin, End>{};
    }
};

template <>
struct ForEachImpl<RangeTag>
{
    template <typename Int, Int Begin, typename F, Int... Values>
    constexpr void work(std::integer_sequence<Int, Values...>, F &&f) const
    {
        using Dummy = int[];
        static_cast<void>(Dummy{0, (static_cast<F &&>(f)(IntegerT<Int, Begin + Values>{}), 0)...});
    }

    template <typename Int, Int Begin, Int End, typename F>
    constexpr void operator()(Range<Int, Begin, End>, F &&f) const
    {
        work<Int, Begin>(std::make_integer_sequence<Int, End - Begin>(),
                         static_cast<F &&>(f));
    }
};
} // namespace detail
} //namespace mp

#endif // RANGE_HPP