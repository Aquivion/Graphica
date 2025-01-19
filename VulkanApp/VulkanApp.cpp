#include "VulkanApp.h"

const int WIDTH = 800;
const int HEIGHT = 600;

VulkanApp::VulkanApp(const std::string &appName) {
    this->initGLFW();
    this->vulkanInstance = new VulkanInstance(appName);
}

VulkanApp::~VulkanApp() { this->cleanup(); }

void VulkanApp::run() { this->mainLoop(); }

void VulkanApp::initGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize glfw");
    }

    // Define client api to GLFW_NO_API, otherwise the default API is OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window =
        glfwCreateWindow(WIDTH, HEIGHT, "Graphica", nullptr, nullptr);

    if (!window) {
        throw std::runtime_error("Failed to create window");
    }
}

void VulkanApp::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VulkanApp::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}