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

struct rel_eq_visitor : public boost::static_visitor<bool> {
	rel_eq_visitor(const var& rhs) : _rhs(rhs) {}
	
	bool operator () (null_t) const { return !_rhs.is_null(); }
	bool operator () (int_t n) const { return !_rhs.is_int() || n != int(_rhs); }
	bool operator () (double_t n) const { return !_rhs.is_double() || n != double(_rhs); }
	bool operator () (string_t s) const { return !_rhs.is_string() || *s.ps != string(_rhs); }
	bool operator () (list_ptr) const { return false; }
	bool operator () (array_ptr) const { return false; }
	bool operator () (set_ptr) const { return false; }
	bool operator () (dict_ptr) const { return false; }
	
	const var& _rhs;
};

struct rel_lt_visitor : public boost::static_visitor<bool> {
	rel_lt_visitor(const var& rhs) : _rhs(rhs) {}
	
	bool operator () (null_t) const { throw exception("invalid < comparison to $"); }
	bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid < comparison to int"); return n < int(_rhs); }
	bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid < comparison to double"); return n < double(_rhs); }
	bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid < comparison to string"); return *s.ps < string(_rhs); }
	bool operator () (list_ptr) const { throw exception("invalid < comparison to list"); }
	bool operator () (array_ptr) const { throw exception("invalid < comparison to array"); }
	bool operator () (set_ptr) const { throw exception("invalid < comparison to set"); }
	bool operator () (dict_ptr) const { throw exception("invalid < comparison to dict"); }
	
	const var& _rhs;
};

struct rel_le_visitor : public boost::static_visitor<bool> {
	rel_le_visitor(const var& rhs) : _rhs(rhs) {}
	
	bool operator () (null_t) const { throw exception("invalid <= comparison to $"); }
	bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid <= comparison to int"); return n <= int(_rhs); }
	bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid <= comparison to double"); return n <= double(_rhs); }
	bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid <= comparison to string"); return *s.ps <= string(_rhs); }
	bool operator () (list_ptr) const { throw exception("invalid <= comparison to list"); }
	bool operator () (array_ptr) const { throw exception("invalid <= comparison to array"); }
	bool operator () (set_ptr) const { throw exception("invalid <= comparison to set"); }
	bool operator () (dict_ptr) const { throw exception("invalid <= comparison to dict"); }
	
	const var& _rhs;
};

struct rel_gt_visitor : public boost::static_visitor<bool> {
	rel_gt_visitor(const var& rhs) : _rhs(rhs) {}
	
	bool operator () (null_t) const { throw exception("invalid > comparison to $"); }
	bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid > comparison to int"); return n > int(_rhs); }
	bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid > comparison to double"); return n > double(_rhs); }
	bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid > comparison to string"); return *s.ps > string(_rhs); }
	bool operator () (list_ptr) const { throw exception("invalid > comparison to list"); }
	bool operator () (array_ptr) const { throw exception("invalid > comparison to array"); }
	bool operator () (set_ptr) const { throw exception("invalid > comparison to set"); }
	bool operator () (dict_ptr) const { throw exception("invalid > comparison to dict"); }
	
	const var& _rhs;
};

struct rel_ge_visitor : public boost::static_visitor<bool> {
	rel_ge_visitor(const var& rhs) : _rhs(rhs) {}
	
	bool operator () (null_t) const { throw exception("invalid >= comparison to $"); }
	bool operator () (int_t n) const { if (!_rhs.is_int()) throw exception("invalid >= comparison to int"); return n >= int(_rhs); }
	bool operator () (double_t n) const { if (!_rhs.is_double()) throw exception("invalid >= comparison to double"); return n >= double(_rhs); }
	bool operator () (string_t s) const { if (!_rhs.is_string()) throw exception("invalid >= comparison to string"); return *s.ps >= string(_rhs); }
	bool operator () (list_ptr) const { throw exception("invalid >= comparison to list"); }
	bool operator () (array_ptr) const { throw exception("invalid >= comparison to array"); }
	bool operator () (set_ptr) const { throw exception("invalid >= comparison to set"); }
	bool operator () (dict_ptr) const { throw exception("invalid >= comparison to dict"); }
	
	const var& _rhs;
};

