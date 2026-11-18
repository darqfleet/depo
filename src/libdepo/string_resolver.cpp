#include "string_resolver.h"
#include "env.h"
using namespace depo::core;

std::string StringResolver::unwrapVars(std::string_view string) {
    std::string result{};
    if (string.empty())
    {
        return result;
    }
    result.reserve(string.size() * 2);
    auto begin{string.begin()};
    const auto end{string.cend()};
    std::match_results<std::string_view::const_iterator> match;

    while (std::regex_search(begin, end, match, m_rgx))
    {
        result.append(begin, match[0].first);
        std::string var{};
        if (match[1].matched)
        {
            var = match[1].str();
        }
        else if (match[2].matched)
        {
            var = match[2].str();
        }
        result.append(Env::get(var));
        begin = match[0].second;
    }
    result.append(begin, end);
    return result;
}

std::regex StringResolver::m_rgx{R"(\$\{(\w+)\}|\$(\w+))"};
