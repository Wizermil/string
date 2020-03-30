#pragma once

extern "C" {
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
}

namespace elixir {

    template <size_t N>
    using StringLiteral = const char[N];

    class StaticString {
    private:
        const char* _str = nullptr;
        size_t _length = 0;
        size_t _hash = 0;

    public:
        constexpr StaticString() noexcept = default;

        template <size_t N>
        constexpr StaticString(const StringLiteral<N>& other) noexcept
        : _str(other),
        _length(N - 1),
        _hash(hash_range(other, other + N - 1)) {
        }

        template<size_t N>
        constexpr StaticString& operator=(StringLiteral<N> const& other) noexcept {
            _str = other;
            _length = N - 1;
            _hash = hash_range(other, other + N - 1);
            return *this;
        }

        constexpr StaticString(const StaticString&) noexcept = default;
        constexpr StaticString& operator=(const StaticString&) noexcept = default;

        constexpr const char* c_str() const noexcept { return _str; }
        constexpr size_t size() const noexcept { return _length; }
        constexpr size_t length() const noexcept { return _length; }
        constexpr bool empty() const noexcept { return size() == 0; }

        constexpr const char* begin() const noexcept { return _str; }
        constexpr const char* end() const noexcept { return _str + _length; }
        constexpr const char* cbegin() const noexcept { return begin(); }
        constexpr const char* cend() const noexcept { return end(); }

        constexpr const char& operator[](size_t pos) const noexcept {
            assert(pos < size());
            return begin()[pos];
        }

        constexpr const char& at(size_t pos) const noexcept {
            assert(pos < size());
            return begin()[pos];
        }

        constexpr const char& front() const noexcept {
            assert(size());
            return begin()[0];
        }

        constexpr const char& back() const noexcept {
            assert(size());
            return begin()[size() - 1];
        }

        constexpr size_t getHash() const noexcept { return _hash; }

    private:
        constexpr int compare(const StaticString& rhs) const noexcept {
            size_t lhs_size = size();
            size_t rhs_size = rhs.size();
            if (lhs_size < rhs_size) return -1;
            if (lhs_size > rhs_size) return 1;
            return strncmp(c_str(), rhs.c_str(), size());
        }

        friend constexpr bool operator==(const StaticString& lhs, StaticString const& rhs) noexcept {
            return (lhs.c_str() == rhs.c_str()) ||
            ((lhs.size() == rhs.size()) && !strncmp(lhs.c_str(), rhs.c_str(), lhs.size()));
        }
        friend constexpr bool operator!=(const StaticString& lhs, const StaticString& rhs) noexcept {
            return !(lhs == rhs);
        }
        friend constexpr bool operator<(const StaticString& lhs, const StaticString& rhs) noexcept {
            return lhs.compare(rhs) < 0;
        }
        friend constexpr bool operator>(const StaticString& lhs, const StaticString& rhs) noexcept {
            return lhs.compare(rhs) > 0;
        }
        friend constexpr bool operator>=(const StaticString& lhs, const StaticString& rhs) noexcept {
            return !(lhs < rhs);
        }
        friend constexpr bool operator<=(const StaticString& lhs, const StaticString& rhs) noexcept {
            return !(lhs > rhs);
        }
    };

    class String {
    private:
        char* _str = nullptr;

    public:
        static constexpr size_t const npos = static_cast<size_t>(-1);

        String() noexcept = default;
        String(const String& rhs) noexcept : String(rhs.c_str(), rhs.size()) {}
        String(String&& rhs) noexcept : _str(rhs._str) { rhs._str = nullptr; }

        String(const char* cstr, size_t length) noexcept;
        String(const char* cstr) noexcept : String(cstr, size_t(cstr ? strlen(cstr) : 0)) {}

        template<size_t N>
        explicit String(StringLiteral<N> const& other) noexcept : String(other, N - 1) {}

        String(const StaticString& s) : String(s.c_str(), s.size()) {}

