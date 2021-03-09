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


//v2.2 copyright Comine.com 20180217S0941
#include "MStdLib.h"
#include "MString.h"
#include "MBuffer.h"


//***********************************************************
//* Module Elements
//***********************************************************
static char GTempChar=0;


////////////////////////////////////////////////////////
static bool GMemCompare(const char *range1,const char *range2,int length)
	{	int i;
	for(i=0;i<length;++i)
		{
		if(range1[i]!=range2[i]) { return false; }
		}

	return true;
	}


////////////////////////////////////////////////////////
static bool GMemICompare(const char *range1,const char *range2,int length)
	{	int i;
	for(i=0;i<length;++i)
		{
		if( MStdToLower(range1[i]) != MStdToLower(range2[i]) )
			{ return false; }
		}

	return true;
	}


//***********************************************************
//* MBuffer Class
//***********************************************************
void MBuffer::ClearObject(void)
	{
	mSize=0;  mBuffer=0;
	}

//////////////////////////////////////////////
MBuffer::MBuffer(void)
	{  ClearObject();  }


//////////////////////////////////////////////
MBuffer::MBuffer(int size)
	{
	ClearObject();
	if(Create(size)==false)
		{
		return;
		}	
	}


//////////////////////////////////////////////
MBuffer::MBuffer(const MBuffer &ref)
	{
	ClearObject();
	if(Create(ref)==false)
		{
		return;
		}
	}


/////////////////////////////////////////////
MBuffer::~MBuffer(void)
	{  Destroy();  }


/////////////////////////////////////////////
bool MBuffer::Create(int size)
	{
	if(size<=0)
		{
		Destroy();
		return false;
		}

	Destroy();

	mBuffer=new(std::nothrow) char[size];
	if(mBuffer==NULL)
		{
		Destroy();
		return false;
		}

	mSize=size;
	return true;
	}


/////////////////////////////////////////////
bool MBuffer::Create(const MBuffer &ref)
	{
	bool ret=Create(((MBuffer &)ref).GetSize());
	if(ret==false) { return false; }

	// Copy the buffer to local buffer
	MStdMemCpy(mBuffer,ref.mBuffer,mSize);

	return true;
	}


/////////////////////////////////////////////
bool MBuffer::Destroy(void)
	{
	mSize=0;
	if(mBuffer!=0)
		{
		delete[] mBuffer;
		mBuffer=0;
		}
	
	ClearObject();
	return true;
	}


/////////////////////////////////////////////
char *MBuffer::GetBuffer(void) {  return mBuffer;  }


/////////////////////////////////////////////
wchar_t *MBuffer::GetWideBuffer(void) { return (wchar_t*)mBuffer; }

////////////////////////////////////////////
char *MBuffer::operator()(void) { return GetBuffer(); }


/////////////////////////////////////////////
MBuffer::operator char *(void){  return GetBuffer(); }


/////////////////////////////////////////////
int MBuffer::GetSize(void) {  return mSize; }


/////////////////////////////////////////////
bool MBuffer::SetString(const char *string)
	{
	int length=MStdStrLen(string)+1;
	if(length>mSize)
		{
		return false;
		}

	MStdStrCpy(mBuffer,string);
	return true;
	}


///////////////////////////////////////////////
bool MBuffer::SetString(const wchar_t *string)		// Set a known string
	{
	int length=2*MString::Length(string)+2;
	if(length>mSize)
		{
		return false;
		}

	MString::Copy((wchar_t*)mBuffer,string);
	return true;	
	}

/////////////////////////////////////////////
bool MBuffer::SetData(void *data,int length)
	{
	if(length>mSize)
		{
		return false;
		}

	MStdMemCpy(mBuffer,data,length);
	return true;
	}


//////////////////////////////////////////////
char &MBuffer::operator [](int index)
	{
	if(index<0 || index>=mSize)
		{
		return GTempChar;
		}
	return mBuffer[index];
	}


//////////////////////////////////////////////
bool MBuffer::StringClear(void) // sets ""
	{
	mBuffer[0]=0;  mBuffer[1]=0; // For UniCode
	return true;
	}


//////////////////////////////////////////////
bool MBuffer::StringAppend(const char *string)
	{
	MStdStrCat(mBuffer,mSize,string);
	return true;
	}


///////////////////////////////////////////////
bool MBuffer::CharAppend(char data)
	{
	for(int i=0;i<mSize-1;++i)
		{
		if(mBuffer[i]==0)
			{
			mBuffer[i]=data;
			mBuffer[i+1]=0;
			return true;
			}
		}
	
	return false;
	}


////////////////////////////////////////////////////
bool MBuffer::StringPrepend(const char *str)
	{
	MStdAssert(str!=0);
	const int strlength=GetStringLength();
	const int newstrlength=MStdStrLen(str);
	if(strlength+newstrlength>=mSize)
		{
		return false;
		}

	for(int i=strlength;i>=0;--i)
		{
		mBuffer[i+newstrlength] = mBuffer[i];
		}

	for(int i=0;i<newstrlength;++i)
		{
		mBuffer[i] = str[i];
		}
	
	return true;
	}


