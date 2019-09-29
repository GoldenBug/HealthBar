cmake_minimum_required(VERSION 3.13)
project(HealthBar)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Do not build in-source.\nPlease remove CMakeCache.txt and the CMakeFiles/ directory.\nThen: mkdir build ; cd build ; cmake .. ; make")
endif ()

set(PROJECT_NAME "HealthBar")

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

option(HEALTHBAR_TESTS "Build HealthBar tests and enable testing" ON)
option(HEALTHBAR_STATIC "Build static libHealthBar library" ON)
option(HEALTHBAR_SHARED "Build shared libHealthBar library" ON)

add_subdirectory(src)

if (HEALTHBAR_TESTS AND (HEALTHBAR_SHARED OR HEALTHBAR_STATIC))
    add_subdirectory(api_test)
endif ()

if (HEALTHBAR_TESTS)
    enable_testing()
    add_subdirectory(api_test testdir)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Profile Release Asan Ubsan." FORCE)
endif (NOT CMAKE_BUILD_TYPE)