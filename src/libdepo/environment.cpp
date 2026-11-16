#include "environment.h"
#include <cstdlib>
#include <string.h>
#include <string>
using namespace depo::core;

std::string_view Environment::get(const char* variable) {
    std::string_view value{getenv(variable)};
    if (!value.empty())
    {
        return value;
    }
    return {};
}

void Environment::set(std::string_view name, std::string_view value) {
    std::string result{};
    if (!name.empty() /*TODO check all chars is capital */ && !value.empty())
    {
        result += name;
        result += '=';
        result += value;
        putenv(strdup(result.c_str()));
    }
}
