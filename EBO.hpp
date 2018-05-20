#if !defined(EBO_HPP)
#define EBO_HPP

#include "Common.hpp"

namespace mp
{
template <typename K, typename V, bool = std::is_empty_v<V>>
struct EBO
{
    V value;
    constexpr EBO(const V &value) : value(value)
    {
    }
    constexpr EBO(V &&value) : value(static_cast<V &&>(value))
    {
    }
};

template <typename K, typename V>
struct EBO<K, V, true>
{
    constexpr EBO(const V &)
    {
    }
};

template <typename K, typename V, bool Empty>
constexpr decltype(auto) EBOGet(EBO<K, V, Empty> &&ebo)
{
    if constexpr (Empty)
        return V{};
    else
        return (ebo.value);
}

template <typename K, typename V, bool Empty>
constexpr decltype(auto) EBOGet(EBO<K, V, Empty> &ebo)
{
    if constexpr (Empty)
        return V{};
    else
        return (ebo.value);
}
} // namespace mp

#endif // EBO_HPP
