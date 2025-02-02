#include "VulkanLogicalDevice.h"

#include <iostream>
#include <set>
#include <stdexcept>

#include "Vulkan/VulkanPhysicalDevice/VulkanPhysicalDevice.h"

namespace VulkanCore {

void VulkanLogicalDevice::cleanup() { vkDestroyDevice(logicalDevice, nullptr); }

void VulkanLogicalDevice::createLogicalDevice(const VulkanPhysicalDevice &device) {
    VkPhysicalDeviceFeatures deviceFeatures{};

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    const QueueFamilyIndices indices = device.getQueueFamilyIndices();
    createQueueCreateInfos(queueCreateInfos, indices);

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (vkCreateDevice(device.getPhysicalDevice(), &createInfo, nullptr, &logicalDevice) !=
        VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device!");
    }

    if (!indices.presentFamily.has_value()) {
        throw std::runtime_error("No present queue family found!");
    }

    vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentQueue);

    std::cout << "Logical device created successfully!" << std::endl;
}

void VulkanLogicalDevice::createQueueCreateInfos(
    std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos,
    const QueueFamilyIndices &indices) const {
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(),
                                              indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }
}

}  // namespace VulkanCore