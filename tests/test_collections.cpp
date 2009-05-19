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

#include <sstream>
using namespace std;

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "dynamic.h"

using namespace dynamic;

BOOST_AUTO_TEST_CASE (test_lists) {
    var l1 = new_list();
    BOOST_CHECK_EQUAL(l1.count(), 0);
    BOOST_CHECK(l1.is_list());
    BOOST_CHECK(l1.is_collection());

    var l2 = new_list(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(l2.count(), 3);
    BOOST_CHECK(l2.is_list());
    BOOST_CHECK(l2.is_collection());
    BOOST_CHECK(l2[0] == 1);
    BOOST_CHECK(l2[1] == "hello");
    BOOST_CHECK(l2[2] == 10.5);
}

BOOST_AUTO_TEST_CASE (test_arrays) {
    var a1 = new_array();
    BOOST_CHECK_EQUAL(a1.count(), 0);
    BOOST_CHECK(a1.is_array());
    BOOST_CHECK(a1.is_collection());

    var a2 = new_array(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(a2.count(), 3);
    BOOST_CHECK(a2.is_array());
    BOOST_CHECK(a2.is_collection());
    BOOST_CHECK(a2[0] == 1);
    BOOST_CHECK(a2[1] == "hello");
    BOOST_CHECK(a2[2] == 10.5);
}

BOOST_AUTO_TEST_CASE (test_sets) {
    var s1 = new_set();
    BOOST_CHECK_EQUAL(s1.count(), 0);
    BOOST_CHECK(s1.is_set());
    BOOST_CHECK(s1.is_collection());

    var s2 = new_set(1)("hello")(10.5)(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(s2.count(), 3);
    BOOST_CHECK(s2.is_set());
    BOOST_CHECK(s2.is_collection());
    BOOST_CHECK(s2[0] == 1);
    BOOST_CHECK(s2[1] == 10.5);
    BOOST_CHECK(s2[2] == "hello");
}

BOOST_AUTO_TEST_CASE (test_dicts) {
    var d1 = new_dict();
    BOOST_CHECK_EQUAL(d1.count(), 0);
    BOOST_CHECK(d1.is_dict());
    BOOST_CHECK(d1.is_collection());

    var d2 = new_dict(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(d2.count(), 3);
    BOOST_CHECK(d2.is_dict());
    BOOST_CHECK(d2.is_collection());
    BOOST_CHECK(d2[1] == $);
    BOOST_CHECK(d2["hello"] == $);
    BOOST_CHECK(d2[10.5] == $);

    var d3 = new_dict(1, "xxx")("hello", "world")(10.5, 3.14);
    BOOST_CHECK_EQUAL(d3.count(), 3);
    BOOST_CHECK(d3.is_dict());
    BOOST_CHECK(d3.is_collection());
    BOOST_CHECK(d3[1] == "xxx");
    BOOST_CHECK(d3["hello"] == "world");
    BOOST_CHECK(d3[10.5] == 3.14);

    var d4 = new_dict();
    d4["hello"] = "world";
    BOOST_CHECK(d4["hello"] == "world");
    BOOST_CHECK(d4["test"] == $);
    BOOST_CHECK_EQUAL(d4.count(), 2);
}

BOOST_AUTO_TEST_CASE (test_complex) {
    var d = new_dict
        ("array", new_array(1)(1.5)("hello"))
        ("list", new_list(2)(3.5)("world"))
        ("set", new_set(3)("xyzzy")(4.5))
        ("dict", new_dict("a", 4)("b", 5.5)("c", "plover"));

    BOOST_CHECK(d.count() == 4);
    BOOST_CHECK(d.is_dict());
    BOOST_CHECK(d["array"].count() == 3);
    BOOST_CHECK(d["array"].is_array());
    BOOST_CHECK(d["array"][0] == 1);
    BOOST_CHECK(d["array"][1] == 1.5);
    BOOST_CHECK(d["array"][2] == "hello");

    BOOST_CHECK(d["list"].count() == 3);
    BOOST_CHECK(d["list"].is_list());
    BOOST_CHECK(d["list"][0] == 2);
    BOOST_CHECK(d["list"][1] == 3.5);
    BOOST_CHECK(d["list"][2] == "world");

    BOOST_CHECK(d["set"].count() == 3);
    BOOST_CHECK(d["set"].is_set());
    BOOST_CHECK(d["set"][0] == 3);
    BOOST_CHECK(d["set"][1] == 4.5);
    BOOST_CHECK(d["set"][2] == "xyzzy");

    BOOST_CHECK(d["dict"].count() == 3);
    BOOST_CHECK(d["dict"].is_dict());
    BOOST_CHECK(d["dict"]["a"] == 4);
    BOOST_CHECK(d["dict"]["b"] == 5.5);
    BOOST_CHECK(d["dict"]["c"] == "plover");

    stringstream ss;
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'array':[1 1.5 'hello'] 'dict':<'a':4 'b':5.5 'c':'plover'> 'list':(2 3.5 'world') 'set':{3 4.5 'xyzzy'}>");

    d["list"][1] = "hello";
    ss.str(string());
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'array':[1 1.5 'hello'] 'dict':<'a':4 'b':5.5 'c':'plover'> 'list':(2 'hello' 'world') 'set':{3 4.5 'xyzzy'}>");

    d["array"][0] = d["array"][1] = d["array"][2] = $;
    ss.str(string());
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'array':[$ $ $] 'dict':<'a':4 'b':5.5 'c':'plover'> 'list':(2 'hello' 'world') 'set':{3 4.5 'xyzzy'}>");

    d["dict"]["b"] = new_array(1)(2.1)(3)(new_list(1)("b"));
    ss.str(string());
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'array':[$ $ $] 'dict':<'a':4 'b':[1 2.1 3 (1 'b')] 'c':'plover'> 'list':(2 'hello' 'world') 'set':{3 4.5 'xyzzy'}>");
}

