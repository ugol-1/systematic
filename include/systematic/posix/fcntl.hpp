#pragma once

#include <fcntl.h>

#include <system_error>


namespace systematic :: posix
{
    /**
     * @brief Perform a file control operation.
     *
     * @param fd File descriptor.
     * @param cmd Operation to perform.
     * @param arg Operation argument.
     *
     * @return Return value of fcntl().
     *
     * @throw std::system_error if fcntl() fails.
    */
    inline int fcntl(int fd, int cmd, int arg)
    {
        int result = ::fcntl(fd, cmd, arg);
        if (result < 0)
            throw std::system_error {errno, std::system_category(), "fcntl() failed"};

        return result;
    }
}
