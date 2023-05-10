project(rnapp)
cmake_minimum_required(VERSION 3.4.1)
set(NODE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../node_modules")
set(RNOH_APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(RNOH_CPP_DIR "${NODE_MODULES_DIR}/@ohos/rnoh/src/main/cpp")

add_subdirectory("${RNOH_CPP_DIR}" ./rn)
add_subdirectory("${NODE_MODULES_DIR}/@ohos/rnoh-svg/src/main/cpp" ./svg)
add_library(rnoh_app SHARED
    "./PackageProvider.cpp"
    "${RNOH_CPP_DIR}/RNOHAppNapiBridge.cpp"
)
target_link_libraries(rnoh_app PUBLIC rnoh)
target_link_libraries(rnoh_app PUBLIC rnoh_svg)





