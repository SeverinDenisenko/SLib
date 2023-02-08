//
// Created by Severin on 08.02.2023.
//

#include "SLib/SList.h"
#include "SLib/SLog.h"

int main(){
    S_LOG_LEVEL_INFO;

    slib::SList<int> list;

    list.push_back(1);
    list.push_front(1);
    list.push_front(1);
    list.push_front(1);
    list.push_front(1);
    list.push_back(1);
    list.push_back(1);
    list.push_back(1);

    list.pop_back();
    list.pop_back();

    return 0;
}

