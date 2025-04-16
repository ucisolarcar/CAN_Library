cmake_minimum_required(VERSION 3.15) # ensures people aren't on super outdated systems 
project(CAN_Library)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE LIBRARY_HEADERS "src/*.h")
file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp")

# put can floats in here
set(EXTERNAL_SOURCES
    external/can.h
    external/canFloat.h
    external/canFloat.cpp
)

# creates the library
add_library(CAN_Library
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCES}
    ${EXTERNAL_SOURCES}
)

target_include_directories(CAN_Library
    PUBLIC src 
    PUBLIC external
)

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.hpp")

add_executable(CAN_Library_Tests
    ${TEST_SOURCES}
    ${TEST_HEADERS}
)

target_link_libraries(CAN_Library_Tests
    CAN_Library
)

target_compile_options(CAN_Library_Tests PRIVATE -g -Wall -Wextra -pedantic)
