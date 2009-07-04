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

namespace dynamic {
	
    var::iterator var::begin() {
        return boost::apply_visitor(begin_visitor(), _var);
    }

    var::iterator var::end() {
        return boost::apply_visitor(end_visitor(), _var);
    }

    var::iterator var::iterator::operator++() {
        return boost::apply_visitor(preinc_visitor(), _iter);
    }

    var::iterator var::iterator::operator++(int) {
        return boost::apply_visitor(postinc_visitor(), _iter);
    }

    var::iterator var::iterator::operator--() {
        return boost::apply_visitor(predec_visitor(), _iter);
    }

    var::iterator var::iterator::operator--(int) {
        return boost::apply_visitor(postdec_visitor(), _iter);
    }

    struct are_strict_equals : public boost::static_visitor<bool> {
        template <typename T, typename U>
        bool operator()(const T&, const U&) const { return false; }

        template <typename T>
        bool operator()(const T& lhs, const T& rhs) const { return lhs == rhs; }
    };

    bool var::iterator::operator==(var::iterator rhs) {
        return boost::apply_visitor(are_strict_equals(), _iter, rhs._iter);
    }

    var& var::iterator::operator*() {
        return boost::apply_visitor(deref_visitor(), _iter);
    }

    var::reverse_iterator var::rbegin() {
        return boost::apply_visitor(rbegin_visitor(), _var);
    }

    var::reverse_iterator var::rend() {
        return boost::apply_visitor(rend_visitor(), _var);
    }

    var::reverse_iterator var::reverse_iterator::operator++() {
        return boost::apply_visitor(rpreinc_visitor(), _iter);
    }

    var::reverse_iterator var::reverse_iterator::operator++(int) {
        return boost::apply_visitor(rpostinc_visitor(), _iter);
    }

    var::reverse_iterator var::reverse_iterator::operator--() {
        return boost::apply_visitor(rpredec_visitor(), _iter);
    }

    var::reverse_iterator var::reverse_iterator::operator--(int) {
        return boost::apply_visitor(rpostdec_visitor(), _iter);
    }

    bool var::reverse_iterator::operator==(var::reverse_iterator rhs) {
        return boost::apply_visitor(are_strict_equals(), _iter, rhs._iter);
    }

}
