#include "VulkanGraphicsPipeline.h"

namespace VulkanCore {

VulkanGraphicsPipeline::VulkanGraphicsPipeline() : vertShaderModule{}, fragShaderModule{} {}

void VulkanGraphicsPipeline::createGraphicsPipeline(VulkanLogicalDevice& logicalDevice) {
    auto vertShaderCode = Utils::readShaderFile("shaders/vert.spv");
    auto fragShaderCode = Utils::readShaderFile("shaders/frag.spv");

    vertShaderModule.createShaderModule(vertShaderCode, logicalDevice);
    fragShaderModule.createShaderModule(fragShaderCode, logicalDevice);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    populatePipelineShaderStageCreateInfo(vertShaderStageInfo, vertShaderModule, VK_SHADER_STAGE_VERTEX_BIT);

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    populatePipelineShaderStageCreateInfo(fragShaderStageInfo, fragShaderModule, VK_SHADER_STAGE_FRAGMENT_BIT);

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    vertShaderModule.cleanup(logicalDevice);
    fragShaderModule.cleanup(logicalDevice);
}

void VulkanGraphicsPipeline::populatePipelineShaderStageCreateInfo(VkPipelineShaderStageCreateInfo& createInfo,
                                                                   const VulkanShaderModule& shaderModule,
                                                                   VkShaderStageFlagBits stage) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    createInfo.stage = stage;
    createInfo.module = shaderModule.getShaderModule();
    createInfo.pName = "main";
}
}  // namespace VulkanCore