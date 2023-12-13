#include "string.hpp"
// TODO: Console style 아직 정용 x
// #include "console_style.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <gtest/gtest.h>

#define PRINTLN(...)          \
    std::cout << "\033[1;4m"; \
    fmt::print(__VA_ARGS__);  \
    std::cout << "\033[0m\n";

class StringTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// TEST_F(StringTest, WTF)
// {
//     char **test_wrapper = new char *[2];
//     char *test = new char[4]{1, 2, 3, 4};
//     test_wrapper[0] = nullptr;
//     test_wrapper[1] = test;
//     String str1{test_wrapper};
//     ASSERT_EQ(str1.size(), 4);
//     delete[] test;
// }

TEST_F(StringTest, ComparisonEqualityAndInequality)
{
    String str1 = "Hello";
    String str2 = "World";
    ASSERT_FALSE(str1 == str2);

    String str_eq1 = "same one";
    String str_eq2 = "same one";
    ASSERT_TRUE(str_eq1 == str_eq2);
}

TEST_F(StringTest, ComparisonNotEqual)
{
    String str1 = "Hello";
    String str2 = "World";
    ASSERT_TRUE(str1 != str2);
}

TEST_F(StringTest, ComparisonLessThan)
{
    String str1 = "A";
    String str2 = "a";
    ASSERT_TRUE(str1 < str2);
}

TEST_F(StringTest, ComparisonNotGreaterThan)
{
    String str1 = "Hello";
    String str2 = "World";
    ASSERT_FALSE(str1 > str2);
}

TEST_F(StringTest, Concatenation)
{
    String str1 = "Hello";
    String str2 = " World";
    String str3 = str1 + str2;

    ASSERT_EQ(String("Hello World"), str3);
}

TEST_F(StringTest, PlusEqualOperator)
{
    String str1 = "Hello, ";
    String str2 = "World!";

    str1 += str2;
    ASSERT_EQ(String("Hello, World!"), str1);

    String emptyStr;
    emptyStr += str2;
    ASSERT_EQ(str2, emptyStr);

    String emptyStr2;
    str2 += emptyStr2;
    ASSERT_EQ(str2, "World!");
}

TEST_F(StringTest, PrintFrontCharacterFuntion)
{
    String s("Exemplary");
    char &front1 = s.front();
    ASSERT_EQ('E', front1);
    front1 = 'e';
    ASSERT_EQ(String("exemplary"), s);

    String const c("Exemplary");
    char const &front2 = c.front();
    ASSERT_EQ('E', front2);
    ASSERT_EQ(String("Exemplary"), &front2);
}

TEST_F(StringTest, PrintBackCharacterFunction)
{
    String s("Exemplary");
    char &back1 = s.back();
    ASSERT_EQ('y', back1);
    back1 = 's';
    ASSERT_EQ(String("Exemplars"), s);

    String const c("Exemplary");
    char const &back2 = c.back();
    ASSERT_EQ('y', back2);
}

TEST_F(StringTest, TrimFunction)
{
    String str1 = "   Hello world   ";
    String trimmed1 = str1.trim();
    ASSERT_EQ(String("Helloworld"), trimmed1);

    String str2 = "       ";
    ASSERT_EQ(String("       "), str2);
    String trimmed2 = str2.trim();
    ASSERT_EQ(String(), trimmed2);

    String str3 = "HelloWorld";
    String trimmed3 = str3.trim();
    ASSERT_EQ(String("HelloWorld"), trimmed3);

    String str4;
    String trimmed4 = str4.trim();
    ASSERT_EQ(String(), trimmed4);
}

// TODO: iterator 구현이 완료 되면 begin, end, find 까지 합쳐 통합 테스트 코드 작성
TEST_F(StringTest, EraseFunction)
{
    // origin
    // String s = "This Is An Example";
    // std::cout << "1) " << s << '\n';

    // s.erase(7, 3);
    // std::cout << "2) " << s << '\n';

    // // s.erase(std::find(s.begin(), s.end(), ' '));
    // std::cout << "3) " << s << '\n';

    // // s.erase(s.find(' '));
    // std::cout << "4) " << s << '\n';

    // auto it = std::next(s.begin(), s.find('s'));
    // s.erase(it, std::next(it, 2));
    // std::cout << "5) " << s << '\n';

    //==================================================//

    // str lenght = 13
    String str = "Hello, World!";

    // Erase "World"
    String erased1 = str.erase(7, 5);
    ASSERT_EQ(String("Hello, !"), erased1);

    // Erase "Hello, "
    String erased2 = str.erase(0, 6);
    ASSERT_EQ(String(" World!"), erased2);

    // Erase entire string
    String erased3 = str.erase(0, 13);
    ASSERT_EQ(String(), erased3);

    // Erase more than length
    String erased4 = str.erase(0, 20);
    ASSERT_NE(String("Hello, World!"), erased4);

    // Erase from out-of-bounds index
    String erased5 = str.erase(15, 3);
    ASSERT_EQ(String("Hello, World!"), erased5);

    String emptyStr;
    String erased6 = emptyStr.erase(0, 1);
    ASSERT_EQ(String(), erased6);
}

