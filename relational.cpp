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
        rel_eq_visitor eqvis(v);
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
        rel_eq_visitor evis(v);
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
        rel_lt_visitor ltvis(v);
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
        rel_le_visitor levis(v);
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
        rel_gt_visitor gtvis(v);
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
        rel_ge_visitor gevis(v);
        return boost::apply_visitor(gevis, _var);
    }

}