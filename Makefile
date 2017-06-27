PROJECT = ctp
PROJECT_DESCRIPTION = ctp wrapper for erlang
PROJECT_VERSION = 0.1.0
ROOT_DIR = $(CURDIR)

include erlang.mk
export ROOT_DIR C_SRC_DIR CC CXXFLAGS LIBFLAGS LDLIBS link_verbose
