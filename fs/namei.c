#include "lard.h"

static struct dentry *lard_lookup(struct inode *directory_inode,
				  struct dentry *directory_entry,
				  unsigned flags)
{
	printk(KERN_INFO "lard_lookup called\n");
	return NULL;
}

static int lard_create(struct inode *directory_inode,
		       struct dentry *directory_entry,
		       umode_t mode,
		       bool excl __attribute__((unused)))
{
	printk(KERN_INFO "lard_create called\n");
	return 0;
}

static int lard_unlink(struct inode *vfs_inode,
		       struct dentry *directory_entry)
{
	printk(KERN_INFO "lard_unlink called\n");
	return 0;
}

static int lard_mkdir(struct inode *directory_inode,
		       struct dentry *directory_entry,
		       umode_t mode)
{
	printk(KERN_INFO "lard_mkdir called\n");
	return 0;
}

static int lard_rmdir(struct inode *directory_inode,
		       struct dentry *directory_entry)
{
	printk(KERN_INFO "lard_rmdir called\n");
	return 0;
}

static int lard_rename(struct inode *old_dir,
		       struct dentry *old_dentry,
		       struct inode *new_dir,
		       struct dentry *new_deentry,
		       unsigned int flags)
{
	printk(KERN_INFO "lard_rename called\n");
	return 0;
}

static int lard_setattr(struct dentry *directory_entry,
			struct iattr *attributes)
{
	printk(KERN_INFO "lard_setattr called\n");
	return 0;
}
static int lard_getattr(const struct path *path,
			struct kstat *stat,
			u32 request_mask,
			unsigned int flags)
{
	printk(KERN_INFO "lard_getattr called\n");
	return 0;
}

const struct inode_operations lard_inode_operations = {
	.create		= lard_create,
	.lookup		= lard_lookup,
	.unlink		= lard_unlink,
	.mkdir		= lard_mkdir,
	.rmdir		= lard_rmdir,
	.rename		= lard_rename,
	.setattr	= lard_setattr,
	.getattr	= lard_getattr
};
