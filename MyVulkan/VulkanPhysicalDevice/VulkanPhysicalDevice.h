#pragma once

#include <vulkan/vulkan.h>

class VulkanPhysicalDevice {
   public:
    VkPhysicalDevice getPhysicalDevice() { return physicalDevice; }

   private:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    void pickPhysicalDevice(VkInstance instance);
    bool isDeviceSuitable(VkPhysicalDevice device);
};