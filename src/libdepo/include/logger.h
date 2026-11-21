#pragma once
#include <atomic>
#include <chrono>
#include <format>
#include <iostream>
#include <mutex>

namespace depo::util {
    enum class LogLevel { DEBUG = 10, INFO = 20, MESSAGE = 30, WARNING = 40, ERROR = 50, CRITICAL = 60 };
    inline constexpr std::string_view logLevelToString(const LogLevel& level) {
        switch (level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::MESSAGE:
            return "MESSAGE";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }

    inline constexpr int levelToStyle(const LogLevel& level) {
        switch (level)
        {
        case LogLevel::DEBUG:
            return 96;
        case LogLevel::INFO:
            return 95;
        case LogLevel::MESSAGE:
            return 94;
        case LogLevel::WARNING:
            return 93;
        case LogLevel::ERROR:
        case LogLevel::CRITICAL:
            return 91;
        default:
            return 96;
        }
    }
    class Logger {
    public:
        static Logger& get() {
            static Logger instance;
            return instance;
        }

        template <typename... Args>
        void put(const LogLevel logLevel, Args&&... args) {
            if (logLevel < m_level.load(std::memory_order_acquire))
            {
                return;
            }

            std::string message{std::format("{} [{}]", timeStamp(), logLevelToString(m_level))};
            ((message += std::format(" {}", std::forward<Args>(args))), ...);
            const int style{levelToStyle(m_level)};
            std::lock_guard<std::mutex> lock{m_mutex};
            std::cout << "\033[" << style << "m" << message << "\033[0m\n";
        }

        void setLevel(const LogLevel& level) noexcept { m_level.store(level, std::memory_order_release); }


        [[nodiscard]] const LogLevel& level() const noexcept { return m_level.load(std::memory_order_acquire); }

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    private:
        [[nodiscard]] static std::string timeStamp() {
            const std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};
            std::chrono::zoned_time localTime{std::chrono::current_zone(),
                                              std::chrono::floor<std::chrono::milliseconds>(now)};
            return std::format("{:%F %H:%M:%S}", localTime);
        }

        Logger() : m_level{LogLevel::INFO} {}
        std::atomic<LogLevel> m_level;
        std::mutex m_mutex;
    };

} // namespace depo::util
