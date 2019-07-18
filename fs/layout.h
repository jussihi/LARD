#include "types.h"

#define LARD_MAGIC		0x4c415244	/* LARD */
#define LARD_SUPER_MAGIC	0x4c53424b	/* LSBK */

/**
 * First BLOB area on disk
 * Size must be aligned to 4096 bytes to conform to 4K BLOB layout.
 * bytes 511,512 must be BIOS magic 0xAA55 to allow booting on UranOS systems.
 */
typedef struct lard_boot_sector {
	u8 jmpBoot[3];
	u8 OEMName[8];			// == "KYS EBIN"
	/* LARD specific information starts here */
	u32 lardmagic;			// == LARD_MAGIC
	u8 sector_size; // 512
	u16 blob_size; // 4096
	unsigned char volumeLabel[16];
	unsigned char volumeID[10];
	u64 blobmap_offset;		// where to read in the blobmap
	BMI root_inode;			// root ino number in blobmap, should be 0
	/* LAST_ALLOCATED_BLOCK */
	BMI LAST_ALLOCATED_BLOB;	// last blobmap index that was allocated
	/* TOTAL BLOCKS */
	u64 TOTAL_BLOBS;		// Amount of indexes in blobmap
	/* FREE BLOCKS */
	u64 FREE_BLOBS;
	/* BOOTABLE */
	/* BITMAP BLOCK NUMBER */ // x * 4096
	LBO BLOBMAP_START;		// First address of BLOBMAP
	/* BLOBMAP LENGTH */
	u32 BLOBMAP_LENGTH;
	u8 padding[666];
	u16 biosmagic; // = 0xAA55;

} __attribute__ ((__packed__)) lard_boot_sector;
