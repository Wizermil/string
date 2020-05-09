#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <catch2/catch.hpp>
#pragma clang diagnostic pop

#include <string/string.hpp>


TEST_CASE("string operation > append", "[string]") {

    SECTION("string& append(size_type count, value_type ch)") {
        {
            wiz::string a;
            a.append(1, 'a');
            REQUIRE(a == "a");
            REQUIRE(a.size() == 1);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"toto", 4};
            a.append(4, 'a');
            REQUIRE(a == "totoaaaa");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            a.append(23, 'a');
            REQUIRE(a == "aaaaaaaaaaaaaaaaaaaaaaa");
            REQUIRE(a.size() == 23);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            a.append(24, 'a');
            REQUIRE(a == "aaaaaaaaaaaaaaaaaaaaaaaa");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
    }

    SECTION("string& append(string const& str)") {
        {
            wiz::string a;
            wiz::string b;
            a.append(b);
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            a.append(b);
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string b{"titi", 4};
            a.append(b);
            REQUIRE(a == "tatatiti");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            a.append(a);
            REQUIRE(a == "tatatata");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tatatatatatatatatatatat", 23};
            a.append(a);
            REQUIRE(a == "tatatatatatatatatatatattatatatatatatatatatatat");
            REQUIRE(a.size() == 46);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            a.append(b);
            REQUIRE(a == "tatalonglonglonglonglonglonglonglong");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            wiz::string b{"longlonglonglonglonglonglonglong", 32};
            a.append(b);
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b{"totototototototototototototototo", 32};
            a.append(b);
            REQUIRE(a == "longlonglonglonglonglonglonglongtotototototototototototototototo");
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& append(string const& str, size_type pos, size_type count = npos)") {
        {
            wiz::string a;
            wiz::string b;
            a.append(b, 0, wiz::string::npos);
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            wiz::string b{"toto", 4};
            a.append(b, 2, wiz::string::npos);
            REQUIRE(a == "to");
            REQUIRE(a.size() == 2);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"toto", 4};
            a.append(a, 2, wiz::string::npos);
            REQUIRE(a == "tototo");
            REQUIRE(a.size() == 6);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string b{"bari", 4};
            a.append(b, 1, 2);
            REQUIRE(a == "totoar");
            REQUIRE(a.size() == 6);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tototototototototototot", 23};
            wiz::string b{"bari", 4};
            a.append(b, 1, 3);
            REQUIRE(a == "totototototototototototari");
            REQUIRE(a.size() == 26);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string b{"abcdefghijklmnopqrstuvwxyz", 26};
            a.append(b, 10, 5);
            REQUIRE(a == "longlonglonglonglonglonglonglongklmno");
            REQUIRE(a.size() == 37);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& append(const_pointer s, size_type count)") {
        {
            wiz::string a;
            a.append("", 0);
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            a.append("longlonglonglonglonglonglonglong", 24);
            REQUIRE(a == "longlonglonglonglonglong");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            a.append("titi", 3);
            REQUIRE(a == "tatatit");
            REQUIRE(a.size() == 7);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            a.append("longlonglonglonglonglonglonglong", 24);
            REQUIRE(a == "tatalonglonglonglonglonglong");
            REQUIRE(a.size() == 28);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            a.append("longlonglonglonglonglonglonglong", 8);
            REQUIRE(a == "longlong");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a.append("totototototototototototototototo", 2);
            REQUIRE(a == "longlonglonglonglonglonglonglongto");
            REQUIRE(a.size() == 34);
            REQUIRE(a.capacity() == 64);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a.append("\0tototototototototototototototot", 32);
            REQUIRE(a == wiz::string{"longlonglonglonglonglonglonglong\0tototototototototototototototot", 64});
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& append(const_pointer s)") {
        {
            wiz::string a;
            a.append("");
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            a.append("longlonglonglonglonglonglonglong");
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            a.append("titi");
            REQUIRE(a == "tatatiti");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            a.append("longlonglonglonglonglonglonglong");
            REQUIRE(a == "tatalonglonglonglonglonglonglonglong");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            a.append("longlonglonglonglonglonglonglong");
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a.append("totototototototototototototototo");
            REQUIRE(a == "longlonglonglonglonglonglonglongtotototototototototototototototo");
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a.append("\0tototototototototototototototot");
            REQUIRE(a == wiz::string{"longlonglonglonglonglonglonglong", 32});
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 32);
        }
    }

    SECTION("string& append(InputIt first, InputIt last)") {
        {
            char const data[] {};
            wiz::string a;
            a.append(&data[0], &data[0] + 0);
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            char const data[] {'t', 'a', 't', 'a'};
            wiz::string a;
            a.append(&data[0], &data[0] + 4);
            REQUIRE(a == "tata");
            REQUIRE(a.size() == 4);
            REQUIRE(a.capacity() == 23);
        }
        {
            char const data[] {'t', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a'};
            wiz::string a;
            a.append(&data[0], &data[0] + 24);
            REQUIRE(a == "tatatatatatatatatatatata");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
        {
            char const data[] {'t', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a',
                't', 'a', 't', 'a'};
            wiz::string a{"bobo", 4};
            a.append(&data[0], &data[0] + 10);
            REQUIRE(a == "bobotatatatata");
            REQUIRE(a.size() == 14);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"bobo", 4};
            a.append(a.data(), a.data() + 2);
            REQUIRE(a == "bobobo");
            REQUIRE(a.size() == 6);
            REQUIRE(a.capacity() == 23);
        }
        {
            char const data[] {'t', 'a', 't', 'a'};
            wiz::string a{"bobo", 4};
            a.append(a.data(), a.data() + 2).append(&data[0], &data[0]+4);
            REQUIRE(a == "bobobotata");
            REQUIRE(a.size() == 10);
            REQUIRE(a.capacity() == 23);
        }
    }

    SECTION("string& append(std::initializer_list<value_type> ilist)") {
        {
            wiz::string a;
            a.append({'a', 'b', 'c', 'd'});
            REQUIRE(a == "abcd");
            REQUIRE(a.size() == 4);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"totototototototototo", 20};
            a.append({'a', 'b', 'c', 'd'});
            REQUIRE(a == "totototototototototoabcd");
            REQUIRE(a.size() == 24);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            a.append({'a', 'b', 'c', 'd'});
            REQUIRE(a == "longlonglonglonglonglonglonglongabcd");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& append(T const& t)") {
        {
            wiz::string a;
            wiz::string_view b;
            a.append(b);
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            wiz::string_view b{"longlonglonglonglonglonglonglong", 32};
            a.append(b);
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string_view b{"titi", 4};
            a.append(b);
            REQUIRE(a == "tatatiti");
            REQUIRE(a.size() == 8);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tata", 4};
            wiz::string_view b{"longlonglonglonglonglonglonglong", 32};
            a.append(b);
            REQUIRE(a == "tatalonglonglonglonglonglonglonglong");
            REQUIRE(a.size() == 36);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a;
            wiz::string_view b{"longlonglonglonglonglonglonglong", 32};
            a.append(b);
            REQUIRE(a == "longlonglonglonglonglonglonglong");
            REQUIRE(a.size() == 32);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string_view b{"totototototototototototototototo", 32};
            a.append(b);
            REQUIRE(a == "longlonglonglonglonglonglonglongtotototototototototototototototo");
            REQUIRE(a.size() == 64);
            REQUIRE(a.capacity() == 64);
        }
    }

    SECTION("string& append(T const& t, size_type pos, size_type count = npos)") {
        {
            wiz::string a;
            wiz::string_view b;
            a.append(b, 0, wiz::string::npos);
            REQUIRE(a == "");
            REQUIRE(a.size() == 0);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a;
            wiz::string_view b{"toto", 4};
            a.append(b, 2, wiz::string::npos);
            REQUIRE(a == "to");
            REQUIRE(a.size() == 2);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"toto", 4};
            wiz::string_view b{"bari", 4};
            a.append(b, 1, 2);
            REQUIRE(a == "totoar");
            REQUIRE(a.size() == 6);
            REQUIRE(a.capacity() == 23);
        }
        {
            wiz::string a{"tototototototototototot", 23};
            wiz::string_view b{"bari", 4};
            a.append(b, 1, 3);
            REQUIRE(a == "totototototototototototari");
            REQUIRE(a.size() == 26);
            REQUIRE(a.capacity() == 46);
        }
        {
            wiz::string a{"longlonglonglonglonglonglonglong", 32};
            wiz::string_view const b{"abcdefghijklmnopqrstuvwxyz", 26};
            a.append(b, 10, 5);
            REQUIRE(a == "longlonglonglonglonglonglonglongklmno");
            REQUIRE(a.size() == 37);
            REQUIRE(a.capacity() == 64);
        }
    }

}
