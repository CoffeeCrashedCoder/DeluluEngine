cmake_minimum_required(VERSION 3.31)
project(DeluluEngine VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

add_executable(DeluluEngine ${ENGINE_SOURCES})
target_include_directories(DeluluEngine PRIVATE src)
target_link_libraries(DeluluEngine PRIVATE
        glad
        glfw
        opengl32
)