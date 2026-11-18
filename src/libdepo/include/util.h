#pragma once
#include <regex>
#include <string_view>

namespace depo::util {
    bool isRegexMatch(std::string_view candidate, const char* regex);
    bool isRegexMatch(std::string_view candidate, const std::regex& regex);
} // namespace depo::util
