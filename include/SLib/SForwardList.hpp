//
// Created by Severin on 12.02.2023.
//

#ifndef SLIB_SFORWARDLIST_HPP
#define SLIB_SFORWARDLIST_HPP

#include <cstdint>
#include <utility>

#include "SException.hpp"

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
    public:
        using size_type = size_t;
        using value_type = T;
        using Iterator = SForwardListIterator<SForwardList<T>>;

        SForwardList() noexcept {
            _create();
        }

        void swap(SForwardList& other){
            std::swap(m_head, other.m_head);
            std::swap(m_size, other.m_size);
        }

        SForwardList(SForwardList&& other) noexcept {
            _create();
            swap(other);
        }

        SForwardList(SForwardList& other) {
            _create();

            try{
                for (auto& i: other) {
                    emplace_front(i);
                }
            } catch (...){
                _delete();
                throw;
            }

            reverse();
        }

        SForwardList& operator=(SForwardList&& other) noexcept {
            if (this == &other)
                return *this;

            _create();
            swap(other);

            return *this;
        }

        SForwardList& operator=(const SForwardList& other) {
            if (this == &other)
                return *this;

            _delete();
            _create();

            try{
                for (auto& i: other) {
                    emplace_front(i);
                }
            } catch (...){
                _delete();
                throw;
            }

            reverse();

            return *this;
        }

        ~SForwardList(){
            _delete();
        }

        void push_front(const T& item){
            emplace_front(item);
        }

        template<typename... Args>
        void emplace_front(Args &&... args) {
            Node *ptr = reinterpret_cast<Node *>(new uint8_t[sizeof(Node)]);

            ptr->next = m_head->next;
            try {
                new(&(ptr->value)) T(std::forward<Args>(args)...);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(ptr);
                throw;
            }

            m_head->next = ptr;
            m_size++;
        }

        void insert_after(SForwardListIterator<SForwardList<T>> iterator, const T& item){
            emplace_after(iterator, item);
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

            Node* ptr = m_head->next->next;

            m_head->next->value.~T();
            delete[] reinterpret_cast<uint8_t *>(m_head->next);

            m_head->next = ptr;
            m_size--;
        }

        T& front(){
            return m_head->next->value;
        }

        const T& front() const{
            return m_head->next->value;
        }

        [[nodiscard]] bool empty() const{
            return m_size == 0;
        }

        [[nodiscard]] size_type size() const{
            return m_size;
        }

        struct Node{
            Node* next;
            T value;
        };

        SForwardListIterator<SForwardList<T>> begin() const{
            return SForwardListIterator<SForwardList<T>>(m_head->next);
        }

        SForwardListIterator<SForwardList<T>> before_begin() const{
            return SForwardListIterator<SForwardList<T>>(m_head);
        }

        SForwardListIterator<SForwardList<T>> end() const{
            return SForwardListIterator<SForwardList<T>>(nullptr);
        }

        void reverse(){
            Node* curr = m_head->next;
            Node* prev = nullptr;
            Node* next = nullptr;

            while(curr != nullptr){
                next = curr->next;

                curr->next = prev;

                prev = curr;
                curr = next;
            }

            m_head->next = prev;
        }
    private:
        void _delete(){
            Node* curr = m_head->next;
            Node* next;

            while (curr != nullptr){
                next = curr->next;

                curr->value.~T();
                delete[] reinterpret_cast<uint8_t*>(curr);

                curr = next;
            }

            delete[] reinterpret_cast<uint8_t*>(m_head);
        }

        void _create(){
            Node *ptr = reinterpret_cast<Node *>(new uint8_t[sizeof(Node)]);
            ptr->next = nullptr;
            m_head = ptr;
            m_size = 0;
        }

        Node* m_head = nullptr;
        size_type m_size = 0;
    };

} // slib

#endif //SLIB_SFORWARDLIST_HPP
