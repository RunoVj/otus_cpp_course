#include <gtest/gtest.h> // googletest header file
#include "ip_filter.h"


TEST(TestHelpFunction, parse4byte_ip_from_str) {
    std::array ar{192, 168, 2, 3};
    EXPECT_EQ(parse4byte_ip_from_str(std::string("192.168.2.3")), ar);
}


TEST(TestHelpFunction, pattern_matches) {
    std::array ip{192, 168, 2, 3};
    EXPECT_TRUE(pattern_matches(0, ip, 192));
    EXPECT_TRUE(pattern_matches(0, ip, 192, 168));
    EXPECT_TRUE(pattern_matches(0, ip, 192, 168, 2));
    EXPECT_FALSE(pattern_matches(0, ip, 192, 192, 2));
    EXPECT_FALSE(pattern_matches(0, ip, 2));
    EXPECT_FALSE(pattern_matches(0, ip, 192, 168, 0));
}