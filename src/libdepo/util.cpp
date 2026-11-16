#include "util.h"
#include <regex>


bool depo::util::isRegexMatch(std::string_view candidate, const char* regex) {
    return std::regex_match(candidate.cbegin(), candidate.cend(), std::regex{regex});
}
bool depo::util::isRegexMatch(std::string_view candidate, const std::regex& regex) {
    return std::regex_match(candidate.cbegin(), candidate.cend(), regex);
}
