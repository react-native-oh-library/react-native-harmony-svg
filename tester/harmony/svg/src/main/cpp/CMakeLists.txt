cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB rnoh_svg_SRC CONFIGURE_DEPENDS
    *.cpp
    componentInstances/*.cpp
    componentBinders/*.cpp
    drawing/*.cpp
    napiBinders/*.cpp
    properties/*.cpp
    turboModules/*.cpp
    utils/*.cpp
    )
add_library(rnoh_svg SHARED ${rnoh_svg_SRC})
target_include_directories(rnoh_svg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rnoh_svg PUBLIC rnoh)