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
#include <boost/utility.hpp>

namespace dynamic {

    using namespace std;
    using namespace boost;

    class exception : public std::exception
    {
	public :
        exception(const char* message) : std::exception() { _message = message; }
        ~exception() throw() {}
		
        const char* what() const throw() { return _message; }
		
	private :
        const char* _message;
    };
	
	class var;
	
	extern const var $;

	class var {
    public :
        var();
        var(int n);
        var(double n);
        var(const string& s);
        var(const char* s);
        var(const var& v);

        var& operator = (int n);
        var& operator = (double n);
        var& operator = (const string& s);
        var& operator = (const char* s);
        var& operator = (const var& v);

        operator int() const;
        operator double() const;
        operator string() const;

        string type() const;

        bool operator == (int n) const;
        bool operator == (double n) const;
        bool operator == (const string& s) const;
        bool operator == (const char* s) const;
        bool operator == (const var& v) const;

        bool operator != (int n) const;
        bool operator != (double n) const;
        bool operator != (const string& s) const;
        bool operator != (const char* s) const;
        bool operator != (const var& v) const;

        bool operator < (int n) const;
        bool operator < (double n) const;
        bool operator < (const string& s) const;
        bool operator < (const char* s) const;
        bool operator < (const var& v) const;

        bool operator <= (int n) const;
        bool operator <= (double n) const;
        bool operator <= (const string& s) const;
        bool operator <= (const char* s) const;
        bool operator <= (const var& v) const;

        bool operator > (int n) const;
        bool operator > (double n) const;
        bool operator > (const string& s) const;
        bool operator > (const char* s) const;
        bool operator > (const var& v) const;

        bool operator >= (int n) const;
        bool operator >= (double n) const;
        bool operator >= (const string& s) const;
        bool operator >= (const char* s) const;
        bool operator >= (const var& v) const;

        bool is_null() const { return get_type() == type_null; }
        bool is_int() const { return get_type() == type_int; }
        bool is_double() const { return get_type() == type_double; }
        bool is_numeric() const { return is_int() || is_double(); }
        bool is_string() const { return get_type() == type_string; }
        bool is_list() const { return get_type() == type_list; }
        bool is_array() const { return get_type() == type_array; }
        bool is_set() const { return get_type() == type_set; }
        bool is_dict() const { return get_type() == type_dict; }
        bool is_collection() const { return is_list() || is_array() || is_set() || is_dict(); }

        var& operator () (int n);
        var& operator () (double n);
        var& operator () (const char* s);
        var& operator () (const string& s);
        var& operator () (const var& v);
        var& operator () (const var& k, const var& v);
        
        ostream& _write_var(ostream& os);
        ostream& _write_string(ostream& os);
        ostream& _write_list(ostream& os);
        ostream& _write_array(ostream& os);
        ostream& _write_set(ostream& os);
        ostream& _write_dict(ostream& os);

        static var new_list();
        static var new_array();
        static var new_set();
        static var new_dict();

        unsigned int count() const;
        var& operator [] (int n);
        var& operator [] (double n);
        var& operator [] (const char* s);
        var& operator [] (const string& s);
        var& operator [] (const var& v);

        struct less_var { bool operator () (const var& lhs, const var& rhs); };

        typedef std::list<var> list_t;
        typedef std::vector<var> array_t;
        typedef std::set<var, less_var> set_t;
        typedef std::map<var, var, less_var> dict_t;

        class iterator {
        public :
            iterator(list_t::iterator iter) : _iter(iter) {}
            iterator(array_t::iterator iter) : _iter(iter) {}
            iterator(set_t::iterator iter) : _iter(iter) {}
            iterator(dict_t::iterator iter) : _iter(iter) {}

            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);

            bool operator==(iterator rhs);
            bool operator!=(iterator rhs) { return !(*this == rhs); }

            var& operator*();

        private :
            typedef variant<list_t::iterator, array_t::iterator, set_t::iterator, dict_t::iterator> iter_t;

            iter_t _iter;
        };

        iterator begin();
        iterator end();

        class reverse_iterator {
        public :
            reverse_iterator(list_t::reverse_iterator riter) : _riter(riter) {}
            reverse_iterator(array_t::reverse_iterator riter) : _riter(riter) {}
            reverse_iterator(set_t::reverse_iterator riter) : _riter(riter) {}
            reverse_iterator(dict_t::reverse_iterator riter) : _riter(riter) {}

            reverse_iterator operator++();
            reverse_iterator operator++(int);
            reverse_iterator operator--();
            reverse_iterator operator--(int);

            bool operator==(reverse_iterator rhs);
            bool operator!=(reverse_iterator rhs) { return !(*this == rhs); }

        private :
            typedef variant<list_t::reverse_iterator, array_t::reverse_iterator, set_t::reverse_iterator, dict_t::reverse_iterator> riter_t;

            riter_t _riter;
        };

        reverse_iterator rbegin();
        reverse_iterator rend();

    private :
        enum type_t { type_null, type_int, type_double, type_string, type_list, type_array, type_set, type_dict };

        struct null_t { null_t() {} };

        struct string_t {
            string_t() : ps(new string) {}
            string_t(const string& s) : ps(new string(s)) {}
            string_t(const char* s) : ps(new string(s)) {}

            shared_ptr<string>  ps;
        };

        typedef int int_t;
        typedef double double_t;

        typedef shared_ptr<list_t> list_ptr;
        typedef shared_ptr<array_t> array_ptr;
        typedef shared_ptr<set_t> set_ptr;
        typedef shared_ptr<dict_t> dict_ptr;

        var(list_ptr _list);
        var(array_ptr _array);
        var(set_ptr _set);
        var(dict_ptr _dict);

        typedef variant<null_t, int_t, double_t, string_t, list_ptr, array_ptr, set_ptr, dict_ptr> var_t;

        type_t get_type() const;

        var_t _var;

		// misc visitors - these used to be local types within the functions that actually used them
		// but it turned out that g++ didn't like passing locally defined objects to boost::apply_visitor().
		// They're here because they need access to the internals of var
#include "iterator_visitors.h"
		// put visitors into separate headers to keep this file from getting out of hand

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
		
    };

    inline ostream& operator << (ostream& os, var& v) { return v._write_var(os); }

    inline var new_list() { return var::new_list(); }
    inline var new_array() { return var::new_array(); }
    inline var new_set() { return var::new_set(); }
    inline var new_dict() { return var::new_dict(); }

    inline var new_list(const var& v) { return var::new_list()(v); }
    inline var new_array(const var& v) { return var::new_array()(v); }
    inline var new_set(const var& v) { return var::new_set()(v); }
    inline var new_dict(const var& k) { return var::new_dict()(k); }
    inline var new_dict(const var& k, const var& v) { return var::new_dict()(k, v); }

}
