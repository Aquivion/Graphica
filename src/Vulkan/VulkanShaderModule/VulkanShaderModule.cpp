#include "VulkanShaderModule.h"

#include <stdexcept>

#include "Vulkan/VulkanLogicalDevice/VulkanLogicalDevice.h"

namespace VulkanCore {

void VulkanShaderModule::createShaderModule(const std::vector<char>& code, const VulkanLogicalDevice& logicalDevice) {
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(logicalDevice.getLogicalDevice(), &createInfo, nullptr, &module) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
}

void VulkanShaderModule::cleanup(const VulkanLogicalDevice& logicalDevice) {
    vkDestroyShaderModule(logicalDevice.getLogicalDevice(), module, nullptr);
}

}  // namespace VulkanCore