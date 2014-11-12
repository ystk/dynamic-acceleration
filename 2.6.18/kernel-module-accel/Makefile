KERNELSRCDIR = ~/linux/build-first
BUILD_DIR := $(shell pwd)
VERBOSE = 1

obj-m := accel.o
accel-objs := dyn_accel.o

all:
	make -C $(KERNELSRCDIR) SUBDIRS=$(BUILD_DIR) KBUILD_VERBOSE=$(VERBOSE) modules

clean:
	rm -f *.o
	rm -f *.ko
	rm -f *.mod.c
	rm -f *~
