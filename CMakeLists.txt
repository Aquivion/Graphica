cmake_minimum_required(VERSION 3.22)
project(VulkanTest)

set(CMAKE_CXX_STANDARD 17)

# Vulkan SDK
set(VULKAN_SDK "C:/VulkanSDK/1.4.304.0")
include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

add_subdirectory(libs/glfw)


# Executable
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE libs/glfw/include)

# Link GLFW and Vulkan library
target_link_libraries(${PROJECT_NAME} glfw vulkan-1)
