#include <vulkan/vulkan.h>
#include <iostream>

int main()
{
    // Vulkan instance creation info
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Test";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Create Vulkan instance
    VkInstance instance;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Vulkan instance created successfully!" << std::endl;

    // Clean up Vulkan instance
    vkDestroyInstance(instance, nullptr);

    return EXIT_SUCCESS;
}
