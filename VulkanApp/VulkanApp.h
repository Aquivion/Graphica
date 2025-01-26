#pragma once

#include "VulkanCore/VulkanCore.h"

struct GLFWwindow;
class VulkanInstance;

class VulkanApp {
   public:
    VulkanApp();
    ~VulkanApp();

    VulkanApp(const VulkanApp &) = delete;
    VulkanApp &operator=(const VulkanApp &) = delete;
    VulkanApp(VulkanApp &&) = delete;
    VulkanApp &operator=(VulkanApp &&) = delete;

    void run();

   private:
    GLFWwindow *window;
    VulkanCore vulkanCore;

    void initGLFW();
    void mainLoop();
    void cleanup();
};