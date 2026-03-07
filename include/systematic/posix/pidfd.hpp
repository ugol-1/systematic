#pragma once

#include <systematic/posix/FileDescriptor.hpp>

#include <sys/syscall.h>
#include <unistd.h>

#include <system_error>
#include <string>


namespace systematic :: posix
{
    /**
     * @brief Open a file descriptor referring to a process.
     *
     * @param pid Target process ID
     *
     * @return FileDescriptor referring to the process (pidfd)
     *
     * @throw std::system_error if the operation fails
     *
     * @note Requires Linux >= 5.3.
    */
    inline FileDescriptor pidfd_open(int pid)
    {
        FileDescriptor pidfd {static_cast<int>(::syscall(SYS_pidfd_open, pid, 0))};
        if (pidfd < 0)
            throw std::system_error {errno, std::system_category(),
                "pidfd_open() failed for pid " + std::to_string(pid)};

        return pidfd;
    }


    /**
     * @brief Duplicate a file descriptor from another process.
     *
     * @param pidfd File descriptor referring to the target process (from pidfd_open)
     * @param fd File descriptor number in the target process
     *
     * @return FileDescriptor valid in the current process
     *
     * @throw std::system_error if the operation fails
     *
     * @note Requires Linux >= 5.6 and appropriate ptrace permissions.
    */
    inline FileDescriptor pidfd_getfd(int pidfd, int fd)
    {
        FileDescriptor local_fd {static_cast<int>(::syscall(SYS_pidfd_getfd, pidfd, fd, 0))};
        if (local_fd < 0)
            throw std::system_error {errno, std::system_category(),
                "pidfd_getfd() failed for fd " + std::to_string(fd)};

        return local_fd;
    }
}
