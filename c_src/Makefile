include env.mk

PRIVATE_DIR = $(ROOT_DIR)/priv
INCLUDE_DIR = $(C_SRC_DIR)/include
CTP_LIB_DIR = $(C_SRC_DIR)/lib/ctp

CXXFLAGS += -I"$(INCLUDE_DIR)"
LDLIBS += -L"$(CTP_LIB_DIR)" -lthostmduserapi -lthosttraderapi
LDFLAGS += -shared -Wl,-rpath,$(CTP_LIB_DIR)
export

.PHONY: all clean

all:
	$(MAKE) -C ctp_md
	$(MAKE) -C ctp_td

clean:
	$(MAKE) -C ctp_md clean
	$(MAKE) -C ctp_td clean
