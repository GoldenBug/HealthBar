cmake_minimum_required(VERSION 3.13)
project(HealthBar)

set(CMAKE_CXX_STANDARD 14)

if (MINGW)
    add_library(HealthBar STATIC
            HealthBarAPI.cpp
            HealthBarAPI.h
            HealthBar_Win.cpp
            HealthBar.h)
endif (MINGW)

if (LINUX)
    add_library(HealthBar STATIC
            HealthBarAPI.cpp
            HealthBarAPI.h
            HealthBar_Unix.cpp
            HealthBar.h)
else ()
    add_library(HealthBar STATIC
            HealthBarAPI.cpp
            HealthBarAPI.h
            HealthBar_Win.cpp
            HealthBar.h)
endif ()


SET(APP_EXE StaticTest)

ADD_EXECUTABLE(${APP_EXE}
        main.cpp)

TARGET_LINK_LIBRARIES(${APP_EXE}
        HealthBar)
