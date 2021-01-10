Introduction:
========================================

This is a basic memory model that is under development. Presently, written entirely in C++, it is intended for educational purposes and fellow programmers who starting off with C++ (with an application in computer architecture)

Author: Vignesh Suresh

Steps to build:
========================================

1) Ensure that you have g++ toolchain available in one of the search paths.

2) 'make clean': Clean all objects, binaries and temporary files.

3) 'make clean_obj': Clean only object files.

4) 'make TEST=xyz': Cleans object files, runs compile/link to give an executable and runs the test xyz.

5) 'make run TEST=xyz': Runs the executable for the test xyz.
