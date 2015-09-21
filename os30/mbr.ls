OUTPUT_FORMAT("binary");
SECTIONS {
	. = 0x7c00;
	.text : {*(.text)}
	.data : {*(.data)}
	. = 0x7c00 + 510;
	.sign : {BYTE(0x55)}
	.sign : {BYTE(0xaa)}
}
