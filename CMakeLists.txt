cmake_minimum_required(VERSION 3.10)
project(MySDL2Project)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(MySDL2Project main.cpp)

# Link SDL2 libraries to your executable
target_link_libraries(MySDL2Project ${SDL2_LIBRARIES})
