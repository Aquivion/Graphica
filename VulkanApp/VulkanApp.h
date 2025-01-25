#ifndef VULKAN_APP
#define VULKAN_APP

#include "VulkanInstance/VulkanInstance.h"

struct GLFWwindow;
class VulkanInstance;

class VulkanApp {
   public:
    VulkanApp();
    ~VulkanApp();

    void run();

   private:
    GLFWwindow* window;
    VulkanInstance vulkanInstance;

    void initVulkan();
    void initGLFW();
    void mainLoop();
    void cleanup();
};

#endif  // VULKAN_APP_H