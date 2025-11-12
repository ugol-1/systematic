#pragma once

#include <sys/mman.h>

#include <system_error>
#include <utility>


namespace systematic :: posix
{
    /**
     * @brief RAII manager for a file memory mapping
    */
    class MemoryMapping
    {
    public:
        /**
         * @brief Map a file to memory and store the pointer.
         *
         * @param length length of the mapped region in bytes
         * @param prot desired memory protection of the mapping, same as in mmap()
         *  (https://man7.org/linux/man-pages/man2/mmap.2.html)
         * @param flags determines whether updates to the mapping are
         *  visible to other processes mapping the same region, and whether
         *  updates are carried through to the underlying file. Same as in mmap().\
         * @param fd descriptor of the file to be mapped
         * @param offset offset of the mapped region from the beginning of the file in bytes.
         *
        */
        explicit MemoryMapping(size_t length, int prot, int flags, int fd, off_t offset = 0)
        :   ptr_ {::mmap(nullptr, length, prot, flags, fd, offset)}
        ,   length_ {length}
        {
            if (ptr_ == MAP_FAILED)
                throw std::system_error {errno, std::system_category(), "mmap() failed"};
        }


        /**
         * @brief Disable copy constructor
         */
        MemoryMapping(MemoryMapping const&) = delete;


        /**
         * @brief Move constructor
        */
        MemoryMapping(MemoryMapping&& other) noexcept
        {
            swap(other);
        }


        /**
         * @brief Unmap the memory region.
        */
        ~MemoryMapping()
        {
            if (ptr_)
                ::munmap(ptr_, length_);
        }


        /**
         * @brief Disable copy assignment
         */
        MemoryMapping& operator=(MemoryMapping const&) = delete;


        /**
         * @brief Move assignment
        */
        MemoryMapping& operator=(MemoryMapping&& other) noexcept
        {
            swap(other);
            return *this;
        }


        /**
         * @brief Swap two MemoryMapping objects
         */
        void swap(MemoryMapping& other) noexcept
        {
            std::swap(ptr_, other.ptr_);
            std::swap(length_, other.length_);
        }


        /**
         * @brief Get const pointer to the mapped memory
         *
         * @return const pointer to the mapped memory
        */
        operator void const * () const noexcept
        {
            return ptr_;
        }


        /**
         * @brief Get pointer to the mapped memory
         *
         * @return pointer to the mapped memory
        */
        operator void * () noexcept
        {
            return ptr_;
        }


    private:
        void * ptr_ = nullptr;
        size_t length_ = 0;
    };
}
