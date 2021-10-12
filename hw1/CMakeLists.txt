cmake_minimum_required(VERSION 3.0)


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CC_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(homework1)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -Werror -std=gnu11")

set(CMAKE_BUILD_TYPE Debug)

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules")
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

add_library(org_lib STATIC
    src/Org_methods.c
)
target_include_directories(org_lib PUBLIC ./include)
set_target_properties(org_lib PROPERTIES PUBLIC_HEADER include/Org_struct.h)

add_library(rw_lib STATIC
    src/Read_write.c
)
target_include_directories(rw_lib PUBLIC ./include)
set_target_properties(rw_lib PROPERTIES PUBLIC_HEADER include/Read_write.h)

set(SOURCES_MAIN src/main.c)
AUX_SOURCE_DIRECTORY(tests SOURCES_UNIT) 

add_executable(main.out ${SOURCES_MAIN})
target_include_directories(main.out PUBLIC ./include)
target_link_libraries(main.out org_lib rw_lib)

add_executable(tests.out ${SOURCES_UNIT})
target_include_directories(tests.out PUBLIC ./include)
target_link_libraries(tests.out org_lib rw_lib gtest pthread gcov)

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE tests.out
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
        EXCLUDE "/usr/*" "${PROJECT_SOURCE_DIR}/src/Read_write.c" "${PROJECT_SOURCE_DIR}/src/main.c" "${PROJECT_SOURCE_DIR}/tests/*"
    )
endif()















