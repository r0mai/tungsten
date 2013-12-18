AC_INIT([tungsten],[version-0.1],[https://github.com/r0mai/tungsten])

AC_LANG(C++)

m4_include([autoconf/m4/boost.m4])

AC_PROG_CXX([g++ clang++])
AC_PROG_CC([gcc clang])
if test "$CXX" = "g++"; then

	GCC_VERSION=`g++ -dumpversion`

	GCC_VERSION_MAJOR=$(echo $GCC_VERSION | cut -d'.' -f1)
	GCC_VERSION_MINOR=$(echo $GCC_VERSION | cut -d'.' -f2)
	GCC_VERSION_PATCH=$(echo $GCC_VERSION | cut -d'.' -f3)
	echo -n "Your g++ version is: $GCC_VERSION... "
	if test "$GCC_VERSION_MAJOR" != "4" ||
		test "$GCC_VERSION_MINOR" != "8" ||
		test "$GCC_VERSION_PATCH" != "2"
	then
		echo "not good enough, trying clang++"
		dnl FIXME AC_PROG_CC caches results, can't use it here
		CXX="clang++"
	else
		echo "good"
	fi
fi

dnl Check for GMP and GMPXX
AC_CHECK_HEADERS([gmp.h], , [AC_MSG_ERROR([gmp.h not found, see http://gmplib.org/])])
AC_CHECK_LIB(gmp, __gmpz_init, , [AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])
AC_CHECK_LIB(gmp, __gmpz_2fac_ui, ,	[AC_MSG_ERROR([GNU MP not found, or not 5.1.0 or up, see http://gmplib.org/])])

dnl Check for MPFR
AC_CHECK_HEADERS([mpfr.h], , [AC_MSG_ERROR([mpfr.h not found, see http://mpfr.org/])])
AC_CHECK_LIB(mpfr, mpfr_add, , [AC_MSG_ERROR([MPFR not found, see http://mpfr.org/])])

dnl Optional optimization
AC_ARG_ENABLE(optimized, AS_HELP_STRING(--enable-optimized, [Compile with optimizations enabled (default is NO)]),,enableval="no")
if test ${enableval} == "yes"; then
	AC_SUBST(OPTIMIZATION_FLAG, [-O2])
else
	AC_SUBST(OPTIMIZATION_FLAG, [-O0])
fi

AC_ARG_ENABLE(assertions, AS_HELP_STRING(--enable-assertions, [Compile with runtime assertions enabled (default is YES)]),,enableval="yes")
if test ${enableval} == "yes"; then
	AC_SUBST(ASSERTIONS_FLAG, [])
else
	AC_SUBST(ASSERTIONS_FLAG, [-DNDEBUG])
fi

BOOST_REQUIRE([1.54.0])

AC_OUTPUT([Tuprules.tup])

