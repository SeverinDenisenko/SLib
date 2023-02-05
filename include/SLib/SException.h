//
// Created by Severin on 05.02.2023.
//

#ifndef SLIB_SEXCEPTION_H
#define SLIB_SEXCEPTION_H

#include <string>
#include <exception>

namespace slib {

    class SException : public std::exception {
    public:
        explicit SException(const char* msg) : msg(msg) {}

        [[nodiscard]] const char* what () const noexcept override{
            return msg;
        }
    private:
        const char* msg;
    };


} // slib

#endif //SLIB_SEXCEPTION_H
