
CC=gcc
CFLAGS=-Wall -nostdlib -O0

IMG=os.img

QEMU=qemu-system-x86_64
QEMUOPT=-m 1024 -vga std


SRCFILE= \
stage2.s main.c put_font.c test_processor.c \
asm_func.s memory_test.c print.c idt.c pic.c \
shell.c memory.c fat12.c fdd2.c \
put_font_11B.c put_font_default.c \
font_data.c \
./interrupt_handler/keycode_encoder.c \
./interrupt_device/timer.c

OBJFILE= \
stage2.o main.o put_font.o asm_func.o test_processor.o \
memory_test.o print.o idt.o pic.o timer.o keycode_encoder.o \
shell.o memory.o fat12.o fdd2.o \
put_font_11B.o put_font_default.o \
font_data.o \
handler20.o handler21.o handler26.o


# make rule

$(IMG): mbr.bin stage2.bin
	mformat -f 1440 -C -B mbr.bin -i $(IMG) ::
	mcopy stage2.bin -i $(IMG) ::
	mcopy mbr.ls -i $(IMG) ::
	mcopy main.c -i $(IMG) ::
	#mcopy fat.txt -i $(IMG) ::
	mcopy exe/exe -i $(IMG) ::

run: $(IMG)
	$(QEMU) $(QEMUOPT) -fda $(IMG)

clean:
	rm -f $(IMG) *.o *.bin

mbr.bin: mbr.s mbr.ls
	$(CC) $(CFLAGS) -c mbr.s -o mbr.o
	ld -Tmbr.ls -o mbr.bin mbr.o

stage2.bin: stage2.ls $(SRCFILE)
	$(CC) $(CFLAGS) -m32 -c stage2.s -o stage2.o
	$(CC) $(CFLAGS) -m32 -c asm_func.s -o asm_func.o
	$(CC) $(CFLAGS) -m32 -c ./interrupt_handler/handler20.s -o handler20.o
	$(CC) $(CFLAGS) -m32 -c ./interrupt_handler/handler21.s -o handler21.o
	$(CC) $(CFLAGS) -m32 -c ./interrupt_handler/handler26.s -o handler26.o
	$(CC) $(CFLAGS) -m32 -c $(SRCFILE)
	ld -Tstage2.ls -melf_i386 -e after_MBR -o stage2.bin $(OBJFILE)

