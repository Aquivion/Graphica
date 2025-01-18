#include "VulkanInstance/VulkanInstance.h"
#include <vulkan/vulkan.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Window", nullptr, nullptr);

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
    glfwTerminate();

    return EXIT_SUCCESS;
}