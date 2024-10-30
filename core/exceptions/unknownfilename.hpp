#pragma once

#include <exception>
#include <string>

class UnknownFilenameException: public std:: exception
{
    public:
        UnknownFilenameException(std::string filename);
        virtual const char* what() const noexcept;

    private:
        std::string filename;
};

