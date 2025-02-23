#pragma once

#include <vulkan/vulkan.h>

namespace VulkanCore {

class VulkanSwapChain;
class VulkanLogicalDevice;

/**
 * @brief VulkanImageView class
 *
 * This class encapsulates the creation and management of a Vulkan image view.
 * An image view is used to specify how an image resource should be accessed and used (e.g 2D texture, 3D texture,
 * depth-stencil texture, etc.)
 */
class VulkanImageView {
   public:
    VulkanImageView() = default;

    /**
     * @brief Creates an image view for a given image.
     *
     * @param device The logical device to use for creating the image view.
     * @param swapChain The swap chain associated with the image.
     * @param image The Vulkan image for which the view is created.
     */
    void createImageView(const VulkanLogicalDevice& device, const VulkanSwapChain& swapChain, VkImage image);

    /**
     * @brief Populates the VkImageViewCreateInfo structure with the necessary information.
     *
     * @param createInfo The structure to populate.
     * @param swapChain The swap chain associated with the image.
     * @param image The Vulkan image for which the view is created.
     */
    void populateCreateInfo(VkImageViewCreateInfo& createInfo, const VulkanSwapChain& swapChain, VkImage image);

    /**
     * @brief Returns the Vulkan image view handle.
     *
     * @return VkImageView The handle to the Vulkan image view.
     */
    VkImageView getImageView() const { return imageView; }

    /**
     * @brief Cleans up the Vulkan image view.
     *
     * @param logicalDevice The logical device used to destroy the image view.
     */
    void cleanup(VkDevice logicalDevice);

   private:
    VkImageView imageView;  // The handle to the Vulkan image view.
};

}  // namespace VulkanCore