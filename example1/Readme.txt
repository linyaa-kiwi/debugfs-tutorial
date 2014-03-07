========================================================================
DebugFS Tutorial
  
author: Chad Versace <chad@kiwitree.net>
date: 2010-05-07
========================================================================


=========
Example 1
=========

----------------
What does it do?
----------------

The kernel module debugfs_example1 creates two files in debugfs:
    /sys/kernel/debug/example1
    /sys/kernel/debug/example1/hello
Reading/writing to `hello` actually reads/writes to a variable in the module.


------------
Instructions
------------

> cd example1
> make
> sudo insmod debugfs_example1.ko
> cd /sys/kernel/debug/example1
> ls -l
-rw-rw-rw- hello
> cat hello
0
> echo 42 >> hello
> cat hello
42
> echo 3 >> hello
> cat hello
3
> sudo rmmod debugfs_example1
