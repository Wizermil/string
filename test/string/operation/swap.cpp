#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operation > swap", "[string]") {

    SECTION("void swap(string& other) noexcept") {
        {
            wiz::string a{"123", 3};
            wiz::string b{"456", 3};
            a.swap(b);
            REQUIRE(a == "456");
            REQUIRE(b == "123");
        }
        {
            wiz::string a{"123", 3};
            wiz::string b;
            a.swap(b);
            REQUIRE(a == "");
            REQUIRE(b == "123");
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b{"totototototototototototototototo", 32};
            a.swap(b);
            REQUIRE(a == "totototototototototototototototo");
            REQUIRE(b == "longlonglonglonglonglonglonglong");
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b;
            a.swap(b);
            REQUIRE(a == "");
            REQUIRE(b == "longlonglonglonglonglonglonglong");
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b{"small", 5};
            a.swap(b);
            REQUIRE(a == "small");
            REQUIRE(b == "longlonglonglonglonglonglonglong");
        }
    }

}
