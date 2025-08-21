cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Executable
add_executable(Engine
        main.cpp
        src/glad.c
        src/camera.cpp
        src/input.cpp
        src/mesh.cpp
        src/mesh_renderer.cpp
        src/mouse.cpp
        src/resources.cpp
        src/shader.cpp
        src/sol.cpp
        src/stb_image.cpp
        src/texture.cpp
        src/transform.cpp
        src/submesh.cpp
)

# Include directories (scoped to this target)
target_include_directories(Engine PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/glad
        ${CMAKE_SOURCE_DIR}/include/khr
        ${CMAKE_SOURCE_DIR}/include/stb
)

# Link libraries
target_link_libraries(Engine PRIVATE
        glfw
        OpenGL::GL
        dl
        pthread
)

# Define macro so you can do e.g. load shaders relative to project root
target_compile_definitions(Engine PRIVATE
        PROJECT_DIR="${CMAKE_SOURCE_DIR}"
)
