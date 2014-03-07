// Copyright 2010, Chad Versace <chad@kiwitree.net>
// 
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
// 
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.

// =====================================================================
// DebugFS Tutorial
// example1
//
// author: Chad Versace <chad@kiwitree.net>
// date: 2010-05-07
// =====================================================================

#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>

// The GPL license is required for the module to load.
// Without it, insmod reports unknown symbols in the module.
MODULE_LICENSE("GPL");

// This directory entry will point to `/sys/kernel/debug/example1`.
static struct dentry *dir = 0;

// File `/sys/kernel/debug/example1/hello` points to this variable.
static u32 hello = 0;

// This is called when the module loads.
int init_module(void)
{
    struct dentry *junk;

    // Create directory `/sys/kernel/debug/example1`.
    //
    // The function signature is
    //     struct dentry* debugfs_create_dir(
    //         const char *name,
    //         struct dentry *parent);
    // If parent is null, then directory is created in root of debugfs.
    //
    // See also linux-source/fs/debugfs/inode.c:debugfs_create_dir
    //
    dir = debugfs_create_dir("example1", 0);
    if (!dir) {
        // Abort module load.
        printk(KERN_ALERT "debugfs_example1: failed to create /sys/kernel/debug/example1\n");
        return -1;
    }

    // Create file `/sys/kernel/debug/example1/hello`.
    // Read/write operations on the file result in read/write operations on the variable `hello`.
    //
    // The function signature is
    //     struct dentry* debugfs_create_u32(
    //         const char *name,
    //         mode_t mode,
    //         struct dentry *parent,
    //         void *data);
    //
    // See also linux-source/fs/debugfs/file.c:debugfs_create_u32
    //
    junk = debugfs_create_u32("hello", 0666, dir, &hello);
    if (!junk) {
        // Abort module load.
        printk(KERN_ALERT "debugfs_example1: failed to create /sys/kernel/debug/example1/hello\n");
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
