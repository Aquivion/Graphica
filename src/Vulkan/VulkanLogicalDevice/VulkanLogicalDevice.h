#pragma once

#include <vulkan/vulkan.h>

#include <optional>

namespace VulkanCore {

class VulkanPhysicalDevice;

class VulkanLogicalDevice {
   public:
    VulkanLogicalDevice() = default;

    void createLogicalDevice(const VulkanPhysicalDevice &device);

    void cleanup();

   private:
    VkDevice logicalDevice = VK_NULL_HANDLE;
};

}  // namespace VulkanCore