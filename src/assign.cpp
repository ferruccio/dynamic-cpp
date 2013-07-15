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

#include <dynamic/var.hpp>

namespace dynamic {

///
/// assign bool to var
///
var& var::operator = (bool n) {
    _var = n;
    return *this;
}

///
/// assign int to var
///
var& var::operator = (int n) {
    _var = n;
    return *this;
}

///
/// assign double to var
///
var& var::operator = (double n) {
    _var = n;
    return *this;
}

///
/// assign string to var
///
var& var::operator = (const std::string& s) {
    _var = string_t(s);
    return *this;
}

///
/// assign string constant to var
///
var& var::operator = (const char* s) {
    _var = string_t(s);
    return *this;
}
    
///
/// assign wide string to var
///
var& var::operator = (const std::wstring& s) {
    _var = wstring_t(s);
    return *this;
}

///
/// assign wide string constant to var
var& var::operator = (const wchar_t* s) {
    _var = wstring_t(s);
    return *this;
}

///
/// assign var to var
///
var& var::operator = (const var& v) {
    _var = v._var;
    return *this;
}

}
