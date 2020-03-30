#pragma once

#if !__has_builtin(__builtin_strlen)
#    error compiler not supported
#endif

#include <cassert>

#include <string/details/config.hpp>

namespace wiz {

    class string_view {
    public:
        using value_type = char;
        using size_type = std::size_t;
        using pointer = value_type*;
        using const_pointer = value_type const*;
        using reference = value_type&;
        using const_reference = value_type const&;
        using iterator = pointer;
        using const_iterator = const_pointer;

    private:
        const_pointer _ptr = nullptr;
        size_type _size = 0;

    public:
        static constexpr size_type const npos = ~static_cast<size_type>(0);

        constexpr string_view() noexcept = default;
        constexpr string_view(string_view const& other) noexcept = default;
        constexpr string_view(const_pointer s, size_type count) noexcept
        : _ptr(s)
        , _size(count) {}
        constexpr string_view(const_pointer s) noexcept
        : _ptr(s)
        , _size(details::_length(s)) {}
        constexpr string_view& operator=(string_view const& view) noexcept = default;

        // access
        constexpr const_pointer data() const noexcept { return _ptr; }

        // capacity
        constexpr size_type size() const noexcept { return _size; }

        // operation
        constexpr string_view substr(size_type pos = 0, size_type count = npos) const noexcept {
            assert(pos <= _size);
            return string_view{_ptr + pos, std::min(count, _size - pos)};
        }
        constexpr int compare(string_view sv) const noexcept {
            size_type const rlen = std::min(_size, sv._size);
            int const retval = details::_compare(_ptr, sv._ptr, rlen);
            if (retval == 0) { // first rlen chars matched
                if (_size == sv._size) {
                    return 0;
                } else if (_size < sv._size) {
                    return -1;
                } else {
                    return 1;
                }
            }
            return retval;
        }
        constexpr int compare(size_type pos1, size_type count1, string_view sv) const noexcept { return substr(pos1, count1).compare(sv); }
        constexpr int compare(size_type pos1, size_type count1, string_view sv, size_type pos2, size_type count2) const noexcept {
            return substr(pos1, count1).compare(sv.substr(pos2, count2));
        }
        constexpr int compare(const_pointer s) const noexcept { return compare(string_view{s}); }
        constexpr int compare(size_type pos1, size_type count1, const_pointer s) const noexcept { return substr(pos1, count1).compare(string_view{s}); }
        constexpr int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const noexcept {
            return substr(pos1, count1).compare(string_view{s, count2});
        }
    };

    constexpr bool operator==(string_view lhs, string_view rhs) noexcept {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        return lhs.compare(rhs) == 0;
    }
    constexpr bool operator!=(string_view lhs, string_view rhs) noexcept {
        return !(lhs == rhs);
    }
    constexpr bool operator<(string_view lhs, string_view rhs) noexcept {
        return lhs.compare(rhs) < 0;
    }
    constexpr bool operator<=(string_view lhs, string_view rhs) noexcept {
        return !(rhs < lhs);
    }
    constexpr bool operator>(string_view lhs, string_view rhs) noexcept {
        return rhs < lhs;
    }
    constexpr bool operator>=(string_view lhs, string_view rhs) noexcept {
        return !(lhs < rhs);
    }

} // namespace wiz
