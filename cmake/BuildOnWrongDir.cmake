if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
            "\nCannot build in source directory\n"
            "use cmake -B <src-dir> <build-dir>\n"
            "And before cleanup <src-dir>\n"
            "rm -rf CMakeFiles CMakeCache.txt\n"
    )
endif ()