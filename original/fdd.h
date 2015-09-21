
#define DEF_PORT_FDC0_COMMAND		0x03F5
#define DEF_PORT_FDC0_MAIN_STATUS_REGISTER		0x03F4

#define DEF_FDC_MSR_RQM		0x80

int read_data_fdd(int, int, int, int);
int fdc0_init(void);
int fdd_command(unsigned char);
int read_fdc0_main_status_register(void);
