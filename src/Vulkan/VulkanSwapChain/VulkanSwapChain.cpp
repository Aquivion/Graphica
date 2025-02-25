#include "VulkanSwapChain.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.h"

namespace VulkanCore {

void VulkanSwapChain::createSwapChain(VulkanPhysicalDevice& device, VkDevice logicalDevice, VkSurfaceKHR surface,
                                      GLFWwindow* window) {
    swapChainSupportDetails = querySwapChainSupport(device.getPhysicalDevice(), surface);
    surfaceFormat = chooseSwapSurfaceFormat(swapChainSupportDetails.formats);
    presentMode = chooseSwapPresentMode(swapChainSupportDetails.presentModes);
    extent = chooseSwapExtent(swapChainSupportDetails.capabilities, window);

    VkSwapchainCreateInfoKHR createInfo{};
    initCreateInfo(createInfo, surface, device);

    if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    uint32_t imageCount;
    vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, swapChainImages.data());

    std::cout << "Swap chain created successfully!" << std::endl;
}

void VulkanSwapChain::cleanup(VkDevice logicalDevice) { vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr); }

void VulkanSwapChain::initCreateInfo(VkSwapchainCreateInfoKHR& info, VkSurfaceKHR surface,
                                     VulkanPhysicalDevice& device) {
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.surface = surface;

    uint32_t imageCount = swapChainSupportDetails.capabilities.minImageCount + 1;
    if (swapChainSupportDetails.capabilities.maxImageCount > 0 &&
        imageCount > swapChainSupportDetails.capabilities.maxImageCount) {
        imageCount = swapChainSupportDetails.capabilities.maxImageCount;
    }
    info.minImageCount = imageCount;
    info.imageFormat = surfaceFormat.format;
    info.imageColorSpace = surfaceFormat.colorSpace;
    info.imageExtent = extent;

    info.imageArrayLayers = 1;  // Always 1 unless stereoscopic 3D application

    // Render directly to images, use VK_IMAGE_USAGE_TRANSFER_DST_BIT if you want to render to a
    // separate image first and then copy it to the swap chain image (post-processing)
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = device.getQueueFamilyIndices();
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        info.queueFamilyIndexCount = 2;
        info.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        info.queueFamilyIndexCount = 0;
        info.pQueueFamilyIndices = nullptr;
    }

    info.preTransform = swapChainSupportDetails.capabilities.currentTransform;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.presentMode = presentMode;
    info.clipped = VK_TRUE;  // Ignore pixels that are obscured (by e.g another window)

    // If the swap chain becomes invalid, e.g. because the window was resized, a new swap chain
    // needs to be created and the old one needs to be referenced here. For now we assume to always
    // have only one swap chain
    info.oldSwapchain = VK_NULL_HANDLE;
}

VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

    actualExtent.width =
        std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height =
        std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    return actualExtent;
}

}  // namespace VulkanCore