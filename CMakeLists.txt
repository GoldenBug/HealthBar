cmake_minimum_required(VERSION 3.13)
project(HealthBar)

set(CMAKE_CXX_STANDARD 14)

if (UNIX AND NOT CYGWIN)
    add_library(HealthBar STATIC
            HealthBarAPI.cpp
            HealthBarAPI.h
            HealthBar_Unix.cpp
            HealthBar.h
            Utils.cpp
            Utils.h)
else ()
    add_library(HealthBar STATIC
            HealthBarAPI.cpp
            HealthBarAPI.h
            HealthBar_Win.cpp
            HealthBar.h
            Utils.cpp
            Utils.h)
endif ()

set_target_properties(HealthBar PROPERTIES PUBLIC_HEADER "HealthBarAPI.h")

SET(APP_EXE StaticTest)
ADD_EXECUTABLE(${APP_EXE}
        main.cpp)
TARGET_LINK_LIBRARIES(${APP_EXE}
        HealthBar)