        template<typename U>
        String(U* first, U* end) {
            const size_t count = static_cast<size_t>(end - first);
            size_t* p = static_cast<size_t*>(malloc(sizeof(size_t) + (count + 1) * sizeof(char)));
            *p = count;
            _str = reinterpret_cast<char*>(p + 1);
            memcpy(_str, first, count);
            _str[count] = '\0';
        }

        String& operator=(const String& rhs) noexcept;

        String& operator=(String&& rhs) noexcept {
            if (_str) {
                free(_str - sizeof(size_t));
            }
            _str = rhs._str;
            rhs._str = nullptr;
            return *this;
        }

        ~String() noexcept {
            if (_str) {
                free(_str - sizeof(size_t));
            }
        }

        void swap(String& other) noexcept {
            auto temp = _str;
            _str = other._str;
            other._str = temp;
        }

        String& append(const String &other) noexcept;
        String substr(size_t pos = 0, size_t n = npos) const noexcept;

        inline String& operator+=(String const& rhs) noexcept { return append(rhs); }

        inline const char* c_str() const noexcept { return _str ? _str : ""; }
        inline size_t size() const noexcept { return _str ? *(reinterpret_cast<size_t*>(_str - sizeof(size_t))) : 0; }
        inline size_t length() const noexcept { return size(); }
        inline bool empty() const noexcept { return size() == 0; }

        inline char* begin() noexcept { return _str; }
        inline char* end() noexcept { return _str + size(); }
        inline const char* begin() const noexcept { return _str; }
        inline const char* end() const noexcept { return _str + size(); }
        inline const char* cbegin() const noexcept { return _str; }
        inline const char* cend() const noexcept { return _str + size(); }

        const char& operator[](size_t pos) const noexcept {
            assert(pos < size());
            return begin()[pos];
        }

        char& operator[](size_t pos) noexcept {
            assert(pos < size());
            return begin()[pos];
        }

        const char& at(size_t pos) const noexcept {
            assert(pos < size());
            return begin()[pos];
        }

        char& at(size_t pos) noexcept {
            assert(pos < size());
            return begin()[pos];
        }

        char& front() noexcept {
            assert(size());
            return begin()[0];
        }

        const char& front() const noexcept {
            assert(size());
            return begin()[0];
        }

        char& back() noexcept {
            assert(size());
            return begin()[size() - 1];
        }

        const char& back() const noexcept {
            assert(size());
            return begin()[size() - 1];
        }

        bool operator==(String const& rhs) const noexcept;

        inline size_t find(const char* s, size_t pos = 0) const noexcept {
            assert(s != nullptr);
            return _str_find(_str, size(), s, pos, _length(s));
        }

        inline size_t find(const String& str, size_t pos = 0) const noexcept {
            return _str_find(_str, size(), str._str, pos, str.size());
        }

        inline size_t find_first_of(const char* s, size_t pos = 0) const noexcept {
            assert(s != nullptr);
            return _str_find_first_of(_str, size(), s, pos, _length(s));
        }

        String& replace(size_t pos, size_t n1, const char* s, size_t n2) noexcept;

        inline String& replace(size_t pos, size_t n, const String& str) noexcept {
            return replace(pos, n, str._str, str.size());
        }

        inline String& replace(const char* first, const char* last, const String& str) noexcept {
            return replace(static_cast<size_t>(first - begin()), static_cast<size_t>(last - first), str._str, str.size());
        }

        inline String& replace(size_t pos, size_t count, const char* cstr) noexcept {
            assert(cstr != nullptr); // String::replace received nullptr
            return replace(pos, count, cstr, _length(cstr));
        }

        String& replace(size_t pos, size_t count, size_t count2, char ch) noexcept;

    private:
        int compare(const String& rhs) const noexcept;

        friend bool operator==(const String& lhs, const char* rhs) noexcept {
            return (lhs.c_str() == rhs) || !strcmp(lhs.c_str(), rhs);
        }

        friend bool operator==(const String& lhs, const StaticString& rhs) noexcept {
            return (lhs.c_str() == rhs.c_str()) ||
            ((lhs.size() == rhs.size()) && !strncmp(lhs.c_str(), rhs.c_str(), lhs.size()));
        }

