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


//v1.3 copyright Comine.com 20201127F1009
#include <windows.h>
#include "MStdLib.h"
#include "MRawHardDrive.h"


//******************************************************
//**  MRawHardDrive class
//******************************************************
void MRawHardDrive::ClearObject(void)
	{
	mhDrive=INVALID_HANDLE_VALUE;
	memset(&mDriveInfo,0,sizeof(mDriveInfo) );
	}


/////////////////////////////////////////////////
MRawHardDrive::MRawHardDrive(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MRawHardDrive::~MRawHardDrive(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MRawHardDrive::Create(const char *drive)
	{
	Destroy();

	// Open Drive
	mhDrive=CreateFileA(drive,GENERIC_READ|GENERIC_WRITE
			,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING
			,0,NULL);
	if(mhDrive==INVALID_HANDLE_VALUE)
		{
		Destroy();  
		return false;
		}

	// Get Drive Info
	DWORD bytecount=0;
	BOOL bret=DeviceIoControl(mhDrive,IOCTL_DISK_GET_DRIVE_GEOMETRY
			,NULL,0,&mDriveInfo,sizeof(mDriveInfo),&bytecount,NULL);
	if(bret==FALSE)
		{
		Destroy();  return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MRawHardDrive::Destroy(void)
	{
	if(mhDrive!=INVALID_HANDLE_VALUE) { CloseHandle(mhDrive);  }
	ClearObject();  return true;
	}


////////////////////////////////////////////////
int MRawHardDrive::GetCylinders(void)
	{
	return (int)mDriveInfo.Cylinders.LowPart;
	}


////////////////////////////////////////////////
int MRawHardDrive::GetTracksPerCylinder(void)
	{
	return mDriveInfo.TracksPerCylinder;
	}


////////////////////////////////////////////////
int MRawHardDrive::GetSectorsPerTrack(void)
	{
	return mDriveInfo.SectorsPerTrack;
	}


////////////////////////////////////////////////
int MRawHardDrive::GetBytesPerSector(void)
	{
	return mDriveInfo.BytesPerSector;
	}


/////////////////////////////////////////////////
bool MRawHardDrive::MoveToSector(int sectnum) // Move to a sector 0-first
	{
	// Perform Calculations 
	__int64 sectoroffset=sectnum;
	sectoroffset*=512;
	LARGE_INTEGER li;  
	li.QuadPart=sectoroffset;

	// SetPointer
	if(SetFilePointerEx(mhDrive,li,NULL,FILE_BEGIN)==FALSE)
		{
		return false;
		}
	
	return true;
	}


/////////////////////////////////////////////////
int MRawHardDrive::GetCurrentSector(void)  // returns Current Sector Number 0-first
	{
	// Get File Size
	LARGE_INTEGER zerooffset;
	zerooffset.QuadPart=0;

	LARGE_INTEGER sectoroffset;
	sectoroffset.QuadPart=0;

	if(SetFilePointerEx(mhDrive,zerooffset,&sectoroffset,FILE_CURRENT)==FALSE)
		{
		return 0;
		}

	return (int)(sectoroffset.QuadPart>>9);
	}


///////////////////////////////////////////////
int MRawHardDrive::ReadSectors(char *buffer,int sectorcount) //=count of sectors read
	{
	BOOL bret;
	DWORD readamount=0;
	bret=ReadFile(mhDrive,buffer,((DWORD)sectorcount)*((DWORD)512),&readamount,NULL);
	if(bret==FALSE)
		{
		return 0;
		}

	if(readamount!=512U*sectorcount)
		{
		return (int)(readamount/512);
		}

	return sectorcount;
	}


///////////////////////////////////////////////
int MRawHardDrive::WriteSectors(const char *buffer,int sectorcount)
	{
	BOOL bret;
	DWORD writeamount=0;
	bret=WriteFile(mhDrive,buffer,((DWORD)sectorcount)*((DWORD)512),&writeamount,NULL);
	if(bret==FALSE)
		{
		return 0;
		}

	if(writeamount!=512U*sectorcount)
		{
		return (int)(writeamount/512);
		}

	return sectorcount;
	}

