#include "print.h"
#include "put_font.h"
#include "memory.h"
#include "shell.h"
#include "fat12.h"

extern unsigned int memory_total;
extern int filecount;
extern struct FAT12_FILE file[];

int execute_file(void);

int do_command(const char *command)
{
	if(!strcmp(command, "memory")) {
		print_memory_size();
	} else if(!strcmp(command, "free")) {
		print_memory_free();
	} else if(!strcmp(command, "ls")) {
		print_rootdir_file();
	} else if(!strcmp(command, "cat")) {
		view_file_text();
	} else if(!strcmp(command, "exe")) {
		execute_file();
	} else if(!strcmp(command, "help")) {
		puts("command:\n");
		puts("memory, free, ls, cat, help, hello\n");
	} else if(!strcmp(command, "hello")) {
		puts("Hello! MyOS world\n");
	} else {

		puts("Unknown command\n");
	}

	return 0;
}

int print_memory_size(void)
{
	char buf[20];

	puts("memory: ");
	int_to_ascii(buf, memory_total / (1024 * 1024));
	puts(buf);
	puts("MB\n");

	return 0;
}

int print_memory_free(void)
{
	char buf[20];
	int free;

	puts("free: ");
	free = get_memory_free_size();
	int_to_ascii(buf, free / 1024);
	strcat(buf, "KB\n");
	puts(buf);

	return 0;
}

int print_rootdir_file(void)
{
	int i;
	int s;
	char buf[20];

	int_to_ascii(buf, filecount);
	puts("file: ");
	puts(buf);
	puts("\n");
	for(i = 0; i < filecount; i++) {
		memcpy(buf, file[i].name, 8);
		memcpy(buf + 8, file[i].ext, 3);
		memcpy(buf + 11, "\0", 1);
		puts(buf);
		s = (int)file[i].size;
		int_to_ascii(buf, s);
		puts(" size :");
		puts(buf);
		puts("\n");
	}

	return 0;
}

int execute_file(void)
{
	char *p;
	char buf[1000];
	int i = 3; /* exe/exe */
	int c;
	void (*func)(void);

	p = (char *)(file[i].cluster * 512 + 0x3e00 + FAT12_IMAGE_ADDR); 
	for(c = 0; c < file[i].size; c++) {
		buf[c] = p[c];
	}
	func = (void *)buf;
	(*func)();

	return 0;
}

int view_file_text(void)
{
	char *p;
	char buf[2];
	int i = 3; /* README */
	int c;

	p = (char *)(file[i].cluster * 512 + 0x3e00 + FAT12_IMAGE_ADDR); 
	buf[1] = '\0';
	for(c = 0; c < file[i].size; c++) {
		buf[0] = p[c];
		puts(buf);
	}

	return 0;
}
