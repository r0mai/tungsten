AC_INIT([tungsten],[version-0.1],[https://github.com/r0mai/tungsten])

m4_include([autoconf/m4/ax_gcc_version.m4])

AC_PROG_CXX([g++ clang++])
if test "$CXX" = "g++"; then
	AX_GCC_VERSION
	GCC_VERSION_MAJOR=$(echo $GCC_VERSION | cut -d'.' -f1)
	GCC_VERSION_MINOR=$(echo $GCC_VERSION | cut -d'.' -f2)
	GCC_VERSION_PATCH=$(echo $GCC_VERSION | cut -d'.' -f3)
	if test "$GCC_VERSION_MAJOR" != "4" ||
		test "$GCC_VERSION_MINOR" != "8" ||
		test "$GCC_VERSION_PATCH" != "2"
	then
		AC_PROG_CXX([clang++])
	fi
fi



AC_CHECK_LIB(gmp, __gmpz_init, ,
	[AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])

AC_OUTPUT(Tuprules.tup)

