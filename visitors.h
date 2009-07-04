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

struct lt_visitor : public boost::static_visitor<bool> {
	bool operator () (null_t, null_t) const { return false; }
	bool operator () (int_t a, int_t b) const { return a < b; }
	bool operator () (double_t a, double_t b) const { return a < b; }
	bool operator () (string_t a, string_t b) const { return a.ps < b.ps; }
	bool operator () (list_ptr, list_ptr) const { return false; }
	bool operator () (array_ptr, array_ptr) const { return false; }
	bool operator () (set_ptr, set_ptr) const { return false; }
	bool operator () (dict_ptr, dict_ptr) const { return false; }
};

struct append_visitor : public boost::static_visitor<void> {
	append_visitor(const var& v) : _v(v) {}
	
	void operator () (null_t) const { throw exception("invalid () operation on $"); }
	void operator () (int_t) const { throw exception("invalid () operation on int"); }
	void operator () (double_t) const { throw exception("invalid () operation on double"); }
	void operator () (string_t) const { throw exception("invalid () operation on string"); }
	void operator () (list_ptr l) const { l->push_back(_v); }
	void operator () (array_ptr a) const { a->push_back(_v); }
	void operator () (set_ptr s) const { s->insert(_v); }
	void operator () (dict_ptr d) const { d->insert(make_pair<var,var>(_v, $)); }
	
	const var& _v;
};

struct append2_visitor : public boost::static_visitor<void> {
	append2_visitor(const var& k, const var& v) : _k(k), _v(v) {}
	
	void operator () (null_t) const { throw exception("invalid (,) operation on $"); }
	void operator () (int_t) const { throw exception("invalid (,) operation on int"); }
	void operator () (double_t) const { throw exception("invalid (,) operation on double"); }
	void operator () (string_t) const { throw exception("invalid (,) operation on string"); }
	void operator () (list_ptr) const { throw exception("invalid (,) operation on list"); }
	void operator () (array_ptr) const { throw exception("invalid (,) operation on array"); }
	void operator () (set_ptr) const { throw exception("invalid (,) operation on set"); }
	void operator () (dict_ptr d) const { d->insert(make_pair<var,var>(_k, _v)); }
	
	const var& _k;
	const var& _v;
};

struct count_visitor : public boost::static_visitor<unsigned int> {
	unsigned int operator () (null_t) const { throw exception("invalid .count() operation on $"); }
	unsigned int operator () (int_t) const { throw exception("invalid .count() operation on int"); }
	unsigned int operator () (double_t) const { throw exception("invalid .count() operation on double"); }
	unsigned int operator () (string_t s) const { return s.ps->length(); }
	unsigned int operator () (list_ptr l) const { return l->size(); }
	unsigned int operator () (array_ptr a) const { return a->size(); }
	unsigned int operator () (set_ptr s) const { return s->size(); }
	unsigned int operator () (dict_ptr d) const { return d->size(); }
};

struct index_visitor : public boost::static_visitor<var&> {
	index_visitor(int n) : _n(n) {}
	
	var& operator () (null_t) const { throw exception("cannot apply [] to $"); }
	var& operator () (int_t) const { throw exception("cannot apply [] to int"); }
	var& operator () (double_t) const { throw exception("cannot apply [] to double"); }
	var& operator () (string_t s) const { throw exception("cannot apply [] to string"); }
	
	var& operator () (list_ptr l) const {
		if (_n < 0 || _n >= int(l->size())) throw exception("[] out of range in list");
		list_t::iterator li = l->begin();
		advance(li, _n);
		return *li;
	}
	
	var& operator () (array_ptr a) const  {
		if (_n < 0 || _n >= int(a->size())) throw exception("[] out of range in array");
		return (*a)[_n];
	}
	
	var& operator () (set_ptr s) const {
		if (_n < 0 || _n >= int(s->size())) throw exception("[] out of range in set");
		set_t::iterator si = s->begin();
		advance(si, _n);
		return const_cast<var&>(*si);
	}
	
	var& operator () (dict_ptr d) const {
		var key(_n);
		dict_t::iterator di = d->find(key);
		if (di == d->end()) throw exception("[] not found in dict");
		return di->second;
	}
	
	int _n;
};

struct index2_visitor : public boost::static_visitor<var&> {
	index2_visitor(var& v) : _v(v) {}
	
	var& operator () (null_t) const { throw exception("cannot apply [] to $"); }
	var& operator () (int_t) const { throw exception("cannot apply [] to int"); }
	var& operator () (double_t) const { throw exception("cannot apply [] to double"); }
	var& operator () (string_t s) const { throw exception("cannot apply [] to string"); }
	var& operator () (list_ptr l) const { throw exception("list[] requires int"); }
	var& operator () (array_ptr a) const { throw exception("array[] requires int"); }
	var& operator () (set_ptr s) const { throw exception("set[] requires int"); }
	
	var& operator () (dict_ptr d) const {
		var key(_v);
		dict_t::iterator di = d->find(key);
		if (di != d->end()) return di->second;
		(*d)[key] = $;
		return (*d)[key];
	}
	
	var& _v;
};

struct output_visitor : public boost::static_visitor<ostream&> {
	output_visitor(ostream& os, var& v) : _os(os), _v(v), boost::static_visitor<ostream&>() {}
	
	ostream& operator () (null_t) { _os << "$"; return _os; }
	ostream& operator () (int_t n) { _os << n; return _os; }
	ostream& operator () (double_t n) { _os << n; return _os; }
	ostream& operator () (string_t s) { return _v._write_string(_os); }
	ostream& operator () (list_ptr) { return _v._write_list(_os); }
	ostream& operator () (array_ptr) { return _v._write_array(_os); }
	ostream& operator () (set_ptr) { return _v._write_set(_os); }
	ostream& operator () (dict_ptr) { return _v._write_dict(_os); }
	
	ostream& _os;
	var& _v;
};

struct eq_visitor : public boost::static_visitor<bool> {
	eq_visitor(const var& rhs) : _rhs(rhs) {}
	
	bool operator () (null_t) const { return _rhs.is_null(); }
	bool operator () (int_t n) const { return _rhs.is_int() && n == int(_rhs); }
	bool operator () (double_t n) const { return _rhs.is_double() && n == double(_rhs); }
	bool operator () (string_t s) const { return _rhs.is_string() && *s.ps == string(_rhs); }
	bool operator () (list_ptr) const { return false; }
	bool operator () (array_ptr) const { return false; }
	bool operator () (set_ptr) const { return false; }
	bool operator () (dict_ptr) const { return false; }
	
	const var& _rhs;
};


struct type_visitor : public boost::static_visitor<string> {
	string operator () (null_t) const { return "null"; }
	string operator () (int_t) const { return "int"; }
	string operator () (double_t) const { return "double"; }
	string operator () (string_t s) const { return "string"; }
	string operator () (list_ptr) const { return "list"; }
	string operator () (array_ptr) const { return "array"; }
	string operator () (set_ptr) const { return "set"; }
	string operator () (dict_ptr) const {return "dict"; }
};

struct type2_visitor : public boost::static_visitor<type_t> {
	type_t operator () (null_t) const { return type_null; }
	type_t operator () (int_t) const { return type_int; }
	type_t operator () (double_t) const { return type_double; }
	type_t operator () (string_t s) const { return type_string; }
	type_t operator () (list_ptr) const { return type_list; }
	type_t operator () (array_ptr) const { return type_array; }
	type_t operator () (set_ptr) const { return type_set; }
	type_t operator () (dict_ptr) const { return type_dict; }
};
