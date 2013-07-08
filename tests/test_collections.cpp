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
using namespace std;

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "dynamic.h"

using namespace dynamic;

BOOST_AUTO_TEST_CASE (test_lists) {
    var l1 = make_list();
    BOOST_CHECK_EQUAL(l1.count(), 0);
    BOOST_CHECK(l1.is_list());
    BOOST_CHECK(l1.is_collection());

    var l2 = make_list(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(l2.count(), 3);
    BOOST_CHECK(l2.is_list());
    BOOST_CHECK(l2.is_collection());
    BOOST_CHECK(l2[0] == 1);
    BOOST_CHECK(l2[1] == "hello");
    BOOST_CHECK(l2[2] == 10.5);
}

BOOST_AUTO_TEST_CASE (test_vectors) {
    var a1 = make_vector();
    BOOST_CHECK_EQUAL(a1.count(), 0);
    BOOST_CHECK(a1.is_vector());
    BOOST_CHECK(a1.is_collection());

    var a2 = make_vector(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(a2.count(), 3);
    BOOST_CHECK(a2.is_vector());
    BOOST_CHECK(a2.is_collection());
    BOOST_CHECK(a2[0] == 1);
    BOOST_CHECK(a2[1] == "hello");
    BOOST_CHECK(a2[2] == 10.5);
}

BOOST_AUTO_TEST_CASE (test_sets) {
    var s1 = make_set();
    BOOST_CHECK_EQUAL(s1.count(), 0);
    BOOST_CHECK(s1.is_set());
    BOOST_CHECK(s1.is_collection());

    var s2 = make_set(1)("hello")(10.5)(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(s2.count(), 3);
    BOOST_CHECK(s2.is_set());
    BOOST_CHECK(s2.is_collection());
    BOOST_CHECK(s2[0] == 1);
    BOOST_CHECK(s2[1] == 10.5);
    BOOST_CHECK(s2[2] == "hello");
}

BOOST_AUTO_TEST_CASE (test_maps) {
    var d1 = make_map();
    BOOST_CHECK_EQUAL(d1.count(), 0);
    BOOST_CHECK(d1.is_map());
    BOOST_CHECK(d1.is_collection());

    var d2 = make_map(1)("hello")(10.5);
    BOOST_CHECK_EQUAL(d2.count(), 3);
    BOOST_CHECK(d2.is_map());
    BOOST_CHECK(d2.is_collection());
    BOOST_CHECK(d2[1] == dynamic::none);
    BOOST_CHECK(d2["hello"] == dynamic::none);
    BOOST_CHECK(d2[10.5] == dynamic::none);

    var d3 = make_map(1, "xxx")("hello", "world")(10.5, 3.14);
    BOOST_CHECK_EQUAL(d3.count(), 3);
    BOOST_CHECK(d3.is_map());
    BOOST_CHECK(d3.is_collection());
    BOOST_CHECK(d3[1] == "xxx");
    BOOST_CHECK(d3["hello"] == "world");
    BOOST_CHECK(d3[10.5] == 3.14);

    var d4 = make_map();
    d4["hello"] = "world";
    BOOST_CHECK(d4["hello"] == "world");
    BOOST_CHECK(d4["test"] == dynamic::none);
    BOOST_CHECK_EQUAL(d4.count(), 2);
}

BOOST_AUTO_TEST_CASE (test_complex) {
    var d = make_map
        ("vector", make_vector(1)(1.5)("hello"))
        ("list", make_list(2)(3.5)("world"))
        ("set", make_set(3)("xyzzy")(4.5))
        ("map", make_map("a", 4)("b", 5.5)("c", "plover"));

    BOOST_CHECK(d.count() == 4);
    BOOST_CHECK(d.is_map());
    BOOST_CHECK(d["vector"].count() == 3);
    BOOST_CHECK(d["vector"].is_vector());
    BOOST_CHECK(d["vector"][0] == 1);
    BOOST_CHECK(d["vector"][1] == 1.5);
    BOOST_CHECK(d["vector"][2] == "hello");

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

    BOOST_CHECK(d["map"].count() == 3);
    BOOST_CHECK(d["map"].is_map());
    BOOST_CHECK(d["map"]["a"] == 4);
    BOOST_CHECK(d["map"]["b"] == 5.5);
    BOOST_CHECK(d["map"]["c"] == "plover");

    stringstream ss;
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'list':(2 3.5 'world') 'map':<'a':4 'b':5.5 'c':'plover'> 'set':{3 4.5 'xyzzy'} 'vector':[1 1.5 'hello']>");

    d["list"][1] = "hello";
    ss.str(string());
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'list':(2 'hello' 'world') 'map':<'a':4 'b':5.5 'c':'plover'> 'set':{3 4.5 'xyzzy'} 'vector':[1 1.5 'hello']>");

    d["vector"][0] = d["vector"][1] = d["vector"][2] = dynamic::none;
    ss.str(string());
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'list':(2 'hello' 'world') 'map':<'a':4 'b':5.5 'c':'plover'> 'set':{3 4.5 'xyzzy'} 'vector':[none none none]>");

    d["map"]["b"] = make_vector(1)(2.1)(3)(make_list(1)("b"));
    ss.str(string());
    ss << d;
    BOOST_CHECK_EQUAL(ss.str(), "<'list':(2 'hello' 'world') 'map':<'a':4 'b':[1 2.1 3 (1 'b')] 'c':'plover'> 'set':{3 4.5 'xyzzy'} 'vector':[none none none]>");
}

