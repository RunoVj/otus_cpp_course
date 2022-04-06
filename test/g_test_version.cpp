#include <gtest/gtest.h> // googletest header file
#include "lib.h"

TEST(TestVersion, CStrEqual) {
    EXPECT_TRUE(version() > 0);
}