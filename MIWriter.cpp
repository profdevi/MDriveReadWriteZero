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


//v2.0 copyright Comine.com 20150810M0909
#include "MStdLib.h"
#include "MIWriter.h"


///////////////////////////////////////////////
bool MIWriter::Write(const void *buffer,int length)
	{
	if(this->OnWrite(buffer,length)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(const char *string)
	{
	int length=MStdStrLen(string)+1;
	if(this->OnWrite(string,length)==false)
		{
		return false;
		}

	return true;	
	}


///////////////////////////////////////////////
bool MIWriter::Write(short value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(int value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(unsigned long value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}



///////////////////////////////////////////////
bool MIWriter::Write(char value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(unsigned char value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(bool boolvalue)
	{
	char value;
	if(boolvalue==false)
		{ value=0;  }
	else
		{ value=1;  }

	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(float value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::Write(double value)
	{
	if(this->OnWrite(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::WriteChars(const char *string)
	{
	int length=MStdStrLen(string);

	if(length==0) { return true; }

	if(this->OnWrite(string,length)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIWriter::WriteChars(const char *str1,const char *str2,const char *str3
		,const char *str4,const char *str5,const char *str6)
	{
	if(str1==NULL) {  return true; }
	if(WriteChars(str1)==false) { return false; }

	if(str2==NULL) {  return true; }
	if(WriteChars(str2)==false) { return false; }

	if(str3==NULL) {  return true; }
	if(WriteChars(str3)==false) { return false; }

	if(str4==NULL) {  return true; }
	if(WriteChars(str4)==false) { return false; }

	if(str5==NULL) {  return true; }
	if(WriteChars(str5)==false) { return false; }

	if(str6==NULL) {  return true; }
	if(WriteChars(str6)==false) { return false; }

	return true;
	}


