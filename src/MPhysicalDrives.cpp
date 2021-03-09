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


//v1.3 copyright Comine.com 20201201T1410
#include <Windows.h>
#include "MStdLib.h"
#include "MIntList.h"
#include "MBuffer.h"
#include "MString.h"
#include "MPhysicalDrives.h"


//******************************************************
//**  Module Elements
//******************************************************
static const int GMaxBufferLength=(1U<<16);
static const int GPhysicalDriveLength=13;	// =MStdStrLength("PhysicalDrive")
static const char GPhysicalDriveName[]="\\\\.\\PhysicalDrive";

//******************************************************
//**  MPhysicalDrives class
//******************************************************
void MPhysicalDrives::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MPhysicalDrives::MPhysicalDrives(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MPhysicalDrives::~MPhysicalDrives(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MPhysicalDrives::Create(void)
	{
	Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MPhysicalDrives::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MPhysicalDrives::GetPhysicalDriveNumbers(MIntList &driveints)
	{
	MBuffer blockinfo;
	if(blockinfo.Create(GMaxBufferLength)==false)
		{
		return false;
		}

	DWORD retval=QueryDosDeviceA(NULL,blockinfo.GetBuffer(),blockinfo.GetSize());
	if(retval==0)
		{
		return false;
		}

	if(driveints.Create()==false)
		{
		return false;
		}

	// Iterate over returned devices
	for(const char *p=blockinfo.GetBuffer();*p!=0;p+=MStdStrLen(p)+1)
		{
		if(MStdStrIBegins(p,"PhysicalDrive")==false) { continue; }
		const int driveint=MStdAToI(p+GPhysicalDriveLength);
		if(driveints.Add(driveint)==false)
			{
			return false;
			}
		}

	return true;
	}


/////////////////////////////////////////////////////////////
bool MPhysicalDrives::IsReadable(int driveid)
	{
	MBuffer drivename(1024);
	MStdSPrintf(drivename.GetBuffer(),drivename.GetSize()-2,"%s%d",GPhysicalDriveName,driveid);
	HANDLE hfile=CreateFileA(drivename.GetBuffer(),0,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hfile==INVALID_HANDLE_VALUE) {  return false;  }
	CloseHandle(hfile);
	return true;
	}


/////////////////////////////////////////////////////////
bool MPhysicalDrives::GetDrivePath(int driveid,MString &drivepath)
	{
	MBuffer buffer(1024);
	MStdSPrintf(buffer.GetBuffer(),buffer.GetSize()-2,"%s%d",GPhysicalDriveName,driveid);
	if(drivepath.Create(buffer.GetBuffer())==false)
		{
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////////////
bool MPhysicalDrives::GetDriveInfo(int driveid,MPhysicalDrivesInfo &driveinfo)
	{
	MString drivepath;
	if(GetDrivePath(driveid,drivepath)==false)
		{
		return false;
		}
	
	// ref http://codexpert.ro/blog/2013/10/26/get-physical-drive-serial-number-part-1/
	HANDLE hfile=CreateFileA(drivepath.Get(),0,FILE_SHARE_READ|FILE_SHARE_WRITE
			,NULL,OPEN_EXISTING,0,NULL);
	if(hfile==INVALID_HANDLE_VALUE) {  return false;  }

	// Get storage area
	STORAGE_PROPERTY_QUERY devdata;
	MStdMemZero(&devdata,sizeof(devdata) );
	devdata.PropertyId=StorageDeviceProperty;
	devdata.QueryType=PropertyStandardQuery;

	STORAGE_DESCRIPTOR_HEADER sdh={0};
	DWORD dwret=0;
	BOOL bret=DeviceIoControl(hfile,IOCTL_STORAGE_QUERY_PROPERTY,&devdata,sizeof(devdata),&sdh,sizeof(sdh),&dwret,NULL);
	if(bret==FALSE)
		{
		CloseHandle(hfile);
		return false;
		}

	MBuffer buffer(sdh.Size);
	buffer.Clear(0);

	bret=DeviceIoControl(hfile,IOCTL_STORAGE_QUERY_PROPERTY,&devdata,sizeof(devdata),buffer.GetBuffer(),buffer.GetSize(),&dwret,NULL);
	if(bret==FALSE)
		{
		CloseHandle(hfile);
		return false;
		}

	STORAGE_DEVICE_DESCRIPTOR *pdevinfo=(STORAGE_DEVICE_DESCRIPTOR *)buffer.GetBuffer();

	// Get Serial Number
	DWORD dataoffset=pdevinfo->SerialNumberOffset;
	if(dataoffset!=0)
		{
		driveinfo.SerialNumber.Create(buffer.GetBuffer()+dataoffset);
		driveinfo.SerialNumber.TrimLeft();
		driveinfo.SerialNumber.TrimRight();
		}
	else
		{
		driveinfo.SerialNumber.Create("?");
		}

	// Get Model Number
	dataoffset = pdevinfo->ProductIdOffset;
	if (dataoffset != 0)
		{
		driveinfo.Model.Create(buffer.GetBuffer() + dataoffset);
		driveinfo.Model.TrimLeft();
		driveinfo.Model.TrimRight();
		}
	else
		{
		driveinfo.Model.Create("?");
		}

	// Get Vendor
	dataoffset = pdevinfo->VendorIdOffset;
	if (dataoffset != 0)
		{
		driveinfo.Vendor.Create(buffer.GetBuffer() + dataoffset);
		driveinfo.Vendor.TrimLeft();
		driveinfo.Vendor.TrimRight();
		}
	else
		{
		driveinfo.Vendor.Create("");
		}

	// Get Drive Size
	// Ref: https://stackoverflow.com/questions/15384916/get-total-size-of-a-hard-disk-in-c-windows
	DISK_GEOMETRY geom;
	MStdMemZero(&geom,sizeof(geom) );

	DWORD retsize=0;
	bret=DeviceIoControl(hfile,IOCTL_DISK_GET_DRIVE_GEOMETRY,NULL,0,&geom,sizeof(geom)
			,&retsize,NULL);
	if(bret==FALSE)
		{
		//=Ignore Failure size
		driveinfo.DriveSize=0LL;
		CloseHandle(hfile);
		return true;
		}

	driveinfo.DriveSize = geom.Cylinders.QuadPart
				*ULONG(geom.TracksPerCylinder)
				*ULONG(geom.SectorsPerTrack)
				*ULONG(geom.BytesPerSector );

	CloseHandle(hfile);
	return true;
	}


///////////////////////////////////////////////////////
bool MPhysicalDrives::Print(void)
	{
	MIntList driveids;
	if(GetPhysicalDriveNumbers(driveids)==false)
		{
		return false;
		}

	int id;
	for(driveids.ReadReset();driveids.Read(id)==true;  )
		{
		MString drivepath;
		if(GetDrivePath(id,drivepath)==false)
			{
			return false;
			}

		MPhysicalDrivesInfo info;
		if(GetDriveInfo(id,info)==false)
			{
			return false;
			}

		MStdPrintf("%s   ",drivepath.Get());
		MStdPrintf("Model:%s   ",info.Model.Get());
		MStdPrintf("Serial:%s   ",info.SerialNumber.Get());   
		
		const double drivesize=double(info.DriveSize);
		const char *suffixbinary;
		double humanreadablesize=0;
		MStdToHumanBinary(drivesize,humanreadablesize,suffixbinary);
		MStdPrintf("Size:%0.1f %cB   ",humanreadablesize,suffixbinary[0]);

		MStdPrintf("Vendor:%s\n", info.Vendor.Get());
		}

	return true;
	}


