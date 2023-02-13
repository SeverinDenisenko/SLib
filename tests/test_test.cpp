//
// Created by Severin on 13.02.2023.
//

#include "SLib/STest.hpp"

S_TEST(Equality, First){
    S_EXPECT_EQ(2, 4);
}

S_TEST(Equality, Second){
    S_EXPECT_EQUALITY(2, 4); // The same as S_EXPECT_EQ but don't write to console
}

S_TEST(Equality, Fourth){
    S_EXPECT_EQ(2, 2);
}

S_TEST(Equality, Fifth){
    S_EXPECT_EQUALITY(4, 4);
}

int main() {
    S_REGISTER_TEST(Equality, First);
    S_REGISTER_TEST(Equality, Second);
    S_REGISTER_TEST(Equality, Fourth);
    S_REGISTER_TEST(Equality, Fifth);

    S_RUN_TESTS();
    return 0;
}

