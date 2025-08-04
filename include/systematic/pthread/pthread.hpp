#pragma once

#include <pthread.h>

#include <string>
#include <system_error>
#include <cerrno>


namespace systematic :: pthread
{
    /// @brief Set thread name
    ///
    /// This function is a wrapper around `pthread_setname_np`.
    ///
    /// @param handle handle to the thread
    /// @param name new name for the thread
    ///
    /// @throw @a std::system_error if setting the thread name fails
    ///
    inline void setName(pthread_t handle, std::string const& name)
    {
        if (::pthread_setname_np(handle, name.c_str()) != 0)
            throw std::system_error {errno, std::system_category(), "pthread_setname_np() failed"};
    }


    /// @brief Set thread name for the current thread
    ///
    /// This function is a wrapper around `pthread_setname_np` for the current thread.
    ///
    /// @param name new name for the current thread
    ///
    /// @throw @a std::system_error if setting the thread name fails
    ///
    inline void setName(std::string const& name)
    {
        setName(::pthread_self(), name);
    }
}

