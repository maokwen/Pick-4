# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Pick-4)

find_package(SDL2 CONFIG REQUIRED)

find_package(lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
link_directories(${LUA_LIBRARIES})

add_library(Pick4 STATIC
  Pick4.cpp
  Scene.cpp
  BitmapFont.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource/font.bmp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Pick4 PRIVATE SDL2::SDL2 SDL2::SDL2main)

add_executable(Pick4test test.cpp)
target_link_libraries(Pick4test PRIVATE SDL2::SDL2 SDL2::SDL2main Pick4)
