#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string access > back", "[string]") {

    SECTION("reference back() noexcept") {
        wiz::string a{"small", 5};
        REQUIRE(a.back() == 'l');
        a.back() = 't';
        REQUIRE(a.back() == 't');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.back() == 'g');
        b.back() = 't';
        REQUIRE(b.back() == 't');
    }

    SECTION("const_reference back() const noexcept") {
        wiz::string const a{"small", 5};
        REQUIRE(a.back() == 'l');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.back() == 'g');
    }

}
