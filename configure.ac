dnl Catch macros that are not expanded.
m4_pattern_forbid([^(AM|AX|LT|TC)_])

m4_define([TC_CLANG_PREREQ],    [4.0])
m4_define([TC_GCC_PREREQ],      [7.0])
m4_define([TC_HAVM_PREREQ],     [0.27])
m4_define([TC_NOLIMIPS_PREREQ], [0.10])

AC_PREREQ([2.64])

## ---------------- ##
## Package set up.  ##
## ---------------- ##

AC_INIT([Meric-de-bellefon Group Tiger Compiler], 4,
        [emmanuel.meric-de-bellefon@epita.fr],
        [emmanuel.meric-de-bellefon-tc],
        [http://tiger.lrde.epita.fr])

## Adding testsuite to the build
EXTA_DIST = testsuite.at tests/ atlocal.in

# Auxiliary files.
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])

# Automake.
AM_INIT_AUTOMAKE([1.14.1 dist-bzip2 no-dist-gzip foreign
                  color-tests parallel-tests
                  nostdinc silent-rules -Wall])
# By default, let "make" hide the compilation command and display a
# "GEN ..." message, unless V=1 is passed to "make".
AM_SILENT_RULES([yes])


## --------------------- ##
## C++ Compiler Set up.  ##
## --------------------- ##

# Look for a C++ compiler.
AC_LANG([C++])
AC_PROG_CXX

# Warn if the C++ compiler is not known to support the required
# features.  Or course, we should rather check for features, not
# version numbers.
cxx_version=$($CXX --version |
  sed -n ['/^[^0-9]*\([0-9][0-9.]*[0-9]\).*$/{s//\1/;p;q;}'])
case $($CXX --version) in
  (*clang*)
    AS_VERSION_COMPARE([$cxx_version], [TC_CLANG_PREREQ],
      [AC_MSG_WARN([clang++ >= TC_CLANG_PREREQ is required, have $cxx_version])])
    ;;
  (*g++*)
    AS_VERSION_COMPARE([$cxx_version], [TC_GCC_PREREQ],
      [AC_MSG_WARN([g++ >= TC_GCC_PREREQ is required, have $cxx_version])])
    ;;
  (*)
    AC_MSG_WARN([g++ >= TC_GCC_PREREQ or clang++ >= TC_CLANG_PREREQ is recommended, have none])
    ;;
esac

# Enable C++ 2014 support.
AC_CANONICAL_HOST
# Passing -stdlib=libc++ to clang++ is a requirement on OS X to enable
# full C++ 2011 support.  For more information on this, see
# http://cplusplusmusings.wordpress.com/2012/07/05/clang-and-standard-libraries
# We don't try to enable it by default on other platforms, as libc++
# is principally supported by OS X.
case $host_os in
  (darwin*)
    AX_CHECK_COMPILE_FLAG([-std=c++17 -stdlib=libc++],
                          [CXXFLAGS="$CXXFLAGS -std=c++17 -stdlib=libc++"
                           stdpass=true])
    ;;
esac
if ! "${stdpass-false}"; then
  AX_CHECK_COMPILE_FLAG([-std=c++17],
                        [CXXFLAGS="$CXXFLAGS -std=c++17"
                         stdpass=true])
fi

if ! "${stdpass-false}"; then
  AC_ERROR([unable to turn on C++14 mode with this compiler])
fi

# Try to use pipes between compiler stages to speed the compilation up.
AX_CHECK_COMPILE_FLAG([-pipe], [CXXFLAGS="$CXXFLAGS -pipe"])

# Use good warnings.
TC_CXX_WARNINGS([[-Wall],
                 [-W],
                 [-Wcast-align],
                 [-Wcast-qual],
                 [-Wformat],
                 [-Wmissing-prototypes],
                 [-Wstrict-prototypes],
                 [-Wwrite-strings],
                 [-Wbad-function-cast],
                 [-Wmissing-declarations],
                 [-Wnested-externs],
		 [-Wunused-parameter],
		 [-Wunused-function],
		 [-Woverloaded-virtual],
])

# Pacify g++ on Boost Variants.
TC_CXX_WARNINGS([[-Wno-shadow]])

# This is so that ICC no longer complain that
#
#  scantiger.ll(177): remark #111: statement is unreachable
#          break;
#          ^
#
#   ./../ast/seqexp.hh(36): remark #193:
#      zero used for undefined preprocessing identifier
#   #if STUDENT
#       ^
#
#    scantiger.cc(924): remark #279: controlling expression is constant
#          while ( 1 )             /* loops until end-of-file is reached */
#                  ^
#
#   ../../src/task/task.hh(38): remark #383:
#     value copied to temporary, reference to
#    temporary used
#           int key = 0, const std::string& deps = "");
#                                                  ^
#   /intel/compiler70/ia32/include/xstring(41): remark #444:
#      destructor for base class "std::_String_val<_Elem, _Ax>" is not virtual
#                   : public _String_val<_Elem, _Ax>
#                            ^
#
#  ../../../src/type/types.hxx(64): remark #522:
#    function "type::Named::type_set(const type::Type *)" redeclared "inline"
#    after being called
#      Named::type_set (const Type* type)
#              ^
#
#  ./../ast/print-visitor.hh(21): warning #654:
#  overloaded virtual function "ast::GenVisitor<K>::visit
#                               [with K=ast::const_kind]"
#   is only partially overridden in class "ast::PrettyPrinter"
#      class PrettyPrinter : public DefaultVisitor<const_kind>
#            ^
#
#  /intel/compiler70/ia32/include/xlocale(1381): remark #810:
#     conversion from "int" to "char" may lose significant bits
#                  return (widen((char)_Tolower((unsigned char)narrow(_Ch),
#                                ^
#
#
#   ./../ast/print-visitor.hh(331): remark #981:
#      operands are evaluated in unspecified order
#           _ostr << "type " << e.name_get () << " = ";
#                               ^
#
#  scantiger.cc(324): remark #1418:
#     external definition with no prior declaration
#    static char yy_hold_char;
#                ^
#
TC_CXX_WARNINGS([[[-wd111,193,279,383,444,522,654,810,981,1418]]])

