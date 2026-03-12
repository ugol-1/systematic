#pragma once

#include <unistd.h>

#include <system_error>


namespace systematic :: posix
{
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
