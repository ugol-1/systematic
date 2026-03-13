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
     * @brief Default constructor creates an empty (unmapped) object.
    */
    MemoryMapping() = default;


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
    :   addr_ {::mmap(nullptr, length, prot, flags, fd, offset)}
    ,   length_ {length}
    {
        if (addr_ == MAP_FAILED)
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
        if (addr_)
            ::munmap(addr_, length_);
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
        std::swap(addr_, other.addr_);
        std::swap(length_, other.length_);
    }


    /**
     * @brief Get pointer to the mapped memory.
     *
     * Const-ness of the MemoryMapping object governs the mapping's
     * lifetime, not the mutability of the mapped region — that is
     * determined by the prot flags passed to mmap().
     *
     * @return pointer to the mapped memory
    */
    void * addr() const noexcept
    {
        return addr_;
    }


    /**
     * @brief Get the length of the mapped memory region
     *
     * @return length in bytes
    */
    size_t length() const noexcept
    {
        return length_;
    }


private:
    void * addr_ = nullptr;
    size_t length_ = 0;
};
}
