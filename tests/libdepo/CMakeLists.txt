add_executable(depocore_tests
        all_tests.cpp
        path_tests.cpp
        trim_string_tests.cpp
        environment_tests.cpp
        utils_tests.cpp

)
target_link_libraries(depocore_tests PUBLIC depocore_static)
AddGTest(depocore_tests)