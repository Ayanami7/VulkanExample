/*
 * vulkanDevice.cpp
 * 
 * Created on 2023-10 by Ayanami7 Follow C++ Standard 17
 * 
 * [introduction]
 * Implementions of VulkanDevice class
 */

#include "vulkanDevice.h"

#include <unordered_map>

namespace vks
{
    /// @brief Default constructor
    /// @param physicalDevice Physical device that is to be used
    VulkanDevice::VulkanDevice(VkPhysicalDevice physicalDevice)
    {
        assert(physicalDevice);
        this->physicalDevice = physicalDevice;

        // Get Property and features from physicalDevice
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        // Features should be checked by the examples before using them
        vkGetPhysicalDeviceFeatures(physicalDevice, &features);
        // Memory properties are used regularly for creating all kinds of buffers
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

        // Get the count of queueFamily
        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        assert(queueFamilyCount > 0);
        queueFamilyProperties.resize(queueFamilyCount);
        // Get the specific property of queueFamily
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

        // Get list of supported extensions
		uint32_t extCount = 0;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, nullptr);
		if (extCount > 0)
		{
			std::vector<VkExtensionProperties> extensions(extCount);
			if (vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
			{
				for (auto ext : extensions)
				{
					supportedExtensions.push_back(ext.extensionName);
				}
			}
		}
    }

    
};