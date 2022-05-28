#include <gtest/gtest.h>
#include "allocator.h"
#include "factorial.h"


TEST(TestMyAllocator, map_insert)
{
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 10>> custom_allocator_map;

    for (int i = 0; i < 10; ++i) {
        custom_allocator_map.insert(std::pair<int, int>(i, factorial(i)));
    }

    for(const auto& elem : custom_allocator_map) {
        EXPECT_EQ(factorial(elem.first), elem.second);
    }
    std::cout << std::endl;
}

