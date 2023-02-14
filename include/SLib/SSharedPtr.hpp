//
// Created by Severin on 15.02.2023.
//

#ifndef SLIB_SSHAREDPTR_H
#define SLIB_SSHAREDPTR_H

#include <cstdint>
#include <utility>

namespace slib {

    template<typename T>
    class SSharedPtr {
    public:
        explicit SSharedPtr(T* ptr = nullptr){
            if (ptr == nullptr)
                m_container = nullptr;
            else
                m_container = new SSharedPtrContainer(ptr);
        }

        SSharedPtr(const SSharedPtr& other) {
            m_container = other.m_container;
            _plus();
        }

        SSharedPtr& operator=(const SSharedPtr& other){
            if (this == &other)
                return *this;

            _minus();
            m_container = other.m_container;
            _plus();

            return *this;
        }

        ~SSharedPtr(){
            _minus();
        }

        T* get(){
            if (m_container == nullptr)
                return nullptr;
            else
                return m_container->m_ptr;
        }

        T& operator*() const{
            return *get();
        }

        T* operator->() const{
            return get();
        }
    private:
        class SSharedPtrContainer {
        public:
            explicit SSharedPtrContainer(T* ptr) : m_ptr(ptr), m_count(1) {}

            T* m_ptr;
            size_t m_count;
        };

        void _minus(){
            if (m_container != nullptr && --m_container->m_count == 0) {
                delete m_container->m_ptr;
                delete m_container;
            }
        }

        void _plus(){
            if(m_container != nullptr)
                m_container->m_count++;
        }

        SSharedPtrContainer* m_container;
    };

} // slib

#endif //SLIB_SSHAREDPTR_H
