#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "blob.h"
#include "types.h"

#define EXEC_NAME "lardebug"

int main(int argc, char **argv) {
	printf("%s - version: %s\n",EXEC_NAME, CONF_VERSION);
	return 0;
}
