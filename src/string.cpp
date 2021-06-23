#include <string/string.hpp>

#include <algorithm>
#include <cstring>
#include <utility>

#include <string/details/config.hpp>

namespace wiz {

    // constructor

    string::string() noexcept
    : _rep(nullptr, 0, SHORT_TAG) {}

    string::string(string const& other, size_type pos) {
        size_type str_sz = other.size();
        assert(pos <= str_sz);
        size_type n = str_sz - pos;
        _init(other.data() + pos, n, n);
    }

    string::string(string const& other, size_type pos, size_type count) {
        size_type str_sz = other.size();
        assert(pos <= str_sz);
        size_type n = std::min(count, str_sz - pos);
        _init(other.data() + pos, n, n);
    }

    string::string(size_type count, value_type ch) {
        _init(count, ch);
    }

    string::string(string::const_pointer s, string::size_type count) noexcept {
        assert(s != nullptr);
        _init(s, count, count);
    }

    string::string(const_pointer s) noexcept
    : string(s, details::_length(s)) {}

    string::string(string const& other)
    : _rep(other._rep) {
        if (other._is_long()) {
            _set_long_capacity(other._rep.l.size);
            _rep.l.ptr = details::_allocate(other._rep.l.size + 1);
            details::_copy(_rep.l.ptr, other._rep.l.ptr, other._rep.l.size + 1);
        }
    }

    string::string(string&& other) noexcept
    : _rep(std::move(other._rep)) {}

    string::~string() {
        if (_is_long()) {
            assert(_rep.l.ptr != nullptr);
            details::_deallocate(_rep.l.ptr);
        }
    }

    string& string::operator=(string const& other) {
        if (WIZ_LIKELY(this != &other)) {
            if (_is_long() || other._is_long()) {
                return assign(other.data(), other.size());
            }
            _rep = other._rep;
        }
        return *this;
    }

    string& string::operator=(string&& other) noexcept {
        assert(this != &other);
        if (_is_long()) {
            assert(_rep.l.ptr != nullptr);
            details::_deallocate(_rep.l.ptr);
        }
        _rep = std::move(other._rep);
        return *this;
    }

    string& string::operator=(const_pointer s) {
        return assign(s);
    }

    string& string::operator=(value_type ch) {
        pointer p;
        if (_is_long()) {
            p = _rep.l.ptr;
            _rep.l.size = 1;
        } else {
            p = _rep.s.buffer;
            _set_short_size(1);
        }
        details::_assign(p[0], ch);
        details::_assign(p[1], value_type{});
        return *this;
    }

    string& string::operator=(std::initializer_list<value_type> ilist) {
        return assign(ilist.begin(), ilist.size());
    }

    string& string::assign(size_type count, value_type ch) {
        size_type cap = capacity();
        if (cap < count) {
            size_type sz = size();
            _grow_by(cap, count - cap, sz, 0, sz);
        }
        pointer p = data();
        details::_assign(p, count, ch);
        details::_assign(p[count], value_type{});
        _set_size(count);
        return *this;
    }

    string& string::assign(string const& str) {
        return *this = str;
    }

    string& string::assign(string const& str, size_type pos, size_type count /*= npos*/) {
        size_type sz = str.size();
        assert(pos <= sz);
        return assign(str.data() + pos, std::min(count, sz - pos));
    }

    string& string::assign(string&& str) noexcept {
        *this = std::move(str);
        return *this;
    }

    string& string::assign(const_pointer s, size_type count) {
        assert(count == 0 || s != nullptr);
        size_type cap = capacity();
        if (cap < count) {
            size_type sz = size();
            _grow_by_and_replace(cap, count - cap, sz, 0, sz, count, s);
        } else {
            pointer p = data();
            details::_move(p, s, count);
            details::_assign(p[count], value_type{});
            _set_size(count);
        }
        return *this;
    }

    string& string::assign(const_pointer s) {
        assert(s != nullptr);
        return assign(s, details::_length(s));
    }

