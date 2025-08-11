# Specify the minimum required CMake version
cmake_minimum_required(VERSION 3.10)
# Set the project name and version
project(OpenGL_Practice VERSION 1.0.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set OpenGL Preference
# GLVID (Recommended)
set(OpenGL_GL_PREFERENCE GLVND)
# LEGACY
#set(OpenGL_GL_PREFERENCE LEGACY)

# Find the OpenGL library on the system
find_package(OpenGL REQUIRED)

# Add GLFW as a subdirectory so CMake can build it
add_subdirectory(external/glfw)

# Add GLAD source files to our project
add_library(glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    libs/glad/include
)

# Create the executable for your main application
add_executable(opengl-practice
    src/main.cpp
)

# Set include directories for your executable
target_include_directories(opengl-practice PRIVATE
    include
    libs/glad/include
    external/glfw/include
)

# Link all the necessary libraries
target_link_libraries(opengl-practice PRIVATE
    glfw
    glad
    OpenGL::GL
)