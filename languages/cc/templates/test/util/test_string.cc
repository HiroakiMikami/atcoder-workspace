#define MAIN

#include <gtest/gtest.h>
#include "common.cc"
#include "util/string.cc"

using namespace string_utils;

TEST(StringTest, ToTest) {
    auto i = to<i32>("10");
    EXPECT_EQ(10, i);

    auto j = to<i32>("-10");
    EXPECT_EQ(-10L, j);
}

TEST(StringTest, SplitTest) {
    EXPECT_EQ(Vector<string>({"10", "1"}), split("10,1", ","));

    EXPECT_EQ(Vector<string>({"10", "1", ""}), split("10,1,", ","));
}