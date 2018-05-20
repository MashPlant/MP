#include "IntegerT.hpp"
#include "Range.hpp"
#include "Tuple.hpp"
#include "Common.hpp"

#include <iostream>
#include <ctime>

using namespace mp;
using namespace mp::literals;

int main()
{
    auto t = mp::make<TupleTag>(1, 2, 3_t, 3.1415926, "1234567");
    forEach(t, [](auto x) { std::cout << x << '\n'; });
}
