#pragma once

#include "Vulkan/VulkanInstance/VulkanInstance.h"
#include "Vulkan/VulkanLogicalDevice/VulkanLogicalDevice.h"
#include "Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.h"
#include "vulkan/vulkan.h"

namespace VulkanCore {

class VulkanCore {
   public:
    VulkanCore() = default;
    VulkanCore(const std::string &appName);

    VkInstance getVkInstance() { return vulkanInstance.getInstance(); }

    void cleanup();

   private:
    void init();

    VulkanInstance vulkanInstance;
    VulkanPhysicalDevice physicalDevice;
    VulkanLogicalDevice logicalDevice;
};

}  // namespace VulkanCore