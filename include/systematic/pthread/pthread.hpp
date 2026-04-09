#pragma once

#include <pthread.h>
#include <sched.h>

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


    /// @brief Set thread CPU affinity
    ///
    /// This function is a wrapper around `pthread_setaffinity_np`.
    ///
    /// @param handle handle to the thread
    /// @param cpu_set CPU set specifying the allowed cores
    ///
    /// @throw @a std::system_error if setting the thread affinity fails
    ///
    inline void setAffinity(pthread_t handle, cpu_set_t const& cpu_set)
    {
        const int status = ::pthread_setaffinity_np(handle, sizeof(cpu_set_t), &cpu_set);
        if (status != 0)
            throw std::system_error {status, std::system_category(), "pthread_setaffinity_np() failed"};
    }


    /// @brief Set CPU affinity for the current thread
    ///
    /// This function is a wrapper around `pthread_setaffinity_np` for the current thread.
    ///
    /// @param cpu_set CPU set specifying the allowed cores
    ///
    /// @throw @a std::system_error if setting the thread affinity fails
    ///
    inline void setAffinity(cpu_set_t const& cpu_set)
    {
        setAffinity(::pthread_self(), cpu_set);
    }
}