    string& string::assign(std::initializer_list<value_type> ilist) {
        return assign(ilist.begin(), ilist.size());
    }

    // access

    string::reference string::at(size_type pos) noexcept { return operator[](pos); }

    string::const_reference string::at(size_type pos) const noexcept { return operator[](pos); }

    string::reference string::operator[](size_type pos) noexcept {
        assert(pos < size());
        if (_is_long()) {
            return _rep.l.ptr[pos];
        }
        return _rep.s.buffer[pos];
    }

    string::const_reference string::operator[](size_type pos) const noexcept {
        assert(pos < size());
        if (_is_long()) {
            return _rep.l.ptr[pos];
        }
        return _rep.s.buffer[pos];
    }

    string::reference string::front() noexcept {
        assert(!empty());
        return operator[](0);
    }

    string::const_reference string::front() const noexcept {
        assert(!empty());
        return operator[](0);
    }

    string::reference string::back() noexcept {
        assert(!empty());
        return operator[](size() - 1);
    }

    string::const_reference string::back() const noexcept {
        assert(!empty());
        return operator[](size() - 1);
    }

    string::const_pointer string::data() const noexcept {
        if (_is_long()) {
            return _rep.l.ptr;
        }
        return _rep.s.buffer;
    }

    string::pointer string::data() noexcept {
        if (_is_long()) {
            return _rep.l.ptr;
        }
        return _rep.s.buffer;
    }

    string::const_pointer string::c_str() const noexcept { return data(); }

    // iterators

    string::iterator string::begin() noexcept {
        if (_is_long()) {
            return _rep.l.ptr;
        }
        return _rep.s.buffer;
    }

    string::const_iterator string::begin() const noexcept {
        if (_is_long()) {
            return _rep.l.ptr;
        }
        return _rep.s.buffer;
    }

    string::const_iterator string::cbegin() const noexcept {
        if (_is_long()) {
            return _rep.l.ptr;
        }
        return _rep.s.buffer;
    }

    string::iterator string::end() noexcept {
        if (_is_long()) {
            return _rep.l.ptr + _rep.l.size;
        }
        return _rep.s.buffer + _get_short_size();
    }

    string::const_iterator string::end() const noexcept {
        if (_is_long()) {
            return _rep.l.ptr + _rep.l.size;
        }
        return _rep.s.buffer + _get_short_size();
    }

    string::const_iterator string::cend() const noexcept {
        if (_is_long()) {
            return _rep.l.ptr + _rep.l.size;
        }
        return _rep.s.buffer + _get_short_size();
    }

    // capacity

    [[nodiscard]] bool string::empty() const noexcept { return size() == 0; }

    string::size_type string::size() const noexcept {
        if (_is_long()) {
            return _rep.l.size;
        }
        return _get_short_size();
    }

    void string::reserve(size_type new_cap) {
        if (WIZ_LIKELY(new_cap > short_string_type::capacity)) {
            new_cap = _recommend(new_cap);
            if (_is_long()) {
                if (WIZ_LIKELY(new_cap > _get_long_capacity())) {
                    pointer str = details::_allocate(new_cap + 1);
                    details::_copy(str, _rep.l.ptr, _rep.l.size + 1);
                    assert(_rep.l.ptr != nullptr);
                    details::_deallocate(_rep.l.ptr);
                    _rep.l.ptr = str;
                    _set_long_capacity(new_cap);
                }
            } else {
                pointer str = details::_allocate(new_cap + 1);
                size_type sz = _get_short_size();
                details::_copy(str, _rep.s.buffer, sz + 1);
                _rep.l.ptr = str;
                _rep.l.size = sz;
                _set_long_capacity(new_cap);
            }
        }
    }

    string::size_type string::capacity() const noexcept {
        if (_is_long()) {
            return _get_long_capacity();
        }
        return short_string_type::capacity;
    }

