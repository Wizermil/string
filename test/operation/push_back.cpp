#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operation > push_back", "[string]") {

    SECTION("void push_back(value_type ch)") {
        {
            wiz::string a;
            a.push_back('a');
            REQUIRE(a == "a");
            REQUIRE(a.size() == 1);
            a.push_back('b');
            REQUIRE(a == "ab");
            REQUIRE(a.size() == 2);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"toto"};
            a.push_back('a');
            REQUIRE(a == "totoa");
            REQUIRE(a.size() == 5);
            a.push_back('b');
            REQUIRE(a == "totoab");
            REQUIRE(a.size() == 6);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tototototototototototo"};
            a.push_back('a');
            REQUIRE(a == "tototototototototototoa");
            REQUIRE(a.size() == 23);
            REQUIRE(a.capacity() == 23);
            a.push_back('b');
            REQUIRE(a == "tototototototototototoab");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong"};
            a.push_back('a');
            REQUIRE(a == "longlonglonglonglonglonglonglonga");
            REQUIRE(a.size() == 33);
            REQUIRE(a.capacity() == 64);
            a.push_back('b');
            REQUIRE(a == "longlonglonglonglonglonglonglongab");
            REQUIRE(a.size() == 34);
            REQUIRE(a.capacity() == 64);
        }
    }

}
