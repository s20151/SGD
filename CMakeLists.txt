cmake_minimum_required(VERSION 3.21)
project(SDL_PROJECT)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_INCLUDE_DIR C:/Users/admin/Desktop/SDL/include)
set(SDL2_LIB_DIR DIR C:/Users/admin/Desktop/SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(SDL_PROJECT src/main.cpp src/RenderWindow.cpp include/RenderWindow.hpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 )