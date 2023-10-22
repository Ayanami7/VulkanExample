/*
 * vulkanBuffer.cpp
 * 
 * Created on 2023-10 by Ayanami7 Follow C++ Standard 17
 * 
 * [introduction]
 * Implementions of vulkanBuffer
 */

#include "vulkanBuffer.h"

namespace vks
{

    /// @brief Map a memory range of this buffer. If successful, mapped points to the specified buffer range.
    /// @param size (Optional) Size of the memory range to map. Pass VK_WHOLE_SIZE to map the complete buffer range.
    /// @param offset (Optional) Byte offset from beginning
    /// @return VkResult of the buffer mapping call
    VkResult Buffer::map(VkDeviceSize size, VkDeviceSize offset)
    {
        return vkMapMemory(device, memory, offset, size, 0, &mapped);
    }

    /// @brief Does not return a result as vkUnmapMemory can't fail.
    void Buffer::unmap()
    {
        if (mapped)
        {
            vkUnmapMemory(device, memory);
            mapped = nullptr;
        }
    }

    /// @brief Attach the allocated memory block to the buffer
    /// @param offset (Optional) Byte offset from beginning
    /// @return VkResult of the bindBufferMemory call
    VkResult Buffer::bind(VkDeviceSize offset)
    {
        return vkBindBufferMemory(device, buffer, memory, offset);
    }

    /// @brief Setup the default descriptor for this buffer
    /// @param size (Optional) Size of the memory range of the descriptor
    /// @param offset (Optional) Byte offset from beginning
    void Buffer::setupDescriptor(VkDeviceSize size,VkDeviceSize offset)
    {
        descriptor.offset = offset;
        descriptor.buffer = buffer;
        descriptor.range = size;
    }

    /// @brief Copies the specified data to mapped buffer
    /// @param data Pointer to the data to copy
    /// @param size Size of the data to copy in machine units
    void Buffer::copyTo(void *data , VkDeviceSize size)
    {
        assert(mapped);
        memcpy(mapped, data, size);
    }

    /// @brief Flush a memory range of the buffer to make it visible to the device
    /// @param size (Optional) Size of the memory range to flush. Pass VK_WHOLE_SIZE to flush the complete buffer range.
    /// @param offset (Optional) Byte offset from beginning 
    /// @return VkResult of the flush call
    VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset)
    {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkFlushMappedMemoryRanges(device, 1, &mappedRange);
    }

    /// @brief Invalidate a memory range of the buffer to make it visible to the host
    /// @param size (Optional) Size of the memory range to invalidate. Pass VK_WHOLE_SIZE to invalidate the complete buffer range.
    /// @param offset (Optional) Byte offset from beginning 
    /// @return VkResult of the invalidate call
    VkResult Buffer::invalidate(VkDeviceSize size, VkDeviceSize offset)
    {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkInvalidateMappedMemoryRanges(device, 1, &mappedRange);
    }

    /// @brief Release all resources held by this buffer
    void Buffer::destroy()
    {
        if (buffer)
        {
            vkDestroyBuffer(device, buffer, nullptr);
        }
        if (memory)
        {
            vkFreeMemory(device, memory, nullptr);
        }
    }
};