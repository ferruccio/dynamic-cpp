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

#include <boost/test/unit_test.hpp>

#include "dynamic.h"

using namespace dynamic;

static const int _via = 10, _vib = 50;
static const double _vda = 10.0, _vdb  = 50.0;
static const char *_vca = "hello", *_vcb = "world";
static const string _vsa = "hello", _vsb = "world";

struct eq_fixture {
    eq_fixture()
        :   vn(),
            via(_via), vib(_vib),
            vda(_vda), vdb(_vdb),
            vca(_vca), vcb(_vcb),
            vsa(_vsa), vsb(_vsb)
    {}


    var vn;
    var via, vib;
    var vda, vdb;
    var vca, vcb;
    var vsa, vsb;
};

BOOST_FIXTURE_TEST_CASE (relational_eq_const, eq_fixture) {
    BOOST_CHECK($ == $);

    BOOST_CHECK(vn == $);
    BOOST_CHECK(via == _via);
    BOOST_CHECK(vib == _vib);
    BOOST_CHECK(vda == _vda);
    BOOST_CHECK(vdb == _vdb);
    BOOST_CHECK(vca == _vca);
    BOOST_CHECK(vca == _vsa);
    BOOST_CHECK(vcb == _vcb);
    BOOST_CHECK(vcb == _vsb);
    BOOST_CHECK(vsa == _vsa);
    BOOST_CHECK(vsa == _vca);
    BOOST_CHECK(vsb == _vsb);
    BOOST_CHECK(vsb == _vcb);
}

BOOST_FIXTURE_TEST_CASE (relational_eq_var, eq_fixture) {
    BOOST_CHECK(vn == vn);
    BOOST_CHECK(via == via);
    BOOST_CHECK(vib == vib);
    BOOST_CHECK(vda == vda);
    BOOST_CHECK(vca == vca);
    BOOST_CHECK(vca == vsa);
    BOOST_CHECK(vcb == vcb);
    BOOST_CHECK(vcb == vsb);
    BOOST_CHECK(vsa == vsa);
    BOOST_CHECK(vsa == vca);
    BOOST_CHECK(vsb == vsb);
    BOOST_CHECK(vsb == vcb);
}

BOOST_FIXTURE_TEST_CASE (relational_eq_null, eq_fixture) {
    BOOST_CHECK(!(vn == via));
    BOOST_CHECK(!(vn == vda));
    BOOST_CHECK(!(vn == vca));
    BOOST_CHECK(!(vn == vsa));

    BOOST_CHECK(!(vn == _via));
    BOOST_CHECK(!(vn == _vda));
    BOOST_CHECK(!(vn == _vca));
    BOOST_CHECK(!(vn == _vsa));
}

BOOST_FIXTURE_TEST_CASE (relational_eq_int, eq_fixture) {
    BOOST_CHECK(!(via == $));
    BOOST_CHECK(!(via == _vda));
    BOOST_CHECK(!(via == _vca));
    BOOST_CHECK(!(via == _vsa));

    BOOST_CHECK(!(via == vn));
    BOOST_CHECK(!(via == vda));
    BOOST_CHECK(!(via == vca));
    BOOST_CHECK(!(via == vsa));

    BOOST_CHECK(!(via == vib));
    BOOST_CHECK(!(via == _vib));
}

BOOST_FIXTURE_TEST_CASE (relational_eq_double, eq_fixture) {
    BOOST_CHECK(!(vda == $));
    BOOST_CHECK(!(vda == _via));
    BOOST_CHECK(!(vda == _vca));
    BOOST_CHECK(!(vda == _vsa));

    BOOST_CHECK(!(vda == vn));
    BOOST_CHECK(!(vda == via));
    BOOST_CHECK(!(vda == vca));
    BOOST_CHECK(!(vda == vsa));

    BOOST_CHECK(!(vda == vdb));
    BOOST_CHECK(!(vda == _vdb));
}

BOOST_FIXTURE_TEST_CASE (relational_eq_string, eq_fixture) {
    BOOST_CHECK(!(vsa == $));
    BOOST_CHECK(!(vsa == _via));
    BOOST_CHECK(!(vsa == _vda));

    BOOST_CHECK(!(vsa == vn));
    BOOST_CHECK(!(vsa == via));
    BOOST_CHECK(!(vsa == vda));

    BOOST_CHECK(!(vsa == vsb));
    BOOST_CHECK(!(vsa == _vsb));
    BOOST_CHECK(!(vsa == vcb));
    BOOST_CHECK(!(vsa == _vcb));
}

BOOST_FIXTURE_TEST_CASE (relational_eq_string_charp, eq_fixture) {
    BOOST_CHECK(!(vca == $));
    BOOST_CHECK(!(vca == _via));
    BOOST_CHECK(!(vca == _vda));

    BOOST_CHECK(!(vca == vn));
    BOOST_CHECK(!(vca == via));
    BOOST_CHECK(!(vca == vda));

    BOOST_CHECK(!(vca == vcb));
    BOOST_CHECK(!(vca == _vcb));
    BOOST_CHECK(!(vca == vsb));
    BOOST_CHECK(!(vca == _vsb));
}