# GCC emits tons of warnings about src/parse/parsetiger.hh regarding
# broken strict aliasing rules:
#
#   ../../src/parse/parsetiger.hh:
#     In instantiation of 'T& parse::variant<S>::as()
#     [with T = ast::DecsList*; long unsigned int S = 16ul]':
#   ../../src/parse/parsetiger.hh:146:7:
#     required from 'void parse::variant<S>::swap(parse::variant<S>&)
#     [with T = ast::DecsList*; long unsigned int S = 16ul]'
#   ../../src/parse/parsetiger.hh:156:7:
#     required from 'void parse::variant<S>::build(parse::variant<S>&)
#     [with T = ast::DecsList*; long unsigned int S = 16ul]'
#   ../../src/parse/parsetiger.hh:872:46:   required from here
#   ../../src/parse/parsetiger.hh:130:46:
#     warning: dereferencing type-punned pointer will break strict-aliasing
#     rules [-Wstrict-aliasing]
#
#   ...
#
# Check whether the C++ compiler supports `-Wno-strict-aliasing' and
# if so, add it to NO_STRICT_ALIASING_CXXFLAGS and let Makefiles use
# it to compile code that include src/parse/parsetiger.hh.
TC_CXX_FLAGS([[-Wno-strict-aliasing]], [NO_STRICT_ALIASING_CXXFLAGS])


## -------------------- ##
## Auxiliary programs.  ##
## -------------------- ##

TC_PROG([flex], [>= 2.5.35], [FLEX], [Flex scanner generator])
AX_CONFIG_SCRIPTS([build-aux/bin/flex++])
FLEX_VERSION
TC_PROG([bison], [>= 3.0], [BISON], [Bison parser generator])
AX_CONFIG_SCRIPTS([build-aux/bin/bison++])

# Compile Emacs files.
AM_PATH_LISPDIR

# Requested by Automake 1.12 for tcsh.
AM_PROG_AR

# We don't need shared libraries, speed the compilation up.
LT_INIT([disable-shared])

# Check for IA-32-GNU/Linux (and x86-64-GNU/Linux) to disable related
# parts on other platforms.
AM_CONDITIONAL([IA32_GNU_LINUX],
               [echo "$host" | grep -q '^\(i.86\|x86_64\).*linux'])
# Check for IA-32-FreeBSD to disable related parts on other platforms.
AM_CONDITIONAL([IA32_FREEBSD],
               [echo "$host" | grep -q '^\(i.86\|amd64\).*freebsd'])
# If one the previous IA-32 conditionals was true, enable SUPPORTED_IA32.
AM_CONDITIONAL([SUPPORTED_IA32],
               [echo "$host" | grep -q '^\(i.86\|x86_64\).*linux\|^\(i.86\|amd64\).*freebsd'])




## ----------- ##
## Libraries.  ##
## ----------- ##

BOOST_REQUIRE([1.61])
BOOST_CONVERSION # boost::lexical_cast
BOOST_FILESYSTEM
BOOST_GRAPH
BOOST_PREPROCESSOR
BOOST_PROGRAM_OPTIONS
BOOST_STRING_ALGO
BOOST_SYSTEM
BOOST_TRIBOOL
BOOST_VARIANT

## ------ ##
## Tcsh.  ##
## ------ ##

# Check for Darwin to help Libtool use the right dynamic module
# extension on this system.
AM_CONDITIONAL([DARWIN], [echo "$host_os" | grep -q '^darwin'])
TC_WITH_TCSH([with_tcsh=yes], [with_tcsh=no])
AM_CONDITIONAL([ENABLE_TCSH], [test x$with_tcsh = xyes])

AC_CONFIG_FILES([tcsh/Makefile])
AC_CONFIG_FILES([doc/Doxyfile])
AX_CONFIG_SCRIPTS([tcsh/run])

## ------- ##
## Tests.  ##
## ------- ##

# Students should create their test suite in tests/.  Add the needed
# configure options here.
AC_CONFIG_FILES([tests/Makefile])

## --------------- ##
## Configuration.  ##
## --------------- ##

# Ask for the creation of config.h.
AC_CONFIG_HEADERS([config.h])

# Ask for the creation of the Makefiles.
AC_CONFIG_FILES([Makefile])

# Instantiate the output files.
AC_OUTPUT
