cmake_minimum_required(VERSION 2.8)

project(isometric)

include(cmake/castella/Install.cmake)
include(cmake/castella/Log.cmake)
include(cmake/castella/Misc.cmake)
include(cmake/castella/Platform.cmake)
include(cmake/castella/String.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

log(info "Cmake build type:" ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(IGD_RELEASE_BUILD False)
    set(IGD_DEBUG_BUILD True)
    register_definitions(IGD_DEBUG_BUILD)
else()
    set(IGD_RELEASE_BUILD True)
    set(IGD_DEBUG_BUILD False)
    register_definitions(IGD_RELEASE_BUILD)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(IGD_INCLUDE_DEBUG_INFO True)
else()
    set(IGD_INCLUDE_DEBUG_INFO False)
endif()

if(CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
    set(IGD_OPTIMIZE_FOR_SIZE True)
else()
    set(IGD_OPTIMIZE_FOR_SIZE False)
endif()

set(IGD_CXX_STANDARD_SWITCH "-std=c++14")
set(IGD_CXX_COMPILER_DIAGNOSTICS_SWITCH "-Wall -Wextra -Wpedantic -Werror")

if(${IGD_OPTIMIZE_FOR_SIZE})
    set(IGD_CXX_OPTIMIZATION_SWITCH "-Os")
else()
    set(IGD_CXX_OPTIMIZATION_SWITCH "-O2")
endif()

string_join(IGD_CXX_COMPILEFLAGS " "
    ${IGD_CXX_STANDARD_SWITCH}
    ${IGD_CXX_COMPILER_DIAGNOSTICS_SWITCH}
    ${IGD_CXX_OPTIMIZATION_SWITCH}
)

log(info "C++ compile flags:" ${IGD_CXX_COMPILEFLAGS})

find_package(Threads REQUIRED)
list(APPEND IGD_EXTERNAL_LIBS ${CMAKE_THREAD_LIBS_INIT})

set(GUM_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/gum)
set(GUM_LIBS gum-static)
add_subdirectory(${GUM_ROOT})
include_directories(${GUM_ROOT})
list(APPEND IGD_EXTERNAL_LIBS ${GUM_LIBS})

string_join(IGD_EXTERNAL_LIBS_STRING " " ${IGD_EXTERNAL_LIBS})
log(info "Linking with:" ${IGD_EXTERNAL_LIBS_STRING})

set(IGD_ROOT ${CMAKE_SOURCE_DIR}/isometric/)
set(IGD_SOURCES
    main.cpp
)
string_prepend(IGD_SOURCES ${IGD_ROOT} ${IGD_SOURCES})
include_directories(${CMAKE_SOURCE_DIR})

dump_definitions()

add_executable(isometric ${IGD_SOURCES} ${GLAD_SOURCES})
set_target_properties(isometric PROPERTIES COMPILE_FLAGS ${IGD_CXX_COMPILEFLAGS})
target_link_libraries(isometric ${IGD_EXTERNAL_LIBS})

highlight_matching(${IGD_ROOT}/*.h)
highlight_matching(${IGD_ROOT}/*.cpp)
