cmake_minimum_required(VERSION 3.31)
project(IRHomeLab)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -D__WXGTK3__ -D__WXGTK__ -D_FILE_OFFSET_BITS=64")

# Setting wxWidgets build options
set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)

# Fetching wxWidgets
include(FetchContent)
FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_TAG v3.2.9
)
FetchContent_MakeAvailable(wxwidgets)

file(GLOB_RECURSE SOURCES ./source/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ./source/include ${wxWidgets_SOURCE_DIR}/include ${wxWidgets_BINARY_DIR}/lib/wx/include/gtk3-unicode-static-3.2/)

target_link_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_BINARY_DIR}/lib/ /usr/lib/aarch64-linux-gnu/)
target_link_libraries(${PROJECT_NAME} PRIVATE wx::core wx::net wx::base X11 atomic)