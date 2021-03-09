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
#ifndef MRawHardDrive_h
#define MRawHardDrive_h

////////////////////////////////////////////////////
#include <windows.h>
#include "MStdLib.h"

//******************************************************
//**  MRawHardDrive class
//******************************************************
class MRawHardDrive
	{
	HANDLE mhDrive;
	DISK_GEOMETRY mDriveInfo;

	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MRawHardDrive(void);
	~MRawHardDrive(void);
	bool Create(const char *drive="\\\\.\\PhysicalDrive0");
	bool Destroy(void);
	int GetCylinders(void);
	int GetTracksPerCylinder(void);
	int GetSectorsPerTrack(void);
	int GetBytesPerSector(void);
	bool MoveToSector(int sectornumber); // Move to a sector 0-first
	int GetCurrentSector(void);  // returns Current Sector Number 0-first
	int ReadSectors(char *buffer,int sectorcount); //=count of sectors read
	int WriteSectors(const char *buffer,int sectorcount);//==count of sectors written
	};

#endif // MRawHardDrive_h

