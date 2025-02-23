#pragma once

#include "Utils/utils.h"
#include "Vulkan/VulkanShaderModule/VulkanShaderModule.h"

namespace VulkanCore {

class VulkanLogicalDevice;
class VulkanSwapChain;

class VulkanGraphicsPipeline {
   public:
    VulkanGraphicsPipeline();

    void createGraphicsPipeline(const VulkanLogicalDevice& device, const VulkanSwapChain& swapChain);

    void populatePipelineShaderStageCreateInfo(VkPipelineShaderStageCreateInfo& createInfo,
                                               const VulkanShaderModule& shaderModule, VkShaderStageFlagBits stage);

    int getValue() const;

    void cleanup(const VulkanLogicalDevice& device);

   private:
    VulkanShaderModule vertShaderModule;
    VulkanShaderModule fragShaderModule;
    VkPipelineLayout pipelineLayout;
};

}  // namespace VulkanCore