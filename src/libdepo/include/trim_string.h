#pragma once
#include <string_view>
#include "enums.h"
namespace depo::core {
    class TrimString {
    public:
        static std::string_view trim(std::string_view string, std::string_view trimChars = " \t\n\r\f\v",
                                     TrimDir trim = TrimDir::BOTH) noexcept;

    private:
        static constexpr std::string_view trimRight(std::string_view string, std::string_view trimChars) noexcept;
        static constexpr std::string_view trimLeft(std::string_view string, std::string_view trimChars) noexcept;
        static constexpr std::string_view trimBoth(std::string_view string, std::string_view trimChars) noexcept;
    };

} // namespace depo::core
