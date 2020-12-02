/*
Copyright (C) 2011-2020, Comine.com ( comine.com@gmail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- The the names of the contributors of this project may not be used to 
  endorse or promote products derived from this software without specific 
  prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
`AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


//v1.0 copyright Comine.com 20201201T2317
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MPhysicalDrives.h"
#include "MRawHardDrive.h"
#include "MFile.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MDriveReadWriteZero";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);
static bool GListDriveInfo(void);			// List out  Drive Info
static bool GWriteZeros(int driveid,const int sectorcount);	// Write Zeros to  drive
static bool GWriteToFile(int driveid, const int sectorcount,const char *filename);	// Write to file from hardrive
static bool GWriteToDrive(int driveid, const int sectorcount, const char* filename);	// Write to drive from file

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<2)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	// Check for -l argument
	if(args.CheckRemoveArg("-l")==true)
		{
		GListDriveInfo();
		return 0;
		}

	//** Get Drive ID
	const char *argvalue;
	int argindex;
	if(args.GetNameValue("-drive=",argvalue,argindex)==false )
		{
		MStdPrintf("**Unable to get -drive=<id>\n");
		return 1;
		}

	const int driveid=MStdAToI(argvalue);
	if(driveid<0 || driveid>255)
		{
		MStdPrintf("**Bad Drive ID \n");
		return 1;
		}

	args.RemoveArg(argindex);

	//** Get 512 byte Block Count
	if(args.GetNameValue("-count=",argvalue,argindex)==false )
		{
		MStdPrintf("**Unable to get -drive=<id>\n");
		return 1;
		}

	const int sectorcount=MStdAToI(argvalue);
	if(sectorcount<0)
		{
		MStdPrintf("**Bad 512 byte sector count\n");
		return 1;
		}

	args.RemoveArg(argindex);

	//** Write zeros to drive
	if(args.CheckRemoveArg("-writezeros")==true)
		{
		if(GWriteZeros(driveid,sectorcount)==false)
			{
			MStdPrintf("**Unable to write zeros to drive id=%d\n",driveid);
			return 2;
			}

		return 0;
		}

	//** Read drive data to file
	if(args.GetNameValue("-tofile=",argvalue,argindex)==true)
		{
		if(GWriteToFile(driveid,sectorcount,argvalue)==false)
			{
			MStdPrintf("**Unable to write drive id=%d to file %s\n",driveid,argvalue);
			return 3;
			}

		return 0;
		}

	//** Write file to drive
	if(args.GetNameValue("-todrive=",argvalue,argindex)==true)
		{
		if(GWriteToDrive(driveid,sectorcount,argvalue)==false)
			{
			MStdPrintf("**Unable to write file %s to drive id=%d\n",argvalue,driveid);
			return 4;
			}

		return 0;
		}

	GDisplayHelp();
	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?|-l] [-drive=<id> -count=<cnt>] \n"
				"              [-read=<fileout>|-write=<filein>|-writezero]\n"
				"           v%s copyright Comine.com\n"
				"\n"
				"   WARNING: This program was meant to read/write/erase \n"
				"            physical drives in Windows.\n"
				"\n"
				"       **Do not run unless you know what you are doing.**\n"
				"\n"
				"   -l             : List out all physical device info \n" 
				"   -drive=<id>    : Drive for which to write data. id=0,1,2,...\n"
				"   -count=<cnt>   : count of 512 byte blocks to write/read/zero\n"
				"   -tofile=<file> : read drive to file\n"
				"   -todisk=<file> : write file to drive\n"
				"   -writezeros    : write zeros to 512 byte blocks\n"
				"\n"
				"   Program must be run as adminstrator to get correct permission for \n"
				"   reading and writing data from physical drives.\n"
				,GApplicationName,GApplicationVersion);
	}


///////////////////////////////////////////////////
static bool GListDriveInfo(void)
	{
	MPhysicalDrives driveinfo;
	if(driveinfo.Create()==false)
		{
		MStdPrintf("**Unable to init system\n");
		return false;
		}

	driveinfo.Print();

	return true;
	}


//////////////////////////////////////////////////////
static bool GWriteZeros(int driveid, const int sectorcount)
	{
	MPhysicalDrives drives;
	if(drives.Create()==false)
		{
		MStdPrintf("**Unable to init system\n");
		return false;
		}

	MString drivepath;
	if(drives.GetDrivePath(driveid,drivepath)==false)
		{
		MStdPrintf("**Unable to get drive path for drive id %d\n",driveid);
		return false;
		}

	// Dummy Buffer
	MStdArray<char> zerobuffer(512);
	MStdMemZero(zerobuffer.Get(),zerobuffer.GetLength());

	MRawHardDrive rawdrive;
	if(rawdrive.Create(drivepath.Get())==false)
		{
		MStdPrintf("**Unable to open drive %s\n",drivepath.Get());
		return false;
		}

	for(int i=0;i<sectorcount;++i)
		{
		if(rawdrive.WriteSectors(zerobuffer.Get(),1)==false)
			{
			return false;
			}

		MStdPrintf("Wrote sector %d                  \r",i);
		}

	MStdPrintf("Wrote %d zeroed sectors to device %s\n",sectorcount,drivepath.Get());
	
	return true;
	}


////////////////////////////////////////////////////////
static bool GWriteToFile(int driveid, const int sectorcount, const char* filename)
	{
	MPhysicalDrives drives;
	if(drives.Create()==false)
		{
		MStdPrintf("**Unable to init system\n");
		return false;
		}

	MString drivepath;
	if(drives.GetDrivePath(driveid,drivepath)==false)
		{
		MStdPrintf("**Unable to get drive path for drive id %d\n",driveid);
		return false;
		}

	MFileOutput fout;
	if(fout.Create(filename)==false)
		{
		MStdPrintf("**Unable to open output file %s\n",filename);
		return false;	
		}

	MRawHardDrive rawdrive;
	if(rawdrive.Create(drivepath.Get())==false)
		{
		MStdPrintf("**Unable to open drive %s\n",drivepath.Get());
		return false;
		}

	MStdArray<char> buffer(512);

	for(int i=0;i<sectorcount;++i)
		{
		if(rawdrive.ReadSectors(buffer.Get(),1)!=1)
			{
			MStdPrintf("**Unable to read drive id=%d to buffer\n",driveid);
			return false;
			}

		if(fout.Write(buffer.Get(),buffer.GetLength())==false)
			{
			MStdPrintf("**Unable to write buffer data to file\n");
			return false;
			}

		MStdPrintf("Wrote sector %d to file                  \r",i);
		}

	MStdPrintf("Wrote %d sectors from drive to file %s\n",sectorcount,filename);
	
	return true;
	}


///////////////////////////////////////////////////////
static bool GWriteToDrive(int driveid, const int sectorcount, const char* filename)
	{
	MPhysicalDrives drives;
	if(drives.Create()==false)
		{
		MStdPrintf("**Unable to init system\n");
		return false;
		}

	MString drivepath;
	if(drives.GetDrivePath(driveid,drivepath)==false)
		{
		MStdPrintf("**Unable to get drive path for drive id %d\n",driveid);
		return false;
		}

	MFileInput fin;
	if(fin.Create(filename)==false)
		{
		MStdPrintf("**Unable to open input file %s\n",filename);
		return false;	
		}

	MRawHardDrive rawdrive;
	if(rawdrive.Create(drivepath.Get())==false)
		{
		MStdPrintf("**Unable to open drive %s\n",drivepath.Get());
		return false;
		}

	MStdArray<char> buffer(512);

	for(int i=0;i<sectorcount;++i)
		{
		if(fin.ReadToBuffer(buffer.Get(),buffer.GetLength())==false)
			{
			MStdPrintf("**Unable to read file to buffer\n");
			return false;
			}

		if(rawdrive.WriteSectors(buffer.Get(),1)!=1)
			{
			MStdPrintf("**Unable to write buffer to drive id=%d \n",driveid);
			return false;
			}

		MStdPrintf("Wrote sector %d to drive                  \r",i);
		}

	MStdPrintf("Wrote %d sectors from file %s to drive id=%d\n",sectorcount,filename,driveid);
	
	return true;
	}

