m4_pattern_forbid([^AX_])

AC_PREREQ([2.60])

# AX_CONFIG_SCRIPTS([SCRIPT1], [SCRIPT2:SOURCE2], ...)
# ----------------------------------------------------
# Same as AC_CONFIG_FILES, but runs chmod a+x.  Does not work well
# with shell lists: don't run
#
#  AX_CONFIG_SCRIPTS([foo bar])
#
# but
#
#  AX_CONFIG_SCRIPTS([foo], [bar])
#
# EXEEXT is available for use:
#
#  AX_CONFIG_SCRIPTS([foo$EXEEXT:foo.in], [bar])
#
AC_DEFUN([AX_CONFIG_SCRIPTS],
[m4_foreach([AC_Script], [$@],
[AC_CONFIG_FILES(AC_Script,
                 [chmod a+x "m4_bpatsubst(]AC_Script[, [:.*])"],
                 [EXEEXT=$EXEEXT])])
])


## Local Variables:
## mode: Autoconf
## End:
