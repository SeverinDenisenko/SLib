//
// Created by Severin on 14.02.2023.
//

#include "SLib/SLib.hpp"
#include "SLib/SForwardList.hpp"

S_TEST(FrowardList, Creation){
    slib::SForwardList<int> list;
    S_EXPECT_EQ(list.size(), 0u);
}

S_TEST(FrowardList, Modifying){
    slib::SForwardList<int> list;

    for (int i = 0; i < 100; ++i) {
        list.push_front(i);
    }

    S_EXPECT_EQ(*list.begin(), 99);

    list.pop_front();

    S_EXPECT_EQ(*list.begin(), 98);
}

S_TEST(FrowardList, Iterator){
    slib::SForwardList<int> list;

    for (int i = 1; i <= 100; ++i) {
        list.push_front(i);
    }

    int sum = 0;
    for (auto i: list) {
        sum += i;
    }

    S_EXPECT_EQ(sum, 5050);
}

int main(){
    S_REGISTER_TEST(FrowardList, Creation);
    S_REGISTER_TEST(FrowardList, Modifying);
    S_REGISTER_TEST(FrowardList, Iterator);

    S_RUN_TESTS();
}
