//
// Created by Severin on 08.02.2023.
//

#include "SLib/SList.hpp"
#include "SLib/SLib.hpp"

S_TEST(List, Creation){
    slib::SList<int> list;
    S_EXPECT_EQ(list.size(), 0u);
}

S_TEST(List, Iterator){
    slib::SList<int> list;

    for (int i = 1; i <= 100; ++i) {
        list.push_back(i);
    }
    for (int i = 1; i <= 100; ++i) {
        list.push_front(i);
    }

    int sum = 0;

    for (auto item : list) {
        sum += item;
    }

    S_EXPECT_EQ(sum, 10100);
}

S_TEST(List, Modifying){
    slib::SList<int> list;

    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    for (int i = 5; i < 10; ++i) {
        list.push_front(i);
    }

    list.insert(list.begin(), 100);
    list.insert(list.end(), 100);

    S_EXPECT_EQ(*list.begin(), 100);
    S_EXPECT_EQ(*list.before_end(), 100);
}

S_TEST(List, CopyMove){
    slib::SList<int> list;

    for (int i = 1; i <= 100; ++i) {
        list.push_back(i);
    }

    slib::SList<int> list2(list);

    S_EXPECT_EQ(*list2.begin(), 1);
    S_EXPECT_EQ(*list2.before_end(), 100);

    slib::SList<int> list3(std::move(list2));

    S_EXPECT_EQ(*list3.begin(), 1);
    S_EXPECT_EQ(*list3.before_end(), 100);
}

int main(){
    S_REGISTER_TEST(List, Creation);
    S_REGISTER_TEST(List, Iterator);
    S_REGISTER_TEST(List, Modifying);
    S_REGISTER_TEST(List, CopyMove);

    S_RUN_TESTS();
    return 0;
}

