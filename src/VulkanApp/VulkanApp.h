#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "Vulkan/VulkanCore/VulkanCore.h"

class VulkanInstance;

class VulkanApp {
   public:
    VulkanApp();
    ~VulkanApp() = default;

    VulkanApp(const VulkanApp &) = delete;
    VulkanApp &operator=(const VulkanApp &) = delete;
    VulkanApp(VulkanApp &&) = delete;
    VulkanApp &operator=(VulkanApp &&) = delete;

    void run();

   private:
    GLFWwindow *window;
    VulkanCore::VulkanCore vulkanCore;

    void initGLFW();
    void initVulkan();
    void mainLoop();
    void cleanup();
};