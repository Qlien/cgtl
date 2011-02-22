SUBDIRS = base search shortpath

CXXTSRCS_GRAPH = graph_cxx.cc
CXXTSRCS = $(CXXTSRCS_GRAPH)

SRCS_GRAPH = $(CXXTSRCS_GRAPH) $(top_builddir)/src/cgt/graph.h \
			 $(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS = -DUSE_UT_CXXTEST

check_PROGRAMS	   = graph_cxx
graph_cxx_SOURCES = $(SRCS_GRAPH)
TESTS = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(CXXTSRCS)
