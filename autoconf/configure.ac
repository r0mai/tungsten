AC_INIT([tungsten],[version-0.1],[https://github.com/r0mai/tungsten])

AC_PROG_CXX([g++ clang++])

AC_CHECK_LIB(gmp, __gmpz_init, ,
	[AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])

AC_OUTPUT(Tuprules.tup)

