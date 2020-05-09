#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operator > arithmetic > addition", "[string]") {

    SECTION("string operator+(string const& lhs, string const& rhs)") {
        wiz::string const str_0("costa rica");
        wiz::string str_3("costa ricans");
        wiz::string str_4;
        wiz::string const str_6("ns");
        str_4 = str_0 + str_6;
        REQUIRE(str_4 == str_3);

        wiz::string const s1("small");
        wiz::string s1l("smallsmallsmallsmallsma");
        wiz::string const s1ll("longlonglonglonglonglong");

        REQUIRE(s1 + s1 == wiz::string("smallsmall"));
        REQUIRE(s1 + s1l == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE(s1 + s1ll == wiz::string("smalllonglonglonglonglonglong"));

        REQUIRE(s1l + s1 == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE(s1l + s1l == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE(s1l + s1ll == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));

        REQUIRE(s1ll + s1 == wiz::string("longlonglonglonglonglongsmall"));
        REQUIRE(s1ll + s1l == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));
        REQUIRE(s1ll + s1ll == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string const& lhs, string::const_pointer rhs)") {
        wiz::string str1, str2;
        str1 = wiz::string("8-chars_") + "8-chars_";
        REQUIRE(str1 == "8-chars_8-chars_");
        str2 = str1 + "7-chars";
        REQUIRE(str1 == "8-chars_8-chars_");

        wiz::string const str_0("costa rica");
        wiz::string str_3("costa ricans");
        wiz::string str_4;
        str_4 = str_0 + "ns";
        REQUIRE(str_4 == str_3);

        wiz::string const s1("small");
        REQUIRE(s1 + "small" == wiz::string("smallsmall"));
        REQUIRE(s1 + "smallsmallsmallsmallsma" == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE(s1 + "longlonglonglonglonglong" == wiz::string("smalllonglonglonglonglonglong"));

        wiz::string s1l("smallsmallsmallsmallsma");
        REQUIRE(s1l + "small" == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE(s1l + "smallsmallsmallsmallsma" == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE(s1l + "longlonglonglonglonglong" == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));

        wiz::string const s1ll("longlonglonglonglonglong");
        REQUIRE(s1ll + "small" == wiz::string("longlonglonglonglonglongsmall"));
        REQUIRE(s1ll + "smallsmallsmallsmallsma" == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));
        REQUIRE(s1ll + "longlonglonglonglonglong" == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string const& lhs, string::value_type rhs)") {
        wiz::string const s1("small");
        REQUIRE(s1 + 'a' == wiz::string("smalla"));
        wiz::string s1l("smallsmallsmallsmallsma");
        REQUIRE(s1l + 'a' == wiz::string("smallsmallsmallsmallsmaa"));
        wiz::string const s1ll("longlonglonglonglonglong");
        REQUIRE(s1ll + 'a' == wiz::string("longlonglonglonglonglonga"));

        wiz::string str;
        str = s1 + 'a';
        str = str + 'a';
        REQUIRE(str == wiz::string("smallaa"));
    }

    SECTION("string operator+(string::const_pointer lhs, string const& rhs)") {
        wiz::string str_4;
        wiz::string const str_5(" marbella");
        wiz::string str_1("costa marbella");
        str_4 = "costa" + str_5;
        REQUIRE(str_4 == str_1);
    }

    SECTION("string operator+(string::value_type lhs, string const& rhs)") {
        wiz::string const s1("small");
        REQUIRE('a' + s1 == wiz::string("asmall"));
        wiz::string s1l("smallsmallsmallsmallsma");
        REQUIRE('a' + s1l == wiz::string("asmallsmallsmallsmallsma"));
        wiz::string const s1ll("longlonglonglonglonglong");
        REQUIRE('a' + s1ll == wiz::string("alonglonglonglonglonglong"));

        wiz::string str;
        str = 'a' + s1;
        str = 'a' + str;
        REQUIRE(str == wiz::string("aasmall"));
    }

    SECTION("string operator+(string&& lhs, string&& rhs)") {
        REQUIRE(wiz::string("small") + wiz::string("small") == wiz::string("smallsmall"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + wiz::string("small") == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + wiz::string("small") == wiz::string("longlonglonglonglonglongsmall"));

        REQUIRE(wiz::string("small") + wiz::string("smallsmallsmallsmallsma") == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + wiz::string("smallsmallsmallsmallsma") == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + wiz::string("smallsmallsmallsmallsma") == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));

        REQUIRE(wiz::string("small") + wiz::string("longlonglonglonglonglong") == wiz::string("smalllonglonglonglonglonglong"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + wiz::string("longlonglonglonglonglong") == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + wiz::string("longlonglonglonglonglong") == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string&& lhs, string const& rhs)") {
        wiz::string const s1("small");
        REQUIRE(wiz::string("small") + s1 == wiz::string("smallsmall"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + s1 == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + s1 == wiz::string("longlonglonglonglonglongsmall"));

        wiz::string s1l("smallsmallsmallsmallsma");
        REQUIRE(wiz::string("small") + s1l == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + s1l == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + s1l == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));

        wiz::string const s1ll("longlonglonglonglonglong");
        REQUIRE(wiz::string("small") + s1ll == wiz::string("smalllonglonglonglonglonglong"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + s1ll == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + s1ll == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string&& lhs, string::const_pointer rhs)") {
        REQUIRE(wiz::string("small") + "small" == wiz::string("smallsmall"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + "small" == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + "small" == wiz::string("longlonglonglonglonglongsmall"));

        REQUIRE(wiz::string("small") + "smallsmallsmallsmallsma" == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + "smallsmallsmallsmallsma" == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + "smallsmallsmallsmallsma" == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));

        REQUIRE(wiz::string("small") + "longlonglonglonglonglong" == wiz::string("smalllonglonglonglonglonglong"));
        REQUIRE(wiz::string("smallsmallsmallsmallsma") + "longlonglonglonglonglong" == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + "longlonglonglonglonglong" == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string&& lhs, string::value_type rhs)") {
        REQUIRE(wiz::string("small") + 'a' == wiz::string("smalla") );
        REQUIRE(wiz::string("longlonglonglonglonglon") + 'a' == wiz::string("longlonglonglonglonglona"));
        REQUIRE(wiz::string("longlonglonglonglonglong") + 'a' == wiz::string("longlonglonglonglonglonga"));
    }

    SECTION("string operator+(string const& lhs, string&& rhs)") {
        wiz::string const s1("small");
        REQUIRE(s1 + wiz::string("small") == wiz::string("smallsmall"));
        REQUIRE(s1 + wiz::string("smallsmallsmallsmallsma") == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE(s1 + wiz::string("longlonglonglonglonglong") == wiz::string("smalllonglonglonglonglonglong"));

        wiz::string s1l("smallsmallsmallsmallsma");
        REQUIRE(s1l + wiz::string("small") == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE(s1l + wiz::string("smallsmallsmallsmallsma") == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE(s1l + wiz::string("longlonglonglonglonglong") == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));

        wiz::string const s1ll("longlonglonglonglonglong");
        REQUIRE(s1ll + wiz::string("small") == wiz::string("longlonglonglonglonglongsmall"));
        REQUIRE(s1ll + wiz::string("smallsmallsmallsmallsma") == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));
        REQUIRE(s1ll + wiz::string("longlonglonglonglonglong") == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string::const_pointer lhs, string&& rhs)") {
        REQUIRE("small" + wiz::string("small") == wiz::string("smallsmall"));
        REQUIRE("small" + wiz::string("smallsmallsmallsmallsma") == wiz::string("smallsmallsmallsmallsmallsma"));
        REQUIRE("small" + wiz::string("longlonglonglonglonglong") == wiz::string("smalllonglonglonglonglonglong"));

        REQUIRE("smallsmallsmallsmallsma" + wiz::string("small") == wiz::string("smallsmallsmallsmallsmasmall"));
        REQUIRE("smallsmallsmallsmallsma" + wiz::string("smallsmallsmallsmallsma") == wiz::string("smallsmallsmallsmallsmasmallsmallsmallsmallsma"));
        REQUIRE("smallsmallsmallsmallsma" + wiz::string("longlonglonglonglonglong") == wiz::string("smallsmallsmallsmallsmalonglonglonglonglonglong"));

        REQUIRE("longlonglonglonglonglong" + wiz::string("small") == wiz::string("longlonglonglonglonglongsmall"));
        REQUIRE("longlonglonglonglonglong" + wiz::string("smallsmallsmallsmallsma") == wiz::string("longlonglonglonglonglongsmallsmallsmallsmallsma"));
        REQUIRE("longlonglonglonglonglong" + wiz::string("longlonglonglonglonglong") == wiz::string("longlonglonglonglonglonglonglonglonglonglonglong"));
    }

    SECTION("string operator+(string::value_type lhs, string&& rhs)") {
        REQUIRE('a' + wiz::string("small") == wiz::string("asmall"));
        REQUIRE('a' + wiz::string("smallsmallsmallsmallsma") == wiz::string("asmallsmallsmallsmallsma"));
        REQUIRE('a' + wiz::string("longlonglonglonglonglong") == wiz::string("alonglonglonglonglonglong"));
    }

}
