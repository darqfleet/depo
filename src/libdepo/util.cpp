#include "util.h"
#include <regex>
#include "env.h"


bool depo::util::isRegexMatch(std::string_view candidate, const char* regex) {
    return std::regex_match(candidate.cbegin(), candidate.cend(), std::regex{regex});
}
bool depo::util::isRegexMatch(std::string_view candidate, const std::regex& regex) {
    return std::regex_match(candidate.cbegin(), candidate.cend(), regex);
}

std::string depo::util::resolveString(std::string_view string) {
    {
        std::string temp_s{string};
        std::smatch match;
        static std::regex m_regex{R"(\$\w+)"};

        while (std::regex_search(temp_s, match, m_regex))
        {
            std::string match_str{match.str()};
            std::string var{match_str.begin() + 1, match_str.end()};
            std::string varEvaluate{core::Env::get(var)};
            temp_s = std::regex_replace(temp_s, m_regex, varEvaluate, std::regex_constants::format_first_only);
        }
        return temp_s;
    }
}
