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
/// @return iterator to the first item in a collection
///
var::const_iterator var::begin() const {
    switch (type()) {
    case type_null :    throw exception("invalid .begin() operation on none");
    case type_int :     throw exception("invalid .begin() operation on int");
    case type_double :  throw exception("invalid .begin() operation on double");
    case type_string :  throw exception("invalid .begin() operation on string");
    case type_wstring : throw exception("invalid .begin() operation on wstring");
    case type_vector :  return boost::get<vector_ptr>(_var)->begin();
    case type_map :     return boost::get<map_ptr>(_var)->begin();
    default :           throw exception("unhandled .begin() operation");
    }
}

var::iterator var::begin() {
    // iterator is implemented via object slicing, so we need to do const casting
    const_iterator result = const_cast<const var*>(this)->begin(); // Call begin() const
    return static_cast<var::iterator&>(result);
}

///
/// @return iterator past the last item in a collection
///
var::const_iterator var::end() const {
    switch (type()) {
    case type_null :    throw exception("invalid .end() operation on none");
    case type_int :     throw exception("invalid .end() operation on int");
    case type_double :  throw exception("invalid .end() operation on double");
    case type_string :  throw exception("invalid .end() operation on string");
    case type_wstring : throw exception("invalid .end() operation on wstring");
    case type_vector :  return boost::get<vector_ptr>(_var)->end();
    case type_map :     return boost::get<map_ptr>(_var)->end();
    default :           throw exception("unhandled .end() operation");
    }
}

var::iterator var::end() {
    const_iterator result = const_cast<const var*>(this)->end(); // Call end() const
    return static_cast<var::iterator&>(result);
}

///
/// pre-increment interator
///
var::const_iterator var::const_iterator::operator++() {
    switch (_iter.which()) {
    case type_vector :  return ++boost::get<vector_type::iterator&>(_iter);
    case type_map :     return ++boost::get<map_type::iterator&>(_iter);
    default :           throw exception("unhandled ++iter");
    }
}

///
/// post-increment iterator
///
var::const_iterator var::const_iterator::operator++(int) {
    switch (_iter.which()) {
    case type_vector :  return boost::get<vector_type::iterator&>(_iter)++;
    case type_map :     return boost::get<map_type::iterator&>(_iter)++;
    default :           throw exception("unhandled iter++");
    }
}

///
/// pre-decrement iterator
///
var::const_iterator var::const_iterator::operator--() {
    switch (_iter.which()) {
    case type_vector :  return --boost::get<vector_type::iterator&>(_iter);
    case type_map :     return --boost::get<map_type::iterator&>(_iter);
    default :           throw exception("unhandled --iter");
    }
}

///
/// post-decement iterator
///
var::const_iterator var::const_iterator::operator--(int) {
    switch (_iter.which()) {
    case type_vector :  return boost::get<vector_type::iterator&>(_iter)--;
    case type_map :     return boost::get<map_type::iterator&>(_iter)++;
    default :           throw exception("unhandled iter--");
    }
}

struct are_strict_equals : public boost::static_visitor<bool> {
    /// different types are never equal
    template <typename T, typename U>
    bool operator()(const T&, const U&) const { return false; }

    /// same type, apply == operator
    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const { return lhs == rhs; }
};

///
/// test two vars for equality
///
bool var::const_iterator::operator==(var::const_iterator rhs) {
    return boost::apply_visitor(are_strict_equals(), _iter, rhs._iter);
}

///
/// dereference iterator
///
const var& var::const_iterator::operator*() const {
    switch (_iter.which()) {
    case type_vector :  return *boost::get<vector_type::iterator>(_iter);
    case type_map :     return const_cast<var&>(boost::get<map_type::iterator>(_iter)->first);
    default :           throw exception("invalid operator*() operation");
    }
}

var& var::iterator::operator*() {
    const var& result = static_cast<var::const_iterator *>(this)->operator*();  // Call const_iterator::operator*()
    return const_cast<var&>(result);
}

///
/// dereference iterator as pair
///
const var::pair_type& var::const_iterator::pair() const {
    switch (_iter.which()) {
    case type_map : return *boost::get<map_type::iterator>(_iter);
    default : throw exception("invalid .value() operation");
    }
}

var::pair_type& var::iterator::pair() {
    const var::pair_type& result = static_cast<var::const_iterator *>(this)->pair();  // Call const_iterator::pair())
    return const_cast<var::pair_type&>(result);
}

///
/// @return reverse_iterator to last item in collection
///
var::reverse_iterator var::rbegin() {
    switch (type()) {
    case type_null :    throw exception("invalid .rbegin() operation on none");
    case type_int :     throw exception("invalid .rbegin() operation on int");
    case type_double :  throw exception("invalid .rbegin() operation on double");
    case type_string :  throw exception("invalid .rbegin() operation on string");
    case type_wstring : throw exception("invalid .rbegin() operation on wstring");
    case type_vector :  return boost::get<vector_ptr>(_var)->rbegin();
    case type_map :     return boost::get<map_ptr>(_var)->rbegin();
    default :           throw exception("unhandled .rbegin() operation");
    }
}

///
/// @return reverse_iterator preceding first item in collection
///
var::reverse_iterator var::rend() {
    switch (type()) {
    case type_null :    throw exception("invalid .rend() operation on none");
    case type_int :     throw exception("invalid .rend() operation on int");
    case type_double :  throw exception("invalid .rend() operation on double");
    case type_string :  throw exception("invalid .rend() operation on string");
    case type_wstring : throw exception("invalid .rend() operation on wstring");
    case type_vector :  return boost::get<vector_ptr>(_var)->rend();
    case type_map :     return boost::get<map_ptr>(_var)->rend();
    default :           throw exception("unhandled .rend() operation");
    }
}

///
/// pre-increment reverse_iterator
///
var::reverse_iterator var::reverse_iterator::operator++() {
    switch (_riter.which()) {
    case type_vector :  return ++boost::get<vector_type::reverse_iterator&>(_riter);
    case type_map :     return ++boost::get<map_type::reverse_iterator&>(_riter);
    default :           throw exception("unhandled ++riter");
    }
}

///
/// post-increment reverse_iterator
///
var::reverse_iterator var::reverse_iterator::operator++(int) {
    switch (_riter.which()) {
    case type_vector :  return boost::get<vector_type::reverse_iterator&>(_riter)++;
    case type_map :     return boost::get<map_type::reverse_iterator&>(_riter)++;
    default :           throw exception("unhandled riter++");
    }
}

///
/// pre-decrement reverse_iterator
///
var::reverse_iterator var::reverse_iterator::operator--() {
    switch (_riter.which()) {
    case type_vector :  return --boost::get<vector_type::reverse_iterator&>(_riter);
    case type_map :     return --boost::get<map_type::reverse_iterator&>(_riter);
    default :           throw exception("unhandled --riter");
    }
}

///
/// post-decrement reverse_iterator
///
var::reverse_iterator var::reverse_iterator::operator--(int) {
    switch (_riter.which()) {
    case type_vector :  return boost::get<vector_type::reverse_iterator&>(_riter)--;
    case type_map :     return boost::get<map_type::reverse_iterator&>(_riter)++;
    default :           throw exception("unhandled iter--");
    }
}

///
/// test two vars for equality, different types are never equal
///
bool var::reverse_iterator::operator==(var::reverse_iterator rhs) {
    return boost::apply_visitor(are_strict_equals(), _riter, rhs._riter);
}

}
