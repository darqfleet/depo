#include <iostream>
#include "logger.h"
#include <chrono>
#include <format>
#include <thread>
#include <random>
#include <stack>
#include <fstream>
// std::string timestamp(const std::string& format) {
//     std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};
//     std::chrono::zoned_time asd{"Warsaw/Europe", now};
//     auto b = std::chrono::floor<std::chrono::milliseconds>(now);
//     // return std::format(asd);
// }
std::string handlerName() {
    const std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};
    std::chrono::zoned_time localTime{std::chrono::current_zone(),
                                      std::chrono::floor<std::chrono::milliseconds>(now)};
    return std::format("log_{:%F:%H:%M}.txt", localTime);
}
auto randomTime() {
    std::random_device rd{};
    std::default_random_engine seed{rd()};
    std::uniform_int_distribution ints{100, 1000};
    return std::chrono::milliseconds{ints(seed)};
}
int main(int argc, char **argv) {
    using namespace depo::core;
    using namespace depo::util;


    Logger& logger{Logger::get()};
    auto logThreaded{
        [&logger](std::string_view name, LogLevel level) {
            for (size_t i{0}; i<100; ++i) {
                auto id{std::this_thread::get_id()};
                logger.put(level, name,  "just some log ", i);
                std::this_thread::sleep_for(randomTime());
            }
        }
    };


    std::thread t0{[&]() {
        size_t counter{0};
        for (size_t i{0}; i<60; ++i) {
            std::this_thread::sleep_for(randomTime());
            if (i > 10 && logger.level() < LogLevel::INFO) {
                logger.setLevel(LogLevel::INFO);
            }
            if (i > 20 && logger.level() < LogLevel::MESSAGE) {
                logger.setLevel(LogLevel::MESSAGE);
            }
            if (i > 30 && logger.level() < LogLevel::WARNING) {
                logger.setLevel(LogLevel::WARNING);
            }
            if (i > 40 && logger.level() < LogLevel::ERROR) {
                logger.setLevel(LogLevel::ERROR);
            }
            if (i > 60 && logger.level() < LogLevel::CRITICAL) {
                logger.setLevel(LogLevel::CRITICAL);
            }
        }
    }};
    std::thread t1{logThreaded, "spawn in debug", LogLevel::DEBUG};
    std::thread t2{logThreaded, "spawn in info", LogLevel::INFO};
    std::thread t3{logThreaded, "spawn in error", LogLevel::ERROR};
    std::thread t4{logThreaded, "spawn in message", LogLevel::MESSAGE};
    std::thread t5{logThreaded, "spawn in critical", LogLevel::CRITICAL};
    std::thread t6{logThreaded, "spawn in warning", LogLevel::WARNING};
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();


    return 0;
}
