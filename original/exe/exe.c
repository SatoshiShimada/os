
void main(void)
{
	char *vram = (char *)0xb8000;
	char buf[] = { "Hello, world     " };
	char *str;
	str = buf;

	for(; *str != '\0'; str++) {
		*vram = *str;
		vram++;
		*vram = 0xf;
		vram++;
	}
	return;
}
