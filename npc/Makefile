VFLAGS = -Wall -j 0 --cc --exe --build
all: sim
sim: wrapper.c top.v
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator $(VFLAGS) $^
	./obj_dir/Vtop
	gtkwave waveform.fst

include ../Makefile
