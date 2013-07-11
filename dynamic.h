#ifndef DYNAMIC_DYNAMIC_HPP
#define DYNAMIC_DYNAMIC_HPP

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

#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>

#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/utility.hpp>

///
/// Dynamic C++ namespace
///
namespace dynamic {

    ///
    /// exception class thrown by Dynamic C++
    ///
    class exception : public std::exception
    {
    public :
        ///
        /// construct exception with message
        ///
        exception(const char* message) : std::exception() { _message = message; }
        ~exception() throw() {}
        
        ///
        /// @return exception message
        ///
        const char* what() const throw() { return _message; }
        
    private :
        const char* _message;
    };
    
    class var;
    
    ///
    /// predefined null object
    ///
    extern const var none;

    ///
    /// the var class is the heart of Dynamic C++
    ///
    class var {
    public :
        typedef std::size_t size_type;

        var();
        var(bool);
        var(int n);
        var(double n);
        var(const std::string& s);
        var(const char* s);
        var(const std::wstring& s);
        var(const wchar_t* s);
        var(const var& v);

        var& operator = (bool);
        var& operator = (int n);
        var& operator = (double n);
        var& operator = (const std::string& s);
        var& operator = (const char* s);
        var& operator = (const std::wstring& s);
        var& operator = (const wchar_t* s);
        var& operator = (const var& v);

        operator bool() const;
        operator int() const;
        operator double() const;
        operator std::string() const;
        operator std::wstring() const;

        std::string type() const;

        bool operator == (bool) const;
        bool operator == (int n) const;
        bool operator == (double n) const;
        bool operator == (const std::string& s) const;
        bool operator == (const char* s) const;
        bool operator == (const std::wstring& s) const;
        bool operator == (const wchar_t* s) const;
        bool operator == (const var& v) const;

        bool operator != (bool) const;
        bool operator != (int n) const;
        bool operator != (double n) const;
        bool operator != (const std::string& s) const;
        bool operator != (const char* s) const;
        bool operator != (const std::wstring& s) const;
        bool operator != (const wchar_t* s) const;
        bool operator != (const var& v) const;

        bool operator < (bool) const;
        bool operator < (int n) const;
        bool operator < (double n) const;
        bool operator < (const std::string& s) const;
        bool operator < (const char* s) const;
        bool operator < (const std::wstring& s) const;
        bool operator < (const wchar_t* s) const;
        bool operator < (const var& v) const;

        bool operator <= (bool) const;
        bool operator <= (int n) const;
        bool operator <= (double n) const;
        bool operator <= (const std::string& s) const;
        bool operator <= (const char* s) const;
        bool operator <= (const std::wstring& s) const;
        bool operator <= (const wchar_t* s) const;
        bool operator <= (const var& v) const;

        bool operator > (bool) const;
        bool operator > (int n) const;
        bool operator > (double n) const;
        bool operator > (const std::string& s) const;
        bool operator > (const char* s) const;
        bool operator > (const std::wstring& s) const;
        bool operator > (const wchar_t* s) const;
        bool operator > (const var& v) const;

        bool operator >= (bool) const;
        bool operator >= (int n) const;
        bool operator >= (double n) const;
        bool operator >= (const std::string& s) const;
        bool operator >= (const char* s) const;
        bool operator >= (const std::wstring& s) const;
        bool operator >= (const wchar_t* s) const;
        bool operator >= (const var& v) const;
        
        /// is var a null?
        bool is_null() const { return get_type() == type_null; }
        /// is var a bool?
        bool is_bool() const { return get_type() == type_bool; }
        /// is var an int?
        bool is_int() const { return get_type() == type_int; }
        /// is var a double?
        bool is_double() const { return get_type() == type_double; }
        /// is var a numeric type?
        bool is_numeric() const { return is_int() || is_double(); }
        /// is var a string?
        bool is_string() const { return get_type() == type_string; }
         /// is var a wide string?
        bool is_wstring() const { return get_type() == type_wstring; }
         /// is var a string type?
        bool is_string_type() const { return is_string() || is_wstring(); }
        /// is var a list?
        bool is_list() const { return get_type() == type_list; }
        /// is var a vector?
        bool is_vector() const { return get_type() == type_vector; }
        /// is var a set?
        bool is_set() const { return get_type() == type_set; }
        /// is var a map?
        bool is_map() const { return get_type() == type_map; }
        /// is var a collection type?
        bool is_collection() const { return is_list() || is_vector() || is_set() || is_map(); }

        var& operator () (bool);
        var& operator () (int n);
        var& operator () (double n);
        var& operator () (const std::string& s);
        var& operator () (const char* s);
        var& operator () (const std::wstring& s);
        var& operator () (const wchar_t* s);
        var& operator () (const var& v);
        var& operator () (const var& k, const var& v);
        
        std::ostream& _write_var(std::ostream& os);
        std::ostream& _write_string(std::ostream& os);
        std::ostream& _write_wstring(std::ostream& os);
        std::ostream& _write_collection(std::ostream& os);

        std::wostream& _write_var(std::wostream& os);
        std::wostream& _write_string(std::wostream& os);
        std::wostream& _write_wstring(std::wostream& os);
        std::wostream& _write_collection(std::wostream& os);
        
        size_type count() const;
        var& operator [] (int n);
        var& operator [] (double n);
        var& operator [] (const std::string& s);
        var& operator [] (const char* s);
        var& operator [] (const std::wstring& s);
        var& operator [] (const wchar_t* s);
        var& operator [] (const var& v);

        /// var comparison functor
        struct less_var {
            /// var comparison function
            bool operator () (const var& lhs, const var& rhs);
        };

