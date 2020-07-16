/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
void ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int myoffset, temp=0, ret;

	while (offset_begin + offset < offset_end)
	{
		// Your code here
		// error occurred, then panic.
		if ((syscall_write_dev(&diskno, 0x13000010, 4)) != 0)
		{
			user_panic("ide_read_error!\n");
		}
		myoffset = offset_begin + offset;
		if ((syscall_write_dev(&myoffset, 0x13000000, 4)) != 0)
		{
			user_panic("ide_read_error!\n");
		}
		//temp = 0;
		if ((syscall_write_dev(&temp, 0x13000020, 4)) != 0)
		{
			user_panic("ide_read_error!\n");
		}
		if ((syscall_read_dev(&ret, 0x13000030, 4)) != 0)
		{
			user_panic("ide_read_error!\n");
		}
		if (ret == 0) user_panic("ide_read_error!\n");
		
		if ((syscall_read_dev(dst + offset, 0x13004000, 512)) != 0) {
			user_panic("ide_read_error!\n");
		}
		offset += 0x200;
	}
}

// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
void ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
	// Your code here
	// int offset_begin = ;
	// int offset_end = ;
	// int offset = ;
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int myoffset, temp, ret=0;

	// DO NOT DELETE WRITEF !!!
	writef("diskno: %d\n", diskno);

	while (offset_begin + offset < offset_end)
	{
		// Your code here
		// error occurred, then panic.
		if ((syscall_write_dev(&diskno, 0x13000010, 4)) != 0)
		{
			user_panic("ide_write_error!\n");
		}
		myoffset = offset_begin + offset;
		if ((syscall_write_dev(&myoffset, 0x13000000, 4)) != 0)
		{
			user_panic("ide_write_error!\n");
		}
		if ((syscall_write_dev(src + offset, 0x13004000, 512)) != 0) {
			user_panic("ide_write_error!\n");
		}
		temp = 1;
		if ((syscall_write_dev(&temp, 0x13000020, 4)) != 0)
		{
			user_panic("ide_write_error!\n");
		}
		if ((syscall_read_dev(&ret, 0x13000030, 4)) != 0)
		{
			user_panic("ide_write_error!\n");
		}
		if (ret == 0) user_panic("ide_write_error!\n");

		offset += 0x200;
	}

	// while ( < ) {
	// copy data from source array to disk buffer.

	// if error occur, then panic.
	// }
}
