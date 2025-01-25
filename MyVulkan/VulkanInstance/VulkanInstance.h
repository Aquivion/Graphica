#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>

#include <string>
#include <vector>

class VulkanInstance {
   public:
    VulkanInstance() = default;
    VulkanInstance(const std::string &appName);

    ~VulkanInstance() = default;
    VulkanInstance(const VulkanInstance &) = delete;
    VulkanInstance &operator=(const VulkanInstance &) = delete;
    VulkanInstance(VulkanInstance &&) = delete;
    VulkanInstance &operator=(VulkanInstance &&) = delete;

    VkInstance getInstance() const { return instance; }

   private:
    VkInstance instance = nullptr;
    std::vector<const char *> validationLayers;

    void checkExtensionSupport(const std::vector<const char *> &requiredExtensions);
    bool checkValidationLayerSupport();

    void setupAppInfo(VkApplicationInfo &appInfo, const std::string &appName);
    void setupCreateInfo(VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo);
    void setupValidationLayers(VkInstanceCreateInfo &createInfo);
};

#endif  // VULKAN_INSTANCE_H
