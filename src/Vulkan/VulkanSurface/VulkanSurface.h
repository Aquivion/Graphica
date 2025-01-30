#pragma once

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif

#include <GLFW/glfw3.h>

namespace VulkanCore {

class VulkanSurface {
   public:
    VulkanSurface() = default;

    void createSurface(GLFWwindow* window, VkInstance instance);

    VkSurfaceKHR getSurface() const { return surface; }

    void cleanup(VkInstance instance);

   private:
    VkSurfaceKHR surface;
};

}  // namespace VulkanCore