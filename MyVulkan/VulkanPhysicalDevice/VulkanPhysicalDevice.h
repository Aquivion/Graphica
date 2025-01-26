#pragma once

#include <vulkan/vulkan.h>

#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    bool isComplete() { return graphicsFamily.has_value(); }
};

class VulkanPhysicalDevice {
   public:
    VkPhysicalDevice getPhysicalDevice() { return physicalDevice; }

   private:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    void pickPhysicalDevice(VkInstance instance);
    /**
     * @brief Checks if the physical device (graphics card) is suitable for operations that need to
     * be performed
     */
    bool isDeviceSuitable(VkPhysicalDevice device);
    /**
     * @brief Finds the supported queue families for the given device. Every command that is
     * interacting with the graphics card needs to be submitted to a queue. There are different
     * types of queues distinguished by their family. Every Queue family allows only a subset of
     * commands
     */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};