#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operator > comparison > equalto", "[string]") {

    SECTION("bool operator==(string const& lhs, string const& rhs) noexcept") {
        {
            wiz::string a{"toto", 4};
            wiz::string b{"toto", 4};
            REQUIRE(a == b);
        }
        {
            wiz::string const a{"toto", 4};
            wiz::string b{"tata", 4};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string const b{"t", 1};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"totototototototototototototototo", 32};
            wiz::string b{"totototototototototototototototo", 32};
            REQUIRE(a == b);
        }
        {
            wiz::string const a{"totototototototototototototototo", 32};
            wiz::string b{"tatatatatatatatatatatatatatatata", 32};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"totototototototototototototototo", 32};
            wiz::string const b{"totototototototototototo", 24};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string b{"totototototototototototototototo", 32};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string const a{"totototototototototototototototo", 32};
            wiz::string b{"tata", 4};
            REQUIRE_FALSE(a == b);
        }
    }

    SECTION("bool operator==(string const& lhs, string::const_pointer rhs) noexcept") {
#warning TODO
    }

    SECTION("bool operator==(string::const_pointer rhs, string const& lhs) noexcept") {
#warning TODO
    }

}
