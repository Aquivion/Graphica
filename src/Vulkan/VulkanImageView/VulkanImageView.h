#pragma once

#include <vulkan/vulkan.h>

namespace VulkanCore {

class VulkanSwapChain;
class VulkanLogicalDevice;

/**
 * @brief VulkanImageView class
 */
class VulkanImageView {
   public:
    VulkanImageView() = default;

    void createImageView(const VulkanLogicalDevice& device, const VulkanSwapChain& swapChain, VkImage image);
    void populateCreateInfo(VkImageViewCreateInfo& createInfo, const VulkanSwapChain& swapChain, VkImage image);
    VkImageView getImageView() const { return imageView; }

    void cleanup(VkDevice logicalDevice);

   private:
    VkImageView imageView;
};

}  // namespace VulkanCore