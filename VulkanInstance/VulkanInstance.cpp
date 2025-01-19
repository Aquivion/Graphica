
#include "VulkanInstance.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

VulkanInstance::VulkanInstance(const std::string &appName) {
    // Application information
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Get required extensions
    // GLFW requires certain extensions for Vulkan to work with a window
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions,
                                         glfwExtensions + glfwExtensionCount);
    checkExtensionSupport(extensions);

    // Vulkan instance creation info
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    // Create the Vulkan instance
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    std::cout << "Vulkan instance created successfully!" << std::endl;
}

void VulkanInstance::checkExtensionSupport(
    const std::vector<const char *> &requiredExtensions) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                           availableExtensions.data());

    for (const char *required : requiredExtensions) {
        bool found = false;
        for (const auto &extension : availableExtensions) {
            if (strcmp(required, extension.extensionName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(
                std::string("Missing required Vulkan extension: ") + required);
        }
    }
}
