cmake_minimum_required(VERSION 3.2)
project(healthbar)

set(SOURCE_FILES
        HealthBarAPI.h
        HealthBar.h
        Utils.h
        HealthBarAPI.cpp
        HealthBar.cpp
        Utils.cpp
        )

add_library(healthbar SHARED STATIC ${SOURCE_FILES})

install(TARGETS healthbar DESTINATION ${HEALTHBAR_INSTALL_LIB_DIR})
install(FILES HealthBarAPI.h DESTINATION ${HEALTHBAR_INSTALL_INCLUDE_DIR})