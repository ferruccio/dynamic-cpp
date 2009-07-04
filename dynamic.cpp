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
#include <cassert>
#include <boost/format.hpp>

namespace dynamic {

    //const var $;
	
    bool var::less_var::operator () (const var& lhs, const var& rhs) {
        // if the two vars are of different types, order by type
        type_t lht = lhs.get_type(), rht = rhs.get_type();
        if (lht != rht) return lht < rht;

        // they are of the same type, order by value
        return boost::apply_visitor(lt_visitor(), lhs._var, rhs._var);
    }

    var& var::operator () (int n) { return operator() (var(n)); }

    var& var::operator () (double n) { return operator() (var(n)); }

    var& var::operator () (const char* s) { return operator() (var(s)); }

    var& var::operator () (const string& s) { return operator() (var(s)); }

    var& var::operator () (const var& v) {    
        boost::apply_visitor(append_visitor(v), _var);
        return *this;
    }

    var& var::operator () (const var& k, const var& v) {
		boost::apply_visitor(append2_visitor(k, v), _var);
        return *this;
    }

    unsigned int var::count() const {
		return boost::apply_visitor(count_visitor(), _var);
    }

    var& var::operator [] (int n) {
		return boost::apply_visitor(index_visitor(n), _var);
    }

    var& var::operator [] (double n) { return operator[] (var(n)); }

    var& var::operator [] (const char* s) { return operator[] (var(s)); }

    var& var::operator [] (const string& s) { return operator[] (var(s)); }

    var& var::operator [] (const var& v) {    
        return boost::apply_visitor(index2_visitor(const_cast<var&>(v)), _var);
    }

    ostream& var::_write_var(ostream& os) {
        output_visitor ovis(os, *this);
        return boost::apply_visitor(ovis, _var);
    }

    ostream& var::_write_string(ostream& os) {
        assert(is_string());
        os << '\'';
        for (const char* s = (*get<string_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << "\\b"; break;
                case '\r' : os << "\\r"; break;
                case '\n' : os << "\\n"; break;
                case '\f' : os << "\\f"; break;
                case '\t' : os << "\\t"; break;
                case '\\' : os << "\\\\"; break;
                case '\'' : os << "\\'"; break;
                default :
                    if (*s < ' ') os << format("\\%03o") % int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ostream& var::_write_list(ostream& os) {
        assert(is_list());
        os << '(';
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << ' ';
            (*vi)._write_var(os);
        }
        os << ')';
        return os;
    }

    ostream& var::_write_array(ostream& os) {
        assert(is_array());
        os << '[';
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << ' ';
            (*vi)._write_var(os);
        }         
        os << ']';
        return os;
    }

    ostream& var::_write_set(ostream& os) {
        assert(is_set());
        os << '{';
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << ' ';
            (*vi)._write_var(os);
        }          
        os << '}';
        return os;
    }

    ostream& var::_write_dict(ostream& os) {
        assert(is_dict());
        os << '<';
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << ' ';
            (*vi)._write_var(os);
            os << ':';
            (*this)[*vi]._write_var(os);
        }
        os << '>';
        return os;
    }

}
