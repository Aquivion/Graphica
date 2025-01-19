#include "VulkanInstance/VulkanInstance.h"
#include <vulkan/vulkan.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

void cleanup(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "glfw initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    // Define client api to GLFW_NO_API, otherwise the default API is OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

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
        cleanup(window);
        return EXIT_FAILURE;
    }

    cleanup(window);

    return EXIT_SUCCESS;
}