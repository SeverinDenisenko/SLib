//
// Created by Severin on 08.02.2023.
//

#include "SLib/SSharedPtr.hpp"
#include "SLib/SLib.hpp"
#include "SLib/SVector.hpp"

struct something{
    explicit something(int k = 10) : k(k){
        i++;
    }

    int do_some(){
        return k;
    }

    ~something(){
        i--;
    }

    static int i;
    int k;
};

int something::i = 0;

S_TEST(SharedPtr, Creation){
    {
        slib::SSharedPtr<something> ptr;
        S_EXPECT_EQ(something::i, 0);
    }
    S_EXPECT_EQ(something::i, 0);

    {
        slib::SSharedPtr<something> ptr(new something());
        S_EXPECT_EQ(something::i, 1);
    }
    S_EXPECT_EQ(something::i, 0);

    {
        slib::SSharedPtr<something> ptr = slib::MakeShared<something>(100);
        S_EXPECT_EQ(something::i, 1);
        S_EXPECT_EQ(ptr->do_some(), 100);
    }
    S_EXPECT_EQ(something::i, 0);

    slib::SVector<slib::SSharedPtr<something>> vec;

    vec.emplace_back(slib::MakeShared<something>(1000));
    vec.emplace_back(slib::MakeShared<something>(100));
    vec.emplace_back(slib::MakeShared<something>(10));

    S_EXPECT_EQ(vec[0]->do_some(), 1000);
    S_EXPECT_EQ(vec[1]->do_some(), 100);
    S_EXPECT_EQ(vec[2]->do_some(), 10);

    S_EXPECT_EQ(something::i, 3);
}

int main(){
    S_REGISTER_TEST(SharedPtr, Creation);

    S_RUN_TESTS();
    return 0;
}

