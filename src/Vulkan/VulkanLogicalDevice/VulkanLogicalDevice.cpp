#include "VulkanLogicalDevice.h"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.h"

namespace VulkanCore {

void VulkanLogicalDevice::cleanup() { vkDestroyDevice(logicalDevice, nullptr); }

void VulkanLogicalDevice::createLogicalDevice(const VkPhysicalDevice physicalDevice) {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    std::cout << "Logical device creation successful!" << std::endl;
}

}  // namespace VulkanCore