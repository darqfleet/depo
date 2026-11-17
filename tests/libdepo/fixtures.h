#pragma once
#include <gtest/gtest.h>
#include "env.h"
using namespace depo::core;

struct EnvFixture : public testing::Test {
    static void SetUpTestSuite() {
        std::cout << "Global setup" << std::endl;
    }

    static void TearDownTestSuite() {
        std::cout << "Global TearDown" << std::endl;
    }
protected:
    void SetUp() override{
        std::cout << "initializing variables" << std::endl;
        putenv(strdup("DEPO_VAR_ONE=DEPO_VALUE_1"));
        putenv(strdup("DEPO_VAR_TWO=DEPO_VALUE_2"));
        putenv(strdup("DEPO_VAR_THREE=DEPO_VALUE_3"));
    }
    void TearDown() override {
        std::cout << "cleaning variables" << std::endl;
        unsetenv("DEPO_VAR_ONE");
        unsetenv("DEPO_VAR_TWO");
        unsetenv("DEPO_VAR_THREE");
    }
};