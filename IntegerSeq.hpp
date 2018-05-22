#if !defined(INTEGERSEQ_HPP)
#define INTEGERSEQ_HPP

#include "Common.hpp"
#include "IntegerT.hpp"

namespace mp
{
template <typename Int, Int... Ints>
struct IntegerSeq
{
    using MPTag = IntegerSeqTag;
    constexpr static int size = sizeof...(Ints);
    template <int Index>
    constexpr auto operator[](IntT<Index>) const
    {
        static_assert(Index >= 0 && Index < size);
        constexpr Int array[] = {Ints..., 0};
        return IntegerT<Int, array[Index]>{};
    }
    template <Int... Ints_>
    constexpr auto operator+(IntegerSeq<Int, Ints_...>) const
    {
        return IntegerSeq<Int, Ints..., Ints_...>{};
    }
    template <Int N>
    constexpr auto operator+(IntegerT<Int, N>) const
    {
        return IntegerSeq<Int, Ints..., N>{};
    }

    template <typename Int_, Int_... Ints_>
    constexpr auto operator==(IntegerSeq<Int_, Ints_...>) const
    {
        return False{};
    }

    constexpr auto operator==(IntegerSeq<Int, Ints...>) const
    {
        return True{};
    }
};

template <typename Int, Int N, Int... Ints>
constexpr auto operator+(IntegerT<Int, N>, IntegerSeq<Int, Ints...>)
{
    return IntegerSeq<Int, N, Ints...>{};
}

template <typename OS, typename Int, Int... Ints>
constexpr decltype(auto) operator<<(OS &&os, IntegerSeq<Int, Ints...>)
{
    if constexpr (sizeof...(Ints) != 0)
    {
        Int array[] = {Ints...};
        for (auto i : array)
            os << i << ' ';
    }
    return static_cast<OS &&>(os);
}

template <int... Ints>
using IntSeq = IntegerSeq<int, Ints...>;
template <char... Chars>
using CharSeq = IntegerSeq<char, Chars...>;

template <typename OS, char... Chars>
constexpr decltype(auto) operator<<(OS &&os, CharSeq<Chars...>)
{
    if constexpr (sizeof...(Chars) != 0)
    {
        char array[] = {Chars...};
        for (auto i : array)
            os << i;
    }
    return static_cast<OS &&>(os);
}
namespace detail
{
template <>
struct MakeImpl<IntegerSeqTag>
{
    template <typename Int, Int Cur, Int End>
    constexpr auto work() const
    {
        if constexpr (Cur == End)
            return IntegerSeq<Int>{};
        else
            return IntegerT<Int, Cur>{} + work<Int, Cur + 1, End>();
    }
    template <typename Int, Int Begin, Int End>
    constexpr auto operator()(IntegerT<Int, Begin>, IntegerT<Int, End>) const
    {
        return work<Int, Begin, End>();
    }
    template <typename Int, Int End>
    constexpr auto operator()(IntegerT<Int, End>) const
    {
        return work<Int, static_cast<Int>(0), End>();
    }
};
template <>
struct ForEachImpl<IntegerSeqTag>
{
    template <typename Int, typename F, Int... Ints>
    constexpr void operator()(IntegerSeq<Int, Ints...>, F &&f) const
    {
        using Dummy = int[];
        static_cast<void>(Dummy{0, (static_cast<F &&>(f)(IntegerT<Int, Ints>{}), 0)...});
    }
};
} // namespace detail
} // namespace mp

#endif // INTEGERSEQ_HPP
