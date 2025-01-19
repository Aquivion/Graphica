#include "VulkanInstance/VulkanInstance.h"
#include <vulkan/vulkan.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

// Global Vulkan objects
VkDevice device;
VkCommandBuffer commandBuffer;
std::vector<VkFramebuffer> swapChainFramebuffers;
std::vector<VkImageView> swapChainImageViews;
VkExtent2D swapChainExtent;
VkRenderPass renderPass;

VkSwapchainKHR swapChain;
std::vector<VkImage> swapChainImages;
VkFormat swapChainImageFormat;
uint32_t graphicsQueueFamilyIndex;

VkQueue graphicsQueue;

VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

void pickPhysicalDevice(VkInstance instance)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0)
    {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // Just pick the first suitable device for simplicity
    physicalDevice = devices[0];

    std::cout << "Physical device selected!" << std::endl;
}

uint32_t findGraphicsQueueFamily(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    for (uint32_t i = 0; i < queueFamilyCount; i++)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            // Check if this queue family supports presentation
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport)
            {
                return i;
            }
        }
    }

    throw std::runtime_error("Failed to find a suitable queue family!");
}

void createLogicalDevice(VulkanInstance &vulkanInstance)
{
    graphicsQueueFamilyIndex = findGraphicsQueueFamily(physicalDevice, vulkanInstance.getSurface()); // Replace with proper query logic
    // Specify queue creation info (graphics queue)
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex; // Assume the first queue family supports graphics
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // Specify device features (leave empty for now)
    VkPhysicalDeviceFeatures deviceFeatures{};

    // Create the logical device
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.pEnabledFeatures = &deviceFeatures;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create logical device!");
    }

    std::cout << "Logical device created successfully!" << std::endl;

    // Retrieve the graphics queue
    vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &graphicsQueue);
    std::cout << "Graphics queue retrieved successfully!" << std::endl;
}

void createSwapChain(VkDevice device, VkSurfaceKHR surface)
{
    // Query swap chain support (omitted here for brevity)
    // Choose swap chain surface format, present mode, and extent (e.g., chooseSwapSurfaceFormat, chooseSwapExtent)

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = 2; // Double buffering
    createInfo.imageFormat = swapChainImageFormat;
    createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    createInfo.imageExtent = swapChainExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    // Sharing mode for queue families
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices = nullptr;

    createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR; // V-Sync
    createInfo.clipped = VK_TRUE;

    // Old swap chain for resizing (nullptr for now)
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create swap chain!");
    }

    // Retrieve swap chain images
    uint32_t imageCount;
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = createInfo.imageFormat;
    swapChainExtent = createInfo.imageExtent;

    std::cout << "Swap chain created successfully!" << std::endl;
}

void createImageViews(VkDevice device)
{
    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++)
    {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = swapChainImages[i];
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = swapChainImageFormat;
        viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device, &viewInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create image view!");
        }
    }

    std::cout << "Image views created successfully!" << std::endl;
}

void createFramebuffers(VkDevice device)
{
    swapChainFramebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++)
    {
        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass; // Use the existing render pass
        framebufferInfo.attachmentCount = 1;     // One attachment per framebuffer
        framebufferInfo.pAttachments = &swapChainImageViews[i];
        framebufferInfo.width = swapChainExtent.width; // Match swap chain extent
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create framebuffer!");
        }
    }

    std::cout << "Framebuffers created successfully!" << std::endl;
}

void createRenderPass(VkDevice device, VkFormat swapChainImageFormat)
{
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = swapChainImageFormat; // Format of the swap chain images
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // Clear the attachment at the start
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create render pass!");
    }
}

