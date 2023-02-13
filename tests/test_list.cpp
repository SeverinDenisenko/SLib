//
// Created by Severin on 08.02.2023.
//

#include "SLib/SForwardList.h"
#include "SLib/SLog.h"

int main(){
    S_LOG_LEVEL_INFO;

    slib::SForwardList<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);
    list.push_front(7);
    list.push_front(8);
    list.push_front(9);
    list.insert_after(list.begin(), 10);
    list.pop_front();

    for (auto &item: list) {
        S_INFO(std::to_string(item));
    }

    return 0;
}

