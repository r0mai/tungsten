#!/bin/bash
#clang++ -fPIC -std=c++0x -I../src -I/usr/include/python2.7 -c Graphics.cpp -o Graphics.o
clang++ -fPIC -std=c++0x -I../src -I/usr/include/python2.7 -c pytungsten.cpp -o pytungsten.o && clang++ -shared -Wl,-soname,pytungsten.so -o pytungsten.so pytungsten.o ../src/*.o -lpython2.7 -lboost_python  /usr/local/lib/libboost_thread.so  /usr/local/lib/libboost_system.so  /usr/local/lib/libboost_filesystem.so   /usr/local/lib/libboost_regex.so   /usr/local/lib/libboost_program_options.so /usr/local/lib/libpng.so /usr/local/lib/libmpfr.so /usr/local/lib/libgmpxx.so /usr/local/lib/libgmp.so
