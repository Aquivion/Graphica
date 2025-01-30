#include "VulkanSurface.h"

#include <iostream>

namespace VulkanCore {

void VulkanSurface::createSurface(GLFWwindow* window, VkInstance instance) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void VulkanSurface::cleanup(VkInstance instance) {
    vkDestroySurfaceKHR(instance, surface, nullptr);
}

}  // namespace VulkanCore