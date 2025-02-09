#pragma once

#include <vector>

#include "vulkan/vulkan.h"

namespace VulkanCore {

class VulkanLogicalDevice;

class VulkanShaderModule {
   public:
    VulkanShaderModule() = default;

    void createShaderModule(const std::vector<char>& filename, const VulkanLogicalDevice& logicalDevice);

    void cleanup(const VulkanLogicalDevice& logicalDevice);

    VkShaderModule getShaderModule() const { return module; }

   private:
    VkShaderModule module;
};

}  // namespace VulkanCore