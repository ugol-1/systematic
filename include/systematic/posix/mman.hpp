#pragma once

#include <systematic/posix/FileDescriptor.hpp>

#include <sys/mman.h>

#include <system_error>


namespace systematic :: posix
{
    /**
     * @brief Create an anonymous file and return a file descriptor for it.
     *
     * @param name Name for debugging (shown in /proc/self/fd/).
     * @param flags MFD_* flags (e.g. MFD_CLOEXEC).
     *
     * @return FileDescriptor for the anonymous file.
     *
     * @throw std::system_error if memfd_create() fails.
    */
    inline FileDescriptor memfd_create(char const * name, unsigned flags = MFD_CLOEXEC)
    {
        FileDescriptor fd {::memfd_create(name, flags)};
        if (fd < 0)
            throw std::system_error {errno, std::system_category(), "memfd_create() failed"};

        return fd;
    }
}
