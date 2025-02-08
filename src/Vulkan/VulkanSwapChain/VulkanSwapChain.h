#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>

namespace VulkanCore {

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR
        capabilities;  // includes information of range of possible resolutions for images
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanSwapChain {
   public:
    VulkanSwapChain() = default;

    void createSwapChain(VkPhysicalDevice device, VkSurfaceKHR surface, GLFWwindow* window);

   private:
    SwapChainSupportDetails swapChainSupportDetails;
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D extent;

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
};

}  // namespace VulkanCore