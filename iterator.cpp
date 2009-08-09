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
	
    var::iterator var::begin() {
		switch (get_type()) {
			case type_null :    throw exception("invalid .begin() operation on $");
			case type_int :     throw exception("invalid .begin() operation on int");
			case type_double :  throw exception("invalid .begin() operation on double");
			case type_string :  throw exception("invalid .begin() operation on string");
			case type_list :    return get<list_ptr>(_var)->begin();
			case type_array :   return get<array_ptr>(_var)->begin();
			case type_set :     return get<set_ptr>(_var)->begin();
			case type_dict :    return get<dict_ptr>(_var)->begin();
			default :           throw exception("unhandled .begin() operation");
		}
    }

    var::iterator var::end() {
		switch (get_type()) {
			case type_null :    throw exception("invalid .end() operation on $");
			case type_int :     throw exception("invalid .end() operation on int");
			case type_double :  throw exception("invalid .end() operation on double");
			case type_string :  throw exception("invalid .end() operation on string");
			case type_list :    return get<list_ptr>(_var)->end();
			case type_array :   return get<array_ptr>(_var)->end();
			case type_set :     return get<set_ptr>(_var)->end();
			case type_dict :    return get<dict_ptr>(_var)->end();
			default :           throw exception("unhandled .end() operation");
		}
    }

    var::iterator var::iterator::operator++() {
        switch (_iter.which()) {
            case list_type :    return ++get<list_t::iterator&>(_iter);
            case array_type :   return ++get<array_t::iterator&>(_iter);
            case set_type :     return ++get<set_t::iterator&>(_iter);
            case dict_type :    return ++get<dict_t::iterator&>(_iter);
            default :           throw exception("unhandled ++iter");
        }
    }

    var::iterator var::iterator::operator++(int) {
        switch (_iter.which()) {
            case list_type :    return get<list_t::iterator&>(_iter)++;
            case array_type :   return get<array_t::iterator&>(_iter)++;
            case set_type :     return get<set_t::iterator&>(_iter)++;
            case dict_type :    return get<dict_t::iterator&>(_iter)++;
            default :           throw exception("unhandled iter++");
        }
    }

    var::iterator var::iterator::operator--() {
        switch (_iter.which()) {
            case list_type :    return --get<list_t::iterator&>(_iter);
            case array_type :   return --get<array_t::iterator&>(_iter);
            case set_type :     return --get<set_t::iterator&>(_iter);
            case dict_type :    return --get<dict_t::iterator&>(_iter);
            default :           throw exception("unhandled --iter");
        }
    }

    var::iterator var::iterator::operator--(int) {
        switch (_iter.which()) {
            case list_type :    return get<list_t::iterator&>(_iter)--;
            case array_type :   return get<array_t::iterator&>(_iter)--;
            case set_type :     return get<set_t::iterator&>(_iter)--;
            case dict_type :    return get<dict_t::iterator&>(_iter)++;
            default :           throw exception("unhandled iter--");
        }
    }

    struct are_strict_equals : public boost::static_visitor<bool> {
        template <typename T, typename U>
        bool operator()(const T&, const U&) const { return false; }

        template <typename T>
        bool operator()(const T& lhs, const T& rhs) const { return lhs == rhs; }
    };

    bool var::iterator::operator==(var::iterator rhs) {
        return boost::apply_visitor(are_strict_equals(), _iter, rhs._iter);
    }

    var& var::iterator::operator*() {
        switch (_iter.which()) {
            case list_type :    return *get<list_t::iterator>(_iter);
            case array_type :   return *get<array_t::iterator>(_iter);
            case set_type :     return const_cast<var&>(*get<set_t::iterator>(_iter));
            case dict_type :    return const_cast<var&>(get<dict_t::iterator>(_iter)->first);
            default :           throw exception("unhandled *iter");
        }
    }

    var::reverse_iterator var::rbegin() {
		switch (get_type()) {
			case type_null :    throw exception("invalid .rbegin() operation on $");
			case type_int :     throw exception("invalid .rbegin() operation on int");
			case type_double :  throw exception("invalid .rbegin() operation on double");
			case type_string :  throw exception("invalid .rbegin() operation on string");
			case type_list :    return get<list_ptr>(_var)->rbegin();
			case type_array :   return get<array_ptr>(_var)->rbegin();
			case type_set :     return get<set_ptr>(_var)->rbegin();
			case type_dict :    return get<dict_ptr>(_var)->rbegin();
			default :           throw exception("unhandled .rbegin() operation");
		}
    }

    var::reverse_iterator var::rend() {
		switch (get_type()) {
			case type_null :    throw exception("invalid .rend() operation on $");
			case type_int :     throw exception("invalid .rend() operation on int");
			case type_double :  throw exception("invalid .rend() operation on double");
			case type_string :  throw exception("invalid .rend() operation on string");
			case type_list :    return get<list_ptr>(_var)->rend();
			case type_array :   return get<array_ptr>(_var)->rend();
			case type_set :     return get<set_ptr>(_var)->rend();
			case type_dict :    return get<dict_ptr>(_var)->rend();
			default :           throw exception("unhandled .rend() operation");
		}
    }

    var::reverse_iterator var::reverse_iterator::operator++() {
        switch (_riter.which()) {
            case list_type :    return ++get<list_t::reverse_iterator&>(_riter);
            case array_type :   return ++get<array_t::reverse_iterator&>(_riter);
            case set_type :     return ++get<set_t::reverse_iterator&>(_riter);
            case dict_type :    return ++get<dict_t::reverse_iterator&>(_riter);
            default :           throw exception("unhandled ++riter");
        }
    }

    var::reverse_iterator var::reverse_iterator::operator++(int) {
        switch (_riter.which()) {
            case list_type :    return get<list_t::reverse_iterator&>(_riter)++;
            case array_type :   return get<array_t::reverse_iterator&>(_riter)++;
            case set_type :     return get<set_t::reverse_iterator&>(_riter)++;
            case dict_type :    return get<dict_t::reverse_iterator&>(_riter)++;
            default :           throw exception("unhandled riter++");
        }
    }

    var::reverse_iterator var::reverse_iterator::operator--() {
        switch (_riter.which()) {
            case list_type :    return --get<list_t::reverse_iterator&>(_riter);
            case array_type :   return --get<array_t::reverse_iterator&>(_riter);
            case set_type :     return --get<set_t::reverse_iterator&>(_riter);
            case dict_type :    return --get<dict_t::reverse_iterator&>(_riter);
            default :           throw exception("unhandled --riter");
        }
    }

    var::reverse_iterator var::reverse_iterator::operator--(int) {
        switch (_riter.which()) {
            case list_type :    return get<list_t::reverse_iterator&>(_riter)--;
            case array_type :   return get<array_t::reverse_iterator&>(_riter)--;
            case set_type :     return get<set_t::reverse_iterator&>(_riter)--;
            case dict_type :    return get<dict_t::reverse_iterator&>(_riter)++;
            default :           throw exception("unhandled iter--");
        }
    }

    bool var::reverse_iterator::operator==(var::reverse_iterator rhs) {
        return boost::apply_visitor(are_strict_equals(), _riter, rhs._riter);
    }

}
