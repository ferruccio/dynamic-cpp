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

struct preinc_visitor : public boost::static_visitor<iterator> {
	iterator operator() (list_t::iterator& i) const { return ++i; }
	iterator operator() (array_t::iterator& i) const { return ++i; }
	iterator operator() (set_t::iterator& i) const { return ++i; }
	iterator operator() (dict_t::iterator& i) const { return ++i; }
};

struct postinc_visitor : public boost::static_visitor<iterator> {
	iterator operator() (list_t::iterator& i) const { return i++; }
	iterator operator() (array_t::iterator& i) const { return i++; }
	iterator operator() (set_t::iterator& i) const { return i++; }
	iterator operator() (dict_t::iterator& i) const { return i++; }
};

struct predec_visitor : public boost::static_visitor<iterator> {
	iterator operator() (list_t::iterator& i) const { return --i; }
	iterator operator() (array_t::iterator& i) const { return --i; }
	iterator operator() (set_t::iterator& i) const { return --i; }
	iterator operator() (dict_t::iterator& i) const { return --i; }
};

struct postdec_visitor : public boost::static_visitor<iterator> {
	iterator operator() (list_t::iterator& i) const { return i--; }
	iterator operator() (array_t::iterator& i) const { return i--; }
	iterator operator() (set_t::iterator& i) const { return i--; }
	iterator operator() (dict_t::iterator& i) const { return i--; }
};

struct deref_visitor : public boost::static_visitor<var&> {
	var& operator() (list_t::iterator i) const { return *i; }
	var& operator() (array_t::iterator i) const { return *i; }
	var& operator() (set_t::iterator i) const { return const_cast<var&>(*i); }
	var& operator() (dict_t::iterator i) const { return const_cast<var&>(i->first); }
};

struct rpreinc_visitor : public boost::static_visitor<reverse_iterator> {
	reverse_iterator operator() (list_t::reverse_iterator& i) const { return ++i; }
	reverse_iterator operator() (array_t::reverse_iterator& i) const { return ++i; }
	reverse_iterator operator() (set_t::reverse_iterator& i) const { return ++i; }
	reverse_iterator operator() (dict_t::reverse_iterator& i) const { return ++i; }
};

struct rpostinc_visitor : public boost::static_visitor<reverse_iterator> {
	reverse_iterator operator() (list_t::reverse_iterator& i) const { return i++; }
	reverse_iterator operator() (array_t::reverse_iterator& i) const { return i++; }
	reverse_iterator operator() (set_t::reverse_iterator& i) const { return i++; }
	reverse_iterator operator() (dict_t::reverse_iterator& i) const { return i++; }
};

struct rpredec_visitor : public boost::static_visitor<reverse_iterator> {
	reverse_iterator operator() (list_t::reverse_iterator& i) const { return --i; }
	reverse_iterator operator() (array_t::reverse_iterator& i) const { return --i; }
	reverse_iterator operator() (set_t::reverse_iterator& i) const { return --i; }
	reverse_iterator operator() (dict_t::reverse_iterator& i) const { return --i; }
};

struct rpostdec_visitor : public boost::static_visitor<reverse_iterator> {
	reverse_iterator operator() (list_t::reverse_iterator& i) const { return i--; }
	reverse_iterator operator() (array_t::reverse_iterator& i) const { return i--; }
	reverse_iterator operator() (set_t::reverse_iterator& i) const { return i--; }
	reverse_iterator operator() (dict_t::reverse_iterator& i) const { return i--; }
};

