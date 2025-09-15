cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest  # or specify a version like 3.3.9
)
FetchContent_MakeAvailable(glfw)

# Find OpenGL
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
        src/component.cpp
        src/entity.cpp
        src/rigidbody.cpp
        src/time.cpp
        src/scene.cpp
        src/box_collider.cpp
        src/component_factory.cpp
        src/playercontroller.cpp
)

# Include directories
target_include_directories(Engine PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/glad
        ${CMAKE_SOURCE_DIR}/include/khr
        ${CMAKE_SOURCE_DIR}/include/stb
        ${CMAKE_SOURCE_DIR}/include/glm
)

# Link libraries
target_link_libraries(Engine PRIVATE
        glfw
        OpenGL::GL
        pthread
)

# Define project directory macro
target_compile_definitions(Engine PRIVATE
        PROJECT_DIR="${CMAKE_SOURCE_DIR}"
)
