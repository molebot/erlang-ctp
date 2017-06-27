PROJECT = $(notdir $(CURDIR))
PROJECT := $(strip $(PROJECT))_nif

C_SRC_OUTPUT = $(PRIVATE_DIR)/$(PROJECT).so

SOURCES := $(wildcard *.cc)
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

$(C_SRC_OUTPUT): $(OBJECTS)
	@mkdir -p $(PRIVATE_DIR)
	$(link_verbose) $(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(C_SRC_OUTPUT)

clean:
	@rm -f $(C_SRC_OUTPUT) $(OBJECTS)
