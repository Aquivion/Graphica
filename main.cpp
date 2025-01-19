#include "VulkanInstance/VulkanInstance.h"
#include <vulkan/vulkan.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

void cleanup()
{
    glfwTerminate();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "glfw initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Window", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "window initialization failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    try
    {
        VulkanInstance vulkanInstance("My Vulkan App");

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    glfwDestroyWindow(window);
    cleanup();

    return EXIT_SUCCESS;
}