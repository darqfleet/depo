#include <iostream>
#include "env.h"
#include "util.h"
int main(int argc, char** argv) {
    using namespace depo;
    core::Env::set("FOO", "BAR");
    core::Env::set("BAR", "$FOO");
    std::cout << util::resolveString("$FOO/some/path/after") << std::endl;
    return 0;
}
