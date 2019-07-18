#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/magic.h>
#include <asm/unaligned.h>

#include "lard.h"


static struct kmem_cache *lard_inode_cache;


static void lard_init_once(void *foo)
{
/*
	lard_inode *li = (lard_inode *) foo;
	inode_init_once(&li->vfs_inode);
*/
}

static struct inode *lard_alloc_inode(struct super_block *sb)
{
	printk(KERN_INFO "lard_alloc_inode called\n");
	return NULL;
}

static void lard_destroy_inode(struct inode *destroy_me)
{
	printk(KERN_INFO "lard_destroy_inode called\n");
	return;
}

static int lard_write_inode(struct inode *inode, struct writeback_control
			    *wbc)
{
	printk(KERN_INFO "lard_write_inode called\n");
	return 0;
}

static void lard_evict_inode(struct inode *inode)
{
	printk(KERN_INFO "lard_evict_inode called\n");
	return;
}

static void lard_put_super(struct super_block *sb)
{
	printk(KERN_INFO "lard_put_super called\n");
	return;
}

static int lard_statfs(struct dentry *dentry, struct kstatfs *kstat)
{
	printk(KERN_INFO "lard_statfs called\n");
	return 0;
}

static int lard_remount(struct super_block *sb, int *flags, char *databuf)
{
	printk(KERN_INFO "lard_remount called\n");
	return 0;
}

static int lard_show_options(struct seq_file *file, struct dentry *dentry)
{
	printk(KERN_INFO "lard_show_options called\n");
	return 0;
}

static struct super_operations lard_super_operations = {
	.alloc_inode	= lard_alloc_inode,
	.destroy_inode	= lard_destroy_inode,
	.write_inode	= lard_write_inode,
	.evict_inode	= lard_evict_inode,
	.put_super	= lard_put_super,
	.statfs		= lard_statfs,
	.remount_fs	= lard_remount,
	.show_options	= lard_show_options
};

static int read_boot_sector(struct super_block *sb, struct lard_superblock *lsb,
			    struct lard_boot_sector *lbs)
{
	return -EOPNOTSUPP;
}

static int lard_fill_sb(struct super_block *sb, void *data, int silent)
{
	struct inode * root_inode;
	struct inode * lard_inode;
	struct lard_boot_sector *lbs;
	struct lard_superblock *lsb;
	struct buffer_head *bh;
	int blocksize, err;

	lbs = kmalloc(sizeof(struct lard_boot_sector), GFP_KERNEL);
	memset(lbs, 0, sizeof(*lsb));
	if (!lbs)
		return -ENOMEM;

	lsb = kmalloc(sizeof(struct lard_superblock), GFP_KERNEL);
	memset(lsb, 0, sizeof(*lsb));
	if (!lsb)
		return -ENOMEM;

	/* assign superblock values */
	sb->s_fs_info = lsb;
	sb->s_op = &lard_super_operations;
	sb->s_magic = LARD_SUPER_MAGIC;

	blocksize = sb_min_blocksize(sb, 512); // assume 512 block/cluster size
	if (!blocksize)
		return -EIO;
	printk(KERN_INFO "blocksize = %d\n", blocksize);

	bh = sb_bread(sb, 0);
	if (bh == NULL)
		return -EIO;

	err = read_boot_sector(sb, lsb, (struct lard_boot_sector *)bh->b_data);
	if (err) return err;
	brelse(bh);

	root_inode = new_inode(sb);
	lard_inode = new_inode(sb);

	if (root_inode == NULL || lard_inode == NULL)
		return -ENOMEM;

	return -ENOMEM;
}

static struct dentry *lard_mount(struct file_system_type *fs,
			  int flags, const char *bdev_name,
			  void *data)
{
	return mount_bdev(fs, flags, bdev_name, data, lard_fill_sb);
}


static struct file_system_type lardfs = {
	.owner		= THIS_MODULE,
	.name		= "lard",
	.mount		= lard_mount,
	.kill_sb	= kill_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
};

static int __init init_lard(void)
{
	int err;
	printk(KERN_INFO "Enabling %s file system.\n", MODULE_NAME);

	lard_inode_cache = kmem_cache_create("LARD_INODE_CACHE",
					     sizeof(lard_inode), 0,
					(SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD|
					 SLAB_ACCOUNT), lard_init_once);

	if (!lard_inode_cache)
		return -ENOMEM;
	err = register_filesystem(&lardfs);
	if (err) {
		printk(KERN_WARNING "Failed to load %s fs.\n", MODULE_NAME);
		return err;
	}
	printk(KERN_INFO "Successfully loaded %s.\n", MODULE_NAME);
	return 0;
}

static void __exit exit_lard(void)
{
	printk(KERN_INFO "Disabling %s file system.\n", MODULE_NAME);
	kmem_cache_destroy(lard_inode_cache);
	unregister_filesystem(&lardfs);
}

module_init(init_lard);
module_exit(exit_lard);
