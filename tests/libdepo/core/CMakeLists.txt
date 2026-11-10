add_executable(depocore_tests
        path_tests.cpp
)
target_link_libraries(depocore_tests PUBLIC depocore_static)
AddGTest(depocore_tests)