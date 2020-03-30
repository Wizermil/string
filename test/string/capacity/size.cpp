#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string capacity > size", "[string]") {

    SECTION("size_type size() const noexcept") {
        wiz::string a;
        REQUIRE(a.size() == 0);

        wiz::string b{"toto", 4};
        REQUIRE(b.size() == 4);
    }

}
