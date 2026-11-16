#pragma once
#include <string_view>
namespace depo::core {
    class StringResolver {
    public:
        static std::string_view eval(std::string_view string) noexcept;
    };
} // namespace depo::core
