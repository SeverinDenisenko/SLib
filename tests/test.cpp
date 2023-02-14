//
// Created by Severin on 13.02.2023.
//

#include "SLib/STest.hpp"

#include <vector>

S_TEST(Equality, First){
    S_EXPECT_EQ(2, 4);
}

S_TEST(Equality, Fourth){
    struct hello{
        int value;

        bool operator==(const hello& other) const{
            return value==other.value;
        }
    };

    hello a{10};
    hello b{11};

    S_EXPECT_EQ(a, b);
}

int main() {
    S_REGISTER_TEST(Equality, First);
    S_REGISTER_TEST(Equality, Fourth);

    S_RUN_TESTS();
    return 0;
}

