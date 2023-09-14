cmake_minimum_required(VERSION 3.27.4)
add_definitions(-std=c++23)
project(snake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
file(GLOB files_snake CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(snake ${files_snake})
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(snake ${SDL2_LIBRARIES})