#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>

#include <string/details/config.hpp>
#include <string/details/helper.hpp>
#include <string/string_view.hpp>

namespace wiz {

    class string {
    public:
        using value_type = char;
        using size_type = std::size_t;
        using pointer = value_type*;
        using const_pointer = value_type const*;
        using reference = value_type&;
        using const_reference = value_type const&;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using difference_type = std::ptrdiff_t;

    private:
        static constexpr size_type const LONG_FLAG = static_cast<size_type>(0xC0ULL);
        static constexpr size_type const LONG_MASK_FLAG = (LONG_FLAG << (((sizeof(size_type) - 1) * 8)));

        struct long_string_type {
            pointer ptr;
            size_type size;
            size_type capacity;
        };

        struct short_string_type {
            static constexpr std::size_t const capacity = sizeof(long_string_type) / sizeof(value_type) - sizeof(unsigned char);
            value_type buffer[capacity];
            unsigned char size;
        };

        static constexpr size_type const SHORT_TAG = short_string_type::capacity << ((sizeof(size_type) - 1) * 8);

        struct raw_string_type {
            static constexpr std::size_t const capacity = sizeof(long_string_type) / sizeof(value_type);
            value_type buffer[capacity];
        };

        union representation_type {
            long_string_type l;
            short_string_type s;
            raw_string_type r;

            WIZ_HIDDEN inline representation_type() noexcept {}
            WIZ_HIDDEN inline representation_type(pointer ptr, size_type size, size_type capacity) noexcept
            : l{ptr, size, capacity} {}
            WIZ_HIDDEN inline representation_type(representation_type const& other) noexcept
            : l(other.l) {}
            WIZ_HIDDEN inline representation_type& operator=(representation_type const& other) noexcept {
                l = other.l;
                return *this;
            }
            WIZ_HIDDEN inline representation_type(representation_type&& other) noexcept
            : l(other.l) {
                other.l.ptr = nullptr;
                other.l.capacity = SHORT_TAG;
            }
            WIZ_HIDDEN inline representation_type& operator=(representation_type&& other) noexcept {
                l = other.l;
                other.l.ptr = nullptr;
                other.l.capacity = SHORT_TAG;
                return *this;
            }
        } _rep;

    public:
        static constexpr size_type const npos = ~static_cast<size_type>(0);

        string() noexcept;
//        string(size_type count, value_type ch);
        string(string const& other, size_type pos);
        string(string const& other, size_type pos, size_type count);
        string(const_pointer s, size_type count) noexcept;
        string(const_pointer s) noexcept;
        template <typename InputIt>
        string(InputIt first, InputIt last) {
            size_type sz = static_cast<size_type>(last - first);
            assert(sz <= max_size());
            if (sz < short_string_type::capacity) {
                for (pointer p = _rep.s.buffer; first != last; ++p, ++first) {
                    details::_assign(*p, *first);
                }
                details::_assign(_rep.s.buffer[sz], value_type{});
                _set_short_size(sz);
            } else {
                _rep.l.ptr = details::_allocate(sz + 1);
                details::_copy(_rep.l.ptr, first, sz);
                details::_assign(_rep.l.ptr[sz], value_type{});
                _rep.l.size = sz;
                _set_long_capacity(sz);
            }
        }
        string(string const& other);
        string(string&& other) noexcept;
//        string(std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        explicit string(T const& t) {
            string_view sv{t};
            size_type sz = sv.size();
            _init(sv.data(), sz, sz);
        }
//        template <typename T>
//        string(T const& t, size_type pos, size_type n);
        ~string();

