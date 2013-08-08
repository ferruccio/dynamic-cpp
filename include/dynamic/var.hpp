#ifndef DYNAMIC_VAR_HPP
#define DYNAMIC_VAR_HPP

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
#include <vector>
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
/// the var class is the heart of Dynamic C++
///
class var {
public :
    typedef std::size_t size_type;
    // Note to dynamic developer: Make sure that code and the variant list for var_t always match
    enum code { type_null = 0, type_bool, type_int, type_double, type_string, type_wstring, type_vector, type_map };

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

    enum code type() const;
    std::string name() const;

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
    bool is_null() const { return type() == type_null; }
    /// is var a bool?
    bool is_bool() const { return type() == type_bool; }
    /// is var an int?
    bool is_int() const { return type() == type_int; }
    /// is var a double?
    bool is_double() const { return type() == type_double; }
    /// is var a numeric type?
    bool is_numeric() const { return is_int() || is_double(); }
    /// is var a string?
    bool is_string() const { return type() == type_string; }
    /// is var a wide string?
    bool is_wstring() const { return type() == type_wstring; }
    /// is var a string type?
    bool is_string_type() const { return is_string() || is_wstring(); }
    /// is var a vector?
    bool is_vector() const { return type() == type_vector; }
    /// is var a map?
    bool is_map() const { return type() == type_map; }
    /// is var a collection type?
    bool is_collection() const { return is_vector() || is_map(); }

    var& operator () (bool);
    var& operator () (int n);
    var& operator () (double n);
    var& operator () (const std::string& s);
    var& operator () (const char* s);
    var& operator () (const std::wstring& s);
    var& operator () (const wchar_t* s);
    var& operator () (const var& v);
    var& operator () (const var& k, const var& v);
        
    std::ostream& _write_var(std::ostream& os) const;
    std::ostream& _write_string(std::ostream& os) const;
    std::ostream& _write_wstring(std::ostream& os) const;
    std::ostream& _write_collection(std::ostream& os) const;

    std::wostream& _write_var(std::wostream& os) const;
    std::wostream& _write_string(std::wostream& os) const;
    std::wostream& _write_wstring(std::wostream& os) const;
    std::wostream& _write_collection(std::wostream& os) const;
        
    size_type count() const;
    var& operator [] (int n);
    var& operator [] (double n);
    var& operator [] (const std::string& s);
    var& operator [] (const char* s);
    var& operator [] (const std::wstring& s);
    var& operator [] (const wchar_t* s);
    var& operator [] (const var& v);
    const var& operator [] (const var& v) const;

    /// var comparison functor
    struct less_var {
        /// var comparison function
        bool operator () (const var& lhs, const var& rhs);
    };

    /// vector type
    typedef std::vector<var> vector_type;
    /// map type
    typedef std::map<var, var, less_var> map_type;
    /// pair type
    typedef map_type::value_type pair_type;

    ///
    /// collection const_iterator class
    ///
    class const_iterator {
    public :
        const_iterator operator++();
        const_iterator operator++(int);
        const_iterator operator--();
        const_iterator operator--(int);

        bool operator==(const_iterator rhs);
        /// iterator inequality
        bool operator!=(const_iterator rhs) { return !(*this == rhs); }

        const var& operator*() const;
        const pair_type& pair() const;

    private :
        friend class var;
        /// initialize from vector iterator
        const_iterator(vector_type::iterator iter) : _iter(iter) {}
        /// initialize from map iterator
        const_iterator(map_type::iterator iter) : _iter(iter) {}

        // make sure base_type and the variant list for iter_t always match
        enum base_type { type_vector = 0, type_map };
        typedef boost::variant<vector_type::iterator, map_type::iterator> iter_t;

        iter_t _iter;
    };

    ///
    /// collection iterator class
    ///
    class iterator : public const_iterator {
    public:
        var& operator*();
        pair_type& pair();

    private:
        friend class var;
        /// initialize from vector iterator
        iterator(vector_type::iterator iter) : const_iterator(iter) {}
        /// initialize from map iterator
        iterator(map_type::iterator iter) : const_iterator(iter) {}
    };

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    ///
    /// collection reverse_iterator class
    ///
    class reverse_iterator {
    public :
        /// initialize from vector reverse iterator
        reverse_iterator(vector_type::reverse_iterator riter) : _riter(riter) {}
        /// initialize from map reverse iterator
        reverse_iterator(map_type::reverse_iterator riter) : _riter(riter) {}

        reverse_iterator operator++();
        reverse_iterator operator++(int);
        reverse_iterator operator--();
        reverse_iterator operator--(int);

        bool operator==(reverse_iterator rhs);
        /// reverse iterator inequality
        bool operator!=(reverse_iterator rhs) { return !(*this == rhs); }

    private :
        // make sure base_type and the variant list for riter_t always match
        enum base_type { type_vector = 0, type_map };
        typedef boost::variant<vector_type::reverse_iterator, map_type::reverse_iterator> riter_t;

        riter_t _riter;
    };

    reverse_iterator rbegin();
    reverse_iterator rend();

private :
    friend var make_vector();
    friend var make_map();

    typedef boost::blank null_t;

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

    typedef boost::shared_ptr<vector_type> vector_ptr;
    typedef boost::shared_ptr<map_type> map_ptr;

    var(vector_ptr _vector);
    var(map_ptr _map);

    typedef boost::variant<null_t, bool_t, int_t, double_t, string_t, wstring_t, vector_ptr, map_ptr> var_t;

    var_t _var;

    struct name_visitor;
    struct count_visitor;
    struct index_int_visitor;
    struct index_var_visitor;
    struct append_value_visitor;
    struct append_key_value_visitor;
    struct equal_visitor;
};

///
/// predefined null object
///
extern const var none;

/// ostream << var
inline std::ostream& operator << (std::ostream& os, const var& v) { return v._write_var(os); }
/// wostream << var
inline std::wostream& operator << (std::wostream& os, const var& v) { return v._write_var(os); }

/// create empty vector
inline var make_vector() { return var(boost::make_shared<var::vector_type>()); }
/// create empty map
inline var make_map() { return var(boost::make_shared<var::map_type>()); }

/// create vector with one item
inline var make_vector(const var& v) { return dynamic::make_vector()(v); }
/// create map with one item (a key) and null value
inline var make_map(const var& k) { return dynamic::make_map()(k); }
/// create map with one item (a key,value pair)
inline var make_map(const var& k, const var& v) { return dynamic::make_map()(k, v); }

}

#endif /* DYNAMIC_VAR_HPP */
