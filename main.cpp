#include "IntegerT.hpp"
#include "Range.hpp"
#include "Tuple.hpp"
#include "Common.hpp"
#include "String.hpp"
#include "Struct.hpp"
#include "TypeName.hpp"

#include <iostream>

using namespace mp;
using namespace mp::literals;

struct A
{
    int a;
    float b;
    struct Accessor
    {
        constexpr static auto get()
        {
            return mp::make<TupleTag>(mp::make<TupleTag>(StaticStr("a"), mp::detail::MemberGetter<&A::a>{}),
                                      mp::make<TupleTag>(StaticStr("b"), mp::detail::MemberGetter<&A::b>{}));
        }
    };
};

int main()
{
    A a{-42, 42.5f};
    forEach(memberTuple(a), [](auto &x) { std::cout << (x += 1) << '\n'; });
    std::cout << a.a << ' ' << a.b << '\n';
}
