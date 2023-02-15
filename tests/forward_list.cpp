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

    list.insert_after(list.before_begin(), 999);
    S_EXPECT_EQ(*list.begin(), 999);
    list.insert_after(list.begin(), 888);
    S_EXPECT_EQ(*++list.begin(), 888);
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

S_TEST(ForwardList, Move){
    slib::SForwardList<int> list;

    for (int i = 1; i <= 100; ++i) {
        list.push_front(i);
    }

    slib::SForwardList<int> list2(std::move(list));
    S_EXPECT_EQ(*list2.begin(), 100);
}

S_TEST(ForwardList, Reverse){
    slib::SForwardList<int> list;

    for (int i = 1; i <= 100; ++i) {
        list.push_front(i);
    }

    list.reverse();

    S_EXPECT_EQ(*list.begin(), 1);
    S_EXPECT_EQ(*++list.begin(), 2);
}

S_TEST(ForwardList, Copy){
    slib::SForwardList<int> list;

    for (int i = 1; i <= 100; ++i) {
        list.push_front(i);
    }

    slib::SForwardList<int> list1(list);

    S_EXPECT_EQ(*list1.begin(), 100);
    S_EXPECT_EQ(*++list1.begin(), 99);
}

int main(){
    S_REGISTER_TEST(FrowardList, Creation);
    S_REGISTER_TEST(FrowardList, Modifying);
    S_REGISTER_TEST(FrowardList, Iterator);
    S_REGISTER_TEST(ForwardList, Move);
    S_REGISTER_TEST(ForwardList, Reverse);
    S_REGISTER_TEST(ForwardList, Copy);

    S_RUN_TESTS();
}
