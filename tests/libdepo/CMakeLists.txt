add_executable(depocore_tests
        all_tests.cpp
        path_tests.cpp
        trim_string_tests.cpp
        env_tests.cpp
        utils_tests.cpp
        string_resolver_tests.cpp
        logger_tests.cpp

)
target_link_libraries(depocore_tests PUBLIC depocore_static)
AddGTest(depocore_tests)