#include "trimString.h"
using namespace depo::core;

std::string_view TrimString::trim(std::string_view string, std::string_view trimChars, TrimDir trim) noexcept {
    switch (trim)
    {
    case TrimDir::LEFT:
        {
            return trimLeft(string, trimChars);
        }
    case TrimDir::RIGHT:
        return trimRight(string, trimChars);
    default:
        {
            return trimBoth(string, trimChars);
        }
    }
}

constexpr std::string_view TrimString::trimRight(std::string_view string, std::string_view trimChars) noexcept {
    const size_t position{string.find_last_not_of(trimChars)};
    if (position == std::string_view::npos)
    {
        return {};
    }
    return string.substr(0, position + 1);
}
constexpr std::string_view TrimString::trimLeft(std::string_view string, std::string_view trimChars) noexcept {
    const size_t position{string.find_first_not_of(trimChars)};
    if (position == std::string_view::npos)
    {
        return {};
    }
    return string.substr(position);
}
constexpr std::string_view TrimString::trimBoth(std::string_view string, std::string_view trimChars) noexcept {
    std::string_view left{trimLeft(string, trimChars)};
    return trimRight(left, trimChars);
}
