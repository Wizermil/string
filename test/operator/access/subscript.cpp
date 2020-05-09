#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operator > access > subscript", "[string]") {

    SECTION("reference operator[](size_type pos) noexcept") {
        wiz::string a{"small", 5};
        REQUIRE(a[0] == 's');
        REQUIRE(a[4] == 'l');
        a[0] = 't';
        REQUIRE(a[0] == 't');
        a[4] = 't';
        REQUIRE(a[4] == 't');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b[0] == 'l');
        REQUIRE(b[31] == 'g');
        b[0] = 't';
        REQUIRE(b[0] == 't');
        b[31] = 't';
        REQUIRE(b[31] == 't');
    }

    SECTION("const_reference operator[](size_type pos) const noexcept") {
        wiz::string const a{"small", 5};
        REQUIRE(a[0] == 's');
        REQUIRE(a[4] == 'l');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b[0] == 'l');
        REQUIRE(b[31] == 'g');
    }

}
