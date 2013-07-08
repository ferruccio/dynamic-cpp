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

#include "dynamic.h"
#include <cassert>
#include <iostream>
#include <iomanip>

namespace dynamic {

    const var none;

    bool var::less_var::operator () (const var& lhs, const var& rhs) {
        // if the two vars are of different types, order by type
        type_t lht = lhs.get_type(), rht = rhs.get_type();
        if (lht != rht) return lht < rht;

        // they are of the same type, order by value
        switch (lht) {
            case type_null : return false;
            case type_bool : return boost::get<bool_t>(lhs._var) < boost::get<bool_t>(rhs._var);
            case type_int : return boost::get<int_t>(lhs._var) < boost::get<int_t>(rhs._var);
            case type_double : return boost::get<double_t>(lhs._var) < boost::get<double_t>(rhs._var);
            case type_string : return *(boost::get<string_t>(lhs._var).ps) < *(boost::get<string_t>(rhs._var).ps);
            case type_wstring : return *(boost::get<wstring_t>(lhs._var).ps) < *(boost::get<wstring_t>(rhs._var).ps);
            case type_list :
            case type_vector :
            case type_set :
            case type_map :
                return false;
            default : throw exception("unhandled type");
        }
    }

    ///
    /// append a bool to a collection
    ///
    var& var::operator () (bool n) { return operator() (var(n)); }

    ///
    /// append an int to a collection
    ///
    var& var::operator () (int n) { return operator() (var(n)); }

    ///
    /// append a double to a collection
    ///
    var& var::operator () (double n) { return operator() (var(n)); }

    ///
    /// append a string to a collection
    ///
    var& var::operator () (const std::string& s) { return operator() (var(s)); }

    ///
    /// append a string constant to a collection
    ///
    var& var::operator () (const char* s) { return operator() (var(s)); }

    ///
    /// append a wide string to a collection
    ///
    var& var::operator () (const std::wstring& s) { return operator() (var(s)); }

    ///
    /// append a wide string constant to a collection
    ///
    var& var::operator () (const wchar_t* s) { return operator() (var(s)); }

    ///
    /// append a single value to a collection
    ///
    var& var::operator () (const var& v) {    
        switch (get_type()) {
            case type_null :    throw exception("invalid () operation on none");
            case type_int :     throw exception("invalid () operation on int");
            case type_double :  throw exception("invalid () operation on double");
            case type_string :  throw exception("invalid () operation on string");
            case type_wstring : throw exception("invalid () operation on wstring");
            case type_list :    boost::get<list_ptr>(_var)->push_back(v); break;
            case type_vector :  boost::get<vector_ptr>(_var)->push_back(v); break;
            case type_set :     boost::get<set_ptr>(_var)->insert(v); break;
            case type_map :     boost::get<map_ptr>(_var)->insert(std::make_pair<var,var>(v, none)); break;
            default :           throw exception("unhandled () operation");
        }
        return *this;
    }

    ///
    /// add a key,value to a map
    ///
    var& var::operator () (const var& k, const var& v) {
        switch (get_type()) {
            case type_null :    throw exception("invalid (,) operation on none");
            case type_int :     throw exception("invalid (,) operation on int");
            case type_double :  throw exception("invalid (,) operation on double");
            case type_string :  throw exception("invalid (,) operation on string");
            case type_wstring : throw exception("invalid (,) operation on wstring");
            case type_list :    throw exception("invalid (,) operation on list");
            case type_vector :  throw exception("invalid (,) operation on vector");
            case type_set :     throw exception("invalid (,) operation on set");
            case type_map :     boost::get<map_ptr>(_var)->insert(std::make_pair<var,var>(k, v)); break;
            default :           throw exception("unhandled (,) operation");
        }
        return *this;
    }

    ///
    /// count of objects in a collection or characters in a string
    ///
    unsigned int var::count() const {
        switch (get_type()) {
            case type_null :    throw exception("invalid .count() operation on none");
            case type_bool :     throw exception("invalid .count() operation on bool");
            case type_int :     throw exception("invalid .count() operation on int");
            case type_double :  throw exception("invalid .count() operation on double");
            case type_string :  return static_cast<unsigned int>(boost::get<string_t>(_var).ps->length());
            case type_wstring : return static_cast<unsigned int>(boost::get<wstring_t>(_var).ps->length());
            case type_list :    return static_cast<unsigned int>(boost::get<list_ptr>(_var)->size());
            case type_vector :  return static_cast<unsigned int>(boost::get<vector_ptr>(_var)->size());
            case type_set :     return static_cast<unsigned int>(boost::get<set_ptr>(_var)->size());
            case type_map :     return static_cast<unsigned int>(boost::get<map_ptr>(_var)->size());
            default :           throw exception("unhandled .count() operation");
        }
    }

