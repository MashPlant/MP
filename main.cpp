#include <iostream>
#include <string>

#include "Struct.hpp"

struct Person
{
    DefineStruct(Person, (int, age), (std::string, name))
};

int main()
{
    Person lch{18, "MashPlant"};
    mp::forEach(mp::members(lch), [](auto &x) { std::cout << x << '\n'; });
}