//
// Created by Severin on 14.02.2023.
//

#include "SLib/SLib.hpp"
#include "SLib/SUniquePtr.hpp"
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

S_TEST(UniquePtr, Creation){
    {
        slib::SUniquePtr<something> ptr;
        S_EXPECT_EQ(something::i, 0);
    }
    S_EXPECT_EQ(something::i, 0);

    {
        slib::SUniquePtr<something> ptr(new something);
        S_EXPECT_EQ(something::i, 1);
    }
    S_EXPECT_EQ(something::i, 0);

    {
        slib::SUniquePtr<something> ptr = slib::MakeUnique<something>();
        S_EXPECT_EQ(something::i, 1);
    }
    S_EXPECT_EQ(something::i, 0);
}

S_TEST(UniquePtr, Access){
    slib::SUniquePtr<something> ptr = slib::MakeUnique<something>(100);
    S_EXPECT_EQ(ptr->do_some(), 100);
}

int main(){
    S_REGISTER_TEST(UniquePtr, Creation);
    S_REGISTER_TEST(UniquePtr, Access);

    S_RUN_TESTS();
}