void recordCommandBuffer(VkCommandBuffer commandBuffer, VkFramebuffer framebuffer, VkExtent2D extent)
{
    // Begin command buffer recording
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;                  // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }
    else
    {
        std::cout << "Command buffer begin recording successfully!" << std::endl;
    }

    VkClearValue clearColor = {{0.0f, 0.0f, 0.0f, 1.0f}}; // RGBA: Black

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;    // Use the render pass created earlier
    renderPassInfo.framebuffer = framebuffer;  // Framebuffer to use
    renderPassInfo.renderArea.offset = {0, 0}; // Start at the top-left corner
    renderPassInfo.renderArea.extent = extent; // Match the swap chain extent
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor; // Specify the clear color

    std::cout << "RenderPass begin" << std::endl;
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Here you would add draw commands if needed
    std::cout << "RenderPass end" << std::endl;
    vkCmdEndRenderPass(commandBuffer);
}

VkCommandPool commandPool;

void createCommandPool(VkDevice device, uint32_t queueFamilyIndex)
{
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndex;
    poolInfo.flags = 0; // Optional

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create command pool!");
    }

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) == VK_SUCCESS)
    {
        std::cout << "Command pool created successfully!" << std::endl;
    }
}

void allocateCommandBuffer(VkDevice device)
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // Primary command buffer
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate command buffer!");
    }

    if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) == VK_SUCCESS)
    {
        std::cout << "Command pool allocated successfully!" << std::endl;
    }
}

void initVulkan(VulkanInstance &vulkanInstance)
{
    // Step 1: Pick a physical device
    pickPhysicalDevice(vulkanInstance.getInstance());

    // Step 2: Create a logical device
    createLogicalDevice(vulkanInstance);

    // Step 3: Create the swap chain
    createSwapChain(device, vulkanInstance.getSurface());

    // Step 4: Create image views for the swap chain images
    createImageViews(device);

    // Step 3: Create command pool
    uint32_t queueFamilyIndex = 0; // Placeholder: Use the correct graphics queue family inde
    createCommandPool(device, graphicsQueueFamilyIndex);

    // Step 4: Allocate command buffer
    allocateCommandBuffer(device);

    // Step 5: Create Render Pass
    VkFormat swapChainImageFormat = VK_FORMAT_B8G8R8A8_SRGB; // Example format
    createRenderPass(device, swapChainImageFormat);

    // Step 6: Create framebuffers for each swap chain image view
    createFramebuffers(device);

    std::cout << "Vulkan initialized successfully!" << std::endl;
}

void drawFrame()
{
    std::cout << "In drawFrame..." << std::endl;
    // Record command buffer for clearing the screen
    recordCommandBuffer(commandBuffer, swapChainFramebuffers[0], swapChainExtent);

    // Create a fence to ensure GPU execution is complete
    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

    std::cout << "RenderFence creation..." << std::endl;
    VkFence renderFence;
    if (vkCreateFence(device, &fenceInfo, nullptr, &renderFence) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create fence!");
    }
    else
    {
        std::cout << "Fence created successfully!" << std::endl;
    }

    // Submit the command buffer to the graphics queue
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    std::cout << "Submit draw command buffer waiting!" << std::endl;
    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, renderFence) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to submit draw command buffer!");
    }
    else
    {
        std::cout << "Submit draw command buffer successfully!" << std::endl;
    }

    // Wait for the GPU to finish execution
    vkWaitForFences(device, 1, &renderFence, VK_TRUE, UINT64_MAX);

    // Clean up the fence
    vkDestroyFence(device, renderFence, nullptr);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Window", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    try
    {
        VulkanInstance vulkanInstance("My Vulkan App", window);

        // Initialize Vulkan components
        initVulkan(vulkanInstance);
        std::cout << "Before Running event loop..." << std::endl;
        while (!glfwWindowShouldClose(window))
        {
            std::cout << "Running event loop..." << std::endl;
            glfwPollEvents();
            std::cout << "After glfwPollEvents..." << std::endl;
            // Render a frame
            drawFrame();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    for (VkFramebuffer framebuffer : swapChainFramebuffers)
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    for (VkImageView imageView : swapChainImageViews)
    {
        vkDestroyImageView(device, imageView, nullptr);
    }
    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyCommandPool(device, commandPool, nullptr);
    vkDestroyDevice(device, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}