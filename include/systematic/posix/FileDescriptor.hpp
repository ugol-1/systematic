#pragma once

#include <fcntl.h>
#include <unistd.h>

#include <system_error>
#include <utility>


namespace systematic :: posix
{
/**
 * @brief A simple RAII resource manager for a file.
 *
 * Constructors open the file and store its descriptor, or attach to an existing one.
 * Destructor closes the file.
*/
class FileDescriptor
{
public:
    /**
     * @brief Attach to an existing file descriptor.
     *
     * @param descriptor existing file descriptor
    */
    explicit FileDescriptor(int descriptor) noexcept
    :   descriptor_ {descriptor}
    {
    }


    /**
     * @brief Open a file and store its descriptor.
     *
     * @param file_name name of the file to open
     * @param flags file open flags, same as in open() (https://man7.org/linux/man-pages/man2/open.2.html)
     *
     * @throw @a std::system_error if open() fails
    */
    explicit FileDescriptor(std::string const& file_name, int flags)
    :   descriptor_ {::open(file_name.c_str(), flags)}
    {
        if (descriptor_ < 0)
            throw std::system_error {errno, std::system_category(), "open() failed"};
    }


    /**
     * @brief Disable copy constructor
     */
    FileDescriptor(FileDescriptor const&) = delete;


    /**
     * @brief Move constructor
     */
    FileDescriptor(FileDescriptor&& other) noexcept
    :   descriptor_ {other.descriptor_}
    {
        other.descriptor_ = -1;
    }


    /**
     * Closes the stored descriptor with close()
     * (https://man7.org/linux/man-pages/man2/close.2.html)
    */
    ~FileDescriptor()
    {
        if (descriptor_ >= 0)
            ::close(descriptor_);
    }


    /**
     * @brief Disable copy assignment
     */
    FileDescriptor& operator=(FileDescriptor const&) = delete;


    /**
     * @brief Move assignment
     */
    FileDescriptor& operator=(FileDescriptor&& other) noexcept
    {
        std::swap(descriptor_, other.descriptor_);
        return *this;
    }


    /**
     * Return file descriptor
     *
     * @return the stored file descriptor
    */
    operator int() const noexcept
    {
        return descriptor_;
    }


private:
    int descriptor_ = -1;
};
}
