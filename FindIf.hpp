#if !defined(FIND_HPP)
#define FIND_HPP

#include "Common.hpp"

namespace mp
{
namespace detail
{
template <typename Tag>
struct FindIfImpl;
struct FindIfT
{
    template <typename Seq, typename F>
    constexpr auto operator()(Seq &&seq, F &&f) const
    {
        return FindIfImpl<TagOf<Seq>>{}(static_cast<Seq &&>(seq), static_cast<F &&>(f));
    }
};
} // namespace detail
constexpr detail::FindIfT findIf;
} // namespace mp

#endif // FIND_HPP