        string& operator=(string const& other);
        string& operator=(string&& other) noexcept;
        string& operator=(const_pointer s);
        string& operator=(value_type ch);
        string& operator=(std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& operator=(T const& t) {
            string_view sv {t};
            return assign(sv);
        }

        string& assign(size_type count, value_type ch);
        string& assign(string const& str);
        string& assign(string const& str, size_type pos, size_type count = npos);
        string& assign(string&& str) noexcept;
        string& assign(const_pointer s, size_type count);
        string& assign(const_pointer s);
        template <typename InputIt>
        string& assign(InputIt first, InputIt last) {
            size_type count = static_cast<size_type>(last - first);
            assert(count <= max_size());
            size_type cap = capacity();
            if (cap < count) {
                size_type sz = size();
                _grow_by(cap, count - cap, sz, 0, sz);
            }
            pointer p = data();
            if (count < short_string_type::capacity) {
                for (; first != last; ++p, ++first) {
                    details::_assign(*p, *first);
                }
                details::_assign(*p, value_type{});
            } else {
                details::_move(p, first, count);
                details::_assign(_rep.l.ptr[count], value_type{});
            }
            _set_size(count);
            return *this;
        }
        string& assign(std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        string& assign(T const& t) {
            string_view sv {t};
            return assign(sv.data(), sv.size());
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& assign(T const& t, size_type pos, size_type count = npos) {
            string_view sv {t};
            size_type sz = sv.size();
            assert(pos <= sz);
            return assign(sv.data() + pos, std::min(count, sz - pos));
        }

        // access
        reference at(size_type pos) noexcept;
        const_reference at(size_type pos) const noexcept;
        reference operator[](size_type pos) noexcept;
        const_reference operator[](size_type pos) const noexcept;
        reference front() noexcept;
        const_reference front() const noexcept;
        reference back() noexcept;
        const_reference back() const noexcept;
        const_pointer data() const noexcept;
        pointer data() noexcept;
        const_pointer c_str() const noexcept;

        // iterator
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
//        reverse_iterator rbegin() noexcept;
//        const_reverse_iterator rbegin() const noexcept;
//        const_reverse_iterator crbegin() const noexcept;
//        reverse_iterator rend() noexcept;
//        const_reverse_iterator rend() const noexcept;
//        const_reverse_iterator crend() const noexcept;

        // capacity
        [[nodiscard]] bool empty() const noexcept;
        size_type size() const noexcept;
        constexpr size_type max_size() const noexcept { return ~static_cast<size_type>(0) >> 2; }
        void reserve(size_type new_cap);
        size_type capacity() const noexcept;
        void shrink_to_fit();

        // operation
        void clear() noexcept;
        string& insert(size_type index, size_type count, value_type ch);
        string& insert(size_type index, const_pointer s);
        string& insert(size_type index, const_pointer s, size_type count);
        string& insert(size_type index, const string& str);
        string& insert(size_type index, const string& str, size_type index_str, size_type count = npos);
        iterator insert(const_iterator pos, value_type ch);
        iterator insert(const_iterator pos, size_type count, value_type ch);
        template <typename InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last) {
            size_type ip = static_cast<size_type>(pos - begin());
            size_type n = static_cast<size_type>(last - first);
            if (WIZ_LIKELY(n != 0)) {
                if (WIZ_UNLIKELY(details::_ptr_in_range(first, data(), data() + size()))) {
                    string const temp(first, last);
                    return insert(pos, temp.data(), temp.data() + temp.size());
                }

                size_type sz = size();
                size_type cap = capacity();
                value_type* p;
                if (cap - sz < n) {
                    _grow_by(cap, sz + n - cap, sz, ip, 0, n);
                    p = data();
                } else {
                    p = data();
                    size_type n_move = sz - ip;
                    if (n_move != 0) {
                        details::_move(p + ip + n, p + ip, n_move);
                    }
                }
                sz += n;
                _set_size(sz);
                details::_assign(p[sz], value_type{});
                for (p += ip; first != last; ++p, ++first) {
                    details::_assign(*p, *first);
                }
            }
            return begin() + ip;
        }
        iterator insert(const_iterator pos, std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        string& insert(size_type pos, T const& t) {
            string_view sv {t};
            return insert(pos, sv.data(), sv.size());
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& insert(size_type index, T const& t, size_type index_str, size_type count = npos) {
            string_view sv {t};
            size_type str_sz = sv.size();
            assert(index_str <= str_sz);
            return insert(index, sv.data() + index_str, std::min(count, str_sz - index_str));
        }
//        iterator erase(const_iterator position);
//        iterator erase(const_iterator first, const_iterator last);
        void push_back(value_type ch);
        void pop_back();
        string& append(size_type count, value_type ch);
        string& append(string const& str);
        string& append(string const& str, size_type pos, size_type count = npos);
        string& append(const_pointer s, size_type count);
        string& append(const_pointer s);
        template <typename InputIt>
        string& append(InputIt first, InputIt last) {
            size_type sz = size();
            size_type cap = capacity();
            size_type count = static_cast<size_type>(last - first);
            if (WIZ_LIKELY(count != 0)) {
                if (WIZ_UNLIKELY(details::_ptr_in_range(first, data(), data() + size()))) {
                    string temp{first, last};
                    append(temp.data(), temp.size());
                } else {
                    if ((cap - sz) < count) {
                        _grow_by(cap, sz + count - cap, sz, sz, 0);
                        details::_copy(_rep.l.ptr + sz, first, count);
                        _rep.l.size = sz + count;
                        details::_assign(_rep.l.ptr[_rep.l.size], value_type{});
                    } else {
                        pointer p = _rep.s.buffer + sz;
                        for (; first != last; ++p, ++first) {
                            details::_assign(*p, *first);
                        }
                        details::_assign(*p, value_type{});
                        _set_short_size(sz + count);
                    }
                }
            }
            return *this;
        }
        string& append(std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& append(T const& t) {
            string_view sv{t};
            return append(sv.data(), sv.size());
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& append(T const& t, size_type pos, size_type count = npos) {
            string_view sv{t};
            size_type sz = sv.size();
            assert(pos <= sz);
            return append(sv.data() + pos, std::min(count, sz - pos));
        }
        string& operator+=(string const& str);
        string& operator+=(value_type ch);
        string& operator+=(const_pointer s);
        string& operator+=(std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& operator+=(T const& t) {
            string_view sv{t};
            return append(sv);
        }
        int compare(string const& str) const noexcept;
        int compare(size_type pos1, size_type count1, string const& str) const;
        int compare(size_type pos1, size_type count1, string const& str, size_type pos2, size_type count2 = npos) const;
        int compare(const_pointer s) const;
        int compare(size_type pos1, size_type count1, const_pointer s) const;
        int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const;
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        int compare(T const& t) const noexcept {
            string_view sv{t};
            size_type lhs_sz = size();
            size_type rhs_sz = sv.size();
            int const result = details::_compare(data(), sv.data(), std::min(lhs_sz, rhs_sz));
            if (result == 0) {
                if (lhs_sz < rhs_sz) {
                    return -1;
                } else if (lhs_sz > rhs_sz) {
                    return 1;
                }
            }
            return result;
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        int compare(size_type pos1, size_type count1, T const& t) const {
            string_view sv{t};
            return compare(pos1, count1, sv.data(), sv.size());
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        int compare(size_type pos1, size_type count1, T const& t, size_type pos2, size_type count2 = npos) const {
            string_view sv{t};
            return string_view{data(), size()}.substr(pos1, count1).compare(sv.substr(pos2, count2));
        }
//        bool starts_with(string_view sv) const noexcept;
//        bool starts_with(value_type c) const noexcept;
//        bool starts_with(const_pointer s) const;
//        bool ends_with(string_view sv) const noexcept;
//        bool ends_with(value_type c) const noexcept;
//        bool ends_with(const_pointer s) const;
        string& replace(size_type pos, size_type count, string const& str);
        string& replace(const_iterator first, const_iterator last, string const& str);
        string& replace(size_type pos, size_type count, string const& str, size_type pos2, size_type count2 = npos);
        template <typename InputIt>
        string& replace(const_iterator first, const_iterator last, InputIt first2, InputIt last2) {
            string temp(first2, last2);
            return replace(first, last, temp);
        }
        string& replace(size_type pos, size_type count, const_pointer cstr, size_type count2);
        string& replace(const_iterator first, const_iterator last, const_pointer cstr, size_type count2);
        string& replace(size_type pos, size_type count, const_pointer cstr);
        string& replace(const_iterator first, const_iterator last, const_pointer cstr);
        string& replace(size_type pos, size_type count, size_type count2, value_type ch);
        string& replace(const_iterator first, const_iterator last, size_type count2, value_type ch);
        string& replace(const_iterator first, const_iterator last, std::initializer_list<value_type> ilist);
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        string& replace(size_type pos, size_type count, T const& t) {
            string_view sv {t};
            return replace(pos, count, sv.data(), sv.size());
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        string& replace(const_iterator first, const_iterator last, T const& t) {
            return replace(static_cast<size_type>(first - begin()), static_cast<size_type>(last - first), t);
        }
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value && !std::is_same_v<std::remove_cvref_t<T>, string>>* = nullptr>
        string& replace(size_type pos, size_type count, T const& t, size_type pos2, size_type count2 = npos) {
            string_view sv {t};
            size_type str_sz = sv.size();
            assert(pos2 <= str_sz);
            return replace(pos, count, sv.data() + pos2, std::min(count2, str_sz - pos2));
        }
        string substr(size_type pos = 0, size_type count = wiz::string::npos ) const;
//        size_type copy(pointer dest, size_type count, size_type pos = 0) const;
//        void resize(size_type count);
//        void resize(size_type count, value_type ch);
        void swap(string& other) noexcept;

        // search
        size_type find(string const& str, size_type pos = 0) const noexcept;
        size_type find(const_pointer s, size_type pos, size_type count) const;
        size_type find(const_pointer s, size_type pos = 0) const;
        size_type find(value_type ch, size_type pos = 0) const noexcept;
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        size_type find(T const& t, size_type pos = 0) const noexcept {
            string_view sv{t};
            return details::_str_find(data(), size(), sv.data(), pos, sv.size());
        }
//        size_type rfind(string const& str, size_type pos = npos) const noexcept;
//        size_type rfind(const_pointer s, size_type pos, size_type count) const;
//        size_type rfind(const_pointer s, size_type pos = npos) const;
//        size_type rfind(value_type ch, size_type pos = npos) const noexcept;
//        template <typename T>
//        size_type rfind(T const& t, size_type pos = npos) const noexcept;
        size_type find_first_of(string const& str, size_type pos = 0) const noexcept;
        size_type find_first_of(const_pointer s, size_type pos, size_type count) const;
        size_type find_first_of(const_pointer s, size_type pos = 0) const;
        size_type find_first_of(value_type ch, size_type pos = 0) const noexcept;
        template <typename T, std::enable_if_t<details::_can_be_converted_to_string_view<T>::value>* = nullptr>
        size_type find_first_of(T const& t, size_type pos = 0) const noexcept {
            string_view sv {t};
            return details::_str_find_first_of(data(), size(), sv.data(), pos, sv.size());
        }
//        size_type find_first_not_of(string const& str, size_type pos = 0) const noexcept;
//        size_type find_first_not_of(const_pointer s, size_type pos, size_type count) const;
//        size_type find_first_not_of(const_pointer s, size_type pos = 0) const;
//        size_type find_first_not_of(value_type ch, size_type pos = 0) const noexcept;
//        template <typename T>
//        size_type find_first_not_of(T const& t, size_type pos = 0) const noexcept;
//        size_type find_last_of(string const& str, size_type pos = npos) const noexcept;
//        size_type find_last_of(const_pointer s, size_type pos, size_type count) const;
//        size_type find_last_of(const_pointer s, size_type pos = npos) const;
//        size_type find_last_of(value_type ch, size_type pos = npos) const noexcept;
//        template <typename T>
//        size_type find_last_of(T const& t, size_type pos = npos) const noexcept;
//        size_type find_last_not_of(string const& str, size_type pos = npos) const noexcept;
//        size_type find_last_not_of(const_pointer s, size_type pos, size_type count) const;
//        size_type find_last_not_of(const_pointer s, size_type pos = npos) const;
//        size_type find_last_not_of(value_type ch, size_type pos = npos) const noexcept;
//        template <typename T >
//        size_type find_last_not_of(T const& t, size_type pos = npos) const noexcept;

    private:
        friend constexpr bool operator==(string const& lhs, string const& rhs) noexcept;
        friend string operator+(string const& lhs, string const& rhs);
        friend string operator+(string const& lhs, string::const_pointer rhs);
        friend string operator+(string const& lhs, string::value_type rhs);
        friend string operator+(string::const_pointer lhs, string const& rhs);
        friend string operator+(string::value_type lhs, string const& rhs);

        WIZ_HIDDEN constexpr bool _is_long() const noexcept { return _rep.s.size >> 6; }

        WIZ_HIDDEN constexpr void _set_short_size(size_type size) noexcept { _rep.s.size = static_cast<unsigned char>(short_string_type::capacity - size); }

        WIZ_HIDDEN constexpr size_type _get_short_size() const noexcept { return short_string_type::capacity - static_cast<size_type>(_rep.s.size); }

        WIZ_HIDDEN constexpr void _set_long_capacity(size_type count) noexcept { _rep.l.capacity = count | LONG_MASK_FLAG; }

        WIZ_HIDDEN constexpr size_type _get_long_capacity() const noexcept { return _rep.l.capacity & ~LONG_MASK_FLAG; }

        WIZ_HIDDEN constexpr void _set_size(size_type size) noexcept {
            if (_is_long()) {
                _rep.l.size = size;
            } else {
                _set_short_size(size);
            }
        }

        WIZ_HIDDEN void _init(const_pointer data, size_type count, size_type capacity);
        WIZ_HIDDEN void _grow_by(size_type old_cap, size_type delta_cap, size_type old_sz, size_type n_copy, size_type n_del, size_type n_add = 0);
        WIZ_HIDDEN void _grow_by_and_replace(size_type old_cap, size_type delta_cap, size_type old_sz, size_type n_copy, size_type n_del, size_type n_add,
                                                    const_pointer p_new_stuff);

        static constexpr size_type _recommend(size_type s) noexcept {
            if (s > short_string_type::capacity) {
                return details::_align_str(s);
            }
            return short_string_type::capacity;
        }
    };

    // function

    string operator+(string const& lhs, string const& rhs);
    string operator+(string const& lhs, string::const_pointer rhs);
    string operator+(string const& lhs, string::value_type rhs);
    string operator+(string::const_pointer lhs, string const& rhs);
    string operator+(string::value_type lhs, string const& rhs);
    string operator+(string&& lhs, string&& rhs);
    string operator+(string&& lhs, string const& rhs);
    string operator+(string&& lhs, string::const_pointer rhs);
    string operator+(string&& lhs, string::value_type rhs);
    string operator+(string const& lhs, string&& rhs);
    string operator+(string::const_pointer lhs, string&& rhs);
    string operator+(string::value_type lhs, string&& rhs);

    constexpr bool operator==(string const& lhs, string const& rhs) noexcept {
        string::size_type lhs_sz = lhs.size();
        if (lhs_sz != rhs.size()) {
            return false;
        }
        string::const_pointer lp = lhs.data();
        string::const_pointer rp = rhs.data();
        if (lhs._is_long()) {
            return details::_compare(lp, rp, lhs_sz) == 0;
        }

        for (; lhs_sz != 0; --lhs_sz, ++lp, ++rp) {
            if (*lp != *rp) {
                return false;
            }
        }
        return true;
    }
    constexpr bool operator==(string const& lhs, string::const_pointer rhs) noexcept {
        assert(rhs != nullptr);
        string::size_type rhs_sz = details::_length(rhs);
        if (lhs.size() != rhs_sz) {
            return false;
        }
        return lhs.compare(0, string::npos, rhs, rhs_sz) == 0;
    }
    constexpr bool operator==(string::const_pointer lhs, string const& rhs) noexcept {
        assert(lhs != nullptr);
        string::size_type lhs_sz = details::_length(lhs);
        if (lhs_sz != rhs.size()) {
            return false;
        }
        return rhs.compare(0, string::npos, lhs, lhs_sz) == 0;
    }

    constexpr bool operator!=(string const& lhs, string const& rhs) noexcept {
        return !operator==(lhs, rhs);
    }
    constexpr bool operator!=(string::const_pointer lhs, string const& rhs) noexcept {
        return !operator==(lhs, rhs);
    }
    constexpr bool operator!=(string const& lhs, string::const_pointer rhs) noexcept {
        return !operator==(lhs, rhs);
    }

    constexpr bool operator<(string const& lhs, string const& rhs) noexcept {
        return lhs.compare(rhs) < 0;
    }
    constexpr bool operator<(string::const_pointer lhs, string const& rhs) noexcept {
        return rhs.compare(lhs) > 0;
    }
    constexpr bool operator<(string const& lhs, string::const_pointer rhs) noexcept {
        return lhs.compare(rhs) < 0;
    }

    constexpr bool operator<=(string const& lhs, string const& rhs) noexcept {
        return !(rhs < lhs);
    }
    constexpr bool operator<=(string::const_pointer lhs, string const& rhs) noexcept {
        return !(rhs < lhs);
    }
    constexpr bool operator<=(string const& lhs, string::const_pointer rhs) noexcept {
        return !(rhs < lhs);
    }

    constexpr bool operator>(string const& lhs, string const& rhs) noexcept {
        return rhs < lhs;
    }
    constexpr bool operator>(string::const_pointer lhs, string const& rhs) noexcept {
        return rhs < lhs;
    }
    constexpr bool operator>(string const& lhs, string::const_pointer rhs) noexcept {
        return rhs < lhs;
    }

    constexpr bool operator>=(string const& lhs, string const& rhs) noexcept {
        return !(lhs < rhs);
    }
    constexpr bool operator>=(string::const_pointer lhs, string const& rhs) noexcept {
        return !(lhs < rhs);
    }
    constexpr bool operator>=(string const& lhs, string::const_pointer rhs) noexcept {
        return !(lhs < rhs);
    }

} // namespace wiz
