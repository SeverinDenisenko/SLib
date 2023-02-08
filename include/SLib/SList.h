//
// Created by Severin on 08.02.2023.
//

#ifndef SLIB_SLIST_H
#define SLIB_SLIST_H

namespace slib {

    template<typename T>
    class SList {

    private:
        struct Node{
            Node* prev;
            Node* next;
            T value;
        };

        Node* m_head;
    };

} // slib

#endif //SLIB_SLIST_H
