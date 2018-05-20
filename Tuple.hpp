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
struct TupleImpl<std::integer_sequence<int, Indices...>, Types...>
    : EBO<IntT<Indices>, Types>...
{
    using MPTag = TupleTag;
    constexpr static int size = sizeof...(Types);

    template <int Index>
    constexpr decltype(auto) operator[](IntT<Index>)
    {
        return EBOGet<IntT<Index>>(*this);
    }
    template <int Index>
    constexpr decltype(auto) operator[](IntT<Index>) const
    {
        return EBOGet<IntT<Index>>(*this);
    }
};
} // namespace detail

template <typename... Types>
using Tuple = detail::TupleImpl<decltype(std::make_integer_sequence<int, sizeof...(Types)>()),
                                Types...>;
namespace detail
{
template <>
struct MakeImpl<TupleTag>
{
    template <typename... Types>
    constexpr auto operator()(Types &&... values) const
    {
        return Tuple<std::decay_t<Types>...>{static_cast<Types>(values)...};
    }
};
template <>
struct ForEachImpl<TupleTag>
{
    template <typename Tp, typename F, int... Indices>
    constexpr void work(Tp &&tuple, F &&f, std::integer_sequence<int, Indices...>) const
    {
        using Dummy = int[];
        static_cast<void>(Dummy{0, (static_cast<F &&>(f)(tuple[IntT<Indices>{}]), 0)...});
    }

    template <typename... Types, typename F>
    constexpr void operator()(Tuple<Types...> &tuple, F &&f)
    {
        work(tuple, static_cast<F &&>(f),
             std::make_integer_sequence<int, sizeof...(Types)>());
    }
};
} // namespace detail
} // namespace mp

#endif // TUPLE_HPP
