obj-m := debugfs_example1.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
WARN_FLAGS += -Wall

.PHONY: default
defualt:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
