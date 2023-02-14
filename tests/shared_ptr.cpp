//
// Created by Severin on 08.02.2023.
//

#include "SLib/SSharedPtr.hpp"
#include "SLib/SLib.hpp"

struct something{
    something(){
        i++;
    }

    ~something(){
        i--;
    }

    static int i;
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
}

int main(){
    S_REGISTER_TEST(SharedPtr, Creation);

    S_RUN_TESTS();
    return 0;
}

