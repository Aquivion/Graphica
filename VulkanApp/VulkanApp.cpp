#include "VulkanApp.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

const int WIDTH = 800;
const int HEIGHT = 600;
const auto PROJECT_NAME = "Graphica";

VulkanApp::VulkanApp() : vulkanInstance{PROJECT_NAME} {}

VulkanApp::~VulkanApp() { cleanup(); }

void VulkanApp::run() {
    initGLFW();
    mainLoop();
}

void VulkanApp::initGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize glfw");
    }

    // Define client api to GLFW_NO_API, otherwise the default API is OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);

    if (!window) {
        throw std::runtime_error("Failed to create glfw window");
    }
}

void VulkanApp::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VulkanApp::cleanup() {
    vkDestroyInstance(vulkanInstance.getInstance(), nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}