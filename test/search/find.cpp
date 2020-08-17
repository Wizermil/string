#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string search > find", "[string]") {

    SECTION("size_type find(string const& str, size_type pos = 0) const noexcept") {
        using csize_type = wiz::string::size_type;
        csize_type npos = wiz::string::npos;
        csize_type csz01;

        const char str_lit01[] = "mave";
        const wiz::string str01("mavericks, santa cruz");
        wiz::string str02(str_lit01);
        wiz::string str03("s, s");
        wiz::string str04;

        csz01 = str01.find(str01);
        REQUIRE(csz01 == 0);
        csz01 = str01.find(str01, 4);
        REQUIRE(csz01 == npos);
        csz01 = str01.find(str02, 0);
        REQUIRE(csz01 == 0);
        csz01 = str01.find(str02, 3);
        REQUIRE(csz01 == npos);
        csz01 = str01.find(str03, 0);
        REQUIRE(csz01 == 8);
        csz01 = str01.find(str03, 3);
        REQUIRE(csz01 == 8 );
        csz01 = str01.find(str03, 12);
        REQUIRE(csz01 == npos);

        // An empty string consists of no characters
        // therefore it should be found at every point in a string,
        // except beyond the end
        csz01 = str01.find(str04, 0);
        REQUIRE(csz01 == 0);
        csz01 = str01.find(str04, 5);
        REQUIRE(csz01 == 5);
        csz01 = str01.find(str04, str01.size());
        REQUIRE(csz01 == str01.size());
        csz01 = str01.find(str04, str01.size()+1);
        REQUIRE(csz01 == npos);
    }

    SECTION("size_type find(const_pointer s, size_type pos, size_type count) const") {
        using csize_type = wiz::string::size_type;
        csize_type csz01;

        const char str_lit01[] = "mave";
        const wiz::string str01("mavericks, santa cruz");

        csz01 = str01.find(str_lit01, 0, 3);
        REQUIRE(csz01 == 0);
        csz01 = str01.find(str_lit01, 3, 0);
        REQUIRE(csz01 == 3);
    }

    SECTION("size_type find(const_pointer s, size_type pos = 0) const") {
        {
            wiz::string use {"anu"};
            wiz::string::size_type pos1 = use.find("a", wiz::string::npos);
            REQUIRE(pos1 == wiz::string::npos);
        }
        {
            wiz::string use {"aaa"};
            wiz::string::size_type pos1 = use.find("ab");
            REQUIRE(pos1 == wiz::string::npos);
        }
        {
            using csize_type = wiz::string::size_type;
            csize_type npos = wiz::string::npos;
            csize_type csz01;

            const char str_lit01[] = "mave";
            const wiz::string str01("mavericks, santa cruz");

            csz01 = str01.find(str_lit01);
            REQUIRE(csz01 == 0);
            csz01 = str01.find(str_lit01, 3);
            REQUIRE(csz01 == npos);
        }
    }

    SECTION("size_type find(value_type ch, size_type pos = 0) const noexcept") {
        using csize_type = wiz::string::size_type;
        csize_type npos = wiz::string::npos;
        csize_type csz01, csz02;

        const wiz::string str01("mavericks, santa cruz");

        csz01 = str01.find('z');
        csz02 = str01.size() - 1;
        REQUIRE(csz01 == csz02);
        csz01 = str01.find('/');
        REQUIRE(csz01 == npos);
    }

    SECTION("size_type find(T const& t, size_type pos = 0) const noexcept") {
        wiz::string_view str1("bar");
        wiz::string str2("foobar");

        auto x = str2.find(str1);
        REQUIRE(x == 3);

        x = str2.find(str1, 1);
        REQUIRE(x == 3);
    }

}
