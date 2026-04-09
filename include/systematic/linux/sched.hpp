#pragma once

#include <sched.h>

#include <initializer_list>


// "linux" is #defined as 1 by GCC on Linux, so we use "linux_" as the namespace name.
namespace systematic :: linux_
{
    /// @brief Wrapper around @a cpu_set_t for managing CPU affinity masks.
    ///
    /// Inherits from @a cpu_set_t, so it can be used directly wherever
    /// a @a cpu_set_t is expected.
    ///
    class CpuSet
    :   public cpu_set_t
    {
    public:
        /// @brief Construct an empty CPU set.
        ///
        CpuSet() noexcept
        {
            CPU_ZERO(this);
        }


        /// @brief Construct a CPU set from an initializer list of core indices.
        ///
        /// @param cores list of CPU core indices to include
        ///
        CpuSet(std::initializer_list<int> cores) noexcept
        :   CpuSet {}
        {
            for (const int core : cores)
                CPU_SET(core, this);
        }


        /// @brief Construct a CPU set from an iterator range of core indices.
        ///
        /// @tparam It iterator type
        /// @param first iterator to the first core index
        /// @param last iterator past the last core index
        ///
        template <typename It>
        CpuSet(It first, It last) noexcept
        :   CpuSet {}
        {
            for (; first != last; ++first)
                CPU_SET(*first, this);
        }


        /// @brief Add a CPU core to the set.
        ///
        /// @param core CPU core index
        ///
        void set(int core) noexcept
        {
            CPU_SET(core, this);
        }


        /// @brief Remove a CPU core from the set.
        ///
        /// @param core CPU core index
        ///
        void clear(int core) noexcept
        {
            CPU_CLR(core, this);
        }


        /// @brief Clear all CPU cores from the set.
        ///
        void clear() noexcept
        {
            CPU_ZERO(this);
        }


        /// @brief Test whether a CPU core is in the set.
        ///
        /// @param core CPU core index
        ///
        /// @return @a true if the core is in the set
        ///
        bool isSet(int core) const noexcept
        {
            return CPU_ISSET(core, this);
        }


        /// @brief Get the number of CPU cores in the set.
        ///
        /// @return number of cores in the set
        ///
        int count() const noexcept
        {
            return CPU_COUNT(this);
        }
    };
}
