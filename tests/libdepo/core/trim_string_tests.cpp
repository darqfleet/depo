#include "depo.h"
#include <gtest/gtest.h>
using namespace depo::core;

TEST(TrimString, trimRight) {
    ASSERT_EQ(TrimString::trim("!@#$%^&keep only text!@#$%^&", "&!#$%@^", TrimDir::RIGHT), "!@#$%^&keep only text");
    ASSERT_EQ(TrimString::trim("keep only text!@#$%^&", "&!#$%@^", TrimDir::RIGHT), "keep only text");
    std::string case_1{TrimString::trim("/no/slash/on/end/", "/", TrimDir::RIGHT)};
    ASSERT_EQ(case_1, "/no/slash/on/end");
    std::string case_2{TrimString::trim("////////no/slash/on/end////", "/", TrimDir::RIGHT)};
    ASSERT_EQ(case_2, "////////no/slash/on/end");
}

TEST(TrimString, trimLeft) {
    ASSERT_EQ(TrimString::trim("!@#$%^&keep only text!@#$%^&", "&!#$%@^", TrimDir::LEFT), "keep only text!@#$%^&");
    ASSERT_EQ(TrimString::trim("!@#$%^&keep only text", "&!#$%@^", TrimDir::LEFT), "keep only text");
    std::string case_1{TrimString::trim("/no/slash/on/start/", "/", TrimDir::LEFT)};
    ASSERT_EQ(case_1, "no/slash/on/start/");
    std::string case_2{TrimString::trim("////////no/slash/on/start/", "/", TrimDir::LEFT)};
    ASSERT_EQ(case_2, "no/slash/on/start/");
}

TEST(TrimString, trimByDefault) {
    EXPECT_EQ(TrimString::trim("  space  "), "space");
    EXPECT_EQ(TrimString::trim("\nnew line\n  "), "new line");
    EXPECT_EQ(TrimString::trim("\ttabula\ttion\t  "), "tabula\ttion");
}
