cmake_minimum_required( VERSION 3.0 )

project( calc VERSION 1.0.0 DESCRIPTION "commandline calculator." )

set( BUILD_TESTS OFF CACHE BOOL "" )

include( CPack )

add_library( libcalc calc.c )
target_include_directories( libcalc PUBLIC include )
target_link_libraries( libcalc PUBLIC -lm -lc )
target_compile_definitions( libcalc
    PRIVATE __CALC_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PRIVATE __CALC_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PRIVATE __CALC_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)
set_target_properties( libcalc PROPERTIES OUTPUT_NAME calc )

add_executable( calc main.c )
target_link_libraries( calc PRIVATE libcalc )

if( BUILD_TESTS )
    add_executable( calc_test test.c )
    target_link_libraries( calc_test PRIVATE libcalc )
endif()

install( TARGETS calc libcalc
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
)

install( FILES "include/calc.h" DESTINATION "include" )