        /// list type
        typedef std::list<var> list_t;
        /// vector type
        typedef std::vector<var> vector_t;
        /// set type
        typedef std::set<var, less_var> set_t;
        /// map type
        typedef std::map<var, var, less_var> map_t;

        ///
        /// collection iterator class
        ///
        class iterator {
        public :
            /// initialize from list iterator
            iterator(list_t::iterator iter) : _iter(iter) {}
            /// initialize from vector iterator
            iterator(vector_t::iterator iter) : _iter(iter) {}
            /// initialize from set iterator
            iterator(set_t::iterator iter) : _iter(iter) {}
            /// initialize from map iterator
            iterator(map_t::iterator iter) : _iter(iter) {}

            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);

            bool operator==(iterator rhs);
            /// iterator inequality
            bool operator!=(iterator rhs) { return !(*this == rhs); }

            var& operator*();

        private :
            // make sure base_type and the variant list for iter_t always match
            enum base_type { list_type = 0, vector_type, set_type, map_type };
            typedef boost::variant<list_t::iterator, vector_t::iterator, set_t::iterator, map_t::iterator> iter_t;

            iter_t _iter;
        };

        iterator begin();
        iterator end();

        ///
        /// collection reverse_iterator class
        ///
        class reverse_iterator {
        public :
            /// initialize from list reverse iterator
            reverse_iterator(list_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from vector reverse iterator
            reverse_iterator(vector_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from set reverse iterator
            reverse_iterator(set_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from map reverse iterator
            reverse_iterator(map_t::reverse_iterator riter) : _riter(riter) {}

            reverse_iterator operator++();
            reverse_iterator operator++(int);
            reverse_iterator operator--();
            reverse_iterator operator--(int);

            bool operator==(reverse_iterator rhs);
            /// reverse iterator inequality
            bool operator!=(reverse_iterator rhs) { return !(*this == rhs); }

        private :
            // make sure base_type and the variant list for riter_t always match
            enum base_type { list_type = 0, vector_type, set_type, map_type };
            typedef boost::variant<list_t::reverse_iterator, vector_t::reverse_iterator, set_t::reverse_iterator, map_t::reverse_iterator> riter_t;

            riter_t _riter;
        };

        reverse_iterator rbegin();
        reverse_iterator rend();

    private :
        friend var make_list();
        friend var make_vector();
        friend var make_set();
        friend var make_map();

        enum type_t { type_null, type_bool, type_int, type_double, type_string, type_wstring, type_list, type_vector, type_set, type_map };

        struct null_t { null_t() {} };

        struct string_t {
            string_t() : ps(boost::make_shared<std::string>()) {}
            string_t(const std::string& s) : ps(boost::make_shared<std::string>(s)) {}
            string_t(const char* s) : ps(boost::make_shared<std::string>(s)) {}

            boost::shared_ptr<std::string>  ps;
        };
        
        struct wstring_t {
            wstring_t() : ps(boost::make_shared<std::wstring>()) {}
            wstring_t(const std::wstring& s) : ps(boost::make_shared<std::wstring>(s)) {}
            wstring_t(const wchar_t* s) : ps(boost::make_shared<std::wstring>(s)) {}

            boost::shared_ptr<std::wstring>  ps;
        };

        typedef bool bool_t;
        typedef int int_t;
        typedef double double_t;

        typedef boost::shared_ptr<list_t> list_ptr;
        typedef boost::shared_ptr<vector_t> vector_ptr;
        typedef boost::shared_ptr<set_t> set_ptr;
        typedef boost::shared_ptr<map_t> map_ptr;

        var(list_ptr _list);
        var(vector_ptr _vector);
        var(set_ptr _set);
        var(map_ptr _map);

        typedef boost::variant<null_t, bool_t, int_t, double_t, string_t, wstring_t, list_ptr, vector_ptr, set_ptr, map_ptr> var_t;

        type_t get_type() const;

        var_t _var;

        /// used to retrieve type from var
        struct type_visitor : public boost::static_visitor<type_t> {
            type_t operator () (null_t) const { return type_null; }
            type_t operator () (bool_t) const { return type_bool; }
            type_t operator () (int_t) const { return type_int; }
            type_t operator () (double_t) const { return type_double; }
            type_t operator () (string_t s) const { return type_string; }
            type_t operator () (wstring_t s) const { return type_wstring; }
            type_t operator () (list_ptr) const { return type_list; }
            type_t operator () (vector_ptr) const { return type_vector; }
            type_t operator () (set_ptr) const { return type_set; }
            type_t operator () (map_ptr) const { return type_map; }
        };

    };

    /// ostream << var
    inline std::ostream& operator << (std::ostream& os, var& v) { return v._write_var(os); }
    /// wostream << var
    inline std::wostream& operator << (std::wostream& os, var& v) { return v._write_var(os); }

    /// create empty list
    inline var make_list() { return var(boost::make_shared<var::list_t>()); }
    /// create empty vector
    inline var make_vector() { return var(boost::make_shared<var::vector_t>()); }
    /// create empty set
    inline var make_set() { return var(boost::make_shared<var::set_t>()); }
    /// create empty map
    inline var make_map() { return var(boost::make_shared<var::map_t>()); }

    /// create list with one item
    inline var make_list(const var& v) { return dynamic::make_list()(v); }
    /// create vector with one item
    inline var make_vector(const var& v) { return dynamic::make_vector()(v); }
    /// create set with one item
    inline var make_set(const var& v) { return dynamic::make_set()(v); }
    /// create map with one item (a key) and null value
    inline var make_map(const var& k) { return dynamic::make_map()(k); }
    /// create map with one item (a key,value pair)
    inline var make_map(const var& k, const var& v) { return dynamic::make_map()(k, v); }

}

#endif /* DYNAMIC_DYNAMIC_HPP */
