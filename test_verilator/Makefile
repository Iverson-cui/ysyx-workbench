VFLAGS = -Wall -j 0 --cc --exe --build
all: sim
sim: top.v wrapper.cpp
	verilator $(VFLAGS) --top-module top --trace-fst $^
	./obj_dir/Vtop
	gtkwave waveform.fst

include ../Makefile

.PHONY: clean
clean:
	rm -rf obj_dir
	rm *.fst
