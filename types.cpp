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

    var::operator int() const {
        try {
            return get<int_t>(_var);
        } catch (bad_get) {
            throw exception("cannot convert to int");
        }
    }

    var::operator double() const {
        try {
            return get<double_t>(_var);
        } catch (bad_get) {
            throw exception("cannot convert to double");
        }
    }

    var::operator string() const {
        try {
            return *get<string_t>(_var).ps;
        } catch (bad_get) {
            throw exception("cannot convert to string");
        }
    }

    var::operator wstring() const {
        try {
            return *get<wstring_t>(_var).ps;
        } catch (bad_get) {
            throw exception("cannot convert to wstring");
        }
    }

    string var::type() const {
        switch (get_type()) {
	        case type_null :    return "null";
	        case type_int :     return "int";
	        case type_double :  return "double";
	        case type_string :  return "string";
	        case type_wstring : return "wstring";
	        case type_list :    return "list";
	        case type_array :   return "array";
	        case type_set :     return "set";
	        case type_dict :    return "dict";
            default :           throw exception("var::type() unhandled type");
        }
    }

    var::type_t var::get_type() const {
        return boost::apply_visitor(type_visitor(), _var);
    }

}
