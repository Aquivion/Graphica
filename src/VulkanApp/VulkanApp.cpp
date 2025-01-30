#include "VulkanApp.h"

#include <iostream>
#include <stdexcept>

const int WIDTH = 800;
const int HEIGHT = 600;
const auto PROJECT_NAME = "Graphica";

VulkanApp::VulkanApp() : vulkanCore{} {}

void VulkanApp::run() {
    initGLFW();
    initVulkan();
    mainLoop();
    cleanup();
}

void VulkanApp::initVulkan() { vulkanCore.init(window, PROJECT_NAME); }

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
    // Vulkan objects like devices and surfaces need to be destroyed before the instance is
    vulkanCore.cleanup();

    vkDestroyInstance(vulkanCore.getVkInstance(), nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();
}