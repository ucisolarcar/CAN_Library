cmake_minimum_required(VERSION 3.15) # ensures people aren't on super outdated systems 
project(CAN_Library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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

# ========== PYTHON BINDINGS ==========
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

# Create the Python module
pybind11_add_module(PyCANLibrary python_bindings/PyCANLibrary.cpp)

target_include_directories( PyCANLibrary
    PRIVATE src PyCANLibrary
    PRIVATE external
)

target_link_libraries(PyCANLibrary PRIVATE CAN_Library)

# ========== INSTALL ==========
install(TARGETS CAN_Library DESTINATION lib)
install(TARGETS PyCANLibrary DESTINATION lib/python) # adjust as needed
