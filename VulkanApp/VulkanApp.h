#include <vulkan/vulkan.h>

#include <iostream>

#include "../VulkanInstance/VulkanInstance.h"

class VulkanApp {
   public:
    VulkanApp(const std::string &appName);
    ~VulkanApp();

    void run();

   private:
    GLFWwindow *window;
    VulkanInstance *vulkanInstance;

    void initGLFW();
    void mainLoop();
    void cleanup();
};