#pragma once
#include <mutex>

namespace depo::util {
    class Logger {
    public:
        static Logger& get() {
            static Logger instance;
            return instance;
        }
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        template<typename... Args>
        void put(Args... args) {
            {
                std::lock_guard<std::mutex> lock{m_mutex};
                std::size_t first{0};
                ((std::cout << (first++ > 0 ? " " : "") << args), ...);
            }
        }
    private:
        static std::mutex m_mutex;
        Logger() = default;
    };
    std::mutex Logger::m_mutex;
}
