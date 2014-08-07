#ifndef DYNAMIC_EXCEPTION_HPP
#define DYNAMIC_EXCEPTION_HPP

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

#include <exception>

namespace dynamic
{

///
/// exception class thrown by Dynamic C++
///
class exception : public std::exception
{
public :
    ///
    /// construct exception with message
    ///
    /// @param message The exception message.
    ///
    /// The message pointer *must* remain valid during the entire lifetime of the exception.
    ///
    exception(const char* message) : std::exception() { _message = message; }
    ~exception() throw() {}

    ///
    /// @return exception message
    ///
    const char* what() const throw() { return _message; }

private :
    const char* _message;
};

} // namespace dynamic

#endif // DYNAMIC_EXCEPTION_HPP
