#include "gtest/gtest.h"
#include "fixtures.h"
#include "string_resolver.h"
using namespace depo::core;

TEST(StringResolver, undercoreCase) {
    Env::set("FOO", "VALUE_FOO");
    std::string_view string{"$FOO_TAIL_STRING"};
    EXPECT_EQ(StringResolver::unwrapVars(string), "");
    std::string_view string2{"SOME_$FOO_TAIL_STRING"};
    EXPECT_EQ(StringResolver::unwrapVars(string2), "SOME_");
    std::string_view string3{"${FOO}_RIGHT_USING"};
    EXPECT_EQ(StringResolver::unwrapVars(string3), "VALUE_FOO_RIGHT_USING");
}

TEST_F(EnvFixture, tail) {
    std::string_view path{"/head/${DEPO_VAR_ONE}/some/dir/$DEPO_VAR_TWO/tail"};
    EXPECT_EQ(StringResolver::unwrapVars(path), "/head/DEPO_VALUE_1/some/dir/DEPO_VALUE_2/tail");
}

TEST_F(EnvFixture, head) {
    std::string_view path{"/head/${DEPO_VAR_ONE}/some/dir/$DEPO_VAR_TWO"};
    EXPECT_EQ(StringResolver::unwrapVars(path), "/head/DEPO_VALUE_1/some/dir/DEPO_VALUE_2");
}

TEST_F(EnvFixture, curlyBrace) {
    std::string_view path{"${DEPO_VAR_ONE}/some/dir/${DEPO_VAR_TWO}"};
    EXPECT_EQ(StringResolver::unwrapVars(path), "DEPO_VALUE_1/some/dir/DEPO_VALUE_2");
}

TEST(StringResolver, guardRecursion) {
    Env::set("FOO", "$BAR");
    Env::set("BAR", "$FOO");
    EXPECT_EQ(StringResolver::unwrapVars("/some/path/$FOO/subdir"), "/some/path/$BAR/subdir");
}

TEST_F(EnvFixture, simple) {
    std::string a{StringResolver::unwrapVars("$DEPO_VAR_ONE")};
    EXPECT_EQ(a, "DEPO_VALUE_1");
}

TEST(StringResolver, empty) {
    EXPECT_EQ(StringResolver::unwrapVars(""), "");
}