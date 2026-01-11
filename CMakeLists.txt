cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(raytracer)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include/)

enable_language(OBJCXX)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.mm)


add_executable(main ${SOURCES})

target_link_libraries(main
    ${SDL2_LIBRARIES}
    "-framework Metal"
    "-framework Foundation"
)
