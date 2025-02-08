#include "VulkanCore.h"

namespace VulkanCore {

const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

VulkanCore::VulkanCore()
    : vulkanInstance{}, physicalDevice{deviceExtensions}, logicalDevice{}, surface{}, swapChain{} {}

void VulkanCore::init(GLFWwindow* window, const std::string& appName) {
    vulkanInstance.createInstance(appName);

    // The window surface has to be created before devices
    surface.createSurface(window, vulkanInstance.getInstance());
    physicalDevice.pickPhysicalDevice(vulkanInstance.getInstance(), surface.getSurface());
    logicalDevice.createLogicalDevice(physicalDevice);
    swapChain.createSwapChain(physicalDevice.getPhysicalDevice(), surface.getSurface(), window);
}

void VulkanCore::cleanup() {
    logicalDevice.cleanup();
    surface.cleanup(vulkanInstance.getInstance());
}

}  // namespace VulkanCore