////////////////////////////////////////////////////
bool MBuffer::CharPrepend(char data)
	{
	const int strlength = GetStringLength();
	if(strlength+1>=mSize)
		{
		return false;
		}

	for(int i=strlength;i>=0;--i)
		{
		mBuffer[i+1]=mBuffer[i];
		}

	mBuffer[0] = data;
	return true;
	}


///////////////////////////////////////////////
bool MBuffer::operator=(const MBuffer &ref)
	{  return Create(ref);  }


////////////////////////////////////////////////
bool MBuffer::ConvertWideToAscii(void)				// Convert the string from Wide to Ascii
	{

	MString tmpstr;
	if(tmpstr.Create(GetWideBuffer())==false)
		{
		return false;
		}

	SetString(tmpstr.Get());
	return true;
	}


///////////////////////////////////////////////
bool MBuffer::ConvertAsciiToWide(void)				// COnvert the string from ascii to wide
	{
	MStringWide tmpstr;
	if(tmpstr.Create(GetBuffer())==false)
		{
		return false;
		}

	SetString(tmpstr.Get());
	return true;
	}


//////////////////////////////////////////////
bool MBuffer::Clear(int val)
	{
	MStdMemSet(mBuffer,val,mSize);
	return true;
	}


//////////////////////////////////////////////
bool MBuffer::Compare(const char *string)
	{
	if(MStdStrCmp(mBuffer,string)==0)
		{ return true; }

	return false;
	}


//////////////////////////////////////////////
bool MBuffer::Compare(const wchar_t *string)
	{
	if(MString::Compare((wchar_t*)mBuffer,string)==0)
		{ return true; }

	return false;
	}


///////////////////////////////////////////////////////
int MBuffer::GetStringLength(void)			// =length of ascii string
	{
	int length=0;
	for(int i=0;i<mSize;++i)
		{
		if(mBuffer[i]==0) { break; }
		else if(mBuffer[i]!=0) { length=length+1; }
		}

	if(length>=mSize)
		{
		return 0;
		}

	return length;
	}


///////////////////////////////////////////////////////
int MBuffer::GetWideStringLength(void)		// =length of unicode string
	{
	int length=0;
	const wchar_t *tmpbuf=(const wchar_t *)mBuffer;
	for(int i=0;i<mSize/2;++i)
		{
		if(tmpbuf[i]==0) { break; }
		else if(tmpbuf[i]!=0) { length=length+1; }
		}

	if(length>=mSize/2)
		{
		return 0;
		}


	return length;
	}


//////////////////////////////////////////////////////
int MBuffer::Search(int start,const char *value,int len)	// =Return index of search value and len
	{
	// Make sure start is legal
	if(start>=mSize || start<0) { return -1; }

	// Check if value is legal
	if(value==NULL)
		{
		return -1;
		}

	// Check if len is out of range
	if(len<=0) { return -1; }

	//!Not Efficient code, but quick to write

	int maxposition=mSize-len+1;
	for(int i=start;i<maxposition;++i)
		{
		if(GMemCompare(mBuffer+i,value,len)==true) { return i; }
		}

	return -1;
	}


//////////////////////////////////////////////////////
int MBuffer::ISearch(int start,const char *value,int len)	// =Return index of search value and len
	{
	// Make sure start is legal
	if(start>=mSize || start<0) { return -1; }

	// Check if value is legal
	if(value==NULL)
		{
		return -1;
		}

	// Check if len is out of range
	if(len<=0) { return -1; }

	//!Not Efficient code, but quick to write

	int maxposition=mSize-len+1;
	for(int i=start;i<maxposition;++i)
		{
		if(GMemICompare(mBuffer+i,value,len)==true) { return i; }
		}

	return -1;
	}


////////////////////////////////////////////////////////
bool MBuffer::TrimRight(void)
	{
	int stringlength;
	stringlength=GetStringLength();
	int i;
	for(i=stringlength-1;i>=0;--i)
		{
		if(MStdIsSpace(mBuffer[i])==false)
			{  return true;  }

		mBuffer[i]=0;
		}

	return true;
	}


///////////////////////////////////////////////////////////////
bool MBuffer::GetSubString(int start, int length, MBuffer &bufout, int requestoutsize)
	{
	MStdAssert(length>0 && start>=0 && start<mSize);
	if(length+1>requestoutsize)
		{
		requestoutsize=length+1;
		}

	if(bufout.Create(requestoutsize)==false)
		{
		return false;
		}

	int index=0;
	for(index=0;index<length;++index)
		{
		bufout.mBuffer[index] = mBuffer[index+start];

		// Dont copy beyond zero '\0'
		if(mBuffer[index+start]==0) { break; }
		}

	bufout.mBuffer[index]=0;
	return true;
	}


/////////////////////////////////////////////////////////////////
bool MBuffer::StrRemove(int length)
	{
	MStdAssert(length>=0 && length<mSize-1);
	for(int i=length;i<mSize;++i)
		{
		mBuffer[i-length] = mBuffer[i];
		if(mBuffer[i]==0) { break; }
		}

	return true;
	}


