# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Pick-4)

find_package(SDL2 CONFIG REQUIRED)

find_package(lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

find_package(sol2 CONFIG REQUIRED)
include_directories(${SOL2_INCLUDE_DIRS})
link_directories(${SOL2_LIBRARIES})

add_executable(Pick4 
  test.cpp
  Pick4.cpp
  Scene.cpp
  BitmapFont.cpp
  FileSystem.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/asserts/font.bmp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/asserts/hello.p4
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

target_link_libraries(Pick4 PRIVATE SDL2::SDL2 SDL2::SDL2main ${LUA_LIBRARIES} sol2)

