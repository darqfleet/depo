#include <gtest/gtest.h>
#include "util.h"
using namespace depo::util;

TEST(isRegexMatch, Literals) {
    EXPECT_EQ(isRegexMatch("SOMETEXT", R"([A-Z]+)"), true);
    EXPECT_EQ(isRegexMatch("SOMETEXT1", R"([A-Z]+)"), false);
    std::string str{"someTextAndDigits456"};
    EXPECT_EQ(isRegexMatch(str, R"([A-Za-z0-9]+)"), true);
    str+="@#$%";
    EXPECT_EQ(isRegexMatch(str, R"([A-Za-z0-9]+)"), false);
}

TEST(isRegexMatch, Regex) {
    std::regex rgx{R"([A-Z]+)"};
    EXPECT_EQ(isRegexMatch("QWERTY", rgx), true);
    EXPECT_EQ(isRegexMatch("QWERTY1", rgx), false);
}