#pragma once

#include <systematic/posix/FileDescriptor.hpp>
#include <systematic/posix/ioctl.hpp>

#include <linux/udmabuf.h>

#include <cstddef>
#include <cstdint>


// "linux" is #defined as 1 by GCC on Linux, so we use "linux_" as the namespace name.
namespace systematic :: linux_ :: udmabuf
{
    /**
     * @brief Create a DMA-BUF from a memfd via UDMABUF_CREATE.
     *
     * @param ubuf_fd File descriptor for /dev/udmabuf.
     * @param memfd File descriptor for the source memfd.
     * @param size Buffer size in bytes.
     *
     * @return DMA-BUF file descriptor.
     *
     * @throw std::system_error if ioctl() fails.
    */
    inline posix::FileDescriptor create(int ubuf_fd, int memfd, std::size_t size)
    {
        udmabuf_create arg {
            .memfd = static_cast<std::uint32_t>(memfd),
            .flags = 0,
            .offset = 0,
            .size = size
        };

        return posix::FileDescriptor {posix::ioctl(ubuf_fd, UDMABUF_CREATE, arg)};
    }
}
