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
    void cleanup();
    VkInstance getInstance() const;

   private:
    VkInstance instance = nullptr;
    std::vector<const char *> validationLayers;

    void checkExtensionSupport(const std::vector<const char *> &requiredExtensions);
    bool checkValidationLayerSupport();

    void setupAppInfo(VkApplicationInfo &appInfo, const std::string &appName);
    void setupCreateInfo(VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo,
                         const std::vector<const char *> &extensions);
    void setupValidationLayers(VkInstanceCreateInfo &createInfo, VkDebugUtilsMessengerCreateInfoEXT &debugCreateInfo);

    std::vector<const char *> getRequiredExtensions();
};

}  // namespace VulkanCore