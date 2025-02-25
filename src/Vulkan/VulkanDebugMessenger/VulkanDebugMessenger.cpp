#include "VulkanDebugMessenger.h"

#include <iostream>
#include <string>

#include "Vulkan/VulkanInstance/VulkanInstance.h"

#ifndef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

const std::vector<std::string> ignoredDebugMessages = {
    "Layer name GalaxyOverlayVkLayer does not conform to naming standard (Policy #LLP_LAYER_3)",
    "Layer name GalaxyOverlayVkLayer_VERBOSE does not conform to naming standard (Policy #LLP_LAYER_3)",
    "Layer name GalaxyOverlayVkLayer_DEBUG does not conform to naming standard (Policy #LLP_LAYER_3)"};

namespace VulkanCore {
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                             const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                             void* pUserData) {
    // Filter ignored messages
    for (const auto& message : ignoredDebugMessages) {
        if (std::string(pCallbackData->pMessage) == message) {
            return VK_FALSE;
        }
    }

    std::string severity = "Unknown Severity";
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        severity = "Diagnostic";
    } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        severity = "Info";
    } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        severity = "Warning";
    } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        severity = "Error";
    }

    if (severity == "Diagnostic") {
        return VK_FALSE;
    }

    std::string type = "Unknown Type";
    if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
        type = "General";
    } else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
        type = "Validation";
    } else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
        type = "Performance";
    }

    std::cerr << "validation layer " << type << " " << severity << ": " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}
void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

// VulkanDebugMessenger::VulkanDebugMessenger() {}

void VulkanDebugMessenger::setupDebugMessenger(VulkanInstance& instance) {
    if (!enableValidationLayers) {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);
    createInfo.pUserData = nullptr;  // Optional

    if (CreateDebugUtilsMessengerEXT(instance.getInstance(), &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void VulkanDebugMessenger::cleanup(VkInstance instance) {
    if (!enableValidationLayers) {
        return;
    }

    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
}

VkResult VulkanDebugMessenger::CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                            const VkAllocationCallbacks* pAllocator,
                                                            VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
}  // namespace VulkanCore