    void string::shrink_to_fit() {
        if (WIZ_LIKELY(_is_long())) {
            size_type sz = _rep.l.size;
            size_type cap = _get_long_capacity();
            if (WIZ_LIKELY(cap > sz)) {
                if (sz > short_string_type::capacity) {
                    pointer str = details::_allocate(sz + 1);
                    details::_copy(str, _rep.l.ptr, _rep.l.size + 1);
                    assert(_rep.l.ptr != nullptr);
                    details::_deallocate(_rep.l.ptr);
                    _rep.l.ptr = str;
                    _set_long_capacity(sz);
                } else {
                    const_pointer str = _rep.l.ptr;
                    details::_copy(_rep.s.buffer, _rep.l.ptr, _rep.l.size + 1);
                    if (str != nullptr) {
                        details::_deallocate(str);
                    }
                    _set_short_size(sz);
                }
            }
        }
    }

    // operation

    void string::clear() noexcept {
        if (_is_long()) {
            _rep.l.size = 0;
            details::_assign(_rep.l.ptr[0], value_type{});
        } else {
            _rep.s.size = static_cast<unsigned char>(short_string_type::capacity);
            details::_assign(_rep.s.buffer[0], value_type{});
        }
    }

    string& string::insert(size_type index, size_type count, value_type ch) {
        size_type sz = size();
        assert(index <= sz);
        if (WIZ_LIKELY(count != 0)) {
            size_type cap = capacity();
            value_type* p;
            if ((cap - sz) < count) {
                _grow_by(cap, sz + count - cap, sz, index, 0, count);
                p = data();
            } else {
                p = data();
                size_type n_move = sz - index;
                if (n_move != 0) {
                    details::_move(p + index + count, p + index, n_move);
                }
            }
            details::_assign(p + index, count, ch);
            sz += count;
            _set_size(sz);
            details::_assign(p[sz], value_type{});
        }
        return *this;
    }

    string& string::insert(size_type index, const_pointer s) {
        assert(s != nullptr);
        return insert(index, s, details::_length(s));
    }

    string& string::insert(size_type index, const_pointer s, size_type count) {
        assert(count == 0 || s != nullptr);
        size_type sz = size();
        assert(index <= sz);
        size_type cap = capacity();
        if (cap - sz < count) {
            _grow_by_and_replace(cap, sz + count - cap, sz, index, 0, count, s);
        } else {
            if (WIZ_LIKELY(count != 0)) {
                value_type* p = data();
                size_type n_move = sz - index;
                if (n_move != 0) {
                    if (p + index <= s && s < p + sz) {
                        s += count;
                    }
                    details::_move(p + index + count, p + index, n_move);
                }
                details::_move(p + index, s, count);
                sz += count;
                _set_size(sz);
                details::_assign(p[sz], value_type{});
            }
        }
        return *this;
    }

    string& string::insert(size_type index, const string& str) {
        return insert(index, str.data(), str.size());
    }

    string& string::insert(size_type index, const string& str, size_type index_str, size_type count /*= npos*/) {
        size_type str_sz = str.size();
        assert(index_str <= str_sz);
        return insert(index, str.data() + index_str, std::min(count, str_sz - index_str));
    }

    string::iterator string::insert(const_iterator pos, value_type ch) {
        size_type ip = static_cast<size_type>(pos - begin());
        size_type sz = size();
        size_type cap = capacity();
        value_type* p;
        if (cap == sz) {
            _grow_by(cap, 1, sz, ip, 0, 1);
            p = data();
        } else {
            p = data();
            size_type n_move = sz - ip;
            if (n_move != 0) {
                details::_move(p + ip + 1, p + ip, n_move);
            }
        }
        details::_assign(p[ip], ch);
        details::_assign(p[++sz], value_type{});
        _set_size(sz);
        return begin() + static_cast<difference_type>(ip);
    }

