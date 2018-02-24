# We use GNU Make features, and that's OK.
AUTOMAKE_OPTIONS = -Wno-portability subdir-objects
ACLOCAL_AMFLAGS = -I build-aux/m4

# We work on C++ only.  This way we don't have to list the sources of
# programs foo whose sources are exactly foo.cc.  A common pattern for
# tests.
AM_DEFAULT_SOURCE_EXT = .cc

BUILT_SOURCES =
CLEANFILES = $(EXTRA_PROGRAMS)
EXTRA_DIST = $(dist_TESTS)
MAINTAINERCLEANFILES =
TESTS = $(check_PROGRAMS) $(dist_TESTS)
check_PROGRAMS =
dist_TESTS = tests/
dist_noinst_DATA =

check: testsuite

testsuite:
	$(srcdir)/tests/test.sh

# Our tests should be run only if the sources are updated: they are
# self contained, and two runs in a row cannot differ.
RECHECK_LOGS =

include build-aux/local.am
include data/local.am

SUBDIRS = . tests
if ENABLE_TCSH
SUBDIRS += tcsh
endif

# Most headers are to be shipped and to be found in src/, e.g.
# tasks/tasks.hh is shipped in $(top_srcdir)/src/task/tasks.hh.  Some
# are *built* in src, e.g., $(top_builddir)/src/modules.hh.
AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src -I$(top_builddir)/src
AM_CPPFLAGS += $(BOOST_CPPFLAGS)
# Find the prelude.
AM_CPPFLAGS += -DPKGDATADIR="\"$(pkgdatadir)\""
AM_CXXFLAGS = $(WARNING_CXXFLAGS)


# Find configuration headers.
AM_CPPFLAGS += -I$(top_builddir)

include lib/local.am
include src/local.am
include doc/local.am

EXTRA_DIST += bootstrap AUTHORS.txt NEWS.txt THANKS.txt

## --------------------- ##
## Version and authors.  ##
## --------------------- ##

BUILT_SOURCES += authors.h
CLEANFILES += authors.h tc.log.bz2
# Improve --version.
AUTHORS_H_GEN = $(srcdir)/build-aux/bin/authors.h-gen
EXTRA_DIST += AUTHORS.txt $(AUTHORS_H_GEN)
authors.h: AUTHORS.txt $(AUTHORS_H_GEN)
	$(AM_V_GEN)$(AUTHORS_H_GEN) $< >$@.tmp
	$(AM_V_at)$(top_srcdir)/build-aux/bin/move-if-change $@.tmp $@


