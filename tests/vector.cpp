//
// Created by Severin on 05.02.2023.
//

#include "SLib/SVector.hpp"
#include "SLib/SLib.hpp"

S_TEST(Vector, Creation){
    slib::SVector<int> vector;
    S_EXPECT_EQ(vector.size(), 0u);
    vector.push_back(1);
    S_EXPECT_EQ(vector.size(), 1u);
    S_EXPECT_EQ(vector[0], 1);
    vector.pop_back();
    S_EXPECT_EQ(vector.size(), 0u);
}

S_TEST(Vector, Resizing){
    slib::SVector<int> vector;
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    S_EXPECT_EQ(vector.size(), 8u);
    vector.resize(2);
    S_EXPECT_EQ(vector.size(), 2u);
    vector.shrink_to_fit();
    S_EXPECT_EQ(vector.capacity(), 2u);
    vector.resize(100);
    S_EXPECT_EQ(vector.capacity(), 100u);
    vector.clear();
    S_EXPECT_EQ(vector.size(), 0u);
}

S_TEST(Vector, Iterator){
    slib::SVector<int> vector;

    for (int i = 1; i <= 100; ++i) {
        vector.emplace_back(i);
    }

    int sum = 0;
    for (auto item : vector) {
        sum += item;
    }

    S_EXPECT_EQ(sum, 5050);
}

int main(){
    S_REGISTER_TEST(Vector, Creation);
    S_REGISTER_TEST(Vector, Resizing);
    S_REGISTER_TEST(Vector, Iterator);

    S_RUN_TESTS();
    return 0;
}
