set(header_path ${HealthBar_SOURCE_DIR}/include/HealthBar)
set(header
        ${header_path}/HealthBar.h
        ${header_path}/HealthBarAPI.h
        ${header_path}/Utils.h)

set(src
        HealthBar_Win.cpp
        HealthBarAPI.cpp
        Utils.cpp)

add_library(goldenbug_healthbar ${header} ${src})


target_include_directories(goldenbug_healthbar PUBLIC $<BUILD_INTERFACE:${GOLDENBUG_HEALTHBAR_SOURCE_DIR}/include/> # for client in subdirectory
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> # for generated files in build mode
        $<INSTALL_INTERFACE:${GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR}> # for client in install mode
        PRIVATE ${header_path}) # for source files
target_compile_definitions(goldenbug_healthbar PUBLIC
        GOLDENBUG_HEALTHBAR_VERSION_MAJOR=${FOONATHAN_MEMORY_VERSION_MAJOR}
        GOLDENBUG_HEALTHBAR_VERSION_MINOR=${FOONATHAN_MEMORY_VERSION_MINOR})

set_target_properties(goldenbug_healthbar PROPERTIES
        OUTPUT_NAME "goldenbug_healthbar-${GOLDENBUG_HEALTHBAR_VERSION_MINOR}")

install(TARGETS goldenbug_healthbar EXPORT goldenbug_healthbarTargets
        RUNTIME DESTINATION ${GOLDENBUG_HEALTHBAR_RUNTIME_INSTALL_DIR}
        LIBRARY DESTINATION ${GOLDENBUG_HEALTHBAR_LIBRARY_INSTALL_DIR}
        ARCHIVE DESTINATION ${GOLDENBUG_HEALTHBAR_ARCHIVE_INSTALL_DIR}
        FRAMEWORK DESTINATION ${GOLDENBUG_HEALTHBAR_FRAMEWORK_INSTALL_DIR})

# Write/install version file
include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/goldenbug_healthbar-config-version.cmake")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config_impl.hpp DESTINATION ${GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/container_node_sizes_impl.hpp DESTINATION ${FOONATHAN_MEMORY_INC_INSTALL_DIR}/foonathan/memory/detail)
install(FILES ${header} DESTINATION ${GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR}/foonathan/memory)
install(FILES ${detail_header} DESTINATION ${GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR}/foonathan/memory/detail)
install(FILES ${version_file} DESTINATION ${GOLDENBUG_HEALTHBAR_CMAKE_CONFIG_INSTALL_DIR})