    ///
    /// index[] operator for collections
    ///
    var& var::operator [] (int n) {
        switch (get_type()) {
            case type_null :    throw exception("cannot apply [] to none");
            case type_bool :    throw exception("cannot apply [] to bool");
            case type_int :     throw exception("cannot apply [] to int");
            case type_double :  throw exception("cannot apply [] to double");
            case type_string :  throw exception("cannot apply [] to string");
            case type_wstring : throw exception("cannot apply [] to wstring");
            case type_list :    {
                                    list_ptr& l = boost::get<list_ptr>(_var);
                                    if (n < 0 || n >= int(l->size())) throw exception("[] out of range in list");
                                    list_t::iterator li = l->begin();
                                    advance(li, n);
                                    return *li;
                                }
            case type_vector :  {
                                    vector_ptr& a = boost::get<vector_ptr>(_var);
                                    if (n < 0 || n >= int(a->size())) throw exception("[] out of range in vector");
                                    return (*a)[n];
                                }
            case type_set :     {
                                    set_ptr& s = boost::get<set_ptr>(_var);
                                    if (n < 0 || n >= int(s->size())) throw exception("[] out of range in set");
                                    set_t::iterator si = s->begin();
                                    advance(si, n);
                                    return const_cast<var&>(*si);
                                }
            case type_map :    {
                                    map_ptr& d = boost::get<map_ptr>(_var);
                                    var key(n);
                                    map_t::iterator di = d->find(key);
                                    if (di == d->end()) throw exception("[] not found in map");
                                    return di->second;
                                }
            default :           throw exception("unhandled [] operation");
        }
    }

    ///
    /// index a collection with a double
    ///
    var& var::operator [] (double n) { return operator[] (var(n)); }

    ///
    /// index a collection with a string
    ///
    var& var::operator [] (const std::string& s) { return operator[] (var(s)); }

    ///
    /// index a collection with a string constant
    ///
    var& var::operator [] (const char* s) { return operator[] (var(s)); }

    ///
    /// index a collection with a wide string
    ///
    var& var::operator [] (const std::wstring& s) { return operator[] (var(s)); }

    ///
    /// index a collection with a wide string constant
    ///
    var& var::operator [] (const wchar_t* s) { return operator[] (var(s)); }
    
    ///
    /// index a collection
    ///
    var& var::operator [] (const var& v) {    
        switch (get_type()) {
            case type_null :    throw exception("cannot apply [var] to none");
            case type_bool :    throw exception("cannot apply [var] to bool");
            case type_int :     throw exception("cannot apply [var] to int");
            case type_double :  throw exception("cannot apply [var] to double");
            case type_string :  throw exception("cannot apply [var] to string");
            case type_wstring : throw exception("cannot apply [var] to wstring");
            case type_list :    throw exception("list[] requires int");
            case type_vector :  throw exception("vector[] requires int");
            case type_set :     throw exception("set[] requires int");
            case type_map :     {
                                    var key(v);
                                    map_ptr& d = boost::get<map_ptr>(_var);
                                    map_t::iterator di = d->find(key);
                                    if (di != d->end()) return di->second;
                                    (*d)[key] = none;
                                    return (*d)[key];
                                }
            default :           throw exception("unhandled [var] operation");
        }
    }

    ///
    /// write a var to an ostream
    ///
    std::ostream& var::_write_var(std::ostream& os) {
        switch (get_type()) {
            case type_null :    os << "none"; return os;
            case type_bool:     os << (boost::get<bool>(_var) ? "true" : "false"); return os;
            case type_int :     os << boost::get<int>(_var); return os;
            case type_double :  os << boost::get<double>(_var); return os;
            case type_string :  return _write_string(os);
            case type_wstring : return _write_wstring(os);
            case type_list :
            case type_vector :
            case type_set :
            case type_map :     return _write_collection(os);
            default :           throw exception("var::_write_var(ostream) unhandled type");
        }
    }

