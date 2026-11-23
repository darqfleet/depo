#pragma once
#include <atomic>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>

#include "enums.h"
#include "env.h"
#include "path.h"
#include "concepts.h"


using namespace depo::core;


namespace depo::util {

    class Logger {
    public:
        static Logger& get() {
            static Logger instance;
            return instance;
        }

        template <Loggable... Args>
        void put(const LogLevel logLevel, Args&&... args) {
            if (logLevel < m_level.load(std::memory_order_acquire))
            {
                return;
            }

            std::string message{std::format("[{}][{}]", timeStamp(), logLevelToString(logLevel))};
            ((message += std::format(" {}", std::forward<Args>(args))), ...);
            const int style{levelToStyle(logLevel)};

            std::lock_guard<std::mutex> lock{m_mutex};
            std::cout << "\033[" << style << "m" << message << "\033[0m\n";
            putToHandler(message + "\n");
        }

        void setLevel(const LogLevel level) noexcept {
            m_level.store(level, std::memory_order_release);
            put(LogLevel::SYSMSG, std::format("logger level changed to: {}", logLevelToString(level)));
        }


        [[nodiscard]] LogLevel level() const noexcept { return m_level.load(std::memory_order_acquire); }


        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    private:
        [[nodiscard]] static std::string timeStamp() {
            const std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};
            std::chrono::zoned_time localTime{std::chrono::current_zone(),
                                              std::chrono::floor<std::chrono::milliseconds>(now)};
            return std::format("{:%F|%H:%M:%S}", localTime);
        }


        static constexpr int levelToStyle(LogLevel level) {
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
            case LogLevel::SYSMSG:
                    return 92;
            default:
                return 96;
            }
        }


        static constexpr std::string_view logLevelToString(LogLevel level) {
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
            case LogLevel::SYSMSG:
                    return "SYSMSG";
            default:
                return "UNKNOWN";
            }
        }

        void putToHandler(std::string_view message) {
            if (m_logFile.is_open())
            {
                m_logFile << message;
                m_logFile.flush();
            }
        }

        static std::string handlerName() {
            const std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};
            std::chrono::zoned_time localTime{std::chrono::current_zone(),
                                              std::chrono::floor<std::chrono::seconds>(now)};
            return std::format("{:%Y-%m-%d_%H-%M-%S}.log", localTime);
        }

        Logger() : m_level{LogLevel::INFO} {

            Path prefDir{"$DEPO_USER_PREF_DIR"};
            if (!prefDir.exists())
            {
                prefDir = Path{Env::get("HOME")};
            }

            Path logsDir{prefDir /= ".depo/logs"};
            if (!logsDir.exists())
            {
                try
                { std::filesystem::create_directories(logsDir.expandedString()); }
                catch (std::filesystem::filesystem_error& err)
                { std::cerr << "cannot create directory:" << logsDir.expandedString() << "\n" << err.what() << "\n"; }
            }

            if (logsDir.exists())
            {
                Path handlerFile{logsDir / handlerName()};
                m_logFile.open(handlerFile.expandedString(), std::ios::app);
            }
            else
            {
                std::cerr << "Logger::stream handler not initialized\n";
            }
        }

        ~Logger() {
            if (m_logFile.is_open())
            {
                m_logFile.close();
            }
        }

        std::atomic<LogLevel> m_level;
        std::ofstream m_logFile;
        std::mutex m_mutex;
    };

} // namespace depo::util
