include(GNUInstallDirs)

set(LIBRARY "libHealthBar")
set(STATICLIBRARY "libHealthBar_static")
set(HEADERS
        HealthBarAPI.h
        HealthBar.h
        Utils.h)
set(LIBRARY_SOURCES
        HealthBar_Win.cpp
        HealthBarAPI.cpp
        Utils.cpp
        ${HEADERS}
        )

set(PROGRAM "HealthBar")
set(PROGRAM_SOURCES
        ../api_test/tests.cpp
        )

include_directories(. ${CMAKE_CURRENT_BINARY_DIR})
include_directories(
        ${PROJECT_BINARY_DIR}/extensions
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/HealthBar_version.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/HealthBar_version.h)

include(GenerateExportHeader)

add_executable(${PROGRAM} ${PROGRAM_SOURCES})
add_compiler_export_flags()

if (HEALTHBAR_SHARED)
    target_link_libraries(${PROGRAM} libHealthBar)
elseif (HEALTHBAR_STATIC)
    target_link_libraries(${PROGRAM} libHealthBar_static)
endif ()

# Disable the PUBLIC declarations when compiling the executable:
set_target_properties(${PROGRAM} PROPERTIES
        COMPILE_FLAGS "-DHEALTHBAR_STATIC_DEFINE")

# Check integrity of node structure when compiled as debug:
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DHEALTHBAR_DEBUG_NODES -DDEBUG")
set(CMAKE_LINKER_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG}")

set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE} -pg")
set(CMAKE_LINKER_PROFILE "${CMAKE_LINKER_FLAGS_RELEASE} -pg")

add_definitions(-DLIBDIR=\"${CMAKE_BINARY_DIR}\")

if (${CMAKE_VERSION} VERSION_GREATER "1.8")
    set(CMAKE_C_VISIBILITY_PRESET hidden)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
elseif (CMAKE_COMPILER_IS_GNUCC OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
endif ()

if (HEALTHBAR_SHARED)
    add_library(${LIBRARY} SHARED ${LIBRARY_SOURCES})
    # Include minor version and patch level in soname for now.
    set_target_properties(${LIBRARY} PROPERTIES
            OUTPUT_NAME "HealthBar"
            SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.gfm.${PROJECT_VERSION_GFM}
            VERSION ${PROJECT_VERSION})

    set_property(TARGET ${LIBRARY}
            APPEND PROPERTY MACOSX_RPATH true)

    # Avoid name clash between PROGRAM and LIBRARY pdb files.
    set_target_properties(${LIBRARY} PROPERTIES PDB_NAME HealthBar_dll)

    generate_export_header(${LIBRARY}
            BASE_NAME ${PROJECT_NAME})

    list(APPEND HEALTHBAR_INSTALL ${LIBRARY})
endif ()

if (HEALTHBAR_STATIC)
    add_library(${STATICLIBRARY} STATIC ${LIBRARY_SOURCES})
    set_target_properties(${STATICLIBRARY} PROPERTIES
            COMPILE_FLAGS -DHEALTHBAR_STATIC_DEFINE
            POSITION_INDEPENDENT_CODE ON)

    if (MSVC)
        set_target_properties(${STATICLIBRARY} PROPERTIES
                OUTPUT_NAME "HealthBar_static"
                VERSION ${PROJECT_VERSION})
    else ()
        set_target_properties(${STATICLIBRARY} PROPERTIES
                OUTPUT_NAME "HealthBar"
                VERSION ${PROJECT_VERSION})
    endif (MSVC)

    if (NOT HEALTHBAR_SHARED)
        generate_export_header(${STATICLIBRARY}
                BASE_NAME ${PROJECT_NAME})
    endif ()

    list(APPEND HEALTHBAR_INSTALL ${STATICLIBRARY})
endif ()

if (MSVC)
    set_property(TARGET ${PROGRAM}
            APPEND PROPERTY LINK_FLAGS /INCREMENTAL:NO)
endif (MSVC)

if (NOT MSVC OR CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS ON)
    include(InstallRequiredSystemLibraries)
endif ()

set(libdir lib${LIB_SUFFIX})

install(TARGETS ${PROGRAM} ${HEALTHBAR_INSTALL}
        EXPORT HealthBar
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${libdir}
        ARCHIVE DESTINATION ${libdir}
        )

if (HEALTHBAR_SHARED OR HEALTHBAR_STATIC)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libHealthBar.pc.in
            ${CMAKE_CURRENT_BINARY_DIR}/libHealthBar.pc @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libHealthBar.pc
            DESTINATION ${libdir}/pkgconfig)

    install(FILES
            HealthBarAPI.h.h
            ${CMAKE_CURRENT_BINARY_DIR}/HealthBar_export.h
            ${CMAKE_CURRENT_BINARY_DIR}/HealthBar_version.h
            DESTINATION include
            )

    install(EXPORT HealthBar DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
endif ()

# Feature tests
include(CheckIncludeFile)
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckSymbolExists)
CHECK_INCLUDE_FILE(stdbool.h HAVE_STDBOOL_H)
CHECK_C_SOURCE_COMPILES(
        "int main() { __builtin_expect(0,0); return 0; }"
        HAVE___BUILTIN_EXPECT)
CHECK_C_SOURCE_COMPILES("
  int f(void) __attribute__ (());
  int main() { return 0; }
" HAVE___ATTRIBUTE__)

# Always compile with warnings
if (MSVC)
    # Force to always compile with W4
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else ()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX /wd4706 /wd4204 /wd4221 /wd4100 /D_CRT_SECURE_NO_WARNINGS")
elseif (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic")
endif ()
