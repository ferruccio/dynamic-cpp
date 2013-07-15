###############################################################################
#
#    Copyright (C) 2009, Ferruccio Barletta (ferruccio.barletta@gmail.com)
#
#    Permission is hereby granted, free of charge, to any person
#    obtaining a copy of this software and associated documentation
#    files (the "Software"), to deal in the Software without
#    restriction, including without limitation the rights to use,
#    copy, modify, merge, publish, distribute, sublicense, and/or sell
#    copies of the Software, and to permit persons to whom the
#    Software is furnished to do so, subject to the following
#    conditions:
#
#    The above copyright notice and this permission notice shall be
#    included in all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
#    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
#    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
#    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
#    OTHER DEALINGS IN THE SOFTWARE.
#
###############################################################################

cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

project( dynamic CXX )

###############################################################################
# Boost package
###############################################################################

set ( Boost_USE_STATIC_LIBS ON )
set ( Boost_USE_MULTITHREADED ON )
find_package( Boost 1.48 COMPONENTS unit_test_framework REQUIRED )
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )

###############################################################################
# Doxygen package
###############################################################################

find_package(Doxygen)
if (${DOXYGEN_FOUND} STREQUAL "YES") # Cannot check result directly due to CMP0012
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
  )
endif()

###############################################################################
# Dynamic package
###############################################################################

include_directories(include)
link_directories(${CMAKE_CURRENT_BINARY_DIR/lib})
set(LIBRARY_OUTPUT_PATH lib)
add_library( dynamic STATIC
  src/assign.cpp
  src/ctor.cpp
  src/dynamic.cpp
  src/iterator.cpp
  src/relational.cpp
  src/types.cpp
)

###############################################################################
# Dynamic test cases
###############################################################################

add_executable(tests
  tests/tests.cpp
  tests/test_collections.cpp
  tests/test_relational_eq.cpp
  tests/test_relational_ne.cpp
)

set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
set_target_properties(tests PROPERTIES LIBRARY_OUTPUT_DIRECTORY lib)
target_link_libraries(tests dynamic ${Boost_LIBRARIES})
