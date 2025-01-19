#include "VulkanApp.h"

const int WIDTH = 800;
const int HEIGHT = 600;

VulkanApp::VulkanApp(const std::string &appName) : vulkanInstance{appName} {
    initGLFW();
}

VulkanApp::~VulkanApp() { cleanup(); }

void VulkanApp::run() { mainLoop(); }

void VulkanApp::initGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize glfw");
    }

    // Define client api to GLFW_NO_API, otherwise the default API is OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Graphica", nullptr, nullptr);

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
    glfwDestroyWindow(window);
    glfwTerminate();
}