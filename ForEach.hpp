#if !defined(FOREACH_HPP)
#define FOREACH_HPP

#include "Common.hpp"

namespace mp
{
namespace detail
{
template <typename Tag>
struct ForEachImpl;

struct ForEachT
{
    template <typename Seq, typename F>
    constexpr void operator()(Seq &&seq, F &&f) const
    {
        ForEachImpl<TagOf<Seq>>{}(static_cast<Seq &&>(seq), static_cast<F &&>(f));
    }
};
} // namespace detail
constexpr detail::ForEachT forEach;
} // namespace mp

#endif // FOREACH_HPP
