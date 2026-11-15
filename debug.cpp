#include <iostream>
#include <string_view>
#include "depo.h"

using namespace depo::core;

int main() {
    std::string s{"/some/extra/slash////"};
    std::string_view d{TrimString::trim(s, " s/")};
    // std::string_view c{TrimString::trimLeft(s, " ")};
    std::cout << d << std::endl;

    std::cout << "\vasd\vasda" << std::endl;
    return 0;
}
