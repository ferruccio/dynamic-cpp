project( dynamic CXX )

cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

find_package( Boost 1.35 REQUIRED )

link_directories ( ${Boost_LIBRARY_DIRS} )

include_directories ( ${Boost_INCLUDE_DIRS} )

add_library( dynamic STATIC
	array.cpp
	assign.cpp
	ctor.cpp
	dict.cpp
	dynamic.cpp
	iterator.cpp
	list.cpp
	relational.cpp
	set.cpp
	types.cpp
)
