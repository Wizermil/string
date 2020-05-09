#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <cstddef>

#include <string/string.hpp>

TEST_CASE("string capacity > max_size", "[string]") {

    SECTION("size_type max_size() const noexcept") {
        wiz::string a;
        REQUIRE(a.max_size() == ((~static_cast<std::size_t>(0)) >> 2));
    }

}
