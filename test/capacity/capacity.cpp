#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string capacity > capacity", "[string]") {

    SECTION("size_type capacity() const noexcept") {
        wiz::string a;
        REQUIRE(a.size() == 0);

        wiz::string b{"toto", 4};
        REQUIRE(b.size() == 4);
    }

}
