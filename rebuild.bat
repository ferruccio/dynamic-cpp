@echo off

setlocal

if "%BOOST_INCLUDEDIR%" == "" set BOOST_INCLUDEDIR=c:\boost\include\boost-1_39
if "%BOOST_LIBRARYDIR%" == "" set BOOST_LIBRARYDIR=c:\boost\lib-x86

:: make a solution for editing/debugging
del CMakeCache.txt
cmake -G "Visual Studio 9 2008"

:: build the thing
del CMakeCache.txt
cmake -G "NMake Makefiles"

nmake clean
nmake

endlocal
