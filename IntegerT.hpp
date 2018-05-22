#if !defined(INTEGERT_HPP)
#define INTEGERT_HPP

#include "Common.hpp"

namespace mp
{
template <typename Int, Int Value>
struct IntegerT
{
    constexpr static Int value = Value;

    using MPTag = IntegerTag;

    template <Int Value_>
    constexpr auto operator+(IntegerT<Int, Value_>) const
    {
        return IntegerT<Int, Value + Value_>{};
    }

    template <Int Value_>
    constexpr auto operator-(IntegerT<Int, Value_>) const
    {
        return IntegerT<Int, Value - Value_>{};
    }

    constexpr auto operator-() const
    {
        return IntegerT<Int, -Value>{};
    }

    template <Int Value_>
    constexpr auto operator*(IntegerT<Int, Value_>)const
    {
        return IntegerT<Int, Value * Value_>{};
    }

    template <Int Value_>
    constexpr auto operator/(IntegerT<Int, Value_>) const
    {
        static_assert(Value_ != 0);
        return IntegerT<Int, Value / Value_>{};
    }

    template <typename OS>
    friend constexpr decltype(auto) operator<<(OS &&os, IntegerT<Int, Value>)
    {
        return os << Value;
    }
};

template <bool Value>
using BoolT = IntegerT<bool, Value>;
using True = BoolT<true>;
using False = BoolT<false>;

template <int Value>
using IntT = IntegerT<int, Value>;

template <typename Int, Int Value, Int Value_>
constexpr auto operator==(IntegerT<Int, Value>, IntegerT<Int, Value_>)
{
    return BoolT<(Value == Value_)>{};
}

template <typename Int, Int Value, Int Value_>
constexpr auto operator!=(IntegerT<Int, Value>, IntegerT<Int, Value_>)
{
    return BoolT<(Value != Value_)>{};
}

template <typename Int, Int Value, Int Value_>
constexpr auto operator<(IntegerT<Int, Value>, IntegerT<Int, Value_>)
{
    return BoolT<(Value < Value_)>{};
}

template <typename Int, Int Value, Int Value_>
constexpr auto operator<=(IntegerT<Int, Value>, IntegerT<Int, Value_>)
{
    return BoolT<(Value <= Value_)>{};
}

template <typename Int, Int Value, Int Value_>
constexpr auto operator>(IntegerT<Int, Value>, IntegerT<Int, Value_>)
{
    return BoolT<(Value > Value_)>{};
}

template <typename Int, Int Value, Int Value_>
constexpr auto operator>=(IntegerT<Int, Value>, IntegerT<Int, Value_>)
{
    return BoolT<(Value >= Value_)>{};
}

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

#endif // INTEGERT_HPP
