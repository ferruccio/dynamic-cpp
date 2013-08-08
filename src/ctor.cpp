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
/// ctor: init with none
///
var::var() : _var() {}

///
/// ctor: init with bool
///
var::var(bool n) : _var(n) {}

///
/// ctor: init with int
///
var::var(int n) : _var(n) {}

///
/// ctor: init with double
///
var::var(double n) : _var(n) {}

///
/// ctor: init with string
///
var::var(const std::string& s) : _var(string_t(s)) {}

///
/// ctor: init with string constant
///
var::var(const char* s) : _var(string_t(s)) {}

///
/// ctor: init with wide string
///
var::var(const std::wstring& s) : _var(wstring_t(s)) {}

///
/// ctor: init with wide string
///
var::var(const wchar_t* s) : _var(wstring_t(s)) {}

///
/// ctor: init with var
///
var::var(const var& v) : _var(v._var) {}

///
/// ctor: init with vector
///
var::var(vector_ptr _vector) : _var(_vector) {}

///
/// ctor: init with map
///
var::var(map_ptr _map) : _var(_map) {}

}
