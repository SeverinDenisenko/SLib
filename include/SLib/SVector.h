//
// Created by Severin on 05.02.2023.
//

#ifndef SLIB_SVECTOR_H
#define SLIB_SVECTOR_H

#include <cstdint>
#include <algorithm>

#include "SException.h"

namespace slib {

    template<typename T>
    class SVector {
    public:
        using size_type = uint32_t;

        SVector() {
            m_ptr = new T[m_capacity];
        }

        explicit SVector(size_type size) {
            m_capacity = size;
            m_size = size;
            m_ptr = new T[m_capacity];
        }

        SVector(const SVector &other) {
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_ptr = new T[m_capacity];
            std::copy(other.m_ptr, other.m_ptr + m_capacity, m_ptr);
        }

        SVector(SVector &&other) noexcept {
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }

        SVector &operator=(const SVector &other) {
            if (this == &other)
                return *this;

            m_capacity = other.m_capacity;
            m_size = other.m_size;

            T* tmp_ptr = new T[m_capacity];
            std::copy(other.m_ptr, other.m_ptr + m_capacity, tmp_ptr);

            delete[] m_ptr;
            m_ptr = tmp_ptr;

            return *this;
        };

        SVector &operator=(SVector &&other) noexcept {
            if (this == &other)
                return *this;

            m_capacity = other.m_capacity;
            m_size = other.m_size;

            delete[] m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;

            return *this;
        };

        ~SVector() {
            delete[] m_ptr;
        }

        const T &operator[](size_type index) const {
            return m_ptr[index];
        }

        T &operator[](size_type index) {
            return m_ptr[index];
        }

        const T &at(size_type index) const {
            if (index < 0 || index >= m_size){
                throw SException("Out of range in SVector.");
            }

            return m_ptr[index];
        }

        T &at(size_type index) {
            if (index < 0 || index >= m_size){
                throw SException("Out of range in SVector.");
            }

            return m_ptr[index];
        }

        void push_back(const T& item){
            emplace_back(item);
        }

        void pop_back(){
            if (m_size == 0){
                throw SException("Can't pop_back SVector with length 0");
            }

            m_size--;
        }

        [[nodiscard]] size_type size() const{
            return m_size;
        }

        void resize(size_type size, const T& value = T()){
            if (size > m_capacity){
                reserve(size);
            }

            for (int i = m_size; i < size; ++i) {
                new(m_ptr + i) T(value);
            }

            m_size = size;
        }

        void reserve(size_type capacity){
            if (m_capacity >= capacity){
                return;
            }

            size_type tmp_capacity = capacity;
            T *tmp_ptr = reinterpret_cast<T*>(new uint8_t[capacity * sizeof(T)]);

            size_type i = 0;
            try{
                for (; i < size(); ++i) {
                    new(tmp_ptr + i) T(m_ptr(i));
                }
            }catch(...){
                for (size_type j = 0; j < i; ++j) {
                    (tmp_ptr + j)->~T();
                }
                delete[] reinterpret_cast<uint8_t*>(tmp_ptr);
                throw;
            }

            for (size_type j = 0; j < size(); ++j) {
                (m_ptr + j)->~T();
            }
            delete[] reinterpret_cast<uint8_t*>(m_ptr);

            m_capacity = tmp_capacity;
            m_ptr = tmp_ptr;
        }

        T& front() {
            return m_ptr[0];
        }

        const T& front() const{
            return m_ptr[0];
        }

        T& back(){
            return m_ptr[m_size - 1];
        }

        const T& back() const{
            return m_ptr[m_size - 1];
        }

        template<typename... Args>
        void emplace_back(Args&&... args){
            if(m_capacity == m_size){
                reserve(m_capacity * 2);
            }

            new(m_ptr + m_size) T(std::forward<Args>(args)...);
            m_size++;
        }

        void shrink_to_fit(){
            size_type tmp_capacity = m_size;
            T *tmp_ptr = new T[tmp_capacity];
            std::copy(m_ptr, m_ptr + m_capacity, tmp_ptr);
            delete[] m_ptr;

            m_capacity = tmp_capacity;
            m_ptr = tmp_ptr;
        }
    private:
        T *m_ptr;
        size_type m_size = 0;
        size_type m_capacity = 10;
    };

} // slib

#endif //SLIB_SVECTOR_H
