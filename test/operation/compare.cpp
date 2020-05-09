#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operation > compare", "[string]") {

    SECTION("int compare(string const& str ) const noexcept") {
        {
            wiz::string a;
            wiz::string b;
            REQUIRE(a.compare(b) == 0);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string b{"toto", 4};
            REQUIRE(a.compare(b) == 0);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            REQUIRE(a.compare(b) == 0);
        }

        {
            wiz::string a{"1", 1};
            wiz::string b{"1", 1};
            REQUIRE(a.compare(b) == 0);
        }
        {
            wiz::string a{"1", 1};
            wiz::string b{"2", 1};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"2", 1};
            wiz::string b{"1", 1};
            REQUIRE(a.compare(b) > 0);
        }

        {
            wiz::string a{"12", 1};
            wiz::string b{"12", 1};
            REQUIRE(a.compare(b) == 0);
        }
        {
            wiz::string a{"12", 2};
            wiz::string b{"13", 2};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"12", 2};
            wiz::string b{"22", 2};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"13", 2};
            wiz::string b{"12", 2};
            REQUIRE(a.compare(b) > 0);
        }
        {
            wiz::string a{"22", 2};
            wiz::string b{"12", 2};
            REQUIRE(a.compare(b) > 0);
        }

        {
            wiz::string a{"123", 3};
            wiz::string b{"123", 3};
            REQUIRE(a.compare(b) == 0);
        }
        {
            wiz::string a{"123", 3};
            wiz::string b{"223", 3};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"123", 3};
            wiz::string b{"133", 3};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"123", 3};
            wiz::string b{"124", 3};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"223", 3};
            wiz::string b{"123", 3};
            REQUIRE(a.compare(b) > 0);
        }
        {
            wiz::string a{"133", 3};
            wiz::string b{"123", 3};
            REQUIRE(a.compare(b) > 0);
        }
        {
            wiz::string a{"124", 3};
            wiz::string b{"123", 3};
            REQUIRE(a.compare(b) > 0);
        }
    }

    SECTION("int compare(size_type pos1, size_type count1, string const& str) const") {
        {
            wiz::string a{"123", 3};
            wiz::string b{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b) == 0);
            REQUIRE(a.compare(2, wiz::string::npos, b) > 0);
            REQUIRE(a.compare(1, 1, b) > 0);
            REQUIRE(a.compare(1, 3, b) > 0);
            REQUIRE(a.compare(1, 3, b) > 0);
        }
        {
            wiz::string const a{"123", 3};
            wiz::string const b{"421", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b) < 0);
            REQUIRE(a.compare(2, wiz::string::npos, b) < 0);
            REQUIRE(a.compare(1, 1, b) < 0);
            REQUIRE(a.compare(1, 3, b) < 0);
            REQUIRE(a.compare(1, 3, b) < 0);
        }
    }

    SECTION("int compare(size_type pos1, size_type count1, string const& str, size_type pos2, size_type count2 = npos) const") {
        {
            wiz::string a{"123", 3};
            wiz::string b{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b, 0, wiz::string::npos) == 0);
            REQUIRE(a.compare(1, 1, b, 1, 1) == 0);
            REQUIRE(a.compare(1, 1, b, 2, 1) < 0);
        }
        {
            wiz::string a{"123", 3};
            wiz::string b{"421", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b, 0 , wiz::string::npos) < 0);
            REQUIRE(a.compare(0, 1, b, 2 , 1) == 0);
        }
    }

    SECTION("int compare(const_pointer s) const") {
        {
            wiz::string a{"123", 3};
            REQUIRE(a.compare("123") == 0);
        }
        {
            wiz::string a{"123", 3};
            REQUIRE(a.compare("223") < 0);
        }
        {
            wiz::string a{"223", 3};
            REQUIRE(a.compare("123") > 0);
        }
    }

    SECTION("int compare(size_type pos1, size_type count1, const_pointer s) const") {
        {
            wiz::string const a{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, "123") == 0);
        }
        {
            wiz::string const a{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, "421") < 0);
        }
    }

    SECTION("int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const") {
        {
            wiz::string const a{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, "123", 0, wiz::string::npos) == 0);
            REQUIRE(a.compare(1, 1, "123", 1, 1) == 0);
            REQUIRE(a.compare(1, 1, "123", 2, 1) < 0);
        }
        {
            wiz::string const a{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, "421", 0 , wiz::string::npos) < 0);
            REQUIRE(a.compare(0, 1, "421", 2 , 1) == 0);
        }
    }

    SECTION("int compare(T const& t) const noexcept") {
        {
            wiz::string a{"123", 3};
            wiz::string_view b{"123", 3};
            REQUIRE(a.compare(b) == 0);
        }
        {
            wiz::string a{"123", 3};
            wiz::string_view b{"223", 3};
            REQUIRE(a.compare(b) < 0);
        }
        {
            wiz::string a{"223", 3};
            wiz::string_view b{"123", 3};
            REQUIRE(a.compare(b) > 0);
        }
    }

    SECTION("int compare(size_type pos1, size_type count1, T const& t) const") {
        {
            wiz::string const a{"123", 3};
            wiz::string_view b{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b) == 0);
        }
        {
            wiz::string const a{"123", 3};
            wiz::string_view b{"421", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b) < 0);
        }
    }

    SECTION("int compare(size_type pos1, size_type count1, T const& t, size_type pos2, size_type count2 = npos) const") {
        {
            wiz::string const a{"123", 3};
            wiz::string_view b{"123", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b, 0, wiz::string::npos) == 0);
            REQUIRE(a.compare(1, 1, b, 1, 1) == 0);
            REQUIRE(a.compare(1, 1, b, 2, 1) < 0);
        }
        {
            wiz::string const a{"123", 3};
            wiz::string_view b{"421", 3};
            REQUIRE(a.compare(0, wiz::string::npos, b, 0 , wiz::string::npos) < 0);
            REQUIRE(a.compare(0, 1, b, 2 , 1) == 0);
        }
    }

}
