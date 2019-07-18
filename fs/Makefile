MODULE_NAME = lard

obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-objs := debug.o \
                       namei.o \
                       super.o

EXTRA_CFLAGS += -Werror

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
