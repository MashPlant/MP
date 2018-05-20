#if !defined(TRANSFORM_HPP)
#define TRANSFORM_HPP

#include "Common.hpp"

namespace mp
{
namespace detail
{
template <typename Tag>
struct TransformImpl;

struct TransformT
{
    template <typename Seq, typename F>
    constexpr auto operator()(Seq &&seq, F &&f) const
    {
        return TransformImpl<TagOf<Seq>>{}(static_cast<Seq &&>(seq), static_cast<F &&>(f));
    }
};
} // namespace detail
constexpr detail::TransformT transform;
} // namespace mp

#endif // TRANSFORM_HPP
