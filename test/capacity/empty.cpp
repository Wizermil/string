#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string capacity > empty", "[string]") {

    SECTION("[[nodiscard]] bool empty() const noexcept") {
        wiz::string a;
        REQUIRE(a.empty());

        wiz::string b{"toto", 4};
        REQUIRE_FALSE(b.empty());
    }

}
