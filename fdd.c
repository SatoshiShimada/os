#include "fdd.h"
#include "asm_func.h"

#define FD_COMMAND_SECTOR_SIZE_512		2
#define FDD_SECTORS_PER_TRACK			18
#define FD_COMMAND_GAP3_SIZE_3_5inch	27
/*
 * read data from flopy disk drive0
 *
 * read data command (0x06)
 * 0: 0x46
 * 1: head, drive
 * 2: cilinder number
 * 3: head number
 * 4: sector number
 * 5: sector size
 * 6: track length (sector count per a tarck)
 * 7: 
 * 8: data length
 */
int read_data_fdd(int drive, int head, int track, int sector)
{
	/* drive range: 0-3 */
	/* head range: 0-1 */
	/* sector range: 0-79 */
	if(drive < 0 || drive > 3) return 1;
	if(head < 0 || head > 1) return 1;

	fdd_command(0x40 | 0x06);
	fdd_command((head << 4) | drive);
	fdd_command(track);
	fdd_command(head);
	fdd_command(sector);
	fdd_command(FD_COMMAND_SECTOR_SIZE_512);
	fdd_command(FDD_SECTORS_PER_TRACK);
	fdd_command(FD_COMMAND_GAP3_SIZE_3_5inch);
	fdd_command(0xff);
	return 0;
}

int fdc0_init(void)
{
	/* send 'recalibra' command to flopy disk controller 0 */
	if(read_fdc0_main_status_register() & DEF_FDC_MSR_RQM) {
		fdd_command(0x07);
		fdd_command(0x00);
		return 0;
	}
	*(char *)(0xb8000) = 'm';
	return 1;
}

int fdd_command(unsigned char command)
{
	if((read_fdc0_main_status_register() & DEF_FDC_MSR_RQM)) {
		out_byte(DEF_PORT_FDC0_COMMAND, command);
		return 0;
	}
	return 1;
}

int
read_fdc0_main_status_register(void)
{
	return (int)(in_byte(DEF_PORT_FDC0_MAIN_STATUS_REGISTER));
}
