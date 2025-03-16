#include "VulkanPhysicalDevice.h"

#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

#include "Vulkan/VulkanSwapChain/VulkanSwapChain.h"

namespace VulkanCore {

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    VkBool32 presentSupport = false;

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        // Check if the device also supports a queue family that can present images to the selected
        // surface
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }
        i++;
    }

    return indices;
}

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

VulkanPhysicalDevice::VulkanPhysicalDevice(const std::vector<const char*>& requiredDeviceExtensions)
    : requiredExtensions(requiredDeviceExtensions) {}

void VulkanPhysicalDevice::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device, surface)) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    std::cout << "Selected GPU: " << deviceProperties.deviceName << std::endl;

    indices = findQueueFamilies(physicalDevice, surface);
}

/**
 * See https://shorturl.at/BKkJU in the Vulkan tutorial, on how to select devices that
 * fullfill specifc features and properties that the application needs
 */
bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices = findQueueFamilies(device, surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);
    if (!extensionsSupported) {
        return false;
    }

    bool swapChainAdequate = false;
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
    swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool VulkanPhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> required(requiredExtensions.begin(), requiredExtensions.end());

    for (const auto& extension : availableExtensions) {
        required.erase(extension.extensionName);
        if (required.empty()) {
            break;
        }
    }

    return required.empty();
}

}  // namespace VulkanCore