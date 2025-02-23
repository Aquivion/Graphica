cmake_minimum_required(VERSION 3.22)
project(Graphica)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Vulkan SDK
set(VULKAN_SDK "C:/VulkanSDK/1.4.304.0")
include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

# GLFW
add_subdirectory(libs/glfw)

# GLM
add_subdirectory(libs/glm)

# Collect your source files
set(SOURCES 
    src/main.cpp
    src/Utils/Utils.cpp
    src/VulkanApp/VulkanApp.cpp
    src/Vulkan/VulkanCore/VulkanCore.cpp
    src/Vulkan/VulkanInstance/VulkanInstance.cpp
    src/Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.cpp
    src/Vulkan/VulkanLogicalDevice/VulkanLogicalDevice.cpp
    src/Vulkan/VulkanSurface/VulkanSurface.cpp
    src/Vulkan/VulkanSwapchain/VulkanSwapchain.cpp
    src/Vulkan/VulkanDebugMessenger/VulkanDebugMessenger.cpp
    src/Vulkan/VulkanImageView/VulkanImageView.cpp
    src/Vulkan/VulkanGraphicsPipeline/VulkanGraphicsPipeline.cpp
    src/Vulkan/VulkanShaderModule/VulkanShaderModule.cpp)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Collect PRIVATE target include directories
set(PRIVATE_INCLUDE_DIRS
    ${Vulkan_INCLUDE_DIRS}
    libs/glfw/include)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDE_DIRS} ./src/)

# Link GLFW and Vulkan library
target_link_libraries(${PROJECT_NAME} glfw vulkan-1 glm::glm)
