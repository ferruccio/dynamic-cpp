/*
    Copyright (C) 2009, 2011 Ferruccio Barletta (ferruccio.barletta@gmail.com)

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

#include <dynamic/exception.hpp>
#include <dynamic/var.hpp>

namespace dynamic {

///
/// cast to bool
///
var::operator bool() const {
    try {
        return boost::get<bool_t>(_var);
    } catch (const boost::bad_get&) {
        throw exception("cannot convert to int");
    }
}

///
/// cast to int
///
var::operator int() const {
    try {
        return boost::get<int_t>(_var);
    } catch (const boost::bad_get&) {
        throw exception("cannot convert to int");
    }
}

///
/// cast to double
///
var::operator double() const {
    try {
        return boost::get<double_t>(_var);
    } catch (const boost::bad_get&) {
        throw exception("cannot convert to double");
    }
}

///
/// cast to string
///
var::operator std::string() const {
    try {
        return *boost::get<string_t>(_var).ps;
    } catch (const boost::bad_get&) {
        throw exception("cannot convert to string");
    }
}

///
/// cast to wide string
///
var::operator std::wstring() const {
    try {
        return *boost::get<wstring_t>(_var).ps;
    } catch (const boost::bad_get&) {
        throw exception("cannot convert to wstring");
    }
}

///
/// @return type name
///
struct var::name_visitor : public boost::static_visitor<std::string>
{
    result_type operator () (const null_t&) const { return "null"; }
    result_type operator () (const bool_t&) const { return "bool"; }
    result_type operator () (const int_t&) const { return "int"; }
    result_type operator () (const double_t&) const { return "double"; }
    result_type operator () (const string_t& value) const { return "string"; }
    result_type operator () (const wstring_t& value) const { return "wstring"; }
    result_type operator () (const vector_ptr& ptr) const { return "vector"; }
    result_type operator () (const map_ptr& ptr) const { return "map"; }
};
std::string var::name() const {
    return boost::apply_visitor(name_visitor(), _var);
}

///
/// @return type identifier
///
var::code var::type() const {
    return code(_var.which());
}

}
