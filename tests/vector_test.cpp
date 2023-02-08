//
// Created by Severin on 05.02.2023.
//

#include "SLib/SVector.h"
#include "SLib/SLog.h"

int main(){
    S_LOG_LEVEL_INFO;

    slib::SVector<int> vector;

    for (int i = 0; i < 100; ++i) {
        vector.push_back(i);
    }

    slib::SVector<int> vector1(vector);
    slib::SVector<int> vector2(vector);

    for (int i = 0; i < 100; ++i) {
        vector1.emplace_back(i + 100);
    }

    vector1.resize(1000);

    vector1.shrink_to_fit();
}
