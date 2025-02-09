#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>

namespace VulkanCore {

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;  // includes information of range of possible resolutions for images
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanPhysicalDevice;

class VulkanSwapChain {
   public:
    VulkanSwapChain() = default;

    void createSwapChain(VulkanPhysicalDevice& device, VkDevice logicalDevice, VkSurfaceKHR surface,
                         GLFWwindow* window);

    void cleanup(VkDevice logicalDevice);

   private:
    VkSwapchainKHR swapChain;
    SwapChainSupportDetails swapChainSupportDetails;
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D extent;
    std::vector<VkImage> swapChainImages;

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

    void initCreateInfo(VkSwapchainCreateInfoKHR& info, VkSurfaceKHR surface, VulkanPhysicalDevice& device);
};

}  // namespace VulkanCore