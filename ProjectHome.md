Dynamic C++ adds dynamic typing capabilities to C++ through a var class. Var types may contain integers, doubles, strings or they may be a null type They can also be containers: vectors, lists, sets and maps.

example:

```
#include <iostream>
#include <dynamic/dynamic.h>

using namespace std;
using namespace dynamic;

void f()
{

    var a = none;  // a is initially null
    cout << a << endl;

    a = 1;      // a is an now integer
    cout << a << endl;

    a = 2.5;    // a is now a double
    cout << a << endl;

    a = "hello, world!"; // a is now a string
    cout << a << endl;

    a = L"hello, wide world!"; // a is now a wide string
    cout << a << endl;

    a = make_list(1)(2)(3); // a is now a list of integers
    cout << a << endl;

    a = make_list(1)(2)(3.5)("hello")(make_vector(1)(2.0)("three"));
    // a is now a list containing 2 ints, a double, a string and an vector of three items

    cout << "c: " << a << endl;
    // some iterator support
    for (var::iterator i = a.begin(); i != a.end(); ++i)
        cout << *i << endl;

    a = make_map("name", "fred")("age", 35)("city", "bedrock")(12, make_vector(1)(2)(3)); // keys and values can be any type
    // a is now a map
    cout << a << endl;

}
```