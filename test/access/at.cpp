#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string access > at", "[string]") {

    SECTION("reference at(size_type pos) noexcept") {
        wiz::string a{"small", 5};
        REQUIRE(a.at(0) == 's');
        REQUIRE(a.at(4) == 'l');
        a.at(0) = 't';
        REQUIRE(a.at(0) == 't');
        a.at(4) = 't';
        REQUIRE(a.at(4) == 't');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.at(0) == 'l');
        REQUIRE(b.at(31) == 'g');
        b.at(0) = 't';
        REQUIRE(b.at(0) == 't');
        b.at(31) = 't';
        REQUIRE(b.at(31) == 't');
    }

    SECTION("const_reference at(size_type pos) const noexcept") {
        wiz::string const a{"small", 5};
        REQUIRE(a.at(0) == 's');
        REQUIRE(a.at(4) == 'l');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.at(0) == 'l');
        REQUIRE(b.at(31) == 'g');
    }

}
