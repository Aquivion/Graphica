#include <iostream>

#include "../VulkanInstance/VulkanInstance.h"

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