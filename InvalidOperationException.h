#ifndef INVALIDOPERATIONEXCEPTION_H
#define INVALIDOPERATIONEXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidOperationException : public std::logic_error {
public:
    InvalidOperationException(const std::string& msg)
        : std::logic_error(msg) {}
};

#endif // INVALIDOPERATIONEXCEPTION_H
