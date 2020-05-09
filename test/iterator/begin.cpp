#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string iterator > begin", "[string]") {

    SECTION("iterator begin() noexcept") {
        wiz::string a{"toto", 4};
        REQUIRE(*a.begin() == 't');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(*b.begin() == 'l');

        wiz::string c;
        REQUIRE(*c.begin() == '\0');
    }

    SECTION("const_iterator begin() const noexcept") {
        wiz::string const a{"toto", 4};
        REQUIRE(*a.begin() == 't');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(*b.begin() == 'l');

        wiz::string const c;
        REQUIRE(*c.begin() == '\0');
    }

    SECTION("const_iterator cbegin() const noexcept") {
        wiz::string a{"toto", 4};
        REQUIRE(*a.cbegin() == 't');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(*b.cbegin() == 'l');

        wiz::string c;
        REQUIRE(*c.cbegin() == '\0');
    }

}
