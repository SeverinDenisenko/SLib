//
// Created by Severin on 13.02.2023.
//

#ifndef SLIB_STEST_HPP
#define SLIB_STEST_HPP

#include <iostream>

#include "SList.hpp"

namespace slib {
    class SUnitTest {
    public:
        virtual void Run() = 0;

        virtual std::string GetModule() = 0;

        virtual std::string GetName() = 0;

        virtual ~SUnitTest() = default;

        template<typename T>
        void ExpectEquality(const T &a, const T &b) {
            if (a == b){
                PrintSuccess();
                return;
            }

            PrintFail();
            std::cerr << "Expected: " << a << ". Actual: " << b << "." << std::endl;
        }

        template<typename T>
        void ExpectEqualitySilent(const T &a, const T &b) {
            if (a == b){
                PrintSuccess();
                return;
            }

            PrintFail();
        }

        void PrintFail(){
            std::cerr << "Test " << GetModule() << "::" << GetName() << " Failed." << std::endl;
        }

        void PrintSuccess(){
            std::cout << "Test " << GetModule() << "::" << GetName() << " Succeeded." << std::endl;
        }
    };

    class STest {
    public:
        STest() noexcept = default;

        void AddTest(SUnitTest *test) {
            tests.push_back(test);
        }

        void RunTests() {
            for (auto item: tests) {
                item->Run();
            }
        }

        ~STest(){
            for (auto item : tests) {
                delete item;
            }
        }

    private:
        SList<SUnitTest *> tests;
    };

    STest sTest;
}

// Definition and declaration macros

#define S_DECLARE_TEST(Module, Name)                              \
    class STest##Module##_##Name: public slib::SUnitTest          \
    {                                                             \
    public:                                                       \
        virtual std::string GetModule() override;                 \
        virtual std::string GetName() override;                   \
        virtual void Run() override;                              \
    }

#define S_DEFINE_TEST(Module, Name)                                       \
    std::string STest##Module##_##Name::GetModule() {return #Module;}     \
    std::string STest##Module##_##Name::GetName() {return #Name;}         \
    void STest##Module##_##Name::Run()

#define S_REGISTER_TEST(Module, Name)                             \
    slib::sTest.AddTest(new STest##Module##_##Name())

#define S_TEST(Module, Name)                                      \
    S_DECLARE_TEST(Module, Name);                                 \
    S_DEFINE_TEST(Module, Name)                                   \

#define S_DECLARE_TEST(Module, Name)                              \
    class STest##Module##_##Name: public slib::SUnitTest          \
    {                                                             \
    public:                                                       \
        virtual std::string GetModule() override;                 \
        virtual std::string GetName() override;                   \
        virtual void Run() override;                              \
    }

    // Testing macros

#define S_RUN_TESTS()                                             \
    slib::sTest.RunTests()

#define S_EXPECT_EQ(A, B)                                         \
    ExpectEquality(A, B)

#define S_EXPECT_EQUALITY(A, B)                                   \
    ExpectEqualitySilent(A, B)

#endif
