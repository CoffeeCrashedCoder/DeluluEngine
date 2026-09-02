cmake_minimum_required(VERSION 3.31)
project(DeluluEngine VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

add_executable(DeluluEngine ${ENGINE_SOURCES})
target_include_directories(DeluluEngine PRIVATE src)
target_link_libraries(DeluluEngine PRIVATE
        glad
        glfw
        opengl32
)