
ASM=gcc
CC=gcc
ASMFLAGS=-Wall -nostdlib
CFLAGS=-Wall -nostdlib -O0

IMG=os.img

QEMU=qemu-system-x86_64
# keyboard layout 'en-us' or 'jp'
QEMUOPT=-m 128 -vga std -k en-us -name "MY OS" -snapshot -cpu core2duo

SRC=main.c print.c color_palette.c
OBJ=main.o print.o color_palette.o asm_func.o 

default: mbr.bin stage2.bin
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=./mbr.bin of=$(IMG) bs=512 count=1 conv=notrunc
	dd if=./stage2.bin of=$(IMG) bs=512 seek=1 conv=notrunc

stage2.bin: stage2.s asm_func.s stage2.ls $(SRc)
	$(ASM) $(ASMFLAGS) -m32 -c stage2.s -o stage2.o
	$(ASM) $(ASMFLAGS) -m32 -c asm_func.s -o asm_func.o
	$(CC) $(CFLAGS) -c -m32 $(SRC)
	ld -Tstage2.ls -melf_i386 -e after_MBR -o stage2.bin stage2.o $(OBJ)

mbr.bin: mbr.s mbr.ls
	$(ASM) $(ASMFLAGS) -c mbr.s -o mbr.o
	ld -Tmbr.ls -o mbr.bin mbr.o

run:
	$(QEMU) $(QEMUOPT) -fda $(IMG)

clean:
	rm -f $(IMG) *.o *.bin

tag:
	ctags -R
