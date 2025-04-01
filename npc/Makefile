VERILATOR_CFLAGS = -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert
TRACE_FLAGS = --trace-fst
# can use TOPNAME macro in cpp file
TOPNAME = top
INC_PATH ?=
NXDC_FILES = constr/top.nxdc
VERILATOR = verilator
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)


$(shell mkdir -p $(BUILD_DIR))
include $(NVBOARD_HOME)/scripts/nvboard.mk

# generating nxdc file first.
all: sim
sim: $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME)   $(TRACE_FLAGS) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

include ../Makefile

$(SRC_AUTO_BIND): $(NXDC_FILES)
# this is for generating the auto_bind.cpp file based on the nxdc file.
# The result is that under the build folder there is a file called auto_bind.cpp
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

.PHONY: clean all sim
clean:
	rm -rf $(BUILD_DIR)
