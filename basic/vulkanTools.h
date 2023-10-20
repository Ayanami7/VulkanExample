/*
 * vulkanTools.hpp
 *
 * Created on 2023-10 by Ayanami7 Follow C++ Standard 17
 *
 * [introduction]
 * Assorted Vulkan helper functions
 */

#pragma once
#ifndef _VULKAN_TOOLS_H_

#include <vulkan/vulkan.h>
#include "vulkanInitializers.hpp"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>

#if defined(_WIN32)
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#endif

// Custom define for better code readability
#define VK_FLAGS_NONE 0
// Default fence timeout in nanoseconds
#define DEFAULT_FENCE_TIMEOUT 100000000000

// Check result on windows platform
#if defined(_WIN32)
#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << vks::tools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}
#endif

const std::string getAssetPath();
const std::string getShaderBasePath();

namespace vks
{
    namespace tools
    {
        // Disable message on fatal errors
        extern bool errorModeSilent;

        // Returns an error code as a string
        std::string errorString(VkResult errorCode);

        // Returns the device type as a string
        std::string physicalDeviceTypeString(VkPhysicalDeviceType type);

        // Selected a suitable supported depth format starting with 32 bit down to 16 bit
        // Returns false if none of the depth formats in the list is supported by the device
        VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat *depthFormat);
        // Same as getSupportedDepthFormat but will only select formats that also have stencil
        VkBool32 getSupportedDepthStencilFormat(VkPhysicalDevice physicalDevice, VkFormat *depthStencilFormat);

        // Returns tru a given format support LINEAR filtering
        VkBool32 formatIsFilterable(VkPhysicalDevice physicalDevice, VkFormat format, VkImageTiling tiling);
        // Returns true if a given format has a stencil part
        VkBool32 formatHasStencil(VkFormat format);

        // Put an image memory barrier for setting an image layout on the sub resource into the given command buffer
        void setImageLayout(
            VkCommandBuffer cmdbuffer,
            VkImage image,
            VkImageLayout oldImageLayout,
            VkImageLayout newImageLayout,
            VkImageSubresourceRange subresourceRange,
            VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
            VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
        // Uses a fixed sub resource layout with first mip level and layer
        void setImageLayout(
            VkCommandBuffer cmdbuffer,
            VkImage image,
            VkImageAspectFlags aspectMask,
            VkImageLayout oldImageLayout,
            VkImageLayout newImageLayout,
            VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
            VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

        // Insert an image memory barrier into the command buffer 
        void insertImageMemoryBarrier(
            VkCommandBuffer cmdbuffer,
            VkImage image,
            VkAccessFlags srcAccessMask,
            VkAccessFlags dstAccessMask,
            VkImageLayout oldImageLayout,
            VkImageLayout newImageLayout,
            VkPipelineStageFlags srcStageMask,
            VkPipelineStageFlags dstStageMask,
            VkImageSubresourceRange subresourceRange);

        // Display error message and exit on fatal error
        void exitFatal(const std::string &message, int32_t exitCode);
        void exitFatal(const std::string &message, VkResult resultCode);

        // Load a SPIR-V shader (binary)
#if defined(_WIN32)
        VkShaderModule loadShader(const char *fileName, VkDevice device);
#endif

        // Checks if a file exists
        bool fileExists(const std::string &filename);

        uint32_t alignedSize(uint32_t value, uint32_t alignment);
    }
};

#endif // _VULKAN_TOOLS_H_