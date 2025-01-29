#include "VulkanCore.h"

namespace VulkanCore {

VulkanCore::VulkanCore(const std::string &appName)
    : vulkanInstance{appName}, physicalDevice{}, logicalDevice{} {
    init();
}

void VulkanCore::init() {
    physicalDevice.pickPhysicalDevice(vulkanInstance.getInstance());
    logicalDevice.createLogicalDevice(physicalDevice.getPhysicalDevice());
}

void VulkanCore::cleanup() {}

}  // namespace VulkanCore