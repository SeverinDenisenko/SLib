//
// Created by Severin on 06.02.2023.
//

#ifndef SLIB_SUNIQUEPTR_HPP
#define SLIB_SUNIQUEPTR_HPP

#include <utility>

namespace slib{

    template<typename T>
    class SUniquePtr{
    public:
        SUniquePtr() noexcept = default;

        explicit SUniquePtr(T* ptr) noexcept : m_ptr(ptr) {}

        ~SUniquePtr(){
            delete m_ptr;
        }

        SUniquePtr(const SUniquePtr& other) = delete;

        SUniquePtr(SUniquePtr&& other) noexcept {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }

        SUniquePtr& operator=(const SUniquePtr& other) = delete;

        SUniquePtr& operator=(SUniquePtr&& other) noexcept {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }

        T* get(){
            return m_ptr;
        }

        T& operator*() const{
            return *get();
        }

        T* operator->() const{
            return get();
        }

        T& operator*(){
            return *get();
        }

        T* operator->(){
            return get();
        }
    private:
        T* m_ptr = nullptr;
    };

    template<typename T, typename... Args>
    SUniquePtr<T> MakeUnique(Args&&... args){
        return SUniquePtr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif //SLIB_SUNIQUEPTR_HPP
