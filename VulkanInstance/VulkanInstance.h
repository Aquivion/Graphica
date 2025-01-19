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

    void checkExtensionSupport(
        const std::vector<const char *> &requiredExtensions);
};

#endif  // VULKAN_INSTANCE_H
