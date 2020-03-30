#pragma once

#if !__has_builtin(__builtin_strlen) || !__has_builtin(__builtin_memcmp)
#    error compiler not supported
#endif

#include <cassert>
#include <cstddef>
#include <cstring>
#include <type_traits>

#include <string/details/config.hpp>

namespace wiz {

    class string_view;

    namespace details {

        WIZ_HIDE_FROM_ABI static constexpr std::size_t const NPOS = ~static_cast<std::size_t>(0);
        WIZ_HIDE_FROM_ABI static constexpr std::size_t const ALIGN = static_cast<std::size_t>(16) / sizeof(std::size_t);

        WIZ_HIDE_FROM_ABI static inline char* _allocate(std::size_t count) noexcept { return new char[count]; }

        WIZ_HIDE_FROM_ABI static inline void _deallocate(char const* p) noexcept { delete[] p; }

        WIZ_HIDE_FROM_ABI static constexpr bool _eq(char c1, char c2) noexcept {
            return c1 == c2;
        }

        WIZ_HIDE_FROM_ABI static constexpr void _assign(char& r, char const& a) noexcept { r = a; }

        WIZ_HIDE_FROM_ABI static constexpr char* _assign(char* p, std::size_t count, char a) noexcept {
            if (WIZ_UNLIKELY(count == 0)) {
                return p;
            }
            return static_cast<char*>(std::memset(p, static_cast<int>(a), count));
        }

        WIZ_HIDE_FROM_ABI static constexpr std::size_t _length(char const* p) noexcept { return __builtin_strlen(p); }

        WIZ_HIDE_FROM_ABI static constexpr char* _copy(char* __restrict__ dest, char const* __restrict__ src, std::size_t count) noexcept {
            assert(src < dest || src >= (dest + count)); // copy overlapped range
            if (WIZ_UNLIKELY(count == 0)) {
                return dest;
            }
            return static_cast<char*>(std::memcpy(dest, src, count));
        }

        WIZ_HIDE_FROM_ABI static constexpr char* _move(char* dest, char const* src, std::size_t count) noexcept {
            if (WIZ_UNLIKELY(count == 0)) {
                return dest;
            }
            return static_cast<char*>(std::memmove(dest, src, count));
        }

        WIZ_HIDE_FROM_ABI static constexpr int _compare(char const* s1, char const* s2, std::size_t n) noexcept {
            if (WIZ_UNLIKELY(n == 0)) {
                return 0;
            }
            return __builtin_memcmp(s1, s2, n);
        }

        WIZ_HIDE_FROM_ABI static constexpr char const* _find(char const* s, std::size_t n, char a) noexcept {
            if (WIZ_UNLIKELY(n == 0)) {
                return nullptr;
            }
            return static_cast<char const*>(std::memchr(s, static_cast<int>(a), n));
        }

        WIZ_HIDE_FROM_ABI static constexpr char const* _search_substring(char const* first1, char const* last1, char const* first2, char const* last2) {
            std::ptrdiff_t len2 = last2 - first2;
            if (WIZ_UNLIKELY(len2 == 0)) {
                return first1;
            }

            std::ptrdiff_t len1 = last1 - first1;
            if (WIZ_UNLIKELY(len1 < len2)) {
                return last1;
            }

            char f2 = *first2;
            while (true) {
                len1 = last1 - first1;
                if (len1 < len2) {
                    return last1;
                }

                first1 = details::_find(first1, static_cast<std::size_t>(len1 - len2 + 1), f2);
                if (first1 == nullptr) {
                    return last1;
                }

                if (details::_compare(first1, first2, static_cast<std::size_t>(len2)) == 0) {
                    return first1;
                }
                ++first1;
            }
        }

        WIZ_HIDE_FROM_ABI static constexpr std::size_t _str_find(char const* p, std::size_t sz, char c, std::size_t pos) noexcept {
            if (WIZ_UNLIKELY(pos >= sz)) {
                return NPOS;
            }
            char const* r = details::_find(p + pos, sz - pos, c);
            if (WIZ_UNLIKELY(r == nullptr)) {
                return NPOS;
            }
            return static_cast<std::size_t>(r - p);
        }

        WIZ_HIDE_FROM_ABI static constexpr std::size_t _str_find(char const* p, std::size_t sz, char const* s, std::size_t pos, std::size_t n) noexcept {
            if (WIZ_UNLIKELY(pos > sz)) {
                return NPOS;
            }
            if (WIZ_UNLIKELY(n == 0)) { // There is nothing to search, just return __pos.
                return pos;
            }
            char const* r = _search_substring(p + pos, p + sz, s, s + n);
            if (WIZ_UNLIKELY(r == p + sz)) {
                return NPOS;
            }
            return static_cast<std::size_t>(r - p);
        }

        template <typename Func>
        WIZ_HIDE_FROM_ABI static constexpr char const* _find_first_of_ce(char const* first1, char const* last1, char const* first2, char const* last2, Func&& pred) {
            for (; first1 != last1; ++first1) {
                for (char const* j = first2; j != last2; ++j) {
                    if (pred(*first1, *j)) {
                        return first1;
                    }
                }
            }
            return last1;
        }

        WIZ_HIDE_FROM_ABI static constexpr std::size_t _str_find_first_of(char const* p, std::size_t sz, char const* s, std::size_t pos, std::size_t n) noexcept {
            if (WIZ_UNLIKELY(pos >= sz || n == 0)) {
                return NPOS;
            }
            char const* r = _find_first_of_ce(p + pos, p + sz, s, s + n, _eq);
            if (WIZ_UNLIKELY(r == p + sz)) {
                return NPOS;
            }
            return static_cast<std::size_t>(r - p);
        }

        template <typename T>
        struct _can_be_converted_to_string_view {
            WIZ_HIDE_FROM_ABI static constexpr bool const value = std::is_convertible_v<T const&, string_view> && !std::is_convertible_v<T const&, char const*>;
        };

        WIZ_HIDE_FROM_ABI static constexpr bool _ptr_in_range(char const* p, char const* first, char const* last) noexcept { return first <= p && p < last; }

        WIZ_HIDE_FROM_ABI static constexpr std::size_t _align_str(std::size_t s) noexcept { return (s + ALIGN - 1) & ~static_cast<std::size_t>(ALIGN - 1); }

    } // namespace details

} // namespace wiz
