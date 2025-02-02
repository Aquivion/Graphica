#pragma once

#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

namespace VulkanCore {

class VulkanPhysicalDevice;
class QueueFamilyIndices;

class VulkanLogicalDevice {
   public:
    VulkanLogicalDevice() = default;

    void createLogicalDevice(const VulkanPhysicalDevice &device);

    void cleanup();

   private:
    VkDevice logicalDevice = VK_NULL_HANDLE;
    VkQueue presentQueue;

    void createQueueCreateInfos(std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos,
                                const QueueFamilyIndices &indices) const;
};

}  // namespace VulkanCore