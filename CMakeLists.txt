set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.15)
project(UPPS)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC src/*.cpp)
set(GLAD_SRC external/glad/glad.c)

include_directories(
    external/glad/include
    include
)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} ${SRC} ${GLAD_SRC})

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
)

