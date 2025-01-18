cmake_minimum_required(VERSION 3.10)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 17)

# Vulkan SDK paths
set(VULKAN_SDK "C:/VulkanSDK/1.4.304.0")

include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

# Link Vulkan library
target_link_libraries(${PROJECT_NAME} vulkan-1)
