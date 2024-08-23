# SPDX-License-Identifier: GPL-2.0 OR MIT
# Copyright 2010 Lina Versace <lina@kiwitree.net>

obj-m := debugfs_example2.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
WARN_FLAGS += -Wall

.PHONY: default
defualt:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
