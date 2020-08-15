# SpellTracker
A generic tracker for games like Ocarina of Time and Majora's Mask Randomizer. SpellTracker uses an
interpreter-style design rather than making assumptions about what tracking a game should be like.

Building
--------
SpellTracker requires the following dependencies:

- A modern C++ compiler supporting C++17 - confirmed working compilers are GNU GCC, Microsoft MSVC, and LLVM clang.
- The Qt framework version 5, with components: XML, Widgets, and LinguistTools.

SpellTracker uses CMake as its build tool, you will need at least version 3.5. Use it to generate a makefile for your 
compiler and system of choice and compile.

Running
-------
Copy the files from the `resources` directory into the same directory as the binary and double click. On some platforms, 
it may be required to copy Qt shared libraries into the same directory if they are not found in the library root of your OS.

Contributing
------------

Please see the issue tracker for how you can help. Contributions are welcomed so long as they are written in correct C++17
and follow Qt5 best practices.
