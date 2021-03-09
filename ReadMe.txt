
This program reads and writes to physical drives on windows.

Usage Scenarios 
================

Example #1: Need to list out physical devices on Windows

	C:> MDriveReadWriteZero -l



Example #2:  Save the first 512 byte block of device to a file mbr.bin
	
	C:> MDriveReadWriteZero -drive=0 -count=1 -tofile=mbr.bin


Example #3:  Write save mbr.bin file back to drive 0

	C:> MDriveReadWriteZero -drive=0 -count=1 -todrive=mbr.bin


Example #4:  Write zeros to the first 1000 blocks(512bytes) of device 2.

	C:> MDriveReadWriteZero -drive=2 -count=1000 -writezeros

Comand 
   usage:  MDriveReadWriteZero [-?|-l] [-drive=<id> -count=<cnt>] 
              [-tofile=<file> |-todrive=<file>|-writezero]
           v1.0 copyright Comine.com

   WARNING: This program was meant to read/write/erase 
            physical drives in Windows.

       **Do not run unless you know what you are doing.**

   -l             : List out all physical device info 
   -drive=<id>    : Drive for which to write data. id=0,1,2,...
   -count=<cnt>   : count of 512 byte blocks to write/read/zero
   -tofile=<file> : read drive to file
   -todisk=<file> : write file to drive
   -writezeros    : write zeros to 512 byte blocks

   Program must be run as adminstrator to get correct permission for 
   reading and writing data from physical drives.


