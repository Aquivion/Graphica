#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace VulkanCore {

class VulkanInstance {
   public:
    VulkanInstance() = default;

    ~VulkanInstance() = default;
    VulkanInstance(const VulkanInstance &) = delete;
    VulkanInstance &operator=(const VulkanInstance &) = delete;
    VulkanInstance(VulkanInstance &&) = delete;
    VulkanInstance &operator=(VulkanInstance &&) = delete;

    void createInstance(const std::string &appName);
    VkInstance getInstance() const;

   private:
    VkInstance instance = nullptr;
    std::vector<const char *> validationLayers;

    void checkExtensionSupport(const std::vector<const char *> &requiredExtensions);
    bool checkValidationLayerSupport();

    void setupAppInfo(VkApplicationInfo &appInfo, const std::string &appName);
    void setupCreateInfo(VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo);
    void setupValidationLayers(VkInstanceCreateInfo &createInfo);
};

}  // namespace VulkanCore