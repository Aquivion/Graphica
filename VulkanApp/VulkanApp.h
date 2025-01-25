#ifndef VULKAN_APP
#define VULKAN_APP

#include "VulkanInstance/VulkanInstance.h"

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
    VulkanInstance vulkanInstance;

    void initGLFW();
    void mainLoop();
    void cleanup();
};

#endif  // VULKAN_APP_H