    ///
    /// write a string to an ostream
    ///
    std::ostream& var::_write_string(std::ostream& os) {
        assert(is_string());
        os << '\'';
        for (const char* s = (*boost::get<string_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << "\\b"; break;
                case '\r' : os << "\\r"; break;
                case '\n' : os << "\\n"; break;
                case '\f' : os << "\\f"; break;
                case '\t' : os << "\\t"; break;
                case '\\' : os << "\\\\"; break;
                case '\'' : os << "\\'"; break;
                default :
                    if (*s < ' ') os << "0" << std::oct << std::setw(3) << std::setfill('0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ///
    /// write a wide string to an ostream
    ///
    std::ostream& var::_write_wstring(std::ostream& os) {
        assert(is_wstring());
        os << '\'';
        for (const wchar_t* s = (*boost::get<wstring_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << L"\\b"; break;
                case '\r' : os << L"\\r"; break;
                case '\n' : os << L"\\n"; break;
                case '\f' : os << L"\\f"; break;
                case '\t' : os << L"\\t"; break;
                case '\\' : os << L"\\\\"; break;
                case '\'' : os << L"\\'"; break;
                default :
                    if (*s < ' ') os << L"0" << std::oct << std::setw(3) << std::setfill('0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ///
    /// write a collection to an ostream
    ///
    std::ostream& var::_write_collection(std::ostream& os) {
        assert(is_collection());
        switch (get_type())
        {
            case type_list : os << "("; break;
            case type_vector : os << "["; break;
            case type_set : os << "{"; break;
            case type_map : os << "<"; break;
            default : assert(false);
        }
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << " ";
            (*vi)._write_var(os);
            if (get_type() == type_map) {
                os << ":";
                (*this)[*vi]._write_var(os);
            }
        }
        switch (get_type())
        {
            case type_list : os << ")"; break;
            case type_vector : os << "]"; break;
            case type_set : os << "}"; break;
            case type_map : os << ">"; break;
            default : assert(false);
        }
        return os;
    }

    ///
    /// write a var to a wostream
    ///
    std::wostream& var::_write_var(std::wostream& os) {
        switch (get_type()) {
            case type_null :    os << "none"; return os;
            case type_bool:     os << (boost::get<bool>(_var) ? "true" : "false"); return os;
            case type_int :     os << boost::get<int>(_var); return os;
            case type_double :  os << boost::get<double>(_var); return os;
            case type_string :  return _write_string(os);
            case type_wstring : return _write_wstring(os);
            case type_list :
            case type_vector :
            case type_set :
            case type_map :     return _write_collection(os);
            default :           throw exception("var::_write_var(wostream) unhandled type");
        }
    }

    ///
    /// write a string to a wostream
    ///
    std::wostream& var::_write_string(std::wostream& os) {
        assert(is_string());
        os << '\'';
        for (const char* s = (*boost::get<string_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << "\\b"; break;
                case '\r' : os << "\\r"; break;
                case '\n' : os << "\\n"; break;
                case '\f' : os << "\\f"; break;
                case '\t' : os << "\\t"; break;
                case '\\' : os << "\\\\"; break;
                case '\'' : os << "\\'"; break;
                default :
                    if (*s < ' ') os << "0" << std::oct << std::setw(3) << std::setfill(L'0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ///
    /// write a wide string to a wostream
    ///
    std::wostream& var::_write_wstring(std::wostream& os) {
        assert(is_wstring());
        os << '\'';
        for (const wchar_t* s = (*boost::get<wstring_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << L"\\b"; break;
                case '\r' : os << L"\\r"; break;
                case '\n' : os << L"\\n"; break;
                case '\f' : os << L"\\f"; break;
                case '\t' : os << L"\\t"; break;
                case '\\' : os << L"\\\\"; break;
                case '\'' : os << L"\\'"; break;
                default :
                    if (*s < ' ') os << "0" << std::oct << std::setw(3) << std::setfill(L'0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }
    
    ///
    /// write a collection to a wostream
    ///
    std::wostream& var::_write_collection(std::wostream& os) {
        assert(is_collection());
        switch (get_type())
        {
            case type_list : os << L"("; break;
            case type_vector : os << L"["; break;
            case type_set : os << L"{"; break;
            case type_map : os << L"<"; break;
            default : assert(false);
        }
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << L" ";
            (*vi)._write_var(os);
            if (get_type() == type_map) {
                os << L":";
                (*this)[*vi]._write_var(os);
            }
        }
        switch (get_type())
        {
            case type_list : os << L")"; break;
            case type_vector : os << L"]"; break;
            case type_set : os << L"}"; break;
            case type_map : os << L">"; break;
            default : assert(false);
        }
        return os;
    }

}
