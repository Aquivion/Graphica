
#include "VulkanInstance.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#ifndef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

namespace VulkanCore {

void VulkanInstance::createInstance(const std::string &appName) {
    VkApplicationInfo appInfo{};
    setupAppInfo(appInfo, appName);

    VkInstanceCreateInfo createInfo{};
    setupCreateInfo(createInfo, appInfo);
    setupValidationLayers(createInfo);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    std::cout << "Vulkan instance created successfully!" << std::endl;
}

void VulkanInstance::setupAppInfo(VkApplicationInfo &appInfo, const std::string &appName) {
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
}

void VulkanInstance::setupCreateInfo(VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo) {
    // GLFW requires certain extensions for Vulkan to work with a window
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    checkExtensionSupport(extensions);

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
}

void VulkanInstance::checkExtensionSupport(const std::vector<const char *> &requiredExtensions) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    for (const char *required : requiredExtensions) {
        bool found = false;
        for (const auto &extension : availableExtensions) {
            if (strcmp(required, extension.extensionName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(std::string("Missing required Vulkan extension: ") + required);
        }
    }
}

void VulkanInstance::setupValidationLayers(VkInstanceCreateInfo &createInfo) {
    // todo: See
    // https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/00_Setup/02_Validation_layers.html
    // to setup a callback function to manage error messages

    validationLayers = {"VK_LAYER_KHRONOS_validation"};

    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
}

bool VulkanInstance::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : validationLayers) {
        bool layerFound = false;

        for (const auto &layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            std::cout << "Validation layer: " << layerName << " not found!" << std::endl;
            return false;
        }
    }
}

VkInstance VulkanInstance::getInstance() const {
    if (instance == VK_NULL_HANDLE) {
        throw std::runtime_error("Trying to access uninitialized vulkan instance!");
    }

    return instance;
}

}  // namespace VulkanCore