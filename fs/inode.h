#ifndef _INODE_H
#define _INODE_H

typedef struct {
	char name[64];
	u64 i_size;			// Size in memory
	loff_t i_off;			// Offset/position on disk

	struct inode vfs_inode;		// Corresponding vfs_inode
} __attribute__ ((__packed__)) lard_inode;

#endif // _INODE_H
