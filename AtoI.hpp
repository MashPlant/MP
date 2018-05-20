#if !defined(ATOI_HPP)
#define ATOI_HPP

#include "IntegerT.hpp"

namespace mp
{
namespace detail
{
template <int N>
constexpr int parse(const char (&arr)[N])
{
    int cur = 0, sgn = 1, ret = 0;
    if (arr[0] == '-')
        sgn = -1, cur = 1;
    for (; cur < N; ++cur)
        ret = ret * 10 + (arr[cur] - '0');
    return ret * sgn;
}
} // namespace detail

namespace literals
{
template <char... Chars>
constexpr auto operator"" _t()
{
    return IntT<detail::parse<sizeof...(Chars)>({Chars...})>{};
}
} // namespace literals
} // namespace mp

#endif // ATOI_HPP
