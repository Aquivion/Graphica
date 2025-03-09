# Graphica - Lightweight Graphics Engine

A lightweight graphics engine build with C++ and Vulkan. It is for game developers who are seeking to build games from scratch with C++ but don't want to deal with the complex Vulkan eco-system directly

## Setup instructions (Windows)

These instructions will guide you setting up the Graphica project on your local machine for development

### Prerequisites

Before you start, ensure you have the following installed:

- **CMake (version 3.22 or higher):** Required for building the project.
  - [CMake Download](https://cmake.org/download/)
- **Vulkan SDK (version 1.4.304.0):** The Vulkan SDK provides the necessary tools and libraries for Vulkan development.
  - Download the appropriate version from the [Vulkan SDK website](https://vulkan.lunarg.com/). Make sure to download version `1.4.304.0` to avoid compatibility issues.
- **A C++ compiler that supports C++17:** For example, GCC, Clang, or MSVC, for example from [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
- **Git:** For cloning the repository.

### External Dependencies

Before building the project, you need to download GLFW and GLM into a `libs` folder at the root of the project.

1. **Create the `libs` folder (if it doesn't already exist):**

   ```bash
   mkdir libs
   ```

2. **Clone GLFW:**

   ```bash
   git clone https://github.com/glfw/glfw.git libs/glfw
   ```

3. **Clone GLM:**

   ```bash
   git clone https://github.com/g-truc/glm.git libs/glm
   ```

After cloning these repositories, re-run CMake so that it picks up the new libraries then launch the project. If you cannot find any errors in the terminal, you are ready to go :rocket:
