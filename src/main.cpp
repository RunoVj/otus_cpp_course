#include <fmt/core.h>
#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <iostream>
#include <string>
#include <string_view>

//#include <type_traits>

#include "template_traits_experiments.h"

#define SHOW(...) \
    std::cout << #__VA_ARGS__ << " : " \
              << std:: __VA_ARGS__ << '\n'


struct A {};

class B {};

enum class E {};

union U { class UC {}; };
static_assert(not std::is_class_v<U>);
static_assert(std::is_class_v<U::UC>);


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    int i = factorial<4>::value;

//    bool i = is_int_v<int>;
    fmt::print("Factorial = {}\n", i);

//    remove_const<int>::type a1;
    remove_const_t<const int> a2;

    fmt::print("decltype(nullptr): {}\nint*: {}",
               std::is_null_pointer<decltype(nullptr)>::value,
               std::is_null_pointer<int*>::value);
}