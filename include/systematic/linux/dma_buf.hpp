#pragma once

#include <systematic/posix/ioctl.hpp>

#include <linux/dma-buf.h>

#include <cstdint>
#include <thread>


// "linux" is #defined as 1 by GCC on Linux, so we use "linux_" as the namespace name.
namespace systematic :: linux_ :: dma_buf
{
    /// @brief Wrapper for `DMA_BUF_IOCTL_SYNC`.
    ///
    /// See https://docs.kernel.org/driver-api/dma-buf.html
    ///
    /// @throws std::system_error if the ioctl fails.
    ///
    inline void sync(int fd, std::uint64_t flags)
    {
        ::dma_buf_sync arg { .flags = flags };
        posix::ioctl(fd, DMA_BUF_IOCTL_SYNC, arg);
    }


    /// @brief RAII guard bracketing CPU access to a DMA-BUF.
    ///
    /// Calls sync() with `DMA_BUF_SYNC_START | flags` on construction; on
    /// destruction issues `DMA_BUF_IOCTL_SYNC` with `DMA_BUF_SYNC_END | flags`
    /// directly via `::ioctl()`, ignoring any error.
    ///
    class SyncGuard
    {
    public:
        /// @param fd DMA-BUF file descriptor. Must remain valid for the lifetime of this object.
        ///
        /// @param flags Access mode (`DMA_BUF_SYNC_READ`, `DMA_BUF_SYNC_WRITE`, or
        ///   `DMA_BUF_SYNC_RW`). Do not pass `DMA_BUF_SYNC_START` / `DMA_BUF_SYNC_END`.
        ///
        /// @throws std::system_error if `DMA_BUF_IOCTL_SYNC` fails.
        ///
        explicit SyncGuard(int fd, std::uint64_t flags)
        :   fd_ {fd}
        ,   flags_ {flags}
        {
            sync(fd_, DMA_BUF_SYNC_START | flags_);
        }


        /// @brief Ends the CPU-access window.
        ///
        /// ioctl() errors are ignored (return value not checked).
        ///
        ~SyncGuard()
        {
            ::dma_buf_sync arg { .flags = DMA_BUF_SYNC_END | flags_ };
            ::ioctl(fd_, DMA_BUF_IOCTL_SYNC, &arg);
        }


        SyncGuard(SyncGuard const&) = delete;
        SyncGuard& operator=(SyncGuard const&) = delete;

    private:
        int const fd_;
        std::uint64_t const flags_;
    };
}
