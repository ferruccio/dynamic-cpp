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

#include <sstream>
#include <iostream>

using namespace std;

#define BOOST_TEST_MODULE dynamic_tests
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <dynamic/dynamic.hpp>

using namespace dynamic;

BOOST_AUTO_TEST_CASE (ctor) {
    BOOST_CHECK_NO_THROW(var());

    var v;
    BOOST_TEST_MESSAGE("sizeof(var) = " << sizeof(v));
}

BOOST_AUTO_TEST_CASE (ctor_bool)
{
    stringstream ss;

    var vb(true);
    BOOST_REQUIRE(vb.is_bool());
    BOOST_REQUIRE_EQUAL(vb.type(), var::type_bool);
    BOOST_REQUIRE(!vb.is_collection());
    BOOST_REQUIRE_EQUAL(vb.name(), "bool");
    BOOST_REQUIRE_EQUAL(bool(vb), true);
    BOOST_REQUIRE_NO_THROW(ss << vb);
    BOOST_REQUIRE_EQUAL(ss.str(), "true");
}

BOOST_AUTO_TEST_CASE (simple_ctor) {
    stringstream ss;

    var v;
    BOOST_CHECK(v.is_null());
    BOOST_CHECK_EQUAL(v.type(), var::type_null);
    BOOST_CHECK(!v.is_collection());
    BOOST_CHECK_EQUAL(v.name(), "null");
    ss << v;
    BOOST_CHECK_EQUAL(ss.str(), "null");

    var vi(12);
    BOOST_CHECK(vi.is_int());
    BOOST_CHECK_EQUAL(vi.type(), var::type_int);
    BOOST_CHECK(vi.is_numeric());
    BOOST_CHECK(!vi.is_collection());
    BOOST_CHECK_EQUAL(vi.name(), "int");
    BOOST_CHECK_EQUAL(int(vi), 12);
    ss.str(string());
    ss << vi;
    BOOST_CHECK_EQUAL(ss.str(), "12");

    var vd(100.5);
    BOOST_CHECK(vd.is_double());
    BOOST_CHECK_EQUAL(vd.type(), var::type_double);
    BOOST_CHECK(vd.is_numeric());
    BOOST_CHECK(!vd.is_collection());
    BOOST_CHECK_EQUAL(vd.name(), "double");
    BOOST_CHECK_CLOSE(double(vd), 100.5, 1e-6);
    ss.str(string());
    ss << vd;
    BOOST_CHECK_EQUAL(ss.str(), "100.5");

    var vs("hello");
    BOOST_CHECK(vs.is_string());
    BOOST_CHECK_EQUAL(vs.type(), var::type_string);
    BOOST_CHECK(!vs.is_collection());
    BOOST_CHECK_EQUAL(vs.name(), "string");
    BOOST_CHECK_EQUAL(string(vs), "hello");
    ss.str(string());
    ss << vs;
    BOOST_CHECK_EQUAL(ss.str(), "\"hello\"");

    var vn(vs);
    BOOST_CHECK(vn.is_string());
    BOOST_CHECK(!vn.is_collection());
    BOOST_CHECK_EQUAL(vn.name(), "string");
    BOOST_CHECK_EQUAL(string(vn), "hello");
    ss.str(string());
    ss << vn;
    BOOST_CHECK_EQUAL(ss.str(), "\"hello\"");
}

BOOST_AUTO_TEST_CASE (simple_assign) {
    stringstream ss;

    var v(10);
    BOOST_CHECK(v.is_int());
    v = none;
    BOOST_CHECK(v.is_null());
    BOOST_CHECK(!v.is_collection());
    BOOST_CHECK_EQUAL(v.name(), "null");
    ss << v;
    BOOST_CHECK_EQUAL(ss.str(), "null");

    var vi;
    vi = 12;
    BOOST_CHECK(vi.is_int());
    BOOST_CHECK(vi.is_numeric());
    BOOST_CHECK(!vi.is_collection());
    BOOST_CHECK_EQUAL(vi.name(), "int");
    BOOST_CHECK_EQUAL(int(vi), 12);
    ss.str(string());
    ss << vi;
    BOOST_CHECK_EQUAL(ss.str(), "12");

    var vd;
    vd = 100.5;
    BOOST_CHECK(vd.is_double());
    BOOST_CHECK(vd.is_numeric());
    BOOST_CHECK(!vd.is_collection());
    BOOST_CHECK_EQUAL(vd.name(), "double");
    BOOST_CHECK_CLOSE(double(vd), 100.5, 1e-6);
    ss.str(string());
    ss << vd;
    BOOST_CHECK_EQUAL(ss.str(), "100.5");

    var vs;
    vs = "hello";
    BOOST_CHECK(vs.is_string());
    BOOST_CHECK_EQUAL(vs.name(), "string");
    BOOST_CHECK_EQUAL(string(vs), "hello");
    BOOST_CHECK(!vs.is_collection());
    ss.str(string());
    ss << vs;
    BOOST_CHECK_EQUAL(ss.str(), "\"hello\"");

    string world = "world";
    vs = world;
    BOOST_CHECK(vs.is_string());
    BOOST_CHECK(!vs.is_collection());
    BOOST_CHECK_EQUAL(vs.name(), "string");
    BOOST_CHECK_EQUAL(string(vs), "world");
    ss.str(string());
    ss << vs;
    BOOST_CHECK_EQUAL(ss.str(), "\"world\"");

    var vn;
    vn = vd;
    BOOST_CHECK(vn.is_double());
    BOOST_CHECK(vn.is_numeric());
    BOOST_CHECK(!vn.is_collection());
    BOOST_CHECK_EQUAL(vn.name(), "double");
    BOOST_CHECK_CLOSE(double(vn), 100.5, 1e-6);
    ss.str(string());
    ss << vn;
    BOOST_CHECK_EQUAL(ss.str(), "100.5");
}

BOOST_AUTO_TEST_CASE(Examples) {

    var a = none;  // a is initially null
    cout << a << endl;

    a = 1;      // a is an now integer
    cout << a << endl;

    a = 2.5;    // a is now a double
    cout << a << endl;

    a = "hello, world!"; // a is now a string
    cout << a << endl;

    a = L"hello, wide world!"; // a is now a wide string
    cout << a << endl;

    a = make_vector(1)(2)(3); // a is now an array of integers
    cout << a << endl;

    a = make_vector(1)(2)(3.5)("hello")(make_vector(1)(2.0)("three"));
    // a is now an array containing 2 ints, a double, a string and an array of three items

    cout << "c: " << a << endl;
    // some iterator support
    for (var::const_iterator i = a.begin(); i != a.end(); ++i)
        cout << *i << endl;

    a = make_map("name", "fred")("age", 35)("city", "bedrock")(12, make_vector(1)(2)(3)); // keys and values can be any type
    // a is now a dictionary
    cout << a << endl;

}
