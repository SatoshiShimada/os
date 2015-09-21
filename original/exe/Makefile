CC=gcc
src=exe.c

default: $(src)
	$(CC) -nostdlib -nostdinc -c exe.c -m32 -Wall
	#ld -e start -Ttext 0x7c00 -o exe *.o
	objcopy -S -O binary -j .text exe.o exe
