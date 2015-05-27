
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fin, *fout;
	char buf[1024];
	char output[1024];
	int i, j;

	fin = fopen("../font_16x16.txt", "r");
	if(!fin) return -1;
	fout = fopen("font_16x16.bin", "w");
	if(!fout) return -1;

	fprintf(fout, "char font = {\n");

	do {
		fgets(buf, sizeof(buf), fin);
		if(buf[0] == '!') break;

		output[0] = 0;
		output[1] = 0;

		for(i = 0, j = 0; i < 16; i++) {
			if(i == 8) j++;
			if(buf[i] == '@') {
				output[j] |= (1 << (i % 8));
			} else if(buf[i] == '.') {
				output[j] &= ~(1 << (i % 8));
			}
		}

		sprintf(buf, "%x, %x,\n", output[0], output[1]);
		fprintf(fout, "%s", buf);

	} while(!feof(fin));

	fprintf(fout, "};\n");

	fclose(fin);
	fclose(fout);

	return 0;
}
