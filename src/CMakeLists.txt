cmake_minimum_required(VERSION 3.10)

project(raycast_sdl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 CONFIG REQUIRED COMPONENTS SDL3-shared)

add_executable(nf_raycast main.c)

target_link_libraries(nf_raycast SDL3::SDL3)

target_include_directories(nf_raycast PUBLIC ${SDL3_INCLUDE_DIRS})
