# MBR of my os.
# filesystem: FAT12 floppy disk
# MBR: 512byte

# FAT12 sector structre
# sector: 
# 1: boot sector
# 9: FAT
# 9: FAT (sub)
# 14: root directory
# 2849: file

.text

# this program run on realmode(16 bits)
.code16

mbr_start:

# BIOS parameter blocks of FAT12
jmp		entry
		nop

.ascii	"MyOS    " # OEM name (8 byte)
.word	0x0200
.byte	0x01
.word	0x0001
.byte	0x02
.word	0x00e0
.word	0x0b40
.byte	0xf0
.word	0x0009
.word	0x0012
.word	0x0002
.int	0x00000000
.int	0x00000000

.byte	0x00
.byte	0x00
.byte	0x29
.int	0xffffffff
.ascii	"MyOS       " # volume label (11 byte)
.ascii	"FAT12   " # FAT type (8 byte)

after_BPB:
# entry
entry:

registers_init:
	xor		%ax, %ax
	mov		%ax, %ds
	mov		%ax, %es
	mov		%ax, %fs
	mov		%ax, %gs
	mov		%ax, %ss
	mov		$0x81ff, %sp

sector_read_from_disk_to_memory:
	# sector read BIOS call with INT 0x13
	# call with:
	# AH = 0x03
	# AL = read sector count
	# CH = track number (low 8bit in total 10 bit)
	# CL = sector number (low 6bit & high 2bit track number in total 10 bit)
	# DH = head number
	# DL = drive number
	# ES:BX = data store buffer address on memory
	# result:
	# CF = 0x00 on success, or error number on error
	# AH = error code (on success is 0x00)
	# AL = readed sector count
	mov		$0x0820, %bx
	mov		%bx, %es
	mov		$0, %ch
	mov		$2, %cl
	mov		$0, %dh
read_loop:
	mov		$0, %si
read_retry:
	mov		$0x02, %ah
	mov		$1, %al
	mov		$0, %bx
	mov		$0, %dl
	int		$0x13
	jnc		read_next
	add		$1, %si
	cmp		$5, %si
	jae		read_error
	mov		$0, %ah
	mov		$0, %dl
	int		$0x13
	jmp		read_retry
read_next:
	mov		%es, %ax
	add		$512/16, %ax
	mov		%ax, %es
	add		$1, %cl
	cmp		$18, %cl
	jbe		read_loop
	mov		$1, %cl
	add		$1, %dh
	cmp		$2, %dh
	jb		read_loop
	mov		$0, %dh
	add		$1, %ch
	cmp		$10, %ch
	jb		read_loop

print_read_success_message:
	mov		$message_boot_success, %si
	call	print_message
	jmp		end

read_error:
	mov		$message_boot_error, %si
	call	print_message
	jmp		end

# message print function
print_message:
	mov		(%si), %al
	add		$1, %si
	cmp		$0, %al
	je		print_fin
	mov		$0x0e, %ah
	mov		$15, %bx
	int		$0x10
	jmp		print_message
print_fin:
	ret

end:
	#jmp		0x8200
	jmp		0xc200

message_boot_success:
	.string	"success\r\n"
message_boot_error:
	.string	"read error\r\n"

# bootsector enable signature
#. = mbr_start + 510
#.byte	0x55
#.byte	0xaa
