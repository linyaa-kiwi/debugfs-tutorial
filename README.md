# DebugFS Tutorial

DebugFS is a synthetic filesystem in the kernel. It resides at
`/sys/kernel/debug` and allows userspace processes to interact with variables
and functions in the kernel. Unlike sysfs, the information provided by debugfs
is intended for kernel debugging only.

This tutorial is hands-on with kernel code. For each example:

  1. Read the README,
  2. Open the source file,
  3. Follow the comments.

Author: Lina Versace <<lina@kiwitree.net>>

## Example 1

### What does it do?

The kernel module *debugfs_example1* creates the below files in *debugfs*:

    /sys/kernel/debug/example1
    /sys/kernel/debug/example1/hello

Reading/writing to file *hello* actually reads/writes to a variable *hello* in
the module.

### Instructions

    $ cd example1
    $ make
    $ sudo insmod debugfs_example1.ko
    $ cd /sys/kernel/debug/example1
    $ ls -l
    -rw-rw-rw- hello
    $ cat hello
    0
    $ echo 42 > hello
    $ cat hello
    42
    $ echo 3 > hello
    $ cat hello
    3
    $ sudo rmmod debugfs_example1

## Example 2

### What does it do?

The kernel module *debugfs_example2* creates the below files in *debugfs*:

    /sys/kernel/debug/example2
    /sys/kernel/debug/example2/add
    /sys/kernel/debug/example2/sum

File *sum* points to the variable *sum* in the module. File *add* is proxy to
the function *add_write_op* which increments the *sum* variable. Appending
integers to file *add* will increase *sum*.

### Instructions

    $ cd example2
    $ make
    $ sudo insmod debugfs_example2.ko
    $ cd /sys/kernel/debug/example2
    $ ls -l
    --w--w--w- add
    -r--r--r-- sum
    $ cat sum
    0
    $ echo 17 >> add
    $ cat sum
    17
    $ echo 2 >> add
    $ cat sum
    19
    $ sudo rmmod debugfs_example2
