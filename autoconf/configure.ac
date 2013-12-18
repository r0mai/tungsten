AC_INIT([tungsten],[version-0.1],[https://github.com/r0mai/tungsten])

AC_LANG(C++)

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



AC_CHECK_LIB(gmp, __gmpz_init, ,
	[AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])

AC_OUTPUT(Tuprules.tup)

