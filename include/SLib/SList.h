//
// Created by Severin on 08.02.2023.
//

#ifndef SLIB_SLIST_H
#define SLIB_SLIST_H

#include <cstdint>
#include <utility>

namespace slib {

    template<typename T>
    class SList {
    public:
        using size_type = uint32_t;

        SList(){
            m_head = reinterpret_cast<Node*>(new uint8_t[sizeof(Node)]);
            m_head->prev = m_head;
            m_head->next = m_head;
        }

        void push_back(const T& item){
            emplace_back(item);
        }

        void push_front(const T& item){
            emplace_front(item);
        }

        template<typename... Args>
        void emplace_back(Args &&... args){
            Node* ptr = reinterpret_cast<Node*>(new uint8_t[sizeof(Node)]);

            ptr->next = m_head;
            ptr->prev = m_head->prev;
            try {
                new(&(ptr->value)) T(std::forward<Args>(args)...);
            } catch (...){
                delete[] reinterpret_cast<uint8_t*>(ptr);
                throw;
            }
            m_head->prev->next = ptr;
            m_head->prev = ptr;
        }

        template<typename... Args>
        void emplace_front(Args &&... args) {
            Node *ptr = reinterpret_cast<Node *>(new uint8_t[sizeof(Node)]);

            ptr->prev = m_head;
            ptr->next = m_head->next;
            try {
                new(&(ptr->value)) T(std::forward<Args>(args)...);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(ptr);
                throw;
            }
            m_head->next->prev = ptr;
            m_head->next = ptr;
        }

        void pop_back(){
            Node* tmp_ptr = m_head->prev;

            m_head->prev->value.~T();
            m_head->prev = m_head->prev->prev;
            m_head->prev->next = m_head;

            delete[] reinterpret_cast<uint8_t *>(tmp_ptr);
        }

        void pop_front(){
            Node* tmp_ptr = m_head->next;

            m_head->next->value.~T();
            m_head->next = m_head->next->next;
            m_head->next->prev = m_head;

            delete[] reinterpret_cast<uint8_t *>(tmp_ptr);
        }

        T& front(){
            return m_head->next;
        }

        T& back(){
            return m_head->prev;
        }
    private:
        struct Node{
            Node* prev;
            Node* next;
            T value;
        };

        Node* m_head = nullptr;
        size_type m_size = 0;
    };

} // slib

#endif //SLIB_SLIST_H
