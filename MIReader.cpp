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


//v2.1 copyright Comine.com 20190615S1128
#include "MStdLib.h"
#include "MIReader.h"



/////////////////////////////////////////////////
bool MIReader::Read(char *string,int bufsize)
	{
	if(bufsize<1)
		{
		return false;
		}

	int i;
	for(i=0;i<bufsize-1;++i)
		{
		if(this->OnRead(string+i,1)==false)
			{
			string[i]=0;
			return true;
			}

		if(string[i]==0) { return true; }
		}

	// buffer full
	string[bufsize-1]=0;
	return true;	
	}


//////////////////////////////////////////////////
bool MIReader::Read(char &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		// May have reached end of file!
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////
bool MIReader::Read(unsigned char &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////
bool MIReader::Read(bool &value)
	{
	char bytevalue;
	if(this->OnRead(&bytevalue,sizeof(bytevalue))==false)
		{
		return false;
		}

	if(bytevalue==0)
		{
		value=false;
		}
	else
		{
		value=true;
		}

	return true;
	}


////////////////////////////////////////////////
bool MIReader::Read(short &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MIReader::Read(int &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MIReader::Read(unsigned long &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIReader::Read(float &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////
bool MIReader::Read(double &value)
	{
	if(this->OnRead(&value,sizeof(value))==false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////
bool MIReader::Read(void *block,int size)
	{
	if(this->OnRead(block,size)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MIReader::ReadLine(char *string,int bufsize)	// Reads whole line till '\n'
	{
	if(bufsize<1)
		{
		return false;
		}

	// Read Line
	int i;
	for(i=0;i<bufsize-1;++i)
		{
		if(this->OnRead(string+i,1)==false)
			{
			//= We have reached EOF
			if(i==0)
				{
				//=We have not input at all
				string[0]=0;
				return false;
				}

			//=We Have some input

			// Place terminating zero
			string[i]=0;
			return true;
			}

		if(string[i]==0)
			{
			return false;
			}

		//Check for end of file
		if(string[i]=='\n')
			{
			string[i+1]=0;
			return true;
			}
		}

	// buffer full
	string[bufsize-1]=0;
	return true;
	}

