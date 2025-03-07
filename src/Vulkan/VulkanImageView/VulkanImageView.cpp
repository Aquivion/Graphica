#include "VulkanImageView.h"

#include <stdexcept>

#include "Vulkan/VulkanLogicalDevice/VulkanLogicalDevice.h"
#include "Vulkan/VulkanSwapChain/VulkanSwapChain.h"

namespace VulkanCore {

void VulkanImageView::createImageView(const VulkanLogicalDevice& device, const VulkanSwapChain& swapChain,
                                      VkImage image) {
    VkImageViewCreateInfo createInfo{};
    populateCreateInfo(createInfo, swapChain, image);

    if (vkCreateImageView(device.getLogicalDevice(), &createInfo, nullptr, &imageView) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image views!");
    }
}

void VulkanImageView::cleanup(VkDevice logicalDevice) { vkDestroyImageView(logicalDevice, imageView, nullptr); }

void VulkanImageView::populateCreateInfo(VkImageViewCreateInfo& createInfo, const VulkanSwapChain& swapChain,
                                         VkImage image) {
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = image;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = swapChain.getSurfaceFormat().format;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;
}

}  // namespace VulkanCore