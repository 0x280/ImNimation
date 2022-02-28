cmake_minimum_required(VERSION 3.0)

project(anim_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}" )

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.hpp" "src/*.cpp")
file(GLOB_RECURSE PROJECT_INCLUDE_FILES "include/*.h" "include/*.hpp")

set( VENDOR_PATH "${CMAKE_SOURCE_DIR}/vendor")
set( IMGUI_BASE_PATH "${VENDOR_PATH}/imgui" )
set(
    IMGUI_FILES
    "${IMGUI_BASE_PATH}/backends/imgui_impl_dx11.cpp"
    "${IMGUI_BASE_PATH}/backends/imgui_impl_dx11.h"
    "${IMGUI_BASE_PATH}/backends/imgui_impl_win32.cpp"
    "${IMGUI_BASE_PATH}/backends/imgui_impl_win32.h"
    "${IMGUI_BASE_PATH}/imconfig.h"
    "${IMGUI_BASE_PATH}/imgui.cpp"
    "${IMGUI_BASE_PATH}/imgui.h"
    "${IMGUI_BASE_PATH}/imgui_demo.cpp"
    "${IMGUI_BASE_PATH}/imgui_draw.cpp"
    "${IMGUI_BASE_PATH}/imgui_internal.h"
    "${IMGUI_BASE_PATH}/imgui_tables.cpp"
    "${IMGUI_BASE_PATH}/imgui_widgets.cpp"
    "${IMGUI_BASE_PATH}/imstb_rectpack.h"
    "${IMGUI_BASE_PATH}/imstb_textedit.h"
    "${IMGUI_BASE_PATH}/imstb_truetype.h"
)

enable_language("RC")

add_executable(anim_test WIN32 "include/resources/resource.rc" "${PROJECT_SOURCE_FILES}" "${PROJECT_INCLUDE_FILES}" "${IMGUI_FILES}")

target_include_directories(anim_test PRIVATE "include/resources" "include/" "${IMGUI_BASE_PATH}" "${IMGUI_BASE_PATH}/backends")
target_link_directories(anim_test PRIVATE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" "${CMAKE_SOURCE_DIR}/dep/lib")
target_link_libraries(anim_test "d3d11" "d3dcompiler")