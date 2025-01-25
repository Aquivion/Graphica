#ifndef VULKAN_PHYSICAL_DEVICE
#define VULKAN_PHYISCAL_DEVICE

#include <vulkan/vulkan.h>

class VulkanPhysicalDevice {
   public:
    VkPhysicalDevice getPhysicalDevice() { return physicalDevice; }

   private:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    void pickPhysicalDevice(VkInstance instance);
};

#endif  // VULKAN_PHYSICAL_DEVICE_H