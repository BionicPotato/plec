#include "../exceptions.hpp"

UnknownFilenameException::UnknownFilenameException(std::string filename): filename(filename) {}

const char* UnknownFilenameException::what() const noexcept
{
    snprintf(errorMessage, sizeof(errorMessage), "Unknown filename '%s'", filename.c_str());
    return errorMessage;
}

