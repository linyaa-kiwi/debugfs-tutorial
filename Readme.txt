========================================================================
DebugFS Tutorial
  
author: Chad Versace <chad@kiwitree.net>
date: 2010-05-07
========================================================================

========
Overview
========

DebugFS is a synthetic filesystem in the kernel. It resides at
/sys/kernel/debug and allows userspace processes to inspect and manipulate
variables in the kernel. Unlike sysfs, the information provided by debugfs is
intended for kernel debugging only.

This tutorial is hands-on with kernel code. For each example
1. Read the Readme,
2. Open the source file,
3. And follow the comments.
