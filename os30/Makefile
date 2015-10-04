
ASM=gcc
CC=gcc
ASMFLAGS=-Wall -nostdlib
CFLAGS=-Wall -nostdlib -O0

IMG=os.img

QEMU=qemu-system-x86_64
# keyboard layout 'en-us' or 'jp'
QEMUOPT=-m 128 -vga std -k en-us -name "MY OS" -snapshot -cpu core2duo

SRC =main.c print.c color_palette.c put_font.c font_data.c
SRC+=dsc_tbl.c pic.c int.c keycode_encoder.c mouse.c
SRC+=fifo.c
OBJ =stage2.o asm_func.o
OBJ+=inthandler.o
OBJ+=main.o print.o color_palette.o put_font.o font_data.o
OBJ+=dsc_tbl.o pic.o int.o keycode_encoder.o mouse.o
OBJ+=fifo.o

$(IMG): mbr.bin stage2.bin
	dd if=/dev/zero of=$(IMG) bs=512 count=2880 status=none
	dd if=./mbr.bin of=$(IMG) bs=512 count=1 conv=notrunc status=none
	dd if=./stage2.bin of=$(IMG) bs=512 seek=1 conv=notrunc status=none

stage2.bin: stage2.s asm_func.s stage2.ls inthandler.s $(SRC)
	$(ASM) $(ASMFLAGS) -m32 -c stage2.s -o stage2.o
	$(ASM) $(ASMFLAGS) -m32 -c asm_func.s -o asm_func.o
	$(ASM) $(ASMFLAGS) -m32 -c inthandler.s -o inthandler.o
	$(CC) $(CFLAGS) -c -m32 $(SRC)
	ld -Tstage2.ls -melf_i386 -e after_MBR -o stage2.bin $(OBJ)

mbr.bin: mbr.s mbr.ls
	$(ASM) $(ASMFLAGS) -c mbr.s -o mbr.o
	ld -Tmbr.ls -o mbr.bin mbr.o

run: $(IMG)
	$(QEMU) $(QEMUOPT) -fda $(IMG)

clean:
	rm -f $(IMG) *.o *.bin

tag:
	ctags -R
