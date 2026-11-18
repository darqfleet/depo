#pragma once
#include <regex>
#include <string_view>

namespace depo::core {
    class StringResolver {
    public:
        static std::string unwrapVars(std::string_view string);

    private:
        static std::regex m_rgx;
    };
} // namespace depo::core
