#include <string_view>
#include <iostream>

int main() {
    std::string_view s{"/some/extra/slash/"};

    auto a{s.find_last_not_of('/')};

    std::cout << s.substr(0, a+1) << std::endl;
    return 0;
}