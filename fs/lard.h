/**
 * lard.h - Definitions and specifications of the LARD filesystem on Linux
 */

#ifndef _LARD_H
#define _LARD_H

#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/buffer_head.h>
#include <linux/types.h>
#include <linux/string.h>

#include <asm/byteorder.h>

#include "blob.h"
#include "layout.h"
#include "types.h"


#ifndef MODULE_NAME
#define MODULE_NAME "LARD"
#endif

#define LARD_MAGIC		0x4c415244	 /* LARD */
#define LARD_SUPER_MAGIC	0x4c53424b	 /* LSBK */

#ifndef SECTOR_SIZE
#define SECTOR_SIZE		512		/* Sector size in bytes */
#endif

#define MAX_NAMELEN		64
/**
 * Define blobs to ease data handling. Data can be spread on multiple blobs
 * One blob is 8 * 512B sectors = 4096 bytes.
 * One page is commonly 4096, so one blob fits into one memory page
 */

extern const struct inode_operations lard_inode_operations;

/**
 * In memory copy of relevant data for Linux VFS
 */
struct lard_superblock {
	u8 header;
	struct superblock *sb;		// 'vfs super'
	u8 sectorSize;
	u32 sectorCount;
	u32 volumeSize;

	u32 usedSectors;

	char volume_name;

	u32 magic;
	u32 flags;
} __attribute__ ((__packed__));


struct lard_dentry {
	u8 signature;
	u8 de_len;
	u8 name[MAX_NAMELEN];
	u64 inode_number;	/* Points to the inode in the i_table */
} __attribute__ ((__packed__));

static inline struct lard_superblock *LARD_SB(struct super_block *sb)
{
	printk(KERN_CRIT "LARD_SB\n");
	return sb->s_fs_info;
}

/*
static inline lard_inode *LARD_I(struct inode *inode)
{
	printk(KERN_CRIT "LARD_I\n");
	return container_of(inode, lard_inode, vfs_inode);
}
*/

MODULE_LICENSE("Dual MIT/GPL"); // Don't taint the kernel :^)
MODULE_DESCRIPTION("LARD file system support");

#endif
