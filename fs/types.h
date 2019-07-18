#ifndef _TYPES_H
#define _TYPES_H

/**
 * Portable type definitions when compiling for UranOS
 */

/* Linux kernel typedefs */
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

/* BLOB specific types */
typedef uint8_t BLOB_TYPE;
enum {
	BLOB_DATA = 0x0,
	BLOB_FILE = 0x1,
	BLOB_DIR  = 0x2
};

/**
 * LARD specific types
 * LBO - Logical BLOB Offset, unsigned 64 bytes, start of disk --> offset
 * VBO - Virtual BLOB Offset, unsigned 64 bytes, relative start offset --> offset
 * BMI - BLOBMAP Index, unsigned 32 bytes, index number in the BLOBMAP
 */
typedef u64 LBO;
typedef u64 VBO;
typedef u32 BMI;

#endif // _TYPES_H
