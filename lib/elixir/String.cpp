#include "String.hpp"

extern "C" {
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
}

#ifndef MIN
#    define MIN(m_a, m_b) (((m_a) < (m_b)) ? (m_a) : (m_b))
#endif

#include <new>

using namespace elixir;

String::String(const char *cstr, size_t length) noexcept {
    if (length && cstr) {
        size_t *p = static_cast<size_t*>(malloc(sizeof(size_t) + length + 1));
        *p = length;
        _str = reinterpret_cast<char*>(p + 1);
        char *dest = _str;
        size_t n = length;
        while (n > 0) {
            new(dest) char(*cstr);
            ++dest;
            ++cstr;
            --n;
        }
        *dest = '\0';
    }
}

String &String::operator=(const String &rhs) noexcept {
    if (this != &rhs) {
        auto const p = _str ? _str - sizeof(size_t) : nullptr;
        new(this) String(rhs);
        free(p);
    }
    return *this;
}

String &String::append(const String &other) noexcept {
    if (other.size() == 0) {
        return (*this);
    }

    if (_str) {
        size_t old_len = size();
        size_t new_len = old_len + other.size();
        // allocated storage starts at _data - 1.
        size_t *p = static_cast<size_t*>(realloc(_str - sizeof(size_t), sizeof(size_t) + new_len + 1));
        *p = new_len;
        _str = reinterpret_cast<char*>(p + 1);
        const char *src = other.c_str();
        char *dest = _str + old_len;
        size_t n = other.size() + 1;
        while (n > 0) {
            new(dest) char(*src);
            ++src;
            ++dest;
            --n;
        }
    } else {
        new(this) String(other);
    }

    return *this;
}

String String::substr(size_t pos, size_t n) const noexcept {
    size_t len = size();
    assert(pos <= len);
    
    if (pos == len)
        return(String(""));

    size_t new_len = len - pos;
    if (n != npos && n < new_len)
        new_len = n;

    return(String(c_str() + pos, new_len));
}

bool String::operator==(String const& rhs) const noexcept {
    return (_str == rhs._str) ||
    ((size() == rhs.size()) && !strncmp(_str, rhs._str, size()));
}

String& String::replace(size_t pos, size_t n1, const char* s, size_t n2) noexcept {
    assert(n2 == 0 || s != nullptr); // "String::replace received nullptr"
    size_t sz = size();
    assert(pos <= sz); // "out of range"

    n1 = MIN(n1, sz - pos);
    if (n1 >= n2) {
        char* p = _str;
        if (n1 != n2) {
            const size_t n_move = sz - pos - n1;
            if (n_move != 0) {
                if (n1 > n2) {
                    _move(p + pos, s, n2);
                    _move(p + pos + n2, p + pos + n1, n_move);
                    goto __finish;
                }
                if (p + pos < s && s < p + sz) {
                    if (p + pos + n1 <= s) {
                        s += n2 - n1;
                    } else { // __p + __pos < __s < __p + __pos + __n1
                        _move(p + pos, s, n1);
                        pos += n1;
                        s += n2;
                        n2 -= n1;
                        n1 = 0;
                    }
                }
                _move(p + pos + n2, p + pos + n1, n_move);
            }
        }
        _move(p + pos, s, n2);
    __finish:
        // sz += n2 - n1; in this and the below function below can cause unsigned integer overflow
        sz += n2 - n1;
        if (_str != nullptr) {
            *(reinterpret_cast<size_t*>(_str - sizeof(size_t))) = sz;
            p[sz] = '\0';
        }
    }
    else
        _grow_by_and_replace(sz, pos, n1, n2, s);
    return *this;
}

String& String::replace(size_t pos, size_t n1, size_t n2, char c) noexcept {
    size_t sz = size();
    assert(pos <= sz); // "out of range"

    n1 = MIN(n1, sz - pos);
    char* p;
    if (n1 >= n2) {
        p = _str;
        if (n1 != n2) {
            size_t n_move = sz - pos - n1;
            if (n_move != 0) {
                _move(p + pos + n2, p + pos + n1, n_move);
            }
        }
    } else {
        _grow_by(sz, pos, n1, n2);
        p = _str;
    }
    _assign(p + pos, n2, c);
    sz += n2 - n1;
    if (_str != nullptr) {
        *(reinterpret_cast<size_t*>(_str - sizeof(size_t))) = sz;
        p[sz] = '\0';
    }
    return *this;
}

int String::compare(const String& rhs) const noexcept {
    return strcmp(_str, rhs._str);
}

void String::_grow_by_and_replace(size_t old_sz, size_t n_copy, size_t n_del, size_t n_add,
                                  const char* p_new_stuff) noexcept
{
    const size_t sz = n_add + old_sz - n_del;
    assert(sz <= SIZE_MAX - 1); // length_error

    char* old_p = _str;
    char* p = static_cast<char*>(malloc(sizeof(size_t) + (sz + 1) * sizeof(char))) + sizeof(size_t);

    if (n_copy != 0) {
        _copy(p, old_p, n_copy);
    }
    if (n_add != 0) {
        _copy(p + n_copy, p_new_stuff, n_add);
    }
    const size_t sec_cp_sz = old_sz - n_del - n_copy;
    if (sec_cp_sz != 0) {
        _copy(p + n_copy + n_add, old_p + n_copy + n_del, sec_cp_sz);
    }
    if (old_p != nullptr) {
        free(old_p - sizeof(size_t));
    }
    _str = p;
    *(reinterpret_cast<size_t*>(_str - sizeof(size_t))) = sz;
    p[sz] = '\0';
}

void String::_grow_by(size_t old_sz, size_t n_copy,  size_t n_del, size_t n_add) noexcept {
    const size_t sz = n_add + old_sz - n_del;
    assert(sz <= SIZE_MAX - 1); // length_error

    char* old_p = _str;
    char* p = static_cast<char*>(malloc(sizeof(size_t) + (sz + 1) * sizeof(char))) + sizeof(size_t);

    if (n_copy != 0) {
        _copy(p, old_p, n_copy);
    }
    const size_t sec_cp_sz = old_sz - n_del - n_copy;
    if (sec_cp_sz != 0) {
        _copy(p + n_copy + n_add, old_p + n_copy + n_del, sec_cp_sz);
    }
    if (old_p != nullptr) {
        free(old_p - sizeof(size_t));
    }
    _str = p;
    *(reinterpret_cast<size_t*>(_str - sizeof(size_t))) = sz;
    p[sz] = '\0';
}
