//
// Created by Severin on 08.02.2023.
//

#include "SLib/SList.h"
#include "SLib/SLog.h"

int main(){
    S_LOG_LEVEL_INFO;

    slib::SList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    list.insert(--list.begin(), 10);
    list.insert(--list.begin(), 11);
    list.insert(--list.begin(), 12);

    for (auto &item: list) {
        S_INFO(std::to_string(item));
    }

    return 0;
}

