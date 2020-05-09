#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operation > substr", "[string]") {

    SECTION("string substr(size_type pos = 0, size_type count = wiz::string::npos ) const") {
        {
            wiz::string a{"123"};
            REQUIRE(a.substr(0) == "123");
        }
        {
            wiz::string a{"123"};
            REQUIRE(a.substr(0, 2) == "12");
        }
        {
            wiz::string a{"123"};
            REQUIRE(a.substr(1, 2) == "23");
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong"};
            REQUIRE(a.substr(4, 4) == "long");
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong"};
            REQUIRE(a.substr(4, 24) == "longlonglonglonglonglong");
        }
    }

}
