cmake_minimum_required(VERSION 3.22)
project(VulkanApp)

set(CMAKE_CXX_STANDARD 17)

# Vulkan SDK
set(VULKAN_SDK "C:/VulkanSDK/1.4.304.0")
include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

# GLFW
add_subdirectory(libs/glfw)

# Collect your source files
set(SOURCES 
    main.cpp
    VulkanInstance/VulkanInstance.cpp)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Collect PRIVATE target include directories
set(PRIVATE_INCLUDE_DIRS
    ${Vulkan_INCLUDE_DIRS}
    libs/glfw/include)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDE_DIRS})

# Link GLFW and Vulkan library
target_link_libraries(${PROJECT_NAME} glfw vulkan-1)
