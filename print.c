/* Interger to Ascii */
int itoa(char *str, unsigned int value)
{
	char buf[30];
	int i;

	buf[0] = '\0';

	for(i = 1; ; i++) {
		buf[i] = (value % 10) + '0';
		value = value / 10;
		if(value == 0) break;
	}
	for(;;) {
		*str = buf[i];
		if(buf[i] == '\0') break;
		str++;
		i--;
	}
	return 0;
}

/* Interger to Ascii */
int int_to_ascii(char *str, unsigned int value)
{
	char buf[30];
	char *p = buf + 29;

	*p = '\0';
	p--;

	for(;;) {
		*p = (value % 10) + '0';
		value = value / 10;
		if(value == 0) break;
		p--;
	}

	while(*p != '\0') {
		*str = *p;
		str++;
		p++;
	}
	*str = '\0';

	return 0;
}

char *strcat(char *dist, const char *src)
{
	int i;

	while(*dist != '\0') dist++;

	i = 0;
	for(;;) {
		*dist = src[i];
		if(*dist == '\0') break;
		i++;
		dist++;
	}

	return dist;
}

int strcmp(const char *str1, const char *str2)
{
	int i;

	if(str1[0] == str2[0] && str1[0] == '\0') return 0;

	i = -1;
	do {
		i++;
		if(str1[i] != str2[i]) {
			if(str1[i] > str2[i]) {
				return 1;
			} else {
				return -1;
			}
		}
	} while((str1[i] != '\0') && (str2[i] != '\0'));

	return 0;
}

void *memset(void *buf, int ch, unsigned int size)
{
	unsigned char *dist = (unsigned char *)buf;
	int i;

	for(i = 0; i < size; i++) {
		dist[i] = (unsigned char)ch;
	}

	return buf;
}

void *memcpy(void *buf1, const void *buf2, unsigned int size)
{
	int i;

	for(i = 0; i < size; i++) {
		*(unsigned char *)(buf1 + i) = *(unsigned char *)(buf2 + i);
	}

	return buf1;
}
