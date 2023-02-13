//
// Created by Severin on 05.02.2023.
//

#ifndef SLIB_SVECTOR_HPP
#define SLIB_SVECTOR_HPP

#include <cstdint>
#include <utility>

#include "SException.hpp"
#include "SLog.hpp"

namespace slib {

    template<typename U>
    class SVectorIterator{
    public:
        using value_type = typename U::value_type;

        explicit SVectorIterator(value_type* ptr) : m_ptr(ptr) {}

        SVectorIterator& operator++(){
            m_ptr++;
            return *this;
        }

        SVectorIterator operator++(int){
            SVectorIterator i = *this;
            ++(*this);
            return i;
        }

        SVectorIterator& operator--(){
            m_ptr--;
            return *this;
        }

        SVectorIterator operator--(int){
            SVectorIterator i = *this;
            --(*this);
            return i;
        }

        value_type& operator[](size_t i){
            return m_ptr[i];
        }

        const value_type& operator[](size_t i) const{
            return m_ptr[i];
        }

        value_type* operator->(){
            return m_ptr;
        }

        const value_type* operator->() const{
            return m_ptr;
        }

        value_type& operator*(){
            return *m_ptr;
        }

        const value_type& operator*() const{
            return *m_ptr;
        }

        bool operator==(const SVectorIterator& other) const{
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const SVectorIterator& other) const{
            return m_ptr != other.m_ptr;
        }
    private:
        value_type* m_ptr;
    };

    template<typename T>
    class SVector {
    public:
        using size_type = size_t;
        using value_type = T;

        SVector() {
            m_ptr = reinterpret_cast<T *>(new uint8_t[m_capacity * sizeof(T)]);
        }

        explicit SVector(size_type size, const T &value = T()) {
            resize(size, value);
        }

        void swap(SVector &other){
            std::swap(m_ptr, other.m_ptr);
            std::swap(m_size, other.m_size);
            std::swap(m_capacity, other.m_capacity);
        }

        SVector(const SVector &other) {
            reserve(other.m_capacity);

            try {
                std::uninitialized_copy(other.m_ptr, other.m_ptr + other.m_size, m_ptr);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(m_ptr);
                throw;
            }

            m_size = other.m_size;
        }

        SVector(SVector &&other) noexcept {
            swap(other);
        }

        SVector &operator=(const SVector &other) {
            if (this == &other)
                return *this;

            reserve(other.m_capacity);

            try {
                std::uninitialized_copy(other.m_ptr, other.m_ptr + other.m_size, m_ptr);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(m_ptr);
                throw;
            }

            m_size = other.m_size;

            return *this;
        };

        SVector &operator=(SVector &&other) noexcept {
            if (this == &other)
                return *this;

            swap(other);

            return *this;
        };

        ~SVector() {
            void _delete();
        }

        const T &operator[](size_type index) const {
            return m_ptr[index];
        }

        T &operator[](size_type index) {
            return m_ptr[index];
        }

        const T &at(size_type index) const {
            if (index < 0 || index >= m_size) {
                throw SException("Out of range in SVector.");
            }

            return m_ptr[index];
        }

        T &at(size_type index) {
            if (index < 0 || index >= m_size) {
                throw SException("Out of range in SVector.");
            }

            return m_ptr[index];
        }

        void push_back(const T &item) {
            emplace_back(item);
        }

        void pop_back() {
            if (m_size == 0) {
                throw SException("Can't pop_back SVector with length 0");
            }

            m_size--;

            (m_ptr + m_size)->~T();
        }

        [[nodiscard]] size_type size() const {
            return m_size;
        }

        void resize(size_type size, const T &value = T()) {
            if (size > m_capacity) {
                reserve(size);
            }

            for (size_type i = m_size; i < size; ++i) {
                new(m_ptr + i) T(value);
            }

            m_size = size;
        }

        void reserve(size_type capacity) {
            if (m_capacity >= capacity)
                return;

            T *tmp_ptr = reinterpret_cast<T *>(new uint8_t[capacity * sizeof(T)]);

            try {
                std::uninitialized_copy(m_ptr, m_ptr + m_size, tmp_ptr);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(tmp_ptr);
                throw;
            }

            _delete();

            m_capacity = capacity;
            m_ptr = tmp_ptr;
        }

        T &front() {
            return m_ptr[0];
        }

        const T &front() const {
            return m_ptr[0];
        }

        T &back() {
            return m_ptr[m_size - 1];
        }

        const T &back() const {
            return m_ptr[m_size - 1];
        }

        template<typename... Args>
        void emplace_back(Args &&... args) {
            if (m_capacity == m_size) {
                reserve(m_capacity * 2);
            }

            new(m_ptr + m_size) T(std::forward<Args>(args)...);
            m_size++;
        }

        void shrink_to_fit() {
            if (m_capacity == m_size)
                return;

            T *tmp_ptr = reinterpret_cast<T *>(new uint8_t[m_size * sizeof(T)]);

            try {
                std::uninitialized_copy(m_ptr, m_ptr + m_size, tmp_ptr);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(tmp_ptr);
                throw;
            }

            _delete();

            m_capacity = m_size;
            m_ptr = tmp_ptr;
        }

        [[nodiscard]] bool empty() const {
            return m_size == 0;
        }

        void clear() {
            _delete();

            m_size = 0;
            m_capacity = 10;

            reserve(m_capacity);
        }

        SVectorIterator<SVector<T>> begin(){
            return SVectorIterator<SVector<T>>(m_ptr);
        }

        SVectorIterator<SVector<T>> end(){
            return SVectorIterator<SVector<T>>(m_ptr + m_size);
        }

        SVectorIterator<SVector<T>> before_end(){
            return SVectorIterator<SVector<T>>(m_ptr + m_size - 1);
        }
    private:
        void _delete() {
            for (size_type j = 0; j < m_size; ++j) {
                (m_ptr + j)->~T();
            }

            delete[] reinterpret_cast<uint8_t *>(m_ptr);
        }

        T *m_ptr = nullptr;
        size_type m_size = 0;
        size_type m_capacity = 10;
    };

    /*
    template<>
    class SVector<bool>{

    };
    */

} // slib

#endif //SLIB_SVECTOR_HPP
