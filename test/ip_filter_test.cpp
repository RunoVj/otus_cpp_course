#include <gtest/gtest.h>
#include "ip_filter.h"


TEST(TestHelpFunction, parse4byte_ip_from_str)
{
    std::array ar{192, 168, 2, 3};
    EXPECT_EQ(parse4byte_ip_from_str(std::string("192.168.2.3")), ar);
}


TEST(TestHelpFunction, pattern_matches)
{
    std::array ip{192, 168, 2, 3};
    EXPECT_TRUE(pattern_matches(0, ip, 192));
    EXPECT_TRUE(pattern_matches(0, ip, 192, 168));
    EXPECT_TRUE(pattern_matches(0, ip, 192, 168, 2));
    EXPECT_FALSE(pattern_matches(0, ip, 192, 192, 2));
    EXPECT_FALSE(pattern_matches(0, ip, 2));
    EXPECT_FALSE(pattern_matches(0, ip, 192, 168, 0));
}


TEST(TestIpFilter, happy_tests)
{
    std::istringstream in_s{"113.162.145.156\t111\t0\n"
                            "157.46.22.1\t5\t6\n"
                            "79.46.70.190\t2\t1\n"
                            "179.210.145.4\t22\t0\n"
                            "219.102.120.135\t486\t0"};
    auto expectation_s = "219.102.120.135\n"
                         "179.210.145.4\n"
                         "157.46.22.1\n"
                         "113.162.145.156\n"
                         "79.46.70.190\n"
                         "157.46.22.1\n"
                         "79.46.70.190\n";
    std::stringstream out_s;
    parse_ip(in_s, out_s);
    EXPECT_EQ(expectation_s, out_s.str());
}


TEST(TestIpFilter, test_exception)
{
    std::istringstream in_s{"113.162.145.156\t111\t0\n"
                            "157.46.22\t5\t6\n"
                            "79.46.70.190\t2\t1\n"
                            "179.210.145.4\t22\t0\n"
                            "219.102.120.135\t486\t0"};
    EXPECT_THROW({
                     try {
                         parse_ip(in_s);
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Wrong ip input: 157.46.22", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}
