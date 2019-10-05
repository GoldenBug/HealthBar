cmake_minimum_required(VERSION 3.2)
project(divider_tests)

add_subdirectory(lib/googletest)

include_directories(${HEALTHBAR_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/tests.cpp main.cpp)

add_executable(healthbar_tests ${SOURCE_FILES})
target_link_libraries(healthbar_tests healthbar gtest)
install(TARGETS healthbar_tests DESTINATION bin)