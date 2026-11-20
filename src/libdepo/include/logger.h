#pragma once
#include <iostream>
#include <sstream>
#include <mutex>

namespace depo::util {


    enum class LogLevel { DEBUG=10, INFO=20, MESSAGE=30, WARNING=40, ERROR=50, CRITICAl=60 };


    enum class LogLevelStyle { DEBUG=96, INFO=95, MESSAGE=94, WARNING=93, ERROR=92, CRITICAl=91 };


    // inline std::string timeStamp() {
    //     auto tes{std::chrono::system_clock::now()};
    //     auto ms{std::chrono::floor<std::chrono::milliseconds>(tes)};
    //     return std::format("[{:%Y-%m-%d]:[%H:%M:%S}]", ms);
    // }

    static std::string_view logLevelToString(const LogLevel& level) {
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
        case LogLevel::CRITICAl:
            return "CRITICAL";
            default:
            return "UNKNOWN";
        }
    }

    inline int levelToStyle(const LogLevel& level) {
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
        case LogLevel::CRITICAl:
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
        void put(const LogLevel& logLevel, Args... args) {
            // auto tes{std::chrono::system_clock::now()};
            // auto ms{std::chrono::floor<std::chrono::milliseconds>(tes)};
            // std::string time =  std::format("{:%Y-%m-%d %H:%M:%S}", ms);
            if (logLevel >= m_level)
            {
                std::stringstream m_logBuff;
                // m_logBuff << time;
                m_logBuff <<"[" << logLevelToString(logLevel) << "]";
                ((m_logBuff << " " << args), ...);
                {
                    std::lock_guard<std::mutex> lock{m_mutex};
                    std::cout << "\e[" << levelToStyle(logLevel) << "m";
                    std::cout <<  m_logBuff.str()  << "\e[0" << "m" << std::endl;
                }
            }

        }

        void setLevel(const LogLevel& level) {
            m_level = level;
        }
        [[nodiscard]] const LogLevel& level() const {
            return m_level;
        }

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    private:
        Logger() :m_level{LogLevel::INFO}{}
        LogLevel m_level;
        static std::mutex m_mutex;
    };
    std::mutex Logger::m_mutex;

} // namespace depo::util
