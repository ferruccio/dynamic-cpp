project( dynamic-unit-tests CXX )

cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

set ( Boost_USE_STATIC_LIBS ON )
set ( Boost_USE_MULTITHREADED ON )
find_package( Boost 1.35 COMPONENTS unit_test_framework REQUIRED )

link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )
include_directories ( .. )

add_executable( tests
	tests.cpp
	test_collections.cpp
	test_relational_eq.cpp
	test_relational_ne.cpp
	
	../array.cpp
	../assign.cpp
	../ctor.cpp
	../dict.cpp
	../dynamic.cpp
	../iterator.cpp
	../list.cpp
	../relational.cpp
	../set.cpp
	../types.cpp
)

target_link_libraries ( tests ${Boost_LIBRARIES} )