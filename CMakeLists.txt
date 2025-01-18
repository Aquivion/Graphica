cmake_minimum_required(VERSION 3.10)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 17)

# Project path
set(PROJECT_PATH "C:/Users/tobaz/Entwicklung/Graphica")

# Vulkan SDK
set(VULKAN_SDK "C:/VulkanSDK/1.4.304.0")
include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

# GLFW
set(GLFW_PATH "C:/Users/tobaz/Entwicklung/Graphica/libs/glfw")
include_directories(${GLFW_PATH}/include)
link_directories(${GLFW_PATH}/build/src)

# Executable
add_executable(${PROJECT_NAME} main.cpp VulkanInstance/VulkanInstance.cpp)

# Link GLFW and Vulkan library
target_link_libraries(${PROJECT_NAME} glfw3 vulkan-1)
