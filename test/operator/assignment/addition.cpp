#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>

TEST_CASE("string operator > assignment > addition", "[string]") {

    SECTION("string& operator+=(string const& str)") {
        {
            wiz::string a;
            wiz::string b;
            a += b;
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            a += b;
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string b{"titi", 4};
            a += b;
            REQUIRE(a == "tatatiti");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            a += a;
            REQUIRE(a == "tatatata");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tatatatatatatatatatatat", 23};
            a += a;
            REQUIRE(a == "tatatatatatatatatatatattatatatatatatatatatatat");
            REQUIRE(a.size() == 46);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            a += b;
            REQUIRE(a == "tatalonglonglonglonglonglonglonglong");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            a += b;
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b{"totototototototototototototototo", 32};
            a += b;
            REQUIRE(a == "longlonglonglonglonglonglonglongtotototototototototototototototo");
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& operator+=(value_type ch)") {
        {
            wiz::string a;
            a += 'a';
            REQUIRE(a == "a");
            REQUIRE(a.size() == 1);
            a += 'b';
            REQUIRE(a == "ab");
            REQUIRE(a.size() == 2);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"toto"};
            a += 'a';
            REQUIRE(a == "totoa");
            REQUIRE(a.size() == 5);
            a += 'b';
            REQUIRE(a == "totoab");
            REQUIRE(a.size() == 6);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tototototototototototo"};
            a += 'a';
            REQUIRE(a == "tototototototototototoa");
            REQUIRE(a.size() == 23);
            REQUIRE(a.capacity() == 23);
            a += 'b';
            REQUIRE(a == "tototototototototototoab");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong"};
            a += 'a';
            REQUIRE(a == "longlonglonglonglonglonglonglonga");
            REQUIRE(a.size() == 33);
            REQUIRE(a.capacity() == 64);
            a += 'b';
            REQUIRE(a == "longlonglonglonglonglonglonglongab");
            REQUIRE(a.size() == 34);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& operator+=(const_pointer s)") {
        {
            wiz::string a;
            a += "";
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            a += "longlonglonglonglonglonglonglong";
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            a += "titi";
            REQUIRE(a == "tatatiti");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            a += "longlonglonglonglonglonglonglong";
            REQUIRE(a == "tatalonglonglonglonglonglonglonglong");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            a += "longlonglonglonglonglonglonglong";
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a += "totototototototototototototototo";
            REQUIRE(a == "longlonglonglonglonglonglonglongtotototototototototototototototo");
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a += "\0tototototototototototototototot";
            REQUIRE(a == wiz::string{"longlonglonglonglonglonglonglong", 32});
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 32);
        }
    }

    SECTION("string& operator+=(std::initializer_list<value_type> ilist)") {
        {
            wiz::string a;
            a += {'a', 'b', 'c', 'd'};
            REQUIRE(a == "abcd");
            REQUIRE(a.size() == 4);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"totototototototototo", 20};
            a += {'a', 'b', 'c', 'd'};
            REQUIRE(a == "totototototototototoabcd");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a += {'a', 'b', 'c', 'd'};
            REQUIRE(a == "longlonglonglonglonglonglonglongabcd");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& operator+=(T const& t)") {
        {
            wiz::string a;
            wiz::string_view b;
            a += b;
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            wiz::string_view b{"longlonglonglonglonglonglonglong", 32};
            a += b;
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string_view b{"titi", 4};
            a += b;
            REQUIRE(a == "tatatiti");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string_view b{"longlonglonglonglonglonglonglong", 32};
            a += b;
            REQUIRE(a == "tatalonglonglonglonglonglonglonglong");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            wiz::string_view b{"longlonglonglonglonglonglonglong", 32};
            a += b;
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string_view b{"totototototototototototototototo", 32};
            a += b;
            REQUIRE(a == "longlonglonglonglonglonglonglongtotototototototototototototototo");
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
    }

}
