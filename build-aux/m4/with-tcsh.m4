#                                                       -*- Autoconf -*-

# _TC_WITH_SWIG(HAS-SWIG, HAS-NOT)
# --------------------------------
# Check whether Swig is requested, enabled, or disabled.  If
# requested, check that Python is present as needed.  If enabled,
# actually enable only if the environment is complete.
AC_DEFUN([_TC_WITH_SWIG],
[AC_ARG_WITH([swig],
            [AC_HELP_STRING([--with-swig],
                            [require Swig modules (defaults to auto)])],
            [],
            [with_swig=auto])

case $with_swig:$enable_shared in
  auto:no)
  AC_MSG_NOTICE([SWIG use disabled: dynamic libraries disabled])
  with_swig=no
  ;;
esac

if test x$with_swig != xno; then
  tc_has_swig=yes
  AM_PATH_PYTHON([2.3])
  adl_CHECK_PYTHON

  # Check for python and swig
  save_CPPFLAGS=$CPPFLAGS
  CPPFLAGS="$CPPFLAGS -I$PYTHONINC"
  AC_CHECK_HEADERS([Python.h],
                   [python_headers=yes],
                   [python_headers=no])

  if test x$python_headers = xno; then
    tc_has_swig=no
    if test x$with_swig = xyes; then
      AC_MSG_ERROR(
          [Python.h is required to build SWIG modules.
          Add `-I python_include_path' to `CPPFLAGS'
          or `--without-swig' to disable SWIG modules.])
    fi
  fi

  CPPFLAGS=$save_CPPFLAGS

  # Check for ruby.
  AC_CHECK_PROGS([RUBY], [ruby], [$am_aux_dir/missing ruby])
  if test "x$RUBY" = "x$am_aux_dir/missing ruby"; then
    AC_MSG_ERROR([no suitable Ruby interpreter found])
  fi

  AC_ARG_VAR([RUBY_CPPFLAGS], [Path to ruby.h])
  AC_ARG_WITH([ruby-includedir], [Include path for ruby.h],
              [RUBY_CPPFLAGS="-I$withval"],
              # Check paths using modern techniques (using `Rbconfig').
              # If it does not work, resort to the old method
              # (inspecting `$:').
              [ruby_config_rubyhdrdir=`$RUBY -rrbconfig \
                 -e "puts(RbConfig::CONFIG[['rubyhdrdir']] || '')"`
               ruby_config_arch=`$RUBY -rrbconfig \
                 -e "puts(RbConfig::CONFIG[['arch']] || '')"`
               if test -n "$ruby_config_rubyhdrdir" \
                    && test -n "$ruby_config_arch"; then
                 RUBY_CPPFLAGS="-I${ruby_config_rubyhdrdir}"
                 RUBY_CPPFLAGS="$RUBY_CPPFLAGS -I${ruby_config_rubyhdrdir}/${ruby_config_arch}"
               else
                 RUBY_CPPFLAGS="-I`$RUBY -e 'puts $:.join("\n")' | \
                 while read line
                   do
                   if [[ -f ${line}/ruby.h ]]; then
                     echo $line
                   fi
                 done`"
               fi])
  save_CPPFLAGS=$CPPFLAGS
  CPPFLAGS="$CPPFLAGS $RUBY_CPPFLAGS"
  AC_CHECK_HEADERS([ruby.h], [],
    [AC_MSG_ERROR(
            [You need Ruby development files to compile the Ruby interface.])])
  CPPFLAGS=$save_CPPFLAGS

  AC_PROG_SWIG([2.0])
  if (eval "$SWIG -version") >/dev/null 2>&1; then :; else
    tc_has_swig=no
  fi

  case $with_swig:$tc_has_swig in
    yes:no)
      AC_MSG_ERROR([SWIG 2.0 is required.
                    Use `--without-swig' to disable SWIG modules.]);;
  esac
fi

case $tc_has_swig in
  yes) $1;;
  * )  $2;;
esac
])

# TC_WITH_TCSH(WITH, WITHOUT)
# ---------------------------
# Should we build tcsh or not.
AC_DEFUN([TC_WITH_TCSH],
[AC_CACHE_CHECK([whether building tcsh],
                [tc_cv_with_tcsh],
                [_TC_WITH_SWIG([tc_cv_with_tcsh=yes],
                               [tc_cv_with_tcsh=no])])
case $tc_cv_with_tcsh in
  yes) $1;;
  no ) $2;;
  *)   AC_MSG_ERROR([incorrect tc_cv_with_tcsh value: $tc_cv_with_tcsh]);;
esac
])
