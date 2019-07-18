#ifndef _BLOB_H
#define _BLOB_H

#include "types.h"

#define BLOB_SIZE		4096

typedef struct BLOB_HEADER {
	BLOB_TYPE type;
	BMI parent;
	BMI child;
} __attribute__ ((__packed__)) BLOB_HEADER;

typedef struct lard_data {
	uint32_t data[128];
} __attribute__ ((__packed__)) lard_data;

typedef struct lard_inode {
	BLOB_HEADER header;
	uint64_t i_size;
	loff_t i_off;
} __attribute__ ((__packed__)) lard_inode;

typedef struct lard_directory {
} __attribute__ ((__packed__)) lard_directory;

typedef struct BLOB {
	BLOB_HEADER header;
	union {
		lard_inode inode;
		lard_directory dir;
		lard_data data;
	};
} __attribute__ ((__packed__)) BLOB;


#endif // _BLOB_H
