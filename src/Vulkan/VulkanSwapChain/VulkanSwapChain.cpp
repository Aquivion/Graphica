#include "VulkanSwapChain.h"

#include <algorithm>

#include "Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.h"

namespace VulkanCore {

void VulkanSwapChain::createSwapChain(VkPhysicalDevice device, VkSurfaceKHR surface,
                                      GLFWwindow* window) {
    swapChainSupportDetails = querySwapChainSupport(device, surface);
    surfaceFormat = chooseSwapSurfaceFormat(swapChainSupportDetails.formats);
    presentMode = chooseSwapPresentMode(swapChainSupportDetails.presentModes);
    extent = chooseSwapExtent(swapChainSupportDetails.capabilities, window);
}

VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(
    const std::vector<VkPresentModeKHR>& availablePresentModes) {
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,
                                             GLFWwindow* window) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                                    capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                                     capabilities.maxImageExtent.height);
    return actualExtent;
}

}  // namespace VulkanCore