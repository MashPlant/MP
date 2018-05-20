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

} // namespace mp

#include "AtoI.hpp"

#endif // INTEGERT_HPP
