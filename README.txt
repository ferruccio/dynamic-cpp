Building Dynamic C++

Requirements:

	CMake 2.6
	Boost 1.35

OSX/Linux:

At the root directory run ./rebuild to create libdynamic.a.
You can also run ../rebuild in the tests directory to build the unit tests.

Note: On Snow Leopard the tests run successfully to completion but the test program terminates abnormally.

Windows:

In a Visual Studio Command Prompt Window:
Run rebuild.bat in the root directory to create dynamic.lib.
Run ..\rebuild.bat in the tests directory.
The rebuild script will also create a Visual Studio solution for you.

Note: You may need to set BOOST_INCLUDEDIR and BOOST_LIBRARYDIR environment variables in order for CMake to find Boost.

Tested with the following configurations:

OSX Leopard, Boost 1.38.0
OSX Snow Leopard, Boost 1.40.0
Windows XP, Boost 1.35.0, Boost 1.39.0, VS2008
Windows 7 x64, Boost 1.48.0, VS2010
Ubuntu Linux 9.04, Boost 1.37.0

Contact: ferruccio.barletta@gmail.com
