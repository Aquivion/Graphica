#pragma once

#include "Utils/utils.h"
#include "Vulkan/VulkanShaderModule/VulkanShaderModule.h"

namespace VulkanCore {

class VulkanLogicalDevice;

class VulkanGraphicsPipeline {
   public:
    VulkanGraphicsPipeline();

    void createGraphicsPipeline(VulkanLogicalDevice& logicalDevice);

    void populatePipelineShaderStageCreateInfo(VkPipelineShaderStageCreateInfo& createInfo,
                                               const VulkanShaderModule& shaderModule, VkShaderStageFlagBits stage);

    int getValue() const;

   private:
    VulkanShaderModule vertShaderModule;
    VulkanShaderModule fragShaderModule;
};

}  // namespace VulkanCore