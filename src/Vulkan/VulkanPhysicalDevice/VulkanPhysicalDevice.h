#pragma once

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

namespace VulkanCore {

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

class SwapChainSupportDetails;

/**
 * @brief Finds the supported queue families for the given device. Every command that is
 * interacting with the graphics card needs to be submitted to a queue. There are different
 * types of queues distinguished by their family. Every Queue family allows only a subset of
 * commands
 */
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

class VulkanPhysicalDevice {
   public:
    VulkanPhysicalDevice() = default;
    VulkanPhysicalDevice(const std::vector<const char*>& requiredDeviceExtensions);

    void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }

    const QueueFamilyIndices& getQueueFamilyIndices() const { return indices; }

    const std::vector<const char*>& getRequiredExtensions() const { return requiredExtensions; }

   private:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    VkPhysicalDeviceProperties deviceProperties;

    QueueFamilyIndices indices;

    const std::vector<const char*> requiredExtensions;

    /**
     * @brief Checks if the physical device (graphics card) is suitable for operations that need to
     * be performed
     */
    bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

    int rateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};

}  // namespace VulkanCore