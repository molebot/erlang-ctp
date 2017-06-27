PROJECT = ctp
PROJECT_DESCRIPTION = ctp wrapper for erlang
PROJECT_VERSION = 0.1.0
ROOT_DIR = $(CURDIR)

# ------------------------------------------------------------------------------
# Standard targets
# ------------------------------------------------------------------------------

include erlang.mk

# ------------------------------------------------------------------------------
# Export variables to sub-make
# ------------------------------------------------------------------------------

export ROOT_DIR C_SRC_DIR CC CXXFLAGS LIBFLAGS LDLIBS link_verbose

# ------------------------------------------------------------------------------
# Generate rebar.config on build
# ------------------------------------------------------------------------------

define REBAR_CONFIG_HOOK
{pre_hooks,
  [{"(linux|darwin|solaris)", compile, "make"},
   {"(freebsd)", compile, "gmake"}]}.
{post_hooks,
  [{"(linux|darwin|solaris)", clean, "make clean"},
   {"(freebsd)", clean, "gmake clean"}]}.
endef

app:: rebar.config
	$(file >> rebar.config,$(REBAR_CONFIG_HOOK))