    string::iterator string::insert(const_iterator pos, size_type count, value_type ch) {
        difference_type p = pos - begin();
        insert(static_cast<size_type>(p), count, ch);
        return begin() + p;
    }

    string::iterator string::insert(const_iterator pos, std::initializer_list<value_type> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    void string::push_back(value_type ch) {
        size_type cap = capacity();
        size_type sz = size();
        if ((cap - sz) < 1) {
            _grow_by(cap, sz + 1 - cap, sz, sz, 0);
        }
        pointer p = data();
        details::_assign(p[sz], ch);
        sz += 1;
        _set_size(sz);
        details::_assign(p[sz], value_type{});
    }

    void string::pop_back() {
        assert(!empty());
        if (_is_long()) {
            _rep.l.size -= 1;
            details::_assign(_rep.l.ptr[_rep.l.size], value_type{});
        } else {
            size_type sz = _get_short_size() - 1;
            _set_short_size(sz);
            details::_assign(_rep.s.buffer[sz], value_type{});
        }
    }

    string& string::append(size_type count, value_type ch) {
        if (WIZ_LIKELY(count != 0)) {
            size_type cap = capacity();
            size_type sz = size();
            if ((cap - sz) < count) {
                _grow_by(cap, sz + count - cap, sz, sz, 0);
            }
            pointer p = data();
            details::_assign(p + sz, count, ch);
            sz += count;
            _set_size(sz);
            details::_assign(p[sz], value_type{});
        }
        return *this;
    }

    string& string::append(string const& str) { return append(str.data(), str.size()); }

    string& string::append(string const& str, size_type pos, size_type count /*= npos*/) {
        size_type sz = str.size();
        assert(pos <= sz);
        return append(str.data() + pos, std::min(count, sz - pos));
    }

    string& string::append(const_pointer s, size_type count) {
        assert(count == 0 || s != nullptr);
        size_type cap = capacity();
        size_type sz = size();
        if ((cap - sz) < count) {
            _grow_by_and_replace(cap, sz + count - cap, sz, sz, 0, count, s);
        } else {
            if (WIZ_LIKELY(count != 0)) {
                value_type* p = data();
                details::_copy(p + sz, s, count);
                sz += count;
                _set_size(sz);
                details::_assign(p[sz], value_type{});
            }
        }
        return *this;
    }

    string& string::append(const_pointer s) {
        assert(s != nullptr);
        return append(s, details::_length(s));
    }

    string& string::append(std::initializer_list<value_type> ilist) { return append(ilist.begin(), ilist.size()); }

    string& string::operator+=(string const& str) {
        return append(str);
    }

    string& string::operator+=(value_type ch) {
        push_back(ch);
        return *this;
    }

    string& string::operator+=(const_pointer s) {
        return append(s);
    }

    string& string::operator+=(std::initializer_list<value_type> ilist) {
        return append(ilist);
    }

    int string::compare(string const& str) const noexcept { return compare(string_view{str.data(), str.size()}); }

    int string::compare(size_type pos1, size_type count1, string const& str) const { return compare(pos1, count1, str.data(), str.size()); }

    int string::compare(size_type pos1, size_type count1, string const& str, size_type pos2, size_type count2 /*= npos*/) const {
        return compare(pos1, count1, string_view{str.data(), str.size()}, pos2, count2);
    }

    int string::compare(const_pointer s) const {
        assert(s != nullptr);
        return compare(0, npos, s, details::_length(s));
    }

    int string::compare(size_type pos1, size_type count1, const_pointer s) const {
        assert(s != nullptr);
        return compare(pos1, count1, s, details::_length(s));
    }

    int string::compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const {
        assert(count2 == 0 || s != nullptr);
        size_type sz = size();
        assert(pos1 <= sz && count2 != npos);
        size_type rlen = std::min(count1, sz - pos1);
        int result = details::_compare(data() + pos1, s, std::min(rlen, count2));
        if (result == 0) {
            if (rlen < count2) {
                return -1;
            } else if (rlen > count2) {
                return 1;
            }
        }
        return result;
    }

    string& string::replace(string::size_type pos, string::size_type count, string const& str) {
        return replace(pos, count, str.data(), str.size());
    }

    string& string::replace(string::const_iterator first, string::const_iterator last, string const& str) {
        return replace(static_cast<size_type>(first - begin()), static_cast<size_type>(last - first), str.data(), str.size());
    }

    string& string::replace(string::size_type pos, string::size_type count, string const& str, string::size_type pos2, string::size_type count2 /*= npos*/) {
        size_type str_sz = str.size();
        assert(pos2 <= str_sz);
        return replace(pos, count, str.data() + pos2, std::min(count2, str_sz - pos2));
    }

    string& string::replace(string::size_type pos, string::size_type count, string::const_pointer cstr, string::size_type count2) {
        assert(count2 == 0 || cstr != nullptr);
        size_type sz = size();
        assert(pos <= sz);
        count = std::min(count, sz - pos);
        size_type cap = capacity();
        if (cap - sz + count < count2) {
            _grow_by_and_replace(cap, sz - count + count2 - cap, sz, pos, count, count2, cstr);
        } else {
            value_type* p = data();
            if (count != count2) {
                size_type n_move = sz - pos - count;
                if (n_move != 0) {
                    if (count > count2) {
                        details::_move(p + pos, cstr, count2);
                        details::_move(p + pos + count2, p + pos + count, n_move);
                        goto __finish;
                    }
                    if (p + pos < cstr && cstr < p + sz) {
                        if (p + pos + count <= cstr) {
                            cstr += count2 - count;
                        } else {
                            details::_move(p + pos, cstr, count);
                            pos += count;
                            cstr += count2;
                            count2 -= count;
                            count = 0;
                        }
                    }
                    details::_move(p + pos + count2, p + pos + count, n_move);
                }
            }
            details::_move(p + pos, cstr, count2);
        __finish:
            // __sz += __n2 - __n1; in this and the below function below can cause unsigned
            // integer overflow, but this is a safe operation, so we disable the check.
            sz += count2 - count;
            _set_size(sz);
            details::_assign(p[sz], value_type{});
        }
        return *this;
    }

    string& string::replace(string::const_iterator first, string::const_iterator last, string::const_pointer cstr, string::size_type count2) {
        return replace(static_cast<size_type>(first - begin()), static_cast<size_type>(last - first), cstr, count2);
    }

    string& string::replace(string::size_type pos, string::size_type count, string::const_pointer cstr) {
        assert(cstr != nullptr);
        return replace(pos, count, cstr, details::_length(cstr));
    }

    string& string::replace(string::const_iterator first, string::const_iterator last, string::const_pointer cstr) {
        return replace(static_cast<size_type>(first - begin()), static_cast<size_type>(last - first), cstr);
    }

    string& string::replace(string::size_type pos, string::size_type count, string::size_type count2, string::value_type ch) {
        size_type sz = size();
        assert(pos <= sz);
        count = std::min(count, sz - pos);
        size_type cap = capacity();
        pointer p;
        if (cap - sz + count < count2) {
            _grow_by(cap, sz - count + count2 - cap, sz, pos, count, count2);
            p = _rep.l.ptr;
        } else {
            p = data();
            if (count != count2) {
                size_type n_move = sz - pos - count;
                if (n_move != 0) {
                    details::_move(p + pos + count2, p + pos + count, n_move);
                }
            }
        }
        details::_assign(p + pos, count2, ch);
        sz += count2 - count;
        _set_size(sz);
        details::_assign(p[sz], value_type{});
        return *this;
    }

    string& string::replace(string::const_iterator first, string::const_iterator last, string::size_type count2, string::value_type ch) {
        return replace(static_cast<size_type>(first - begin()), static_cast<size_type>(last - first), count2, ch);
    }

    string& string::replace(string::const_iterator first, string::const_iterator last, std::initializer_list<string::value_type> ilist) {
        return replace(first, last, ilist.begin(), ilist.end());
    }

    string string::substr(size_type pos /*= 0*/, size_type count /*= wiz::string::npos*/) const {
        return string(*this, pos, count);
    }

    void string::swap(string& other) noexcept { std::swap(_rep, other._rep); }

    // search

    string::size_type string::find(string const& str, size_type pos /*= 0*/) const noexcept {
        return details::_str_find(data(), size(), str.data(), pos, str.size());
    }

    string::size_type string::find(const_pointer s, size_type pos, size_type count) const {
        assert(count == 0 || s != nullptr);
        return details::_str_find(data(), size(), s, pos, count);
    }

    string::size_type string::find(const_pointer s, size_type pos /*= 0*/) const {
        assert(s != nullptr);
        return details::_str_find(data(), size(), s, pos, details::_length(s));
    }

    string::size_type string::find(value_type ch, size_type pos /*= 0*/) const noexcept {
        return details::_str_find(data(), size(), ch, pos);
    }

    string::size_type string::find_first_of(string const& str, size_type pos /*= 0*/) const noexcept {
        return details::_str_find_first_of(data(), size(), str.data(), pos, str.size());
    }

    string::size_type string::find_first_of(const_pointer s, size_type pos, size_type count) const {
        assert(count == 0 || s != nullptr);
        return details::_str_find_first_of(data(), size(), s, pos, count);
    }

    string::size_type string::find_first_of(const_pointer s, size_type pos /*= 0*/) const {
        assert(s != nullptr);
        return details::_str_find_first_of(data(), size(), s, pos, details::_length(s));
    }

    string::size_type string::find_first_of(value_type ch, size_type pos /*= 0*/) const noexcept {
        return find(ch, pos);
    }

    // helper

    WIZ_HIDDEN void string::_init(const_pointer data, size_type count, size_type capacity) {
        if (count > short_string_type::capacity) {
            capacity = _recommend(capacity);
            _rep.l.ptr = details::_allocate(capacity + 1);
            details::_copy(_rep.l.ptr, data, count);
            details::_assign(_rep.l.ptr[count], value_type{});
            _rep.l.size = count;
            _set_long_capacity(capacity);
        } else {
            details::_copy(_rep.s.buffer, data, count);
            details::_assign(_rep.s.buffer[count], value_type{});
            _set_short_size(count);
        }
    }

    WIZ_HIDDEN void string::_init(size_type count, value_type ch) {
        if (count > short_string_type::capacity) {
            size_type capacity = _recommend(count);
            _rep.l.ptr = details::_allocate(capacity + 1);
            details::_assign(_rep.l.ptr, count, ch);
            details::_assign(_rep.l.ptr[count], value_type{});
            _rep.l.size = count;
            _set_long_capacity(capacity);
        } else {
            details::_assign(_rep.s.buffer, count, ch);
            details::_assign(_rep.s.buffer[count], value_type{});
            _set_short_size(count);
        }
    }

    WIZ_HIDDEN void string::_grow_by(size_type old_cap, size_type delta_cap, size_type old_sz, size_type n_copy, size_type n_del, size_type n_add /*= 0*/) {
        size_type ms = max_size();
        assert(delta_cap <= (ms - old_cap));
        pointer old_p = data();
        size_type cap = old_cap < ((ms >> 1) - details::ALIGN) ? _recommend(std::max(old_cap + delta_cap, old_cap << 1)) : ms - 1;
        pointer p = details::_allocate(cap + 1);
        if (n_copy != 0) {
            details::_copy(p, old_p, n_copy);
        }
        size_type sec_cp_sz = old_sz - n_del - n_copy;
        if (sec_cp_sz != 0) {
            details::_copy(p + n_copy + n_add, old_p + n_copy + n_del, sec_cp_sz);
        }
        if (_is_long()) {
            assert(_rep.l.ptr != nullptr);
            details::_deallocate(old_p);
        }
        _rep.l.ptr = p;
        _set_long_capacity(cap);
    }

    WIZ_HIDDEN void string::_grow_by_and_replace(size_type old_cap, size_type delta_cap, size_type old_sz, size_type n_copy, size_type n_del, size_type n_add,
                                                const_pointer p_new_stuff) {
        size_type ms = max_size();
        assert(delta_cap <= (ms - old_cap - 1));
        pointer old_p = data();
        size_type cap = old_cap < ((ms >> 1) - details::ALIGN) ? _recommend(std::max(old_cap + delta_cap, old_cap << 1)) : ms - 1;
        pointer p = details::_allocate(cap + 1);

        if (n_copy != 0) {
            details::_copy(p, old_p, n_copy);
        }
        if (n_add != 0) {
            details::_copy(p + n_copy, p_new_stuff, n_add);
        }
        size_type sec_cp_sz = old_sz - n_del - n_copy;
        if (sec_cp_sz != 0) {
            details::_copy(p + n_copy + n_add, old_p + n_copy + n_del, sec_cp_sz);
        }
        if (_is_long()) {
            assert(_rep.l.ptr != nullptr);
            details::_deallocate(old_p);
        }
        _rep.l.ptr = p;
        old_sz = n_copy + n_add + sec_cp_sz;
        _rep.l.size = old_sz;
        _set_long_capacity(cap);
        details::_assign(p[old_sz], value_type{});
    }

    // function

    string operator+(string const& lhs, string const& rhs) {
        string r;
        string::size_type lhs_sz = lhs.size();
        string::size_type rhs_sz = rhs.size();
        r._init(lhs.data(), lhs_sz, lhs_sz + rhs_sz);
        r.append(rhs.data(), rhs_sz);
        return r;
    }

    string operator+(string const& lhs, string::const_pointer rhs) {
        string r;
        string::size_type lhs_sz = lhs.size();
        string::size_type rhs_sz = details::_length(rhs);
        r._init(lhs.data(), lhs_sz, lhs_sz + rhs_sz);
        r.append(rhs, rhs_sz);
        return r;
    }

    string operator+(string const& lhs, string::value_type rhs) {
        string r;
        string::size_type lhs_sz = lhs.size();
        r._init(lhs.data(), lhs_sz, lhs_sz + 1);
        r.push_back(rhs);
        return r;
    }

    string operator+(string::const_pointer lhs, string const& rhs) {
        string r;
        string::size_type lhs_sz = details::_length(lhs);
        string::size_type rhs_sz = rhs.size();
        r._init(lhs, lhs_sz, lhs_sz + rhs_sz);
        r.append(rhs.data(), rhs_sz);
        return r;
    }

    string operator+(string::value_type lhs, string const& rhs) {
        string r;
        string::size_type rhs_sz = rhs.size();
        r._init(&lhs, 1, 1 + rhs_sz);
        r.append(rhs.data(), rhs_sz);
        return r;
    }

    string operator+(string&& lhs, string&& rhs) {
        return std::move(lhs.append(rhs));
    }

    string operator+(string&& lhs, string const& rhs) {
        return std::move(lhs.append(rhs));
    }

    string operator+(string&& lhs, string::const_pointer rhs) {
        return std::move(lhs.append(rhs));
    }

    string operator+(string&& lhs, string::value_type rhs) {
        lhs.push_back(rhs);
        return std::move(lhs);
    }

    string operator+(string const& lhs, string&& rhs) {
        return std::move(rhs.insert(0, lhs));
    }

    string operator+(string::const_pointer lhs, string&& rhs) {
        return std::move(rhs.insert(0, lhs));
    }

    string operator+(string::value_type lhs, string&& rhs) {
        rhs.insert(rhs.begin(), lhs);
        return std::move(rhs);
    }

} // namespace wiz
