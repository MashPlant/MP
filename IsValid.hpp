#if !defined(ISVALID_HPP)
#define ISVALID_HPP

#include "Common.hpp"
#include "IntegerT.hpp"

namespace mp
{
namespace detail
{
struct IsValidT
{
    template <typename F, typename... Args,
              typename = decltype(std::declval<F>()(std::declval<Args>()...))>
    static constexpr auto impl(int) { return True{}; }

    template <typename F, typename... Args>
    static constexpr auto impl(float) { return False{}; }

    template <typename F>
    struct ValidChecker
    {
        template <typename... Args>
        constexpr auto operator()(Args &&... args) { return impl<F, Args...>(0); }
    };

    template <typename F>
    constexpr auto operator()(F &&) const { return ValidChecker<F>{}; }
};
} // namespace detail
constexpr detail::IsValidT isValid;
} // namespace mp

#endif // ISVALID_HPP
