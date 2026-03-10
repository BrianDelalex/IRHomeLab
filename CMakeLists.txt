cmake_minimum_required(VERSION 3.31)
project(IRHomeLab)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -D__WXGTK3__ -D__WXGTK__ -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL")

message(INFO "sysroot ${CMAKE_SYSROOT}")

add_subdirectory(RemoteControllerMock)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES ./source/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(GLOB_RECURSE DEBUG_SOURCES ./source/debug_src/*.cpp)
    target_sources(${PROJECT_NAME} PRIVATE ${DEBUG_SOURCES})
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
target_compile_options(${PROJECT_NAME} PRIVATE
    "-idirafter${CMAKE_SYSROOT}/usr/include"
    "-idirafter${CMAKE_SYSROOT}/usr/include/aarch64-linux-gnu")

target_include_directories(${PROJECT_NAME} PRIVATE
    ./source/include
    ./third_party/cpp-httplib
    ./third_party/nlohmann_json/single_include
    ${CMAKE_SYSROOT}/usr/include/wx-3.2
    ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/wx/include/gtk3-unicode-3.2)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SYSROOT}/lib/aarch64-linux-gnu
    ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu)

target_link_libraries(${PROJECT_NAME} PRIVATE
    X11
    atomic
    ssl
    crypto
    wx_gtk3u_xrc-3.2
    wx_gtk3u_html-3.2
    wx_gtk3u_qa-3.2
    wx_gtk3u_core-3.2
    wx_baseu_xml-3.2
    wx_baseu_net-3.2
    wx_baseu-3.2 )
