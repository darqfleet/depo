#include <gtest/gtest.h>
#include "logger.h"
using namespace depo::util;

TEST(Logger, logLevelToString) {
    EXPECT_EQ(logLevelToString(LogLevel::DEBUG), "DEBUG");
    EXPECT_EQ(logLevelToString(LogLevel::INFO), "INFO");
    EXPECT_EQ(logLevelToString(LogLevel::MESSAGE), "MESSAGE");
    EXPECT_EQ(logLevelToString(LogLevel::WARNING), "WARNING");
    EXPECT_EQ(logLevelToString(LogLevel::ERROR), "ERROR");
    EXPECT_EQ(logLevelToString(LogLevel::CRITICAL), "CRITICAL");
}

TEST(Logger, setLevel) {
    Logger& logger{Logger::get()};
    EXPECT_EQ(logger.level(), LogLevel::INFO);
    logger.setLevel(LogLevel::DEBUG);
    EXPECT_EQ(logger.level(), LogLevel::DEBUG);
    logger.setLevel(LogLevel::INFO);
    EXPECT_EQ(logger.level(), LogLevel::INFO);
    logger.setLevel(LogLevel::MESSAGE);
    EXPECT_EQ(logger.level(), LogLevel::MESSAGE);
    logger.setLevel(LogLevel::WARNING);
    EXPECT_EQ(logger.level(), LogLevel::WARNING);
    logger.setLevel(LogLevel::ERROR);
    EXPECT_EQ(logger.level(), LogLevel::ERROR);
    logger.setLevel(LogLevel::CRITICAL);
    EXPECT_EQ(logger.level(), LogLevel::CRITICAL);
}
TEST(Logger, defaultConstructor) {
    Logger& logger{Logger::get()};
    EXPECT_EQ(logger.level(), LogLevel::INFO);

}

TEST(Logger, LoggerLevel) {
    EXPECT_EQ(static_cast<int>(LogLevel::DEBUG), 10);
    EXPECT_EQ(static_cast<int>(LogLevel::INFO), 20);
    EXPECT_EQ(static_cast<int>(LogLevel::MESSAGE), 30);
    EXPECT_EQ(static_cast<int>(LogLevel::WARNING), 40);
    EXPECT_EQ(static_cast<int>(LogLevel::ERROR), 50);
    EXPECT_EQ(static_cast<int>(LogLevel::CRITICAL), 60);
}