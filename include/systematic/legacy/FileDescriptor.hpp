#pragma once

#include <fcntl.h>

#include <boost/throw_exception.hpp>

#include <system_error>


namespace cyboola_core
{
/**
 * @brief A simple RAII resource manager for a file.
 *
 * Constructor opens the file, destructor closes it.
*/
class FileDescriptor
{
public:
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
     * Closes the stored descriptor with close()
     * (https://man7.org/linux/man-pages/man2/close.2.html)
    */
    ~FileDescriptor()
    {
        close(descriptor_);
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
    int const descriptor_;
};
}
