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
        {
            wiz::string a{"toto", 4};
            wiz::string::const_pointer b{"toto"};
            REQUIRE(a == b);
        }
        {
            wiz::string const a{"toto", 4};
            wiz::string::const_pointer b{"tata"};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string::const_pointer const b{"t"};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"totototototototototototototototo", 32};
            wiz::string::const_pointer b{"totototototototototototototototo"};
            REQUIRE(a == b);
        }
        {
            wiz::string const a{"totototototototototototototototo", 32};
            wiz::string::const_pointer b{"tatatatatatatatatatatatatatatata"};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"totototototototototototototototo", 32};
            wiz::string::const_pointer const b{"totototototototototototo"};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string::const_pointer b{"totototototototototototototototo"};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string const a{"totototototototototototototototo", 32};
            wiz::string::const_pointer b{"tata"};
            REQUIRE_FALSE(a == b);
        }
    }

    SECTION("bool operator==(string::const_pointer rhs, string const& lhs) noexcept") {
        {
            wiz::string::const_pointer a{"toto"};
            wiz::string b{"toto", 4};
            REQUIRE(a == b);
        }
        {
            wiz::string::const_pointer const a{"toto"};
            wiz::string b{"tata", 4};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string::const_pointer a{"toto"};
            wiz::string const b{"t", 1};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string::const_pointer a{"totototototototototototototototo"};
            wiz::string b{"totototototototototototototototo", 32};
            REQUIRE(a == b);
        }
        {
            wiz::string::const_pointer const a{"totototototototototototototototo"};
            wiz::string b{"tatatatatatatatatatatatatatatata", 32};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string::const_pointer a{"totototototototototototototototo"};
            wiz::string const b{"totototototototototototo", 24};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string::const_pointer a{"toto"};
            wiz::string b{"totototototototototototototototo", 32};
            REQUIRE_FALSE(a == b);
        }
        {
            wiz::string::const_pointer const a{"totototototototototototototototo"};
            wiz::string b{"tata", 4};
            REQUIRE_FALSE(a == b);
        }
    }

}
