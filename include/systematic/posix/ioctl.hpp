#pragma once

#include <sys/ioctl.h>

#include <system_error>


namespace systematic :: posix
{
    /**
     * @brief Perform a device control operation.
     *
     * @tparam T Request-specific data structure (e.g. dma_heap_allocation_data, udmabuf_create).
     *
     * @param fd File descriptor.
     * @param request Device-dependent request code.
     * @param arg Request argument, passed to ioctl() by pointer.
     *
     * @return Return value of ioctl().
     *
     * @throw std::system_error if ioctl() fails.
    */
    template <typename T>
    int ioctl(int fd, unsigned long request, T& arg)
    {
        int result = ::ioctl(fd, request, &arg);
        if (result < 0)
            throw std::system_error {errno, std::system_category(), "ioctl() failed"};

        return result;
    }
}
