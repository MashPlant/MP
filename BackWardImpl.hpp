#if !defined(INTEGERSEQIMPL_HPP)
#define INTEGERSEQIMPL_HPP

#include "Common.hpp"
#include "IntegerSeq.hpp"
#include "Tuple.hpp"

// instead of forward declaration, I use backward implemention

namespace mp::detail
{
template <>
struct TransformImpl<IntegerSeqTag>
{
    template <typename Int, typename F, Int... Ints>
    constexpr auto operator()(IntegerSeq<Int, Ints...>, F &&f) const
    {
        using RetType = Tuple<decltype(static_cast<F &&>(f)(IntegerT<Int, Ints>{}))...>;
        return RetType{static_cast<F &&>(f)(IntegerT<Int, Ints>{})...};
    }
};

template <typename Int, Int... Ints>
struct TypeNameImpl<IntegerSeq<Int, Ints...>>
{
    // C++17 folding expression
    constexpr static auto name = "IntegerSeq<"_str + TypeName<Int>::name +
                                 (... + (", "_str + parseInt<Ints>())) + ">"_str;
};
template <>
struct FindIfImpl<IntegerSeqTag>
{
    template <typename Int, typename F, Int... Ints>
    constexpr auto operator()(IntegerSeq<Int, Ints...> seq, F &&f) const
    {
        return work<0>(seq, static_cast<F &&>(f));
    }
    template <int Cur, typename Int, typename F, Int... Ints>
    constexpr auto work(IntegerSeq<Int, Ints...> seq, F &&f) const
    {
        if constexpr (Cur == sizeof...(Ints))
            return IntT<-1>{};
        else if constexpr (ValueOf<decltype(static_cast<F &&>(f)(seq[IntT<Cur>{}]))>)
            return IntT<Cur>{};
        else
            return work<Cur + 1>(seq, static_cast<F &&>(f));
    }
};
} // namespace mp::detail

#endif // INTEGERSEQIMPL_HPP
