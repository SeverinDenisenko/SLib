//
// Created by Severin on 12.02.2023.
//

#ifndef SLIB_SFORWARDLIST_H
#define SLIB_SFORWARDLIST_H

#include <cstdint>
#include <utility>

#include "SException.h"

namespace slib {

    template<typename T>
    class SForwardListIterator{
    public:
        using value_type = typename T::value_type;
        using node_type = typename T::Node;

        explicit SForwardListIterator(node_type* node): m_node(node) {}

        SForwardListIterator& operator++(){
            m_node = m_node->next;
            return *this;
        }

        SForwardListIterator operator++(int){
            SForwardListIterator i = *this;
            ++(*this);
            return i;
        }

        value_type* operator->(){
            return *(m_node->value);
        }

        const value_type* operator->() const{
            return *(m_node->value);
        }

        value_type& operator*(){
            return m_node->value;
        }

        const value_type& operator*() const{
            return m_node->value;
        }

        bool operator==(const SForwardListIterator& other) const{
            return m_node == other.m_node;
        }

        bool operator!=(const SForwardListIterator& other) const{
            return m_node != other.m_node;
        }

        node_type* m_node;
    };

    template <typename T>
    class SForwardList {
        using size_type = size_t;
        using value_type = T;

        SForwardList() = default;

        void swap(SForwardList& other){
            std::swap(m_head, other.m_head);
            std::swap(m_size, other.m_size);
        }

        SForwardList(SForwardList&& other) noexcept {
            swap(other);
        }

        SForwardList& operator=(SForwardList&& other) noexcept {
            if (this == &other)
                return *this;

            swap(other);

            return *this;
        }

        void push_front(const T& item){
            emplace_front(item);
        }

        template<typename... Args>
        void emplace_front(Args &&... args) {
            Node *ptr = reinterpret_cast<Node *>(new uint8_t[sizeof(Node)]);

            ptr->next = m_head;
            try {
                new(&(ptr->value)) T(std::forward<Args>(args)...);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(ptr);
                throw;
            }

            m_head = ptr;
            m_size++;
        }

        void insert_after(const T& item){
            emplace_front(item);
        }

        template<typename... Args>
        void emplace_after(SForwardListIterator<SForwardList<T>> iterator, Args &&... args){
            Node *ptr = reinterpret_cast<Node *>(new uint8_t[sizeof(Node)]);

            Node *curr = iterator.m_node;
            Node *next = iterator.m_node->next;
            ptr->next = next;
            try {
                new(&(ptr->value)) T(std::forward<Args>(args)...);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(ptr);
                throw;
            }

            curr->next = ptr;
            m_size++;
        }

        void pop_front(){
            if(m_head == nullptr)
                throw SException("Can't pop_front 0-length forward list");

            Node* ptr = m_head->next;

            m_head->value.~T();
            delete[] reinterpret_cast<uint8_t *>(m_head);

            m_head = ptr;
            m_size--;
        }

        T& front(){
            return m_head->value;
        }

        const T& front() const{
            return m_head->value;
        }

        bool empty(){
            return m_size == 0;
        }

        struct Node{
            Node* next;
            T value;
        };

        SForwardListIterator<SForwardList<T>> begin(){
            return SListIterator<SForwardList<T>>(m_head);
        }

        SForwardListIterator<SForwardList<T>> end(){
            return SListIterator<SForwardList<T>>(nullptr);
        }

    private:
        Node* m_head = nullptr;
        size_type m_size = 0;
    };

} // slib

#endif //SLIB_SFORWARDLIST_H
