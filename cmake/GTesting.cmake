include(FetchContent)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(INSTALL_GMOCK "Install GMock" OFF)
option(INSTALL_GTEST "Install GTest" OFF)
FetchContent_MakeAvailable(gtest)

include(GoogleTest)
include(CoverageTests)
include(ValgrindMemCheck)

macro(AddGTest target)
    message(DEBUG "Adding GTest for: ${target}")
    target_link_libraries(${target} PRIVATE gtest_main gmock)
    gtest_discover_tests(${target})
    AddValgrindMemCheck(${target})
    AddCoverage(${target})
endmacro()