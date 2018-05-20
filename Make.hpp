#if !defined(MAKE_HPP)
#define MAKE_HPP

#include "Common.hpp"

namespace mp
{
namespace detail
{
template <typename>
struct MakeImpl;

template <typename Tag>
struct MakeT
{
    template <typename... Args>
    constexpr auto operator()(Args &&... args) const
    {
        return MakeImpl<Tag>{}(static_cast<Args &&>(args)...);
    }
};
} // namespace detail

template <typename Tag>
constexpr detail::MakeT<Tag> make;
} // namespace mp

#endif // MAKE_HPP
