
#include "fat12.h"

/* 14sectors * 512 byte / 32 byte  = 224 files */
#define ROOTDIR_MAX_FILE		((14 * 512) / 32)

int filecount;
struct FAT12_FILE file[ROOTDIR_MAX_FILE];

void get_rootdir_file(void)
{
	int i = 0;
	struct FAT12_FILE *file_buf;

	file_buf = (struct FAT12_FILE *)0xa600;
	file_buf = (struct FAT12_FILE *)(FAT12_IMAGE_ADDR + FAT12_OFFSET_ROOTDIR);

	for(i = 0; i < ROOTDIR_MAX_FILE; i++) {
		if(file_buf[i].cluster == 0) break;
		file[i] = file_buf[i];
	}

	filecount = i;

	return;
}
