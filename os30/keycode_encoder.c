#include "keycode.h"

extern KEYCODE keycode;

/* =========================================================== */
/* scan code set 1 */
static char keytable1_ja[] = {
	 0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '^',  0 ,  0 , 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
	'O', 'P', '@', '[',  0 ,  0 , 'A', 'S', 'D', 'F', 'G', 'H',
	'J', 'K', 'L', ';', ':',  0 ,  0 , ']', 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,  0 ,
	 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , '7',
	'8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};
static char keytable1_ja_shift[] = {
};
static char keytable1_en[] = {
	 0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=','\b','\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
	'o', 'p', '[', ']','\n',  0 , 'a', 's', 'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';','\'', '`',  0 ,'\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,  0 ,
	 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , '7',
	'8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};
static char keytable1_en_shift[] = {
	 0 ,  0 , '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
	'_', '+','\b','\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
	'O', 'P', '{', '}','\n',  0 , 'A', 'S', 'D', 'F', 'G', 'H',
	'J', 'K', 'L', ':','\"', '~',  0 , '|', 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', '<', '>', '?',  0 , '*',  0 , ' ',  0 ,  0 ,
	 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , '7',
	'8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};
/* scan code set 2 */
static char keytable2_en[] = {
};
static char keytable2_en_shift[] = {
};
static char keytable2_ja[] = {
};
static char keytable2_ja_shift[] = {
};

static char *keytable, *keytable_shift;
/* =========================================================== */

void key_encoder(unsigned int code)
{
	if(keycode.len >= KEYCODE_BUFFER_SIZE) return;

	keycode.code[keycode.i_write] = (unsigned char)code;
	keycode.i_write++;
	keycode.len++;

	if(keycode.i_write == KEYCODE_BUFFER_SIZE) keycode.i_write = 0;

	return;
}

unsigned char get_keycode(void)
{
	unsigned char ret;

	if(keycode.len == 0) return 0;

	ret = keycode.code[keycode.i_read];
	keycode.i_read++;
	if(keycode.i_read == KEYCODE_BUFFER_SIZE) keycode.i_read = 0;
	keycode.len--;

	return ret;
}

void set_keytable(char keytype)
{
	switch(keytype) {
	case KEY_EN1:
		keytable = keytable1_en;
		keytable_shift = keytable1_en_shift;
		break;
	case KEY_EN2:
		keytable = keytable2_en;
		keytable_shift = keytable2_en_shift;
		break;
	case KEY_JA1:
		keytable = keytable1_ja;
		keytable_shift = keytable1_ja_shift;
		break;
	case KEY_JA2:
		keytable = keytable2_ja;
		keytable_shift = keytable2_ja_shift;
		break;
	default:	
		keytable = keytable1_en;
		keytable_shift = keytable1_en_shift;
		break;
	}
	return;
}

char get_keycode_ascii(void)
{
	unsigned char code;
	char key;

	code = get_keycode();
	if(code == 0) return 0;
	if(code >= 0x80) { /* leave key */
		switch(code - 0x80) {
		case 0x2a: /* left shift */
			keycode.f_keystatus &= (~KEYCODE_STATUS_SHIFT_L);
			break;
		case 0x36:
			keycode.f_keystatus &= (~KEYCODE_STATUS_SHIFT_R);
			break;
		}
		return 0;
	}

	switch(code) {
	case 0x01: /* escape */
		break;
	case 0x2a: /* left shift */
		keycode.f_keystatus |= KEYCODE_STATUS_SHIFT_L;
		break;
	case 0x1d: /* left control */
		break;
	case 0x38: /* left alt */
		break;
	case 0x36: /* right shift */
		keycode.f_keystatus |= KEYCODE_STATUS_SHIFT_R;
		break;
	}
	
	if((keycode.f_keystatus &
		(KEYCODE_STATUS_SHIFT_L | KEYCODE_STATUS_SHIFT_R)) != 0)
	{
		key = keytable_shift[code];
	} else {
		key = keytable[code];
	}

	return key;
}

