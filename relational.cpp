/*
    Copyright (C) 2009, Ferruccio Barletta (ferruccio.barletta@gmail.com)

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#include "dynamic.h"

namespace dynamic {

    /*  ==
    */
    bool var::operator == (int n) const {
        return is_int() && get<int_t>(_var) == n;
    }

    bool var::operator == (double n) const {
        return is_double() && get<double_t>(_var) == n;
    }

    bool var::operator == (const string& s) const {
        return is_string() && *get<string_t>(_var).ps == s;
    }

    bool var::operator == (const char* s) const {
        return is_string() && *get<string_t>(_var).ps == s;
    }

    bool var::operator == (const var& v) const {
        struct eq_visitor : public boost::static_visitor<bool> {
            eq_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { return _rhs.is_null(); }
            bool operator () (int_t n) const { return _rhs.is_int() && n == int(_rhs); }
            bool operator () (double_t n) const { return _rhs.is_double() && n == double(_rhs); }
            bool operator () (string_t s) const { return _rhs.is_string() && *s.ps == string(_rhs); }
            bool operator () (list_ptr) const { return false; }
            bool operator () (array_ptr) const { return false; }
            bool operator () (set_ptr) const { return false; }
            bool operator () (dict_ptr) const { return false; }

            const var& _rhs;
        };
    
        eq_visitor eqvis(v);
        return boost::apply_visitor(eqvis, _var);
    }

    /*  !=
    */
    bool var::operator != (int n) const {
        return !is_int() || get<int_t>(_var) != n;
    }

    bool var::operator != (double n) const {
        return !is_double() || get<double_t>(_var) != n;
    }

    bool var::operator != (const string& s) const {
        return !is_string() || *get<string_t>(_var).ps != s;
    }

    bool var::operator != (const char* s) const {
        return !is_string() || *get<string_t>(_var).ps != s;
    }

    bool var::operator != (const var& v) const {
        struct eq_visitor : public boost::static_visitor<bool> {
            eq_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { return !_rhs.is_null(); }
            bool operator () (int_t n) const { return !_rhs.is_int() || n != int(_rhs); }
            bool operator () (double_t n) const { return !_rhs.is_double() || n != double(_rhs); }
            bool operator () (string_t s) const { return !_rhs.is_string() || *s.ps != string(_rhs); }
            bool operator () (list_ptr) const { return false; }
            bool operator () (array_ptr) const { return false; }
            bool operator () (set_ptr) const { return false; }
            bool operator () (dict_ptr) const { return false; }

            const var& _rhs;
        };
    
        eq_visitor evis(v);
        return boost::apply_visitor(evis, _var);
    }

    /*  <
    */
    bool var::operator < (int n) const {
        if (is_int()) return get<int_t>(_var) < n;
        throw exception("invalid < comparison to int");
    }

    bool var::operator < (double n) const {
        if (is_double()) return get<double_t>(_var) < n;
        throw exception("invalid < comparison to double");
    }

    bool var::operator < (const string& s) const {
        if (is_string()) return *get<string_t>(_var).ps < s;
        throw exception("invalid < comparison to string");
    }

    bool var::operator < (const char* s) const {
        if (is_string()) return *get<string_t>(_var).ps < s;
        throw exception("invalid < comparison to char*");
    }

    bool var::operator < (const var& v) const {
        struct lt_visitor : public boost::static_visitor<bool> {
            lt_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { throw exception("invalid < comparison to $"); }
            bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid < comparison to int"); return n < int(_rhs); }
            bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid < comparison to double"); return n < double(_rhs); }
            bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid < comparison to string"); return *s.ps < string(_rhs); }
            bool operator () (list_ptr) const { throw exception("invalid < comparison to list"); }
            bool operator () (array_ptr) const { throw exception("invalid < comparison to array"); }
            bool operator () (set_ptr) const { throw exception("invalid < comparison to set"); }
            bool operator () (dict_ptr) const { throw exception("invalid < comparison to dict"); }

            const var& _rhs;
        };
    
        lt_visitor ltvis(v);
        return boost::apply_visitor(ltvis, _var);
    }

    /*  <=
    */
    bool var::operator <= (int n) const {
        if (is_int()) return get<int_t>(_var) <= n;
        throw exception("invalid <= comparison to int");
    }

    bool var::operator <= (double n) const {
        if (is_double()) return get<double_t>(_var) <= n;
        throw exception("invalid <= comparison to double");
    }

    bool var::operator <= (const string& s) const {
        if (is_string()) return *get<string_t>(_var).ps <= s;
        throw exception("invalid <= comparison to string");
    }

    bool var::operator <= (const char* s) const {
        if (is_string()) return *get<string_t>(_var).ps <= s;
        throw exception("invalid <= comparison to char*");
    }

    bool var::operator <= (const var& v) const {
        struct le_visitor : public boost::static_visitor<bool> {
            le_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { throw exception("invalid <= comparison to $"); }
            bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid <= comparison to int"); return n <= int(_rhs); }
            bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid <= comparison to double"); return n <= double(_rhs); }
            bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid <= comparison to string"); return *s.ps <= string(_rhs); }
            bool operator () (list_ptr) const { throw exception("invalid <= comparison to list"); }
            bool operator () (array_ptr) const { throw exception("invalid <= comparison to array"); }
            bool operator () (set_ptr) const { throw exception("invalid <= comparison to set"); }
            bool operator () (dict_ptr) const { throw exception("invalid <= comparison to dict"); }

            const var& _rhs;
        };
    
        le_visitor levis(v);
        return boost::apply_visitor(levis, _var);
    }

    /*  >
    */
    bool var::operator > (int n) const {
        if (is_int()) return get<int_t>(_var) > n;
        throw exception("invalid > comparison to int");
    }

    bool var::operator > (double n) const {
        if (is_double()) return get<double_t>(_var) > n;
        throw exception("invalid > comparison to double");
    }

    bool var::operator > (const string& s) const {
        if (is_string()) return *get<string_t>(_var).ps > s;
        throw exception("invalid > comparison to string");
    }

    bool var::operator > (const char* s) const {
        if (is_string()) return *get<string_t>(_var).ps > s;
        throw exception("invalid > comparison to char*");
    }

    bool var::operator > (const var& v) const {
        struct gt_visitor : public boost::static_visitor<bool> {
            gt_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { throw exception("invalid > comparison to $"); }
            bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid > comparison to int"); return n > int(_rhs); }
            bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid > comparison to double"); return n > double(_rhs); }
            bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid > comparison to string"); return *s.ps > string(_rhs); }
            bool operator () (list_ptr) const { throw exception("invalid > comparison to list"); }
            bool operator () (array_ptr) const { throw exception("invalid > comparison to array"); }
            bool operator () (set_ptr) const { throw exception("invalid > comparison to set"); }
            bool operator () (dict_ptr) const { throw exception("invalid > comparison to dict"); }

            const var& _rhs;
        };
    
        gt_visitor gtvis(v);
        return boost::apply_visitor(gtvis, _var);
    }

    /*  >=
    */
    bool var::operator >= (int n) const {
        if (is_int()) return get<int_t>(_var) >= n;
        throw exception("invalid >= comparison to int");
    }

    bool var::operator >= (double n) const {
        if (is_double()) return get<double_t>(_var) >= n;
        throw exception("invalid >= comparison to double");
    }

    bool var::operator >= (const string& s) const {
        if (is_string()) return *get<string_t>(_var).ps >= s;
        throw exception("invalid >= comparison to string");
    }

    bool var::operator >= (const char* s) const {
        if (is_string()) return *get<string_t>(_var).ps >= s;
        throw exception("invalid >= comparison to char*");
    }

    bool var::operator >= (const var& v) const {
        struct ge_visitor : public boost::static_visitor<bool> {
            ge_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { throw exception("invalid >= comparison to $"); }
            bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid >= comparison to int"); return n >= int(_rhs); }
            bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid >= comparison to double"); return n >= double(_rhs); }
            bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid >= comparison to string"); return *s.ps >= string(_rhs); }
            bool operator () (list_ptr) const { throw exception("invalid >= comparison to list"); }
            bool operator () (array_ptr) const { throw exception("invalid >= comparison to array"); }
            bool operator () (set_ptr) const { throw exception("invalid >= comparison to set"); }
            bool operator () (dict_ptr) const { throw exception("invalid >= comparison to dict"); }

            const var& _rhs;
        };
    
        ge_visitor gevis(v);
        return boost::apply_visitor(gevis, _var);
    }

}