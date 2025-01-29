#pragma once

#include <vulkan/vulkan.h>

#include <optional>

namespace VulkanCore {

class VulkanLogicalDevice {
   public:
    VulkanLogicalDevice() = default;

    void createLogicalDevice(const VkPhysicalDevice physicalDevice);

    void cleanup();

   private:
    VkDevice logicalDevice = VK_NULL_HANDLE;
};

}  // namespace VulkanCore