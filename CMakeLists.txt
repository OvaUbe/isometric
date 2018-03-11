cmake_minimum_required(VERSION 3.2)

project(isometric)

include(cmake/castella/Install.cmake)
include(cmake/castella/Log.cmake)
include(cmake/castella/Misc.cmake)
include(cmake/castella/Platform.cmake)
include(cmake/castella/String.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR True)
set(CMAKE_AUTOMOC True)

log(info "Cmake build type:" ${CMAKE_BUILD_TYPE})
log(info "C++ standard:" ${CMAKE_CXX_STANDARD})

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

set(IGD_CXX_COMPILER_DIAGNOSTICS_SWITCH "-Wall -Wextra -Wpedantic -Werror")

if(${IGD_OPTIMIZE_FOR_SIZE})
    set(IGD_CXX_OPTIMIZATION_SWITCH "-Os")
else()
    set(IGD_CXX_OPTIMIZATION_SWITCH "-O2")
endif()

string_join(IGD_CXX_COMPILEFLAGS " "
    ${IGD_CXX_COMPILER_DIAGNOSTICS_SWITCH}
    ${IGD_CXX_OPTIMIZATION_SWITCH}
)

log(info "C++ compile flags:" ${IGD_CXX_COMPILEFLAGS})

find_package(Threads REQUIRED)
list(APPEND IGD_EXTERNAL_LIBS ${CMAKE_THREAD_LIBS_INIT})

find_package(Qt5Quick)
find_package(Qt5Core)
list(APPEND IGD_EXTERNAL_LIBS Qt5::Quick Qt5::Core)

set(GUM_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/gum)
set(GUM_LIBS gum-static)
add_subdirectory(${GUM_ROOT})
include_directories(${GUM_ROOT})
list(APPEND IGD_EXTERNAL_LIBS ${GUM_LIBS})

string_join(IGD_EXTERNAL_LIBS_STRING " " ${IGD_EXTERNAL_LIBS})
log(info "Linking with:" ${IGD_EXTERNAL_LIBS_STRING})

set(IGD_ROOT ${CMAKE_SOURCE_DIR}/isometric/)
set(IGD_UI_ROOT ${CMAKE_SOURCE_DIR}/ui/)
set(IGD_QML_ROOT ${IGD_UI_ROOT}qml/)

set(IGD_UI_SOURCES
    backend/Launcher.cpp
    backend/TypeRegistrator.cpp
    main.cpp
)
string_prepend(IGD_UI_SOURCES ${IGD_UI_ROOT} ${IGD_UI_SOURCES})

set(IGD_RCC_RESOURCES
    ${IGD_QML_ROOT}/res.qrc
)
qt5_add_resources(IGD_RCC_SOURCES ${IGD_RCC_RESOURCES})

set(IGD_SOURCES

)
string_prepend(IGD_SOURCES ${IGD_ROOT} ${IGD_SOURCES})

dump_definitions()

add_executable(isometric ${IGD_UI_SOURCES} ${IGD_RCC_SOURCES} ${IGD_SOURCES})
set_target_properties(isometric PROPERTIES COMPILE_FLAGS ${IGD_CXX_COMPILEFLAGS})
target_link_libraries(isometric ${IGD_EXTERNAL_LIBS})

highlight_matching(${IGD_ROOT}/*.h)
highlight_matching(${IGD_ROOT}/*.cpp)
highlight_matching(${IGD_UI_ROOT}/*.h)
highlight_matching(${IGD_UI_ROOT}/*.cpp)
highlight_matching(${CMAKE_SOURCE_DIR}/*.qml)
