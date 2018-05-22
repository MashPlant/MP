#if !defined(TUPLE_HPP)
#define TUPLE_HPP

#include "Common.hpp"
#include "EBO.hpp"
#include "IntegerT.hpp"

namespace mp
{
namespace detail
{
template <typename, typename...>
struct TupleImpl;

template <int... Indices, typename... Types>
struct TupleImpl<IntSeq<Indices...>, Types...>
    : EBO<IntT<Indices>, Types>...
{
};
} // namespace detail

template <typename... Types>
struct Tuple
{
    using ImplType = detail::TupleImpl<decltype(make<IntegerSeqTag>(IntT<sizeof...(Types)>{})), Types...>;
    using MPTag = TupleTag;
    constexpr static int size = sizeof...(Types);
    ImplType storage;

    template <int Index>
    constexpr decltype(auto) operator[](IntT<Index>)
    {
        return EBOGet<IntT<Index>>(storage);
    }
    template <int Index>
    constexpr decltype(auto) operator[](IntT<Index>) const
    {
        return EBOGet<IntT<Index>>(storage);
    }
};

template <>
struct Tuple<>
{
    using MPTag = TupleTag;
    constexpr static int size = 0;
};

namespace detail
{
template <>
struct MakeImpl<TupleTag>
{
    template <typename... Types>
    constexpr auto operator()(Types &&... values) const
    {
        return Tuple<std::decay_t<Types>...>{static_cast<Types &&>(values)...};
    }
};
template <>
struct ForEachImpl<TupleTag>
{
    template <typename Tp, typename F, int... Indices>
    constexpr void work(Tp &&tuple, F &&f, IntSeq<Indices...>) const
    {
        using Dummy = int[];
        static_cast<void>(Dummy{0, (static_cast<F &&>(f)(static_cast<Tp &&>(tuple)[IntT<Indices>{}]), 0)...});
    }

    template <typename... Types, typename F>
    constexpr void operator()(Tuple<Types...> &&tuple, F &&f) const
    {
        work(static_cast<Tuple<Types...> &&>(tuple), static_cast<F &&>(f),
             make<IntegerSeqTag>(IntT<sizeof...(Types)>{}));
    }

    template <typename... Types, typename F>
    constexpr void operator()(Tuple<Types...> &tuple, F &&f) const
    {
        work(tuple, static_cast<F &&>(f),
             make<IntegerSeqTag>(IntT<sizeof...(Types)>{}));
    }

    template <typename... Types, typename F>
    constexpr void operator()(const Tuple<Types...> &tuple, F &&f) const
    {
        work(tuple, static_cast<F &&>(f),
             make<IntegerSeqTag>(IntT<sizeof...(Types)>{}));
    }
};
template <>
struct TransformImpl<TupleTag>
{
    template <typename Tp, typename F, int... Indices>
    constexpr auto work(Tp &&tuple, F &&f, IntSeq<Indices...>) const
    {
        using RetType = Tuple<decltype(static_cast<F &&>(f)(static_cast<Tp &&>(tuple)[IntT<Indices>{}]))...>;
        return RetType{static_cast<F &&>(f)(static_cast<Tp &&>(tuple)[IntT<Indices>{}])...};
    }
    template <typename... Types, typename F>
    constexpr auto operator()(Tuple<Types...> &&tuple, F &&f) const
    {
        return work(static_cast<Tuple<Types...> &&>(tuple), static_cast<F &&>(f),
                    make<IntegerSeqTag>(IntT<sizeof...(Types)>{}));
    }
    template <typename... Types, typename F>
    constexpr auto operator()(Tuple<Types...> &tuple, F &&f) const
    {
        return work(tuple, static_cast<F &&>(f),
                    make<IntegerSeqTag>(IntT<sizeof...(Types)>{}));
    }
    template <typename... Types, typename F>
    constexpr auto operator()(const Tuple<Types...> &tuple, F &&f) const
    {
        return work(tuple, static_cast<F &&>(f),
                    make<IntegerSeqTag>(IntT<sizeof...(Types)>{}));
    }
};
template <typename... Types>
struct TypeNameImpl<Tuple<Types...>>
{
    constexpr static auto name = "Tuple<"_str + TypeNames<Types...>::name + ">"_str;
};
template <>
struct FindIfImpl<TupleTag>
{
    template <int Cur, typename... Types, typename F>
    constexpr auto work(const Tuple<Types...> &tuple, F &&f) const
    {
        if constexpr (Cur == sizeof...(Types))
            return -1_t;
        else if constexpr (ValueOf<decltype(static_cast<F &&>(f)(tuple[IntT<Cur>{}]))>)
            return IntT<Cur>{};
        else
            return work<Cur + 1>(tuple, static_cast<F &&>(f));
    }
    template <typename... Types, typename F>
    constexpr auto operator()(const Tuple<Types...> &tuple, F &&f) const
    {
        return work<0>(tuple, static_cast<F &&>(f));
    }
};
} // namespace detail
} // namespace mp

#endif // TUPLE_HPP
