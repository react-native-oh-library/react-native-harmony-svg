cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

set(rnoh_svg_generated_dir "${CMAKE_CURRENT_SOURCE_DIR}/generated")
file(GLOB_RECURSE rnoh_svg_generated_SRC "${rnoh_svg_generated_dir}/**/*.cpp")
file(GLOB rnoh_svg_SRC CONFIGURE_DEPENDS
    *.cpp
    componentInstances/*.cpp
    drawing/*.cpp
    properties/*.cpp
    turboModules/*.cpp
    utils/*.cpp
    svgImage/*.cpp
    downloadUtils/*.cpp
    )
add_library(rnoh_svg SHARED ${rnoh_svg_SRC} ${rnoh_svg_generated_SRC})
target_include_directories(rnoh_svg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${rnoh_svg_generated_dir})

target_link_libraries(rnoh_svg PUBLIC rnoh)
target_link_libraries(rnoh_svg PUBLIC libimage_source.so)
target_link_libraries(rnoh_svg PUBLIC libpixelmap.so)
target_link_libraries(rnoh_svg PUBLIC libimage_packer.so)
target_link_libraries(rnoh_svg PUBLIC librawfile.z.so)
target_link_libraries(rnoh_svg PUBLIC librcp_c.so)
target_link_libraries(rnoh_svg PUBLIC libohfileuri.so)
target_link_libraries(rnoh_svg PUBLIC libdeviceinfo_ndk.z.so)
target_link_directories(rnoh_svg PUBLIC ${HMOS_SDK_NATIVE}/sysroot/usr/lib/aarch64-linux-ohos)