// TODO: 링크에 있는 test code로 변경 https://en.cppreference.com/w/cpp/string/basic_string/find
TEST_F(StringTest, FindFunction)
{
    String str = "Hello, World!";

    String found1 = str.find("World");
    ASSERT_EQ(String("World"), found1);

    String found2 = str.find("lo");
    ASSERT_EQ(String("lo"), found2);

    String found3 = str.find("foo");
    ASSERT_EQ(String(), found3);

    String emptyStr;
    String found5 = emptyStr.find("bar");
    ASSERT_EQ(String(), found5);

    String found4 = str.find("");
    ASSERT_EQ(String(), found4);
}

TEST_F(StringTest, SubstrFunction)
{
    String a = "0123456789abcdefghij";

    String substr1 = a.substr(10);
    ASSERT_EQ(String("abcdefghij"), substr1);

    String substr2 = a.substr(5, 3);
    ASSERT_EQ(String("567"), substr2);

    String substr3 = a.substr(a.size() - 3, 50); // =(17, 3)
    ASSERT_EQ(String("hij"), substr3);
}

TEST_F(StringTest, EmptyFunction)
{
    String s;
    std::boolalpha(std::cout);
    PRINTLN("s.empty():{}\t s:{}", s.empty(), s);
    ASSERT_EQ(true, s.empty());
    ASSERT_EQ(String(), s);

    s = "Exemplar";
    PRINTLN("s.empty():{}\t s:{}", s.empty(), s);
    ASSERT_EQ(false, s.empty());
    ASSERT_EQ(String("Exemplar"), s);

    s = "";
    PRINTLN("s.empty():{}\t s:{}", s.empty(), s);
    ASSERT_EQ(true, s.empty());
    ASSERT_EQ(String(), s);
}

TEST_F(StringTest, PopBackFunction)
{
    String str("Short string!");
    std::cout << "before=\"" << str << "\"\n";
    ASSERT_EQ(str.size(), 13);

    str.pop_back();
    std::cout << " after=\"" << str << "\"\n";
    ASSERT_EQ(str.size(), 12);

    String str2;
    ASSERT_EQ(str2.size(), 0);

    str2.pop_back();
    ASSERT_EQ(str2.size(), 0);
}

TEST_F(StringTest, PushBackFunction)
{
    String str("Short string");
    std::cout << "1) " << str << " (Size: " << str.size() << ")" << '\n';
    ASSERT_EQ(str.size(), 12);
    ASSERT_EQ(String("Short string"), str);

    str.push_back("!");
    std::cout << "2) " << str << " (Size: " << str.size() << ")" << '\n';
    ASSERT_EQ(str.size(), 13);
    ASSERT_EQ(String("Short string!"), str);
}

TEST_F(StringTest, AtFunction)
{
    String s("message");
    s = "abc";
    s.at(2) = 'x';
    ASSERT_EQ('x', s.at(2));
    ASSERT_EQ(s.size(), 3);

    try
    {
        s.at(3) = 'x';
    }
    catch (std::out_of_range const &exc)
    {
        std::cout << exc.what() << '\n';
    }
}

TEST_F(StringTest, ClearFunction)
{
    String s("Exemplar");
    s.clear();

    ASSERT_TRUE(s.empty());
    ASSERT_EQ(s.size(), 0);

    String s2;
    s2.clear();

    ASSERT_TRUE(s2.empty());
    ASSERT_EQ(s2.size(), 0);
}

TEST_F(StringTest, ReserveFunction)
{
    String s;
    std::cout << "Before: " << s.capacity() << '\n';

    GTEST_SKIP();
}

TEST_F(StringTest, IteratorFunction)
{
    String str = "abcdefg";
    size_t i = 0;

    for (String::Iterator it = str.begin(); it < str.end(); ++it, ++i)
    {
        char expectedChar = str.at(i);
        ASSERT_EQ(expectedChar, *it);
    }
}

TEST_F(StringTest, OriginalStringIteratorFunction)
{
    std::string str = "abcdefg";
    size_t i = 0;

    for (std::string::iterator it = str.begin(); it < str.end(); ++it, ++i)
    {
        char expectedChar = str.at(i);
        ASSERT_EQ(expectedChar, *it);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}