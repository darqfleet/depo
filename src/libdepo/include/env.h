#pragma once
#include <string_view>

namespace depo::core {
    class Env {
    public:
        [[nodiscard]] static std::string_view get(std::string_view variable);
        static void set(std::string_view name, std::string_view value);
        static void unset(std::string_view name);
        /*TODO implement append and prepend*/
    };
} // namespace depo::core
