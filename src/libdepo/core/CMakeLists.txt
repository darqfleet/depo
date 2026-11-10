add_library(depocore_obj OBJECT path.cpp)

target_include_directories(depocore_obj PUBLIC include)
#target_include_directories(depocore_obj INTERFACE
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/depo>"
#        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
#)

set_target_properties(depocore_obj PROPERTIES
        POSITION_INDEPENDENT_CODE 1)

target_sources(depocore_obj
        PUBLIC FILE_SET HEADERS
        BASE_DIRS include
        FILES include/path.h

)
#find_package(mongocxx 4.0 REQUIRED)
#find_package(bsoncxx 4.0 REQUIRED)
#target_link_libraries(depocore_obj PRIVATE
#        nlohmann_json::nlohmann_json
#        mongo::bsoncxx_shared
#        mongo::mongocxx_shared
#)

add_library(depocore SHARED)
target_link_libraries(depocore
        depocore_obj
#        mongo::bsoncxx_shared
#        mongo::mongocxx_shared
)

add_library(depocore_static STATIC)
target_link_libraries(depocore_static depocore_obj)


CoveragePrepare(depocore_obj)
CoveragePostCleanup(depocore_static)
ApplyClangFormat(depocore_static .)
ApplyCPPCheck(depocore_obj)