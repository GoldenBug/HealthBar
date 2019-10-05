cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(HEALTHBAR_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(HEALTHBAR_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(HEALTHBAR_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(HEALTHBAR_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/healthbar)

include_directories(${HEALTHBAR_INSTALL_INCLUDE_DIR})
include_directories(${HEALTHBAR_HEADERS_DIR})

add_subdirectory(src)
target_include_directories(healthbar PUBLIC src)
#add_subdirectory(test)