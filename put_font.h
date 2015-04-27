#define X_CHAR_COUNT	80
#define Y_CHAR_COUNT	25
/*
 * put character to screen
 * target: screen mode 3+(text, 16 colors, 80x25, VRAM:0xb8000)
 *
 * vram: 0x000b8000 - 0x000bffff
 *
 * one character 2 byte
 *
 * +---+---+------------------------------+
 * Byte Bits fucntions
 * +---+---+------------------------------+
 * |   | 15| Character code               |
 * | 1 | : |                              |
 * |   | 8 |                              |
 * |---+   +                              +
 * |   | 7 | brink or luminosity enable   |
 * |   +   +                              +
 * |   | 6 | Background color             |
 * |   | 5 | 6:Red, 5:Green, 4:Blue       |
 * |   | 4 |                              |
 * | 2 +   +                              +
 * |   | 3 | brightness or font type      |
 * |   +   +                              +
 * |   | 2 | Foreground color             |
 * |   | 1 | 2:Red, 1:Green, 0:Blue       |
 * |   | 0 |                              |
 * +---+---+------------------------------+
 *
 */
#define	COLOR_BLACK			0x00
#define	COLOR_BLUE			0x01
#define	COLOR_GREEN			0x02
#define	COLOR_CYAN			0x03
#define	COLOR_RED			0x04
#define	COLOR_MAGENTA		0x05
#define	COLOR_BROWN			0x06
#define	COLOR_LIGHTGRAY		0x07
#define	COLOR_DARKGRAY		0x08
#define	COLOR_LIGHTBLUE		0x09
#define	COLOR_LIGHTGREEN	0x0a
#define	COLOR_LIGHTCYAN		0x0b
#define	COLOR_LIGHTRED		0x0c
#define	COLOR_LIGHTMAGENTA	0x0d
#define	COLOR_LIGHTBROWN	0x0e
#define	COLOR_WHITE			0x0f

int put_font(char, int, int, int, int);
int puts_position(char *, int, int);
int puts(char *);
int init_screen(void);
