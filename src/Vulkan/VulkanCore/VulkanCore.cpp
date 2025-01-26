#include "VulkanCore.h"

VulkanCore::VulkanCore(const std::string &appName)
    : vulkanInstance{appName}, vulkanPhysicalDevice{} {}

void VulkanCore::init() { vulkanPhysicalDevice.pickPhysicalDevice(vulkanInstance.getInstance()); }