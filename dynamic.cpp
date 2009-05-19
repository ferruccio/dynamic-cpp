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

    const var $;

    bool var::less_var::operator () (const var& lhs, const var& rhs) {
        // if the two vars are of different types, order by type
        type_t lht = lhs.get_type(), rht = rhs.get_type();
        if (lht != rht) return lht < rht;

        // they are of the same type, order by value
        struct lt_visitor : public boost::static_visitor<bool> {
            lt_visitor(const var& rhs) : _rhs(rhs) {}

            bool operator () (null_t) const { return false; }
            bool operator () (int_t n) const { return n < int(_rhs); }
            bool operator () (double_t n) const { return n < double(_rhs); }
            bool operator () (string_t s) const { return *s.ps < string(_rhs); }
            bool operator () (list_ptr) const { return false; }
            bool operator () (array_ptr) const { return false; }
            bool operator () (set_ptr) const { return false; }
            bool operator () (dict_ptr) const { return false; }

            const var& _rhs;
        };
    
        lt_visitor ltvis(rhs);
        return boost::apply_visitor(ltvis, lhs._var);
    }

    var& var::operator () (int n) { return operator() (var(n)); }

    var& var::operator () (double n) { return operator() (var(n)); }

    var& var::operator () (const char* s) { return operator() (var(s)); }

    var& var::operator () (const string& s) { return operator() (var(s)); }

    var& var::operator () (const var& v) {
        struct append_visitor : public boost::static_visitor<void> {
            append_visitor(const var& v) : _v(v) {}

            void operator () (null_t) const { throw exception("invalid () operation on $"); }
            void operator () (int_t) const { throw exception("invalid () operation on int"); }
            void operator () (double_t) const { throw exception("invalid () operation on double"); }
            void operator () (string_t) const { throw exception("invalid () operation on string"); }
            void operator () (list_ptr l) const { l->push_back(_v); }
            void operator () (array_ptr a) const { a->push_back(_v); }
            void operator () (set_ptr s) const { s->insert(_v); }
            void operator () (dict_ptr d) const { d->insert(make_pair<var,var>(_v, $)); }

            const var& _v;
        };
    
        boost::apply_visitor(append_visitor(v), _var);
        return *this;
    }

    var& var::operator () (const var& k, const var& v) {
        struct append_visitor : public boost::static_visitor<void> {
            append_visitor(const var& k, const var& v) : _k(k), _v(v) {}

            void operator () (null_t) const { throw exception("invalid (,) operation on $"); }
            void operator () (int_t) const { throw exception("invalid (,) operation on int"); }
            void operator () (double_t) const { throw exception("invalid (,) operation on double"); }
            void operator () (string_t) const { throw exception("invalid (,) operation on string"); }
            void operator () (list_ptr) const { throw exception("invalid (,) operation on list"); }
            void operator () (array_ptr) const { throw exception("invalid (,) operation on array"); }
            void operator () (set_ptr) const { throw exception("invalid (,) operation on set"); }
            void operator () (dict_ptr d) const { d->insert(make_pair<var,var>(_k, _v)); }

            const var& _k;
            const var& _v;
        };
    
        boost::apply_visitor(append_visitor(k, v), _var);
        return *this;
    }

    unsigned int var::count() const {
        struct count_visitor : public boost::static_visitor<unsigned int> {
            unsigned int operator () (null_t) const { throw exception("invalid .count() operation on $"); }
            unsigned int operator () (int_t) const { throw exception("invalid .count() operation on int"); }
            unsigned int operator () (double_t) const { throw exception("invalid .count() operation on double"); }
            unsigned int operator () (string_t s) const { return s.ps->length(); }
            unsigned int operator () (list_ptr l) const { return l->size(); }
            unsigned int operator () (array_ptr a) const { return a->size(); }
            unsigned int operator () (set_ptr s) const { return s->size(); }
            unsigned int operator () (dict_ptr d) const { return d->size(); }
        };
    
        return boost::apply_visitor(count_visitor(), _var);
    }

    var& var::operator [] (int n) {
        struct index_visitor : public boost::static_visitor<var&> {
            index_visitor(int n) : _n(n) {}

            var& operator () (null_t) const { throw exception("cannot apply [] to $"); }
            var& operator () (int_t) const { throw exception("cannot apply [] to int"); }
            var& operator () (double_t) const { throw exception("cannot apply [] to double"); }
            var& operator () (string_t s) const { throw exception("cannot apply [] to string"); }

            var& operator () (list_ptr l) const {
                if (_n < 0 || _n >= int(l->size())) throw exception("[] out of range in list");
                list_t::iterator li = l->begin();
                advance(li, _n);
                return *li;
            }

            var& operator () (array_ptr a) const  {
                if (_n < 0 || _n >= int(a->size())) throw exception("[] out of range in array");
                return (*a)[_n];
            }

            var& operator () (set_ptr s) const {
                if (_n < 0 || _n >= int(s->size())) throw exception("[] out of range in set");
                set_t::iterator si = s->begin();
                advance(si, _n);
                return *si;
            }

            var& operator () (dict_ptr d) const {
                var key(_n);
                dict_t::iterator di = d->find(key);
                if (di == d->end()) throw exception("[] not found in dict");
                return di->second;
            }

            int _n;
        };
    
        return boost::apply_visitor(index_visitor(n), _var);
    }

    var& var::operator [] (double n) { return operator[] (var(n)); }

    var& var::operator [] (const char* s) { return operator[] (var(s)); }

    var& var::operator [] (const string& s) { return operator[] (var(s)); }

    var& var::operator [] (const var& v) {
        struct index_visitor : public boost::static_visitor<var&> {
            index_visitor(var& v) : _v(v) {}

            var& operator () (null_t) const { throw exception("cannot apply [] to $"); }
            var& operator () (int_t) const { throw exception("cannot apply [] to int"); }
            var& operator () (double_t) const { throw exception("cannot apply [] to double"); }
            var& operator () (string_t s) const { throw exception("cannot apply [] to string"); }
            var& operator () (list_ptr l) const { throw exception("list[] requires int"); }
            var& operator () (array_ptr a) const { throw exception("array[] requires int"); }
            var& operator () (set_ptr s) const { throw exception("set[] requires int"); }

            var& operator () (dict_ptr d) const {
                var key(_v);
                dict_t::iterator di = d->find(key);
                if (di != d->end()) return di->second;
                (*d)[key] = $;
                return (*d)[key];
            }

            var& _v;
        };
    
        return boost::apply_visitor(index_visitor(const_cast<var&>(v)), _var);
    }

    ostream& var::_write_var(ostream& os) {
        struct output_visitor : public boost::static_visitor<ostream&> {
            output_visitor(ostream& os, var& v) : _os(os), _v(v), boost::static_visitor<ostream&>() {}

            ostream& operator () (null_t) { _os << "$"; return _os; }
            ostream& operator () (int_t n) { _os << n; return _os; }
            ostream& operator () (double_t n) { _os << n; return _os; }
            ostream& operator () (string_t s) { return _v._write_string(_os); }
            ostream& operator () (list_ptr) { return _v._write_list(_os); }
            ostream& operator () (array_ptr) { return _v._write_array(_os); }
            ostream& operator () (set_ptr) { return _v._write_set(_os); }
            ostream& operator () (dict_ptr) { return _v._write_dict(_os); }

            ostream& _os;
            var& _v;
        };

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
