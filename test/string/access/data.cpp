#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string access > data", "[string]") {

    SECTION("const_pointer data() const noexcept") {
        wiz::string const a{"small", 5};
        REQUIRE(a.data()[0] == 's');
        REQUIRE(a.data()[4] == 'l');
        REQUIRE(a.data()[5] == '\0');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.data()[0] == 'l');
        REQUIRE(b.data()[31] == 'g');
        REQUIRE(b.data()[32] == '\0');

        wiz::string const c;
        REQUIRE(c.data()[0] == '\0');
    }

    SECTION("pointer data() noexcept") {
        wiz::string a{"small", 5};
        REQUIRE(a.data()[0] == 's');
        REQUIRE(a.data()[4] == 'l');
        REQUIRE(a.data()[5] == '\0');
        a.data()[0] = 't';
        REQUIRE(a.data()[0] == 't');
        a.data()[4] = 't';
        REQUIRE(a.data()[4] == 't');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.data()[0] == 'l');
        REQUIRE(b.data()[31] == 'g');
        REQUIRE(b.data()[32] == '\0');
        b.data()[0] = 't';
        REQUIRE(b.data()[0] == 't');
        b.data()[31] = 't';
        REQUIRE(b.data()[31] == 't');

        wiz::string const c;
        REQUIRE(c.data()[0] == '\0');
    }

}
