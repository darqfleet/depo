#include <iostream>
#include "logger.h"

int main(int argc, char **argv) {
    depo::util::Logger& l{depo::util::Logger::get()};
    l.put(depo::util::LogLevel::ERROR, "some text");
    return 0;
}
