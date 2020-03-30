#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operation > pop_back", "[string]") {

    SECTION("void pop_back()") {
        {
            wiz::string a{"toto"};
            a.pop_back();
            REQUIRE(a == "tot");
            REQUIRE(a.size() == 3);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"totototototototototototo"};
            a.pop_back();
            REQUIRE(a == "tototototototototototot");
            REQUIRE(a.size() == 23);
            REQUIRE(a.capacity() == 24);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong"};
            a.pop_back();
            REQUIRE(a == "longlonglonglonglonglonglonglon");
            REQUIRE(a.size() == 31);
            REQUIRE(a.capacity() == 32);
        }
    }

}
