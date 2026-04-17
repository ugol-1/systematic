#pragma once

#include <sys/prctl.h>

#include <system_error>
#include <string>


// "linux" is #defined as 1 by GCC on Linux, so we use "linux_" as the namespace name.
namespace systematic :: linux_
{
    /**
     * @brief Thin wrapper around @c ::prctl() that throws on failure.
     *
     * @param option @c PR_* operation selector
     * @param arg2,arg3,arg4,arg5 Option-specific arguments (see prctl(2))
     *
     * @return The non-negative return value from @c ::prctl() (semantics depend on @a option)
     *
     * @throw std::system_error if @c ::prctl() returns -1
     */
    inline int prctl(int option,
        unsigned long arg2 = 0, unsigned long arg3 = 0,
        unsigned long arg4 = 0, unsigned long arg5 = 0)
    {
        int const rv = ::prctl(option, arg2, arg3, arg4, arg5);
        if (rv < 0)
            throw std::system_error {errno, std::system_category(),
                "prctl() failed for option " + std::to_string(option)};

        return rv;
    }
}
