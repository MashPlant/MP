#if !defined(FILTER_HPP)
#define FILTER_HPP

#include "Common.hpp"

namespace mp
{
namespace detail
{
template <typename Tag>
struct FilterImpl;

struct FilterT
{
    template <typename Seq, typename F>
    constexpr auto operator()(Seq &&seq, F &&f) const
    {
        return FilterImpl<TagOf<Seq>>(static_cast<Seq &&>(seq), static_cast<F &&>(f));
    }
};
} // namespace detail
constexpr detail::FilterT filter;
} // namespace mp

#endif // FILTER_HPP
