project( dynamic CXX )

cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

find_package( Boost 1.48 REQUIRED )

link_directories ( ${Boost_LIBRARY_DIRS} )

include_directories ( ${Boost_INCLUDE_DIRS} )

add_library( dynamic STATIC
	assign.cpp
	ctor.cpp
	dynamic.cpp
	iterator.cpp
	relational.cpp
	types.cpp
)
