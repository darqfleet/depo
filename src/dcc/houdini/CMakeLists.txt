list(APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )
find_package(Houdini REQUIRED)
add_library(depohou SHARED depohou_entry.cpp
        sop_node_template.cpp)
#target_include_directories(somelib PRIVATE .)
target_link_libraries(depohou PRIVATE Houdini depocore)
houdini_configure_target(depohou)
houdini_configure_target(depocore)