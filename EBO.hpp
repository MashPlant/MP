#if !defined(EBO_HPP)
#define EBO_HPP

#include "Common.hpp"

namespace mp
{
template <typename K, typename V, bool = std::is_empty_v<V>>
struct EBO
{
    V value;
    template <typename V_>
    constexpr EBO(V_ &&value) : value(static_cast<V_ &&>(value))
    {
    }
    constexpr EBO() = default;
};

template <typename K, typename V>
struct EBO<K, V, true> : V
{
    template <typename V_>
    constexpr EBO(V_ &&value) : V(static_cast<V_ &&>(value))
    {
    }
    constexpr EBO() = default;
};

template <typename K, typename V, bool Empty>
constexpr decltype(auto) EBOGet(EBO<K, V, Empty> &&ebo)
{
    if constexpr (Empty)
        return static_cast<V &&>(ebo);
    else
        return static_cast<V &&>(ebo.value);
}
template <typename K, typename V, bool Empty>
constexpr decltype(auto) EBOGet(EBO<K, V, Empty> &ebo)
{
    if constexpr (Empty)
        return static_cast<V &>(ebo);
    else
        return (ebo.value);
}
template <typename K, typename V, bool Empty>
constexpr decltype(auto) EBOGet(const EBO<K, V, Empty> &ebo)
{
    if constexpr (Empty)
        return static_cast<const V &>(ebo);
    else
        return (ebo.value);
}
} // namespace mp

#endif // EBO_HPP
