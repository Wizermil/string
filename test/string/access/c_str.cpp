#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string access > c_str", "[string]") {

    SECTION("const_pointer c_str() const noexcept") {
        wiz::string const a{"small", 5};
        REQUIRE(a.c_str()[0] == 's');
        REQUIRE(a.c_str()[4] == 'l');
        REQUIRE(a.c_str()[5] == '\0');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.c_str()[0] == 'l');
        REQUIRE(b.c_str()[31] == 'g');
        REQUIRE(b.c_str()[32] == '\0');

        wiz::string const c;
        REQUIRE(c.c_str()[0] == '\0');
    }

}
