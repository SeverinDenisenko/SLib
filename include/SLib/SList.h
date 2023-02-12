//
// Created by Severin on 08.02.2023.
//

#ifndef SLIB_SLIST_H
#define SLIB_SLIST_H

#include <cstdint>
#include <utility>

namespace slib {

    template<typename T>
    class SListIterator{
    public:
        using value_type = typename T::value_type;
        using node_type = typename T::Node;

        explicit SListIterator(node_type* node): m_node(node) {}

        SListIterator& operator++(){
            m_node = m_node->next;
            return *this;
        }

        SListIterator operator++(int){
            SListIterator i = *this;
            ++(*this);
            return i;
        }

        SListIterator& operator--(){
            m_node = m_node->prev;
            return *this;
        }

        SListIterator operator--(int){
            SListIterator i = *this;
            --(*this);
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

        bool operator==(const SListIterator& other) const{
            return m_node == other.m_node;
        }

        bool operator!=(const SListIterator& other) const{
            return m_node != other.m_node;
        }

        node_type* m_node;
    };

    template<typename T>
    class SList {
    public:
        using size_type = size_t;
        using value_type = T;

        SList(){
            m_head = reinterpret_cast<Node*>(new uint8_t[sizeof(Node)]);
            m_head->prev = m_head;
            m_head->next = m_head;
        }

        void swap(SList& other){
            std::swap(m_head, other.m_head);
            std::swap(m_size, other.m_size);
        }

        SList(SList&& other) noexcept {
            swap(other);
        }

        /*
        SList(const SList& other){

        }
        */

        /*
        SList& operator=(const SList& other){
            if (this == &other)
                return *this;

            //TODO

            return *this;
        }
        */

        SList& operator=(SList&& other) noexcept {
            if (this == &other)
                return *this;

            swap(other);

            return *this;
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
            m_size++;
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
            m_size++;
        }

        template<typename... Args>
        void insert(SListIterator<SList<T>> place, Args &&... args){
            Node* place_ptr = place.m_node;

            Node *ptr = reinterpret_cast<Node *>(new uint8_t[sizeof(Node)]);

            ptr->prev = place_ptr;
            ptr->next = place_ptr->next;
            try {
                new(&(ptr->value)) T(std::forward<Args>(args)...);
            } catch (...) {
                delete[] reinterpret_cast<uint8_t *>(ptr);
                throw;
            }

            place_ptr->next->prev = ptr;
            place_ptr->next = ptr;
            m_size++;
        }

        void pop_back(){
            Node* tmp_ptr = m_head->prev;

            m_head->prev->value.~T();
            m_head->prev = m_head->prev->prev;
            m_head->prev->next = m_head;
            m_size--;

            delete[] reinterpret_cast<uint8_t *>(tmp_ptr);
        }

        void pop_front(){
            Node* tmp_ptr = m_head->next;

            m_head->next->value.~T();
            m_head->next = m_head->next->next;
            m_head->next->prev = m_head;
            m_size--;

            delete[] reinterpret_cast<uint8_t *>(tmp_ptr);
        }

        T& front(){
            return m_head->next->value;
        }

        T& back(){
            return m_head->prev->value;
        }

        SListIterator<SList<T>> begin(){
            return SListIterator<SList<T>>(m_head->next);
        }

        SListIterator<SList<T>> end(){
            return SListIterator<SList<T>>(m_head->prev);
        }

        struct Node{
            Node* prev;
            Node* next;
            T value;
        };
    private:
        Node* m_head = nullptr;
        size_type m_size = 0;
    };

} // slib

#endif //SLIB_SLIST_H
