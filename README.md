Tungsten
========

Wolfram Mathematica clone written in C++11.

tungsten has the following dependencies:

* gcc (4.8) or clang (3.2)
* boost (1.53)
* tup (0.6-291)
* gmp (5.1.0)
* mpfr (3.1.1)
* readline (6.2)

For the web front end
python (2.7)

Note: It is very likely that tungsten will work with newer versions of these libraries, but less likely with previous versions.
Note: It is recommended to install everything to /usr/local/ (The default install location for all of these libraries). This way tungsten should work without any extra configuration.

## Installing dependencies:

### clang (http://clang.llvm.org/)

From svn trunk: http://clang.llvm.org/get_started.html
Note: clang also has a lot of dependencies (see system requirements), but most (if not all) can be installed via apt-get.

### boost (http://boost.org):

See Getting Started section: http://www.boost.org/doc/libs/1_53_0/more/getting_started/unix-variants.html
You must build the binaries as well (see section 5.1).
Note: if you want to build the web front end as well you should first aquire python, since boost.python depends on it.

### tup (http://gittup.org/tup/):

```
apt-add-repository 'deb http://ppa.launchpad.net/anatol/tup/ubuntu lucid main'
apt-get update
apt-get install tup
```

### gmp (http://gmplib.org/):

After downloading and extracting the archive http://gmplib.org/manual/Installing-GMP.html#Installing-GMP.

### mpfr (http://www.mpfr.org/):

See INSTALL document in the downloaded archive.

### readline (http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html):

See INSTALL document in the downloaded archive.

### python (http://www.python.org/):

```
apt-get install python2.7-dev
```

## Building tungsten:

From the root directory of tungsten

```
cd tungsten
mkdir build
cd build
cmake ..
make
```

## Multithreading

Pass `-DENABLE_MULTITHREADING:BOOLEAN=ON` to cmake to enable Multithreading
