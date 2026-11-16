#pragma once
#include <string_view>

namespace depo::core {
    class Environment {
    public:
        [[nodiscard]] static std::string_view get(const char* variable);
        static void set(std::string_view name, std::string_view value);
    };
} // namespace depo::core
