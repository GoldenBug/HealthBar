cmake_minimum_required(VERSION 3.13)
project(HealthBar)

# define library version (update: apparently you can also do it in project()!)
set(GOLDENBUG_HEALTHBAR_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(GOLDENBUG_HEALTHBAR_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(GOLDENBUG_HEALTHBAR ${GOLDENBUG_HEALTHBAR_VERSION_MAJOR}.${GOLDENBUG_HEALTHBAR_VERSION_MINOR} CACHE STRING "version" FORCE)

# installation destinations
if (UNIX AND NOT CYGWIN)
    include(GNUInstallDirs)

    set(GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/goldenbug_healthbar")
    set(GOLDENBUG_HEALTHBAR_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}")
    set(GOLDENBUG_HEALTHBAR_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(GOLDENBUG_HEALTHBAR_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(GOLDENBUG_HEALTHBAR_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")

    set(GOLDENBUG_HEALTHBAR_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/goldenbug_healthbar/cmake")
    set(GOLDENBUG_HEALTHBAR_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/goldenbug_healthbar")

    set(GOLDENBUG_HEALTHBAR_RUNTIME_INSTALL_DIR "bin") # for the nodesize_dbg, just ignore version and the like
    set(GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR "include/goldenbug_healthbar") # header filestree

elseif (WIN32 OR CYGWIN)
    set(GOLDENBUG_HEALTHBAR_INC_INSTALL_DIR "include/goldenbug_healthbar")
    set(GOLDENBUG_HEALTHBAR_RUNTIME_INSTALL_DIR "bin")
    set(GOLDENBUG_HEALTHBAR_LIBRARY_INSTALL_DIR "bin")
    set(GOLDENBUG_HEALTHBAR_ARCHIVE_INSTALL_DIR "lib")
    set(GOLDENBUG_HEALTHBAR_FRAMEWORK_INSTALL_DIR "bin")

    set(GOLDENBUG_HEALTHBAR_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(GOLDENBUG_HEALTHBAR_ADDITIONAL_FILES_INSTALL_DIR "./")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
    message(FATAL_ERROR "Could not set install folders for this platform!")
endif ()

# subdirectories
add_subdirectory(src)
if (GOLDENBUG_HEALTHBAR_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()
if (GOLDENBUG_HEALTHBAR_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()
if (GOLDENBUG_HEALTHBAR_BUILD_TOOLS)
    add_subdirectory(tool)
endif ()

# install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION ${GOLDENBUG_HEALTHBAR_ADDITIONAL_FILES_INSTALL_DIR})

install(EXPORT goldenbug_healthbarTargets DESTINATION ${GOLDENBUG_HEALTHBAR_CMAKE_CONFIG_INSTALL_DIR}
        FILE goldenbug_healthbar-config.cmake)
