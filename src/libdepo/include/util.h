#pragma once
#include <regex>
#include <string_view>

namespace depo::util {
    std::string resolveString(std::string_view string);
    bool isRegexMatch(std::string_view candidate, const char* regex);
    bool isRegexMatch(std::string_view candidate, const std::regex& regex);
} // namespace depo::util
