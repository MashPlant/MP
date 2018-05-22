#include <iostream>
#include <string>

#include "Struct.hpp"
#include "IsValid.hpp"

using namespace mp;
using namespace mp::literals;

struct Person
{
    DefineStruct(Person, (int, age), (std::string, name))
};

int main()
{
    Person lch{18, "MashPlant"};
    auto s = mp::Struct<Person>(lch);
    s.dynApply("name", [](auto &x) -> decltype(++x) { return ++x; });
    std::cout << lch.age << ' ' << lch.name;
}