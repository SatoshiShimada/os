#define FAT12_FILE_INFO_READONLY	0x01
#define FAT12_FILE_INFO_HIDDEN		0x02
#define FAT12_FILE_INFO_SYSTEM		0x04
#define FAT12_FILE_INFO_NOFILE		0x08
#define FAT12_FILE_INFO_DIRECTORY	0x10

/*
 * offset: size : info
 * ---------------------
 * 0x0000: 1    : boot sector
 * 0x0200: 9    : FAT-1
 * 0x1400: 9    : FAT-2
 * 0x2600: 14   : root directory
 * 0x4200: 2849 : file
 * ---------------------
 * total: 2880 sectors
 */
#define FAT12_IMAGE_ADDR			0x8000
#define FAT12_OFFSET_MBR			0x0000
#define FAT12_OFFSET_FAT_1			0x0200
#define FAT12_OFFSET_FAT_2			0x1400
#define FAT12_OFFSET_ROOTDIR		0x2600
#define FAT12_OFFSET_FILE			0x4200

/* 32 byte */
struct FAT12_FILE {
	unsigned char  name[8];
	unsigned char  ext[3];
	unsigned char  type;
	         char  reserve;
	unsigned char  time;
	unsigned short make_time;
	unsigned short make_date;
	unsigned short last_date;
	unsigned short cluster_first;
	unsigned short write_time;
	unsigned short write_date;
	unsigned short cluster;
	unsigned int   size;
};


void get_rootdir_file(void);
