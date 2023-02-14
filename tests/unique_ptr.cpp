//
// Created by Severin on 14.02.2023.
//

#include "SLib/SLib.hpp"
#include "SLib/SUniquePtr.hpp"
#include "SLib/SVector.hpp"

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
        slib::SUniquePtr<something> ptr = slib::make_unique<something>();
        S_EXPECT_EQ(something::i, 1);
    }
    S_EXPECT_EQ(something::i, 0);
}

int main(){
    S_REGISTER_TEST(UniquePtr, Creation);

    S_RUN_TESTS();
}
