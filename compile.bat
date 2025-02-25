set PATH_VULKAN_SDK=C:\VulkanSDK\1.4.304.0\Bin
set PATH_VULKAN_SHADER=.\src\VulkanApp\Shader

REM Compile vertex shader
"%PATH_VULKAN_SDK%\glslc.exe" "%PATH_VULKAN_SHADER%\TestShader\test.vert" -o "%PATH_VULKAN_SHADER%\TestShader\test_vert.spv"

REM Compile fragment shader
"%PATH_VULKAN_SDK%\glslc.exe" "%PATH_VULKAN_SHADER%\TestShader\test.frag" -o "%PATH_VULKAN_SHADER%\TestShader\test_frag.spv"

pause