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

        [[nodiscard]] virtual std::string GetModule() const = 0;

        [[nodiscard]] virtual std::string GetName() const = 0;

        virtual ~SUnitTest() = default;

        template<typename T, typename U>
        void ExpectEquality(const T &a, const U &b) const {
            if (a == b){
                PrintSuccess();
                return;
            }

            PrintFail();
            if constexpr(has_ostream_operator<T>::value && has_ostream_operator<U>::value){
                std::cerr << "Expected: " << a << ". Actual: " << b << "." << std::endl;
            }
        }

        void PrintFail() const{
            std::cerr << "Test " << GetModule() << "::" << GetName() << " Failed." << std::endl;
        }

        void PrintSuccess() const{
            std::cout << "Test " << GetModule() << "::" << GetName() << " Succeeded." << std::endl;
        }

    private:
        template<class Class>
        struct has_ostream_operator_impl {
            template<class V>
            static auto test(V*) -> decltype(std::declval<std::ostream>() << std::declval<V>());
            template<typename>
            static auto test(...) -> std::false_type;

            using type = typename std::is_same<std::ostream&, decltype(test<Class>(0))>::type;
        };

        template<class Class>
        struct has_ostream_operator : has_ostream_operator_impl<Class>::type {};
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
        virtual std::string GetModule() const override;                 \
        virtual std::string GetName() const override;                   \
        virtual void Run() override;                              \
    }

#define S_DEFINE_TEST(Module, Name)                                       \
    std::string STest##Module##_##Name::GetModule() const {return #Module;}     \
    std::string STest##Module##_##Name::GetName() const {return #Name;}         \
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
        virtual std::string GetModule() const override;                 \
        virtual std::string GetName() const override;                   \
        virtual void Run() override;                              \
    }

    // Testing macros

#define S_RUN_TESTS()                                             \
    slib::sTest.RunTests()

#define S_EXPECT_EQ(A, B)                                         \
    ExpectEquality(A, B)

#endif
