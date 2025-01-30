#include "VulkanCore.h"

namespace VulkanCore {

VulkanCore::VulkanCore() : vulkanInstance{}, physicalDevice{}, logicalDevice{}, surface{} {}

void VulkanCore::init(GLFWwindow* window, const std::string& appName) {
    vulkanInstance.createInstance(appName);

    // The window surface has to be created before devices
    surface.createSurface(window, vulkanInstance.getInstance());
    physicalDevice.pickPhysicalDevice(vulkanInstance.getInstance());
    logicalDevice.createLogicalDevice(physicalDevice.getPhysicalDevice());
}

void VulkanCore::cleanup() {
    logicalDevice.cleanup();
    surface.cleanup(vulkanInstance.getInstance());
}

}  // namespace VulkanCore