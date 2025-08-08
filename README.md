# C++ OpenGL Template Project

This repository provides a robust, multiplatform template for creating C++ applications with OpenGL. It is configured to use modern tools and best practices, making it easy to get started with graphics programming on Windows, macOS, and Linux.

## Features

GLFW: For creating windows, handling user input (keyboard, mouse), and managing OpenGL contexts.

GLAD: An OpenGL loader that correctly loads all OpenGL functions for your specific version and profile.

CMake: A powerful, multiplatform build system that generates native project files for various IDEs and build tools.

Git Submodules: GLFW is included as a Git submodule, ensuring a consistent version of the library for all collaborators.

## Prerequisites

Before you begin, ensure you have the following installed:

- A C++ Compiler: A modern compiler that supports C++17 (e.g., GCC, Clang, MSVC).

- CMake: Version 3.10 or higher.

- Git: To clone the repository and its submodules.

## Getting Started

Follow these steps to set up and build the project on your machine.

### Step 1: Clone the Repository

Clone the repository and initialize the Git submodule for GLFW.
Bash

git clone --recursive <https://github.com/your-username/your-repository-name.git>
cd your-repository-name

```Note: The --recursive flag clones the repository and its submodules in a single command. If you already cloned without it, run git submodule update --init from the project's root directory.```

### Step 2: Configure and Build with CMake

The project uses an out-of-source build, which means all generated build files are placed in a separate directory to keep your source tree clean.
Bash

### Create a build directory

```bash []
    mkdir build
    cd build
```

### Configure the project with CMake

```bash []
    cmake ..
```

### Build the project (use -jN for parallel builds, e.g., -j4)

```bash []
    cmake --build .
```

### Step 3: Run the Executable

After a successful build, you will find the executable in the build/ directory.
Bash

### On Linux/macOS

```bash []
    ./my-opengl-project
```

### On Windows

```cmd []
    my-opengl-project.exe
```

## Working with IDEs

The strength of CMake is its ability to generate project files for various development environments.

- Visual Studio: Open the project's root folder in Visual Studio, and it will automatically detect and configure the CMake project.

- VS Code: Install the "CMake Tools" extension. Open the project folder, and the extension will handle the configuration.

- CLion: Open the project folder directly. CLion has native and seamless support for CMake projects.

## Project Structure

This project follows a conventional directory structure to keep things organized:

```src/:``` Your main application source files (.cpp).

```include/:``` Your custom header files (.h, .hpp).

```libs/glad/:``` Contains the manually downloaded GLAD source and header files.

```external/glfw/:``` The GLFW library, managed as a Git submodule.

```build/:``` All generated build files. This directory is ignored by Git.

```CMakeLists.txt:``` The main build script for the project.

```bash[]
my-opengl-project/
├── .git/
├── .gitignore
├── CMakeLists.txt
├── README.md
├── src/
│   └── main.cpp
├── include/
│   └── (Your custom headers)
├── libs/
│   ├── glad/
│   │   ├── include/
│   │   │   └── glad/
│   │   │       └── gl.h
│   │   └── src/
│   │       └── glad.c
├── external/
│   └── glfw/
│       ├── (GLFW repository contents)
└── build/
    └── (Generated files, ignored by Git)
```