        friend String operator+(String const& lhs, String const& rhs) noexcept {
            String result(lhs);
            return String(result.append(rhs));
        }

        friend bool operator!=(String const& lhs, String const& rhs) noexcept {
            return !(lhs == rhs);
        }

        friend bool operator<(String const& lhs, String const& rhs) noexcept {
            return lhs.compare(rhs) < 0;
        }

        friend bool operator>(String const& lhs, String const& rhs) noexcept {
            return lhs.compare(rhs) > 0;
        }

        friend bool operator>=(String const& lhs, String const& rhs) noexcept {
            return !(lhs < rhs);
        }

        friend bool operator<=(String const& lhs, String const& rhs) noexcept {
            return !(lhs > rhs);
        }

        static constexpr size_t _str_find(const char* p, size_t sz, const char* s, size_t pos, size_t n) noexcept {
            if (pos > sz) {
                return npos;
            }

            if (n == 0) {
                return pos;
            }

            const char* r = _search_substring(p + pos, p + sz, s, s + n);

            if (r == p + sz) {
                return npos;
            }
            return static_cast<size_t>(r - p);

        }

        static constexpr size_t _str_find_first_of(const char* p, size_t sz, const char* s, size_t pos, size_t n) noexcept {
            if (pos > sz) {
                return npos;
            }

            if (n == 0) {
                return pos;
            }

            size_t fpos = npos;
            size_t len = n;
            while (len > 0)
            {
                char* f = __builtin_strchr(p + pos, *s);
                if (f != nullptr) {
                    size_t tpos = static_cast<size_t>(f - p);
                    if (fpos == npos || tpos < fpos)
                        fpos = tpos;
                }

                s++;
                len--;
            }

            return fpos;
        }

        static constexpr const char* _search_substring(const char* first1, const char* last1, const char* first2, const char* last2) noexcept {
            const ptrdiff_t len2 = last2 - first2;
            if (len2 == 0) {
                return first1;
            }

            ptrdiff_t len1 = last1 - first1;
            if (len1 < len2) {
                return last1;
            }

            char f2 = *first2;
            while (true) {
                len1 = last1 - first1;

                if (len1 < len2) {
                    return last1;
                }

                first1 = _find(first1, static_cast<size_t>(len1 - len2 + 1), f2);
                if (first1 == nullptr) {
                    return last1;
                }

                if (_compare(first1, first2, static_cast<size_t>(len2)) == 0)
                    return first1;

                ++first1;
            }
        }

        static constexpr const char* _find(const char* s, size_t n, const char& a) noexcept {
            if (n == 0) {
                return nullptr;
            }
            return __builtin_char_memchr(s, static_cast<int>(a), n);
        }

        static constexpr int _compare(const char* s1, const char* s2, size_t n) noexcept {
            if (n == 0) {
                return 0;
            }
            return __builtin_memcmp(s1, s2, n);
        }

        static constexpr size_t _length(const char* s) noexcept {
            return __builtin_strlen(s);
        }

        static inline char* _move(char* s1, const char* s2, size_t n) noexcept {
            return n == 0 ? s1 : static_cast<char*>(memmove(s1, s2, n));
        }

        static inline char* _copy(char* __restrict__ s1, const char* __restrict__ s2, size_t n) noexcept {
            assert(s2 < s1 || s2 >= s1 + n); // copy overlapped range
            return n == 0 ? s1 : static_cast<char*>(memcpy(s1, s2, n));
        }

        void _grow_by_and_replace(size_t old_sz, size_t n_copy, size_t n_del, size_t n_add,
                                  const char* p_new_stuff) noexcept;

        void _grow_by(size_t old_sz, size_t n_copy, size_t n_del, size_t n_add) noexcept;

        static inline char* _assign(char* s, size_t n, char a) noexcept {
            return n == 0 ? s : static_cast<char*>(memset(s, static_cast<int>(static_cast<unsigned char>(a)), n));
        }
    };

}
