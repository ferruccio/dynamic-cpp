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

#include <algorithm> // std::equal

#include <dynamic/exception.hpp>
#include <dynamic/var.hpp>

namespace dynamic {

///
/// var == bool
///
bool var::operator == (bool n) const {
    return *this == var(n);
}

///
/// var == int
///
bool var::operator == (int n) const {
    return *this == var(n);
}

///
/// var == double
///
bool var::operator == (double n) const {
    return *this == var(n);
}

///
/// var == string
///
bool var::operator == (const std::string& s) const {
    return *this == var(s);
}

///
/// var == string constant
///
bool var::operator == (const char* s) const {
    return *this == var(s);
}

///
/// var == wide string
///
bool var::operator == (const std::wstring& s) const {
    return *this == var(s);
}

///
/// var == wide string constant
///
bool var::operator == (const wchar_t* s) const {
    return *this == var(s);
}

///
/// var == var
///
struct var::equal_visitor : public boost::static_visitor<bool>
{
    // Different types
    template <typename T, typename U>
    result_type operator () (const T& lhs, const U& rhs) const
    {
        return false;
    }
    // Same types
    template <typename T>
    result_type operator () (const T& lhs, const T& rhs) const
    {
        // Use overloaded functions to handle explicit specialization
        return equal(lhs, rhs);
    }

private:
    bool equal(const null_t&, const null_t&) const
    {
        return true;
    }
    bool equal(const bool_t& lhs, const bool_t& rhs) const
    {
        return lhs == rhs;
    }
    bool equal(const int_t& lhs, const int_t& rhs) const
    {
        return lhs == rhs;
    }
    bool equal(const double_t& lhs, const double_t& rhs) const
    {
        return lhs == rhs;
    }
    bool equal(const string_t& lhs, const string_t& rhs) const
    {
        return *(lhs.ps) == *(rhs.ps);
    }
    bool equal(const wstring_t& lhs, const wstring_t& rhs) const
    {
        return *(lhs.ps) == *(rhs.ps);
    }
    bool equal(const vector_ptr& lhs, const vector_ptr& rhs) const
    {
        return std::equal(lhs->begin(), lhs->end(), rhs->begin());
    }
    bool equal(const map_ptr& lhs, const map_ptr& rhs) const
    {
        return std::equal(lhs->begin(), lhs->end(), rhs->begin());
    }
};
bool var::operator == (const var& v) const {
    return boost::apply_visitor(equal_visitor(), _var, v._var);
}

///
/// var != bool
///
bool var::operator != (bool n) const {
    return *this != var(n);
}

///
/// var != int
///
bool var::operator != (int n) const {
    return *this != var(n);
}

///
/// var != double
///
bool var::operator != (double n) const {
    return *this != var(n);
}

///
/// var != string
///
bool var::operator != (const std::string& s) const {
    return *this != var(s);
}

///
/// var != string constant
///
bool var::operator != (const char* s) const {
    return *this != var(s);
}

///
/// var != wide string
///
bool var::operator != (const std::wstring& s) const {
    return *this != var(s);
}

///
/// var != wide string constant
///
bool var::operator != (const wchar_t* s) const {
    return *this != var(s);
}

///
/// var != var
///
bool var::operator != (const var& v) const {
    return !boost::apply_visitor(equal_visitor(), _var, v._var);
}

///
/// var < bool
///
bool var::operator < (bool n) const {
    const var v(n);
    return less_var()(*this, v);
}

///
/// var < int
///
bool var::operator < (int n) const {
    const var v(n);
    return less_var()(*this, v);
}

///
/// var < double
///
bool var::operator < (double n) const {
    const var v(n);
    return less_var()(*this, v);
}

///
/// var < string
///
bool var::operator < (const std::string& s) const {
    const var v(s);
    return less_var()(*this, v);
}

///
/// var < string constant
///
bool var::operator < (const char* s) const {
    const var v(s);
    return less_var()(*this, v);
}

///
/// var < wide string
///
bool var::operator < (const std::wstring& s) const {
    const var v(s);
    return less_var()(*this, v);
}

///
/// var < wide string constant
///
bool var::operator < (const wchar_t* s) const {
    const var v(s);
    return less_var()(*this, v);
}

///
/// var < var
///
bool var::operator < (const var& v) const {
    return less_var()(*this, v);
}

///
/// var <= bool
///
bool var::operator <= (bool n) const {
    if (is_bool()) return boost::get<bool_t>(_var) <= n;
    throw exception("invalid <= comparison to bool");
}

///
/// var <= int
///
bool var::operator <= (int n) const {
    if (is_int()) return boost::get<int_t>(_var) <= n;
    throw exception("invalid <= comparison to int");
}

///
/// var <= double
///
bool var::operator <= (double n) const {
    if (is_double()) return boost::get<double_t>(_var) <= n;
    throw exception("invalid <= comparison to double");
}

///
/// var <= string
///
bool var::operator <= (const std::string& s) const {
    if (is_string()) return *boost::get<string_t>(_var).ps <= s;
    throw exception("invalid <= comparison to string");
}

///
/// var <= string constant
///
bool var::operator <= (const char* s) const {
    if (is_string()) return *boost::get<string_t>(_var).ps <= s;
    throw exception("invalid <= comparison to char*");
}
    
///
/// var <= wide string
///
bool var::operator <= (const std::wstring& s) const {
    if (is_wstring()) return *boost::get<wstring_t>(_var).ps <= s;
    throw exception("invalid <= comparison to wstring");
}

///
/// var <= wide string constant
///
bool var::operator <= (const wchar_t* s) const {
    if (is_wstring()) return *boost::get<wstring_t>(_var).ps <= s;
    throw exception("invalid <= comparison to wchar_t*");
}

///
/// var <= var
///
bool var::operator <= (const var& v) const {
    switch (type()) {
    case type_null :    throw exception("invalid <= comparison to none");
    case type_bool :    return v.is_bool() && boost::get<bool_t>(_var) <= boost::get<bool_t>(v._var);
    case type_int :     return v.is_int() && boost::get<int_t>(_var) <= boost::get<int_t>(v._var);
    case type_double :  return v.is_double() && boost::get<double_t>(_var) <= boost::get<double_t>(v._var);
    case type_string :  return v.is_string() && *boost::get<string_t>(_var).ps <= *boost::get<string_t>(v._var).ps;
    case type_wstring : return v.is_wstring() && *boost::get<wstring_t>(_var).ps <= *boost::get<wstring_t>(v._var).ps;
    case type_vector :  throw exception("vector <= not implemented");
    case type_map :     throw exception("map <= not implemented");
    default :           throw exception("(unhandled type) <= not implemented");
    }
}

///
/// var > bool
///
bool var::operator > (bool n) const {
    if (is_bool()) return boost::get<bool_t>(_var) > n;
    throw exception("invalid > comparison to bool");
}

///
/// var > int
///
bool var::operator > (int n) const {
    if (is_int()) return boost::get<int_t>(_var) > n;
    throw exception("invalid > comparison to int");
}

///
/// var > double
///
bool var::operator > (double n) const {
    if (is_double()) return boost::get<double_t>(_var) > n;
    throw exception("invalid > comparison to double");
}

///
/// var > string
///
bool var::operator > (const std::string& s) const {
    if (is_string()) return *boost::get<string_t>(_var).ps > s;
    throw exception("invalid > comparison to string");
}

///
/// var > string constant
bool var::operator > (const char* s) const {
    if (is_string()) return *boost::get<string_t>(_var).ps > s;
    throw exception("invalid > comparison to char*");
}

///
/// var > wide string
///
bool var::operator > (const std::wstring& s) const {
    if (is_wstring()) return *boost::get<wstring_t>(_var).ps > s;
    throw exception("invalid > comparison to wstring");
}

///
/// var > wide string constant
///
bool var::operator > (const wchar_t* s) const {
    if (is_wstring()) return *boost::get<wstring_t>(_var).ps > s;
    throw exception("invalid > comparison to wchar_t*");
}

///
/// var > var
///
bool var::operator > (const var& v) const {
    switch (type()) {
    case type_null :    throw exception("invalid > comparison to none");
    case type_bool :    return v.is_bool() && boost::get<bool_t>(_var) > boost::get<bool_t>(v._var);
    case type_int :     return v.is_int() && boost::get<int_t>(_var) > boost::get<int_t>(v._var);
    case type_double :  return v.is_double() && boost::get<double_t>(_var) > boost::get<double_t>(v._var);
    case type_string :  return v.is_string() && *boost::get<string_t>(_var).ps > *boost::get<string_t>(v._var).ps;
    case type_wstring : return v.is_wstring() && *boost::get<wstring_t>(_var).ps > *boost::get<wstring_t>(v._var).ps;
    case type_vector :  throw exception("vector > not implemented");
    case type_map :     throw exception("map > not implemented");
    default :           throw exception("(unhandled type) > not implemented");
    }
}

///
/// var >= bool
///
bool var::operator >= (bool n) const {
    if (is_bool()) return boost::get<bool_t>(_var) >= n;
    throw exception("invalid >= comparison to bool");
}

///
/// var >= int
///
bool var::operator >= (int n) const {
    if (is_int()) return boost::get<int_t>(_var) >= n;
    throw exception("invalid >= comparison to int");
}

///
/// var >= double
///
bool var::operator >= (double n) const {
    if (is_double()) return boost::get<double_t>(_var) >= n;
    throw exception("invalid >= comparison to double");
}

///
/// var >= string
///
bool var::operator >= (const std::string& s) const {
    if (is_string()) return *boost::get<string_t>(_var).ps >= s;
    throw exception("invalid >= comparison to string");
}

///
/// var >= string constant
///
bool var::operator >= (const char* s) const {
    if (is_string()) return *boost::get<string_t>(_var).ps >= s;
    throw exception("invalid >= comparison to char*");
}
    
///
/// var >= wide string
///
bool var::operator >= (const std::wstring& s) const {
    if (is_wstring()) return *boost::get<wstring_t>(_var).ps >= s;
    throw exception("invalid >= comparison to wstring");
}

///
/// var >= wide string constant
///
bool var::operator >= (const wchar_t* s) const {
    if (is_wstring()) return *boost::get<wstring_t>(_var).ps >= s;
    throw exception("invalid >= comparison to wchar_t*");
}

///
/// var >= var
///
bool var::operator >= (const var& v) const {
    switch (type()) {
    case type_null :    throw exception("invalid >= comparison to none");
    case type_bool :    return v.is_bool() && boost::get<bool_t>(_var) >= boost::get<bool_t>(v._var);
    case type_int :     return v.is_int() && boost::get<int_t>(_var) >= boost::get<int_t>(v._var);
    case type_double :  return v.is_double() && boost::get<double_t>(_var) >= boost::get<double_t>(v._var);
    case type_string :  return v.is_string() && *boost::get<string_t>(_var).ps >= *boost::get<string_t>(v._var).ps;
    case type_wstring : return v.is_wstring() && *boost::get<wstring_t>(_var).ps >= *boost::get<wstring_t>(v._var).ps;
    case type_vector :  throw exception("vector >= not implemented");
    case type_map :     throw exception("map >= not implemented");
    default :           throw exception("(unhandled type) >= not implemented");
    }
}

}
