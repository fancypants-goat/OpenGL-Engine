cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(.)
include_directories(include)
include_directories(include/glad)
include_directories(include/khr)
include_directories(include/stb)
include_directories(Resources)

add_executable(Engine
        camera.cpp
        camera.h
        glad.c
        main.cpp
        shader.cpp
        shader.h
        stb_image.cpp
        texture.cpp
        texture.h
        vertex.h
        resources.cpp
        resources.h
        input.cpp
        input.h
        mouse.cpp
        mouse.h
        mesh_group.cpp
        mesh_group.h
        mesh.cpp
        mesh.h
        transform.cpp
        transform.h
)

target_link_libraries(Engine
        glfw
        OpenGL::GL
        dl
        pthread
)


add_definitions(-DPROJECT_DIR="${CMAKE_SOURCE_DIR}")
