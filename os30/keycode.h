
#define KEYCODE_BUFFER_SIZE		32

#define KEYCODE_STATUS_SHIFT_L		0x01
#define KEYCODE_STATUS_SHIFT_R		0x02
#define KEYCODE_STATUS_CONTROL_L	0x04
#define KEYCODE_STATUS_CONTROL_R	0x08
#define KEYCODE_STATUS_ALT_L		0x10
#define KEYCODE_STATUS_ALT_R		0x20
#define KEYCODE_STATUS_WINDOWS_L	0x40
#define KEYCODE_STATUS_WINDOWS_R	0x80

/*
#define KEY_EN1						0x01
#define KEY_JA1						0x02
#define KEY_EN2						0x03
#define KEY_JA2						0x04
*/

enum {
	KEY_EN1 = 0,
	KEY_EN2 = 1,
	KEY_JA1 = 2,
	KEY_JA2 = 3,
} keyboard_layout;

typedef struct {
	unsigned char code[32];
	int len;
	/* index of buffer */
	int i_write;
	int i_read;
	
	unsigned int f_keystatus;
	/* bit
	 * 0: shift L
	 * 1: shift R
	 * 2: control L
	 * 3: control R
	 * 4: alt L
	 * 5: alt R
	 * 6: windows_key L
	 * 7: windows_key R
	 */
} KEYCODE;

void key_encoder(unsigned int);
unsigned char get_keycode(void);
char get_keycode_ascii(void);
void set_keytable(char);

