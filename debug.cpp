#include <iostream>
#include <regex>
// bool regexValidation(std::string_view candidate, const char* regex) {
//     std::regex rgx{regex};
// }

int main() {
    std::smatch match;
    // std::regex rgx{R"([A-Z])"};
    std::regex rgx{"[A-Z]+"};
    if (std::regex_match("ZXCVBNM", rgx)) {
        std::cout << "regex matched!" << std::endl;
    }else {
        std::cout << "regex not matched" << std::endl;
    }

    return 0;
}
