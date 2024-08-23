// SPDX-License-Identifier: GPL-2.0 OR MIT
// Copyright 2010 Lina Versace <lina@kiwitree.net>

// ===========================
// DebugFS Tutorial: Example 2
// ===========================

#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>

// The GPL license is required for the module to load.
// Without it, insmod reports unknown symbols in the module.
MODULE_LICENSE("GPL");

// This directory entry will point to `/sys/kernel/debug/example2`.
static struct dentry *dir = 0;

// File `/sys/kernel/debug/example2/sum` points to this variable.
static u32 sum = 0;

// This is called when `/sys/kernel/debug/example2/add` is written to.
//
// Executing `echo 17 >> /sys/kernel/debug/example2/add` will call
// `add_write_op(NULL, 17)`. The data argument is NULL because... that`s
// explained later.
//
static int add_write_op(void *data, u64 value)
{
    sum += value;
	return 0;
}

// Here we define the file operations associated with
// `/sys/kernel/debug/example2s/add`.
//
// To each file in debugfs belongs a struct of type `struct file_operations`.
// The members of the struct that we are concerned with are
//     struct file_operations {
//         .read,
//         .write,
//         .open,
//         // ...
//     };
// Each member is a function pointer that is called when the file is
// read, written to, or opened.
//
// We could define the file operations by hand, but `<linux/fs.h>` provides
// a macro for this purpose.
//
DEFINE_SIMPLE_ATTRIBUTE(add_fops, NULL, add_write_op, "%llu\n");
//
// Ah, that macro needs some explanation.
//
// The macro has form
//     DEFINE_SIMPLE_ATTRIBUTE(fops_name, read_op, write_op, printf_fmt)
// and it defines `add_ops` to be
//     struct file_operations add_ops = {
//         .read = NULL,
//         .write = add_write_op,
//         .open = add_fops_open, // Also defined by macro
//         // ...
//     };
//
// The read function is NULL because we will later set the permissions of
// `/sys/kernel/debug/example2/add` to be write-only. Hence, the
// `add_fops.read` will never be derefenced.
//
// See the default debugfs file operations at
// linux-source/fs/debugfs/file.c:const struct file_operations debugfs_file_operations
//
// See also linux-source/include/linux/fs.h:DEFINE_SIMPLE_ATTRIBUTE
//

// This is called when the module loads.
int init_module(void)
{
    struct dentry *junk;

    // Create directory `/sys/kernel/debug/example2`.
    //
    // The function signature is
    //     struct dentry* debugfs_create_dir(
    //         const char *name,
    //         struct dentry *parent);
    // If parent is null, then directory is created in root of debugfs.
    //
    // See also linux-source/fs/debugfs/inode.c:debugfs_create_dir
    //
    dir = debugfs_create_dir("example2", 0);
    if (!dir) {
        // Abort module load.
        printk(KERN_ALERT "debugfs_example2: failed to create /sys/kernel/debug/example2\n");
        return -1;
    }

    // Create file `/sys/kernel/debug/example2/add`.
    //
    // The function signature is
    //     struct dentry* debugfs_create_file(
    //         const char *name,
    //         mode_t mode,
    //         struct dentry *parent,
    //         void *data,
    //         const struct file_operations *fops);
    //
    // Since no function in `add_fops` accesses the file`s data, we may
    // set `data = NULL`.
    //
    // See also linux-source/fs/debugfs/inode.c:debugfs_create_file
    //
    junk = debugfs_create_file(
            "add",
            0222,
            dir,
            NULL,
            &add_fops);
    if (!junk) {
        // Abort module load.
        printk(KERN_ALERT "debugfs_example2: failed to create /sys/kernel/debug/example2/add\n");
        return -1;
    }

    // Create file `/sys/kernel/debug/example2/sum`.
    //
    // The function signature is
    //     struct dentry* debugfs_create_u32(
    //         const char *name,
    //         mode_t mode,
    //         struct dentry *parent,
    //         void *data);
    //
    // Unlike `debugfs_create_file`, there is no fops parameter. That is
    // because `debugfs_create_u32` provides default file operations for the
    // u32 type.  In debugfs.h, there is a collection of similar functions
    // named debugfs_create_TYPE.
    //
    // Note that we set permissions to be read-only.
    //
    // See also linux-source/fs/debugfs/file.c:debugfs_create_u32
    //
    junk = debugfs_create_u32("sum", 0444, dir, &sum);
    if (!junk) {
        // Abort module load.
        printk(KERN_ALERT "debugfs_example2: failed to create /sys/kernel/debug/example2/add\n");
        return -1;
    }

    return 0;
}

// This is called when the module is removed.
void cleanup_module(void)
{
    // We must manually remove the debugfs entries we created. They are not
    // automatically removed upon module removal.
    debugfs_remove_recursive(dir);
}
