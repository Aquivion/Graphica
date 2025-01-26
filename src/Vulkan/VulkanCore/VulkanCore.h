#pragma once

#include "Vulkan/VulkanDevices/VulkanDevices.h"
#include "Vulkan/VulkanInstance/VulkanInstance.h"
#include "vulkan/vulkan.h"

/**
 * @brief The Vulkan Core that manages all Vulkan related objects and features
 */
class VulkanCore {
   public:
    VulkanCore() = default;
    VulkanCore(const std::string &appName);

    VkInstance getVkInstance() { return vulkanInstance.getInstance(); }

   private:
    void init();

    VulkanInstance vulkanInstance;
    VulkanPhysicalDevice vulkanPhysicalDevice;
};