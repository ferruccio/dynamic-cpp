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
        struct begin_visitor : public boost::static_visitor<iterator> {
            iterator operator () (null_t) const { throw exception("invalid .begin() operation on $"); }
            iterator operator () (int_t) const { throw exception("invalid .begin() operation on int"); }
            iterator operator () (double_t) const { throw exception("invalid .begin() operation on double"); }
            iterator operator () (string_t s) const { throw exception("invalid .begin() operation on string"); }
            iterator operator () (list_ptr l) const { return l->begin(); }
            iterator operator () (array_ptr a) const { return a->begin(); }
            iterator operator () (set_ptr s) const { return s->begin(); }
            iterator operator () (dict_ptr d) const { return d->begin(); }
        };

        return boost::apply_visitor(begin_visitor(), _var);
    }

    var::iterator var::end() {
        struct end_visitor : public boost::static_visitor<iterator> {
            iterator operator () (null_t) const { throw exception("invalid .end() operation on $"); }
            iterator operator () (int_t) const { throw exception("invalid .end() operation on int"); }
            iterator operator () (double_t) const { throw exception("invalid .end() operation on double"); }
            iterator operator () (string_t s) const { throw exception("invalid .end() operation on string"); }
            iterator operator () (list_ptr l) const { return l->end(); }
            iterator operator () (array_ptr a) const { return a->end(); }
            iterator operator () (set_ptr s) const { return s->end(); }
            iterator operator () (dict_ptr d) const { return d->end(); }
        };

        return boost::apply_visitor(end_visitor(), _var);
    }

    var::iterator var::iterator::operator++() {
        struct preinc_visitor : public boost::static_visitor<iterator> {
            iterator operator() (list_t::iterator& i) const { return ++i; }
            iterator operator() (array_t::iterator& i) const { return ++i; }
            iterator operator() (set_t::iterator& i) const { return ++i; }
            iterator operator() (dict_t::iterator& i) const { return ++i; }
        };

        return boost::apply_visitor(preinc_visitor(), _iter);
    }

    var::iterator var::iterator::operator++(int) {
        struct postinc_visitor : public boost::static_visitor<iterator> {
            iterator operator() (list_t::iterator& i) const { return i++; }
            iterator operator() (array_t::iterator& i) const { return i++; }
            iterator operator() (set_t::iterator& i) const { return i++; }
            iterator operator() (dict_t::iterator& i) const { return i++; }
        };

        return boost::apply_visitor(postinc_visitor(), _iter);
    }

    var::iterator var::iterator::operator--() {
        struct predec_visitor : public boost::static_visitor<iterator> {
            iterator operator() (list_t::iterator& i) const { return --i; }
            iterator operator() (array_t::iterator& i) const { return --i; }
            iterator operator() (set_t::iterator& i) const { return --i; }
            iterator operator() (dict_t::iterator& i) const { return --i; }
        };

        return boost::apply_visitor(predec_visitor(), _iter);
    }

    var::iterator var::iterator::operator--(int) {
        struct postdec_visitor : public boost::static_visitor<iterator> {
            iterator operator() (list_t::iterator& i) const { return i--; }
            iterator operator() (array_t::iterator& i) const { return i--; }
            iterator operator() (set_t::iterator& i) const { return i--; }
            iterator operator() (dict_t::iterator& i) const { return i--; }
        };

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
        struct deref_visitor : public boost::static_visitor<var&> {
            var& operator() (list_t::iterator i) const { return *i; }
            var& operator() (array_t::iterator i) const { return *i; }
            var& operator() (set_t::iterator i) const { return const_cast<var&>(*i); }
            var& operator() (dict_t::iterator i) const { return const_cast<var&>(i->first); }
        };

        return boost::apply_visitor(deref_visitor(), _iter);
    }

    var::reverse_iterator var::rbegin() {
        struct rbegin_visitor : public boost::static_visitor<reverse_iterator> {
            reverse_iterator operator () (null_t) const { throw exception("invalid .rbegin() operation on $"); }
            reverse_iterator operator () (int_t) const { throw exception("invalid .rbegin() operation on int"); }
            reverse_iterator operator () (double_t) const { throw exception("invalid .rbegin() operation on double"); }
            reverse_iterator operator () (string_t s) const { throw exception("invalid .rbegin() operation on string"); }
            reverse_iterator operator () (list_ptr l) const { return l->rbegin(); }
            reverse_iterator operator () (array_ptr a) const { return a->rbegin(); }
            reverse_iterator operator () (set_ptr s) const { return s->rbegin(); }
            reverse_iterator operator () (dict_ptr d) const { return d->rbegin(); }
        };

        return boost::apply_visitor(rbegin_visitor(), _var);
    }

    var::reverse_iterator var::rend() {
        struct rend_visitor : public boost::static_visitor<reverse_iterator> {
            reverse_iterator operator () (null_t) const { throw exception("invalid .rend() operation on $"); }
            reverse_iterator operator () (int_t) const { throw exception("invalid .rend() operation on int"); }
            reverse_iterator operator () (double_t) const { throw exception("invalid .rend() operation on double"); }
            reverse_iterator operator () (string_t s) const { throw exception("invalid .rend() operation on string"); }
            reverse_iterator operator () (list_ptr l) const { return l->rend(); }
            reverse_iterator operator () (array_ptr a) const { return a->rend(); }
            reverse_iterator operator () (set_ptr s) const { return s->rend(); }
            reverse_iterator operator () (dict_ptr d) const { return d->rend(); }
        };

        return boost::apply_visitor(rend_visitor(), _var);
    }

    var::reverse_iterator var::reverse_iterator::operator++() {
        struct preinc_visitor : public boost::static_visitor<reverse_iterator> {
            reverse_iterator operator() (list_t::reverse_iterator& i) const { return ++i; }
            reverse_iterator operator() (array_t::reverse_iterator& i) const { return ++i; }
            reverse_iterator operator() (set_t::reverse_iterator& i) const { return ++i; }
            reverse_iterator operator() (dict_t::reverse_iterator& i) const { return ++i; }
        };

        return boost::apply_visitor(preinc_visitor(), _iter);
    }

    var::reverse_iterator var::reverse_iterator::operator++(int) {
        struct postinc_visitor : public boost::static_visitor<reverse_iterator> {
            reverse_iterator operator() (list_t::reverse_iterator& i) const { return i++; }
            reverse_iterator operator() (array_t::reverse_iterator& i) const { return i++; }
            reverse_iterator operator() (set_t::reverse_iterator& i) const { return i++; }
            reverse_iterator operator() (dict_t::reverse_iterator& i) const { return i++; }
        };

        return boost::apply_visitor(postinc_visitor(), _iter);
    }

    var::reverse_iterator var::reverse_iterator::operator--() {
        struct predec_visitor : public boost::static_visitor<reverse_iterator> {
            reverse_iterator operator() (list_t::reverse_iterator& i) const { return --i; }
            reverse_iterator operator() (array_t::reverse_iterator& i) const { return --i; }
            reverse_iterator operator() (set_t::reverse_iterator& i) const { return --i; }
            reverse_iterator operator() (dict_t::reverse_iterator& i) const { return --i; }
        };

        return boost::apply_visitor(predec_visitor(), _iter);
    }

    var::reverse_iterator var::reverse_iterator::operator--(int) {
        struct postdec_visitor : public boost::static_visitor<reverse_iterator> {
            reverse_iterator operator() (list_t::reverse_iterator& i) const { return i--; }
            reverse_iterator operator() (array_t::reverse_iterator& i) const { return i--; }
            reverse_iterator operator() (set_t::reverse_iterator& i) const { return i--; }
            reverse_iterator operator() (dict_t::reverse_iterator& i) const { return i--; }
        };

        return boost::apply_visitor(postdec_visitor(), _iter);
    }

    bool var::reverse_iterator::operator==(var::reverse_iterator rhs) {
        return boost::apply_visitor(are_strict_equals(), _iter, rhs._iter);
    }

}
