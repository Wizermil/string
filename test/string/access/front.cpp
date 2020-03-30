#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string access > front", "[string]") {

    SECTION("reference front() noexcept") {
        wiz::string a{"small", 5};
        REQUIRE(a.front() == 's');
        a.front() = 't';
        REQUIRE(a.front() == 't');

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.front() == 'l');
        b.front() = 't';
        REQUIRE(b.front() == 't');
    }

    SECTION("const_reference front() const noexcept") {
        wiz::string const a{"small", 5};
        REQUIRE(a.front() == 's');

        wiz::string const b{"longlonglonglonglonglonglonglong", 32};
        REQUIRE(b.front() == 'l');
    }

}
