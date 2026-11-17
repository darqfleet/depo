#include <gtest/gtest.h>
#include <sstream>
#include "env.h"
#include "fixtures.h"
using namespace depo::core;

TEST(Env, pipeline) {
    Env::set("DEPO", "/mnt/depo");
    std::string_view depo{Env::get("DEPO")};
    EXPECT_EQ(depo, "/mnt/depo");
    Env::set("DEPO", "/home/depo");
    std::string_view depo2{Env::get("DEPO")};
    EXPECT_EQ(depo, "/mnt/depo");
    EXPECT_EQ(depo2, "/home/depo");
}

TEST_F(EnvFixture, checkVars) {
    EXPECT_EQ(Env::get("DEPO_VAR_ONE"), "DEPO_VALUE_1");
    EXPECT_EQ(Env::get("DEPO_VAR_TWO"), "DEPO_VALUE_2");
    EXPECT_EQ(Env::get("DEPO_VAR_THREE"), "DEPO_VALUE_3");
}


TEST_F(EnvFixture, overrideVars) {
    EXPECT_EQ(Env::get("DEPO_VAR_ONE"), "DEPO_VALUE_1");
    std::string override_var{"DEPO_VALUE_OVERRIDDEN"};
    Env::set("DEPO_VAR_ONE", override_var);
    ASSERT_EQ(Env::get("DEPO_VAR_ONE"), override_var);
}


TEST_F(EnvFixture, unsettingVasr) {
    Env::unset("DEPO_VAR_ONE");
    Env::unset("DEPO_VAR_TWO");
    Env::unset("DEPO_VAR_THREE");
    ASSERT_EQ(Env::get("DEPO_VAR_ONE"), "");
    ASSERT_EQ(Env::get("DEPO_VAR_TWO"), "");
    ASSERT_EQ(Env::get("DEPO_VAR_THREE"), "");
}

TEST(Env, getUnsettedVariable) {
    std::string emptyVar{Env::get("SomeVar")};
    EXPECT_EQ(emptyVar, "");
}

TEST(Env, setAndGetVar) {
    std::string s{"EXTRA_VAR"};
    std::string_view s2{"EXTRA_VAR"};
    Env::set("EXTRA_VAR", "EXTRA_VALUE");
    std::string extVar{Env::get("EXTRA_VAR")};
    EXPECT_EQ(extVar, "EXTRA_VALUE");
    std::string extVar2{Env::get(s)};
    EXPECT_EQ(extVar2, "EXTRA_VALUE");
    std::string extVar3{Env::get(s2)};
    EXPECT_EQ(extVar3, "EXTRA_VALUE");
}

TEST(Env, unsetVar) {
    Env::set("EXTRA_VAR", "EXTRA_VALUE");
    std::string extVar{Env::get("EXTRA_VAR")};
    EXPECT_EQ(extVar, "EXTRA_VALUE");
    Env::unset("EXTRA_VAR");
    extVar = Env::get("EXTRA_VAR");
    EXPECT_EQ(extVar, "");
    Env::unset("NotExistingVar");

}

TEST(Env, setWrongName) {
    std::string_view name{"1FGH"};
    std::stringstream message;
    message << "Variable name must be match by [A-Z_]+ pattern. Name has illegal chars: " << name;

    EXPECT_THROW(Env::set(name, "value"), std::runtime_error);
    try {
        Env::set(name, "12value");
    } catch (std::runtime_error &err) {
        EXPECT_STREQ(message.str().c_str(), err.what());
    }
}

TEST(Env, setEmptyArgs) {
    std::string_view arg1{};
    std::string_view arg2{"SOMEVALUE"};

    EXPECT_THROW(Env::set(arg1, arg2), std::runtime_error);
    try {
        Env::set(arg1, arg2);
    }catch (std::exception& err) {
        std::stringstream message;
        message << "name or value cannot be empty. ";
        message << " name: " << "<empty> value: " << arg2;
        EXPECT_STREQ(message.str().c_str(), err.what());
    }
    try {
        Env::set(arg2, arg1);
    }catch (std::exception& err) {
        std::stringstream message;
        message << "name or value cannot be empty. ";
        message << " name: " << arg2 << " value: " << "<empty>";
        EXPECT_STREQ(message.str().c_str(), err.what());
    }
    try {
        Env::set(arg1, arg1);
    }catch (std::exception& err) {
        std::stringstream message;
        message << "name or value cannot be empty. ";
        message << " name: <empty> value: <empty>";
        EXPECT_STREQ(message.str().c_str(), err.what());
    }
}

TEST(Env, setVar) {
    Env::set("MYVAR", "MYVALUE");
    EXPECT_STREQ(getenv("MYVAR"), "MYVALUE");
}
