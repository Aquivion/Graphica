set PATH_VULKAN_SDK=C:\VulkanSDK\1.4.304.0\Bin
set PATH_VULKAN_SHADER=.\src\Vulkan\VulkanGraphicsPipeline\VulkanShader

REM Compile vertex shader
"%PATH_VULKAN_SDK%\glslc.exe" "%PATH_VULKAN_SHADER%\VulkanVertexShader\shader.vert" -o "%PATH_VULKAN_SHADER%\VulkanVertexShader\vert.spv"

REM Compile fragment shader
"%PATH_VULKAN_SDK%\glslc.exe" "%PATH_VULKAN_SHADER%\VulkanFragmentShader\shader.frag" -o "%PATH_VULKAN_SHADER%\VulkanFragmentShader\frag.spv"

pause