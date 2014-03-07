========================================================================
DebugFS Tutorial
  
author: Chad Versace <chad@kiwitree.net>
date: 2010-05-07
========================================================================


=========
Example 2
=========

----------------
What does it do?
----------------

The kernel module debugfs_example2 creates three files in debugfs:
    /sys/kernel/debug/example2
    /sys/kernel/debug/example2/add
    /sys/kernel/debug/example2/sum
File `sum` points to a variable in the module. File `add`, however, points to
no variable.  It is proxy to the function `add_write_op`, defined in the
module. Calling `add_write_op` increments `sum`.

Appending integers to file `add` will increase `sum`. For example:
> cat sum
0
> echo 17 >> add
> echo 2 >> add
> cat sum
19


------------
Instructions
------------

> cd example2
> make
> sudo insmod debugfs_example2.ko
> cd /sys/kernel/debug/example2
> ls -l
--w--w--w- add
-r--r--r-- sum
> cat sum
0
> echo 17 >> add
> echo 2 >> add
> cat sum
19
> sudo rmmod debugfs_example2
