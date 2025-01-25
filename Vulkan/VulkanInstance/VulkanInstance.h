#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class VulkanInstance {
   public:
    VulkanInstance() = default;
    VulkanInstance(const std::string &appName);

    VkInstance getInstance() const { return instance; }

   private:
    VkInstance instance = nullptr;
    std::vector<const char *> validationLayers;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    void checkExtensionSupport(const std::vector<const char *> &requiredExtensions);
    bool checkValidationLayerSupport();

    void setupAppInfo(VkApplicationInfo &appInfo, const std::string &appName);
    void setupCreateInfo(VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo);
    void setupValidationLayers(VkInstanceCreateInfo &createInfo);
};

#endif  // VULKAN_INSTANCE_H
