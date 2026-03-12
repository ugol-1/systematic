#pragma once

#include <systematic/posix/FileDescriptor.hpp>

#include <unistd.h>

#include <system_error>


namespace systematic :: posix
{
    /**
     * @brief Duplicate a file descriptor.
     *
     * @param fd File descriptor to duplicate.
     *
     * @return New FileDescriptor referring to the same file.
     *
     * @throw std::system_error if dup() fails.
    */
    inline FileDescriptor dup(int fd)
    {
        FileDescriptor new_fd {::dup(fd)};
        if (new_fd < 0)
            throw std::system_error {errno, std::system_category(), "dup() failed"};

        return new_fd;
    }


    /**
     * @brief Set the size of a file.
     *
     * @param fd File descriptor.
     * @param length Desired file size in bytes.
     *
     * @throw std::system_error if ftruncate() fails.
    */
    inline void ftruncate(int fd, off_t length)
    {
        if (::ftruncate(fd, length) < 0)
            throw std::system_error {errno, std::system_category(), "ftruncate() failed"};
    }
}
