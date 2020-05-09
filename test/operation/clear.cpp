#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>


TEST_CASE("string operation > clear", "[string]") {

    SECTION("void clear() noexcept") {
        wiz::string a{"toto", 4};
        a.clear();
        REQUIRE(a.empty());
        REQUIRE(a.size() == 0);
        REQUIRE(a.capacity() == 23);

        wiz::string b{"longlonglonglonglonglonglonglong", 32};
        b.clear();
        REQUIRE(b.empty());
        REQUIRE(b.size() == 0);
        REQUIRE(b.capacity() == 32);
    }

}

