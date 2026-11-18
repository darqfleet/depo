#include <cstdlib>
#include <sstream>
#include <string>

#include "env.h"
#include "util.h"

using namespace depo::core;

std::string_view Env::get(const std::string_view variable) {
    const char* var{getenv(std::string{variable}.c_str())};
    std::string_view value;
    if (var != nullptr)
    {
        value = var;
    }
    return value;
}

void Env::set(std::string_view name, std::string_view value) {
    if (name.empty() || value.empty())
    {
        std::stringstream expMessage{};
        expMessage << "name or value cannot be empty. ";
        expMessage << " name: " << (name.empty() ? "<empty>" : name);
        expMessage << " value: " << (value.empty() ? "<empty>" : value);
        throw std::runtime_error{expMessage.str()};
    }
    else
    {
        const bool nameIsValid{util::isRegexMatch(name, R"([A-Z_]+)")};
        if (!nameIsValid)
        {
            std::stringstream expMessage{};
            expMessage << "Variable name must be match by [A-Z_]+ pattern. ";
            expMessage << "Name has illegal chars: " << name;
            throw std::runtime_error{expMessage.str()};
        }
        else
        {
            setenv(std::string{name}.c_str(), std::string{value}.c_str(), 1);
        }
    }
}

void Env::unset(std::string_view name) { unsetenv(std::string{name}.c_str()); }
