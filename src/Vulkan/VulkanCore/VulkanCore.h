#pragma once

#include "Vulkan/VulkanInstance/VulkanInstance.h"
#include "Vulkan/VulkanLogicalDevice/VulkanLogicalDevice.h"
#include "Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanSurface/VulkanSurface.h"
#include "Vulkan/VulkanSwapChain/VulkanSwapChain.h"
#include "vulkan/vulkan.h"

namespace VulkanCore {

class VulkanCore {
   public:
    VulkanCore();

    ~VulkanCore() = default;
    VulkanCore(const VulkanCore &) = delete;
    VulkanCore &operator=(const VulkanCore &) = delete;
    VulkanCore(VulkanCore &&) = delete;
    VulkanCore &operator=(VulkanCore &&) = delete;

    VkInstance getVkInstance() { return vulkanInstance.getInstance(); }

    void init(GLFWwindow *window, const std::string &appName);

    void cleanup();

   private:
    VulkanInstance vulkanInstance;
    VulkanPhysicalDevice physicalDevice;
    VulkanLogicalDevice logicalDevice;
    VulkanSurface surface;
    VulkanSwapChain swapChain;
};

}  // namespace VulkanCore