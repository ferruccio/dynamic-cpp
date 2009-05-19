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

    string var::type() const {
        struct type_visitor : public boost::static_visitor<string> {
            string operator () (null_t) const { return "null"; }
            string operator () (int_t) const { return "int"; }
            string operator () (double_t) const { return "double"; }
            string operator () (string_t s) const { return "string"; }
            string operator () (list_ptr) const { return "list"; }
            string operator () (array_ptr) const { return "array"; }
            string operator () (set_ptr) const { return "set"; }
            string operator () (dict_ptr) const {return "dict"; }
        };

        return boost::apply_visitor(type_visitor(), _var);
    }

    var::type_t var::get_type() const {
        struct type_visitor : public boost::static_visitor<type_t> {
            type_t operator () (null_t) const { return type_null; }
            type_t operator () (int_t) const { return type_int; }
            type_t operator () (double_t) const { return type_double; }
            type_t operator () (string_t s) const { return type_string; }
            type_t operator () (list_ptr) const { return type_list; }
            type_t operator () (array_ptr) const { return type_array; }
            type_t operator () (set_ptr) const { return type_set; }
            type_t operator () (dict_ptr) const { return type_dict; }
        };
    
        return boost::apply_visitor(type_visitor(), _var);
    }

}
