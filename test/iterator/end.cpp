#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string iterator > end", "[string]") {

    SECTION("iterator end() noexcept") {
        wiz::string a{"toto", 4};
        REQUIRE(*a.end() == '\0');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(*b.end() == '\0');

        wiz::string c;
        REQUIRE(*c.end() == '\0');
    }

    SECTION("const_iterator end() const noexcept") {
        wiz::string const a{"toto", 4};
        REQUIRE(*a.end() == '\0');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(*b.end() == '\0');

        wiz::string const c;
        REQUIRE(*c.end() == '\0');
    }

    SECTION("const_iterator cend() const noexcept") {
        wiz::string a{"toto", 4};
        REQUIRE(*a.cend() == '\0');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(*b.cend() == '\0');

        wiz::string c;
        REQUIRE(*c.cend() == '\0');
    }

}
