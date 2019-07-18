.PHONY: all clean

CC = gcc

VERSION = 0.0.1

CFLAGS += -DCONF_VERSION=\"$(VERSION)\"
CFLAGS += -I../fs/

DEP = %.h
OBJ = mklardfs.o lardebug.o
SRC = mklardfs.c lardebug.c
EXE = mklardfs lardebug

%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(EXE)

clean:
	rm -f ./*.o $(EXE)
