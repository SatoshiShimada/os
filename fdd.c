#include "asm_func.h"
#include "fdd.h"

#define DEF_FDD_WRITE_COMMAND_RETRY	500
#define DEF_FDD_MSR_RQM		0x80
#define DEF_FDD_MSR_DIO		0x40
#define DEF_PORT_FDD_COMMAND	0x03f5
#define DEF_PORT_FDD_MSR		0x03f4

int fdd_command(int command)
{
	int i;
	unsigned char msr;

	for(i = 0; i < DEF_FDD_WRITE_COMMAND_RETRY; i++) {
		msr = in_byte(DEF_PORT_FDD_MSR);
		msr = msr & (DEF_FDD_MSR_DIO | DEF_FDD_MSR_RQM);
		if(DEF_FDD_MSR_RQM == msr) {
			out_byte(DEF_PORT_FDD_COMMAND, command);
			return DEF_FDD_OK;
		}
	}
	return DEF_FDD_ERROR;
}

int read_data_from_fdd(int drive, int head, int track, int sector)
{
	int i;
	int status;
	int parameter;

	status = fdd_command(FDC_COMMAND_READ_DATA);

	parameter = (int)(head | drive);
	status |= fdd_command(parameter);
	status |= fdd_command(track);
	status |= fdd_command(head >> 2);
	if(DEF_FDD_SECTORS_PER_TRACK < sector) {
		sector = DEF_FDD_SECTORS_PER_TRACK;
	}
	status |= fdd_command(sector);
	status |= fdd_command(FDD_COMMAND_SECTOR_SIZE_512);
	status |= fdd_command(DEF_FDD_SECTORS_PER_TRACK);
	status |= fdd_command(FDD_COMMAND_GAP3_SIZE_3_5);
	status |= fdd_command(DEF_FDD_COMMAND_PRM_DTL);

	if(status == DEF_FDD_OK) {
		fdd_wait();
		for(i = 0; i < DEF_FDD_NUM_STATUS; i++) {
			//status |= read1
		}
	}
	return 0;
}
