#pragma once

#include <systematic/posix/FileDescriptor.hpp>
#include <systematic/posix/ioctl.hpp>

#include <linux/dma-heap.h>
#include <fcntl.h>

#include <cstddef>
#include <cstdint>


// "linux" is #defined as 1 by GCC on Linux, so we use "linux_" as the namespace name.
namespace systematic :: linux_ :: dma_heap
{
    /**
     * @brief Allocate a DMA-BUF from a DMA heap via DMA_HEAP_IOCTL_ALLOC.
     *
     * @param heap_fd File descriptor for the DMA heap device (e.g. /dev/dma_heap/system).
     * @param size Buffer size in bytes.
     * @param fd_flags File descriptor flags for the allocated DMA-BUF (e.g. O_CLOEXEC | O_RDWR).
     *
     * @return DMA-BUF file descriptor.
     *
     * @throw std::system_error if ioctl() fails.
    */
    inline posix::FileDescriptor alloc(int heap_fd, std::size_t size, std::uint32_t fd_flags)
    {
        dma_heap_allocation_data arg {
            .len = size,
            .fd = 0,
            .fd_flags = fd_flags,
            .heap_flags = 0
        };

        posix::ioctl(heap_fd, DMA_HEAP_IOCTL_ALLOC, arg);

        return posix::FileDescriptor {static_cast<int>(arg.fd)};
    }
}
