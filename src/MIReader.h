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
#ifndef MIREADER_H
#define MIREADER_H

////////////////////////////////////////////
struct MIReader
	{
	////////////////////////////////////////////
	virtual bool OnRead(void *buffer,int length)=0;

	////////////////////////////////////////////
	bool Read(char *string,int bufsize);
	bool Read(char &value);
	bool Read(unsigned char &value);
	bool Read(bool &value);
	bool Read(short &value);
	bool Read(int &value);
	bool Read(unsigned long &value);
	bool Read(float &value);
	bool Read(double &value);
	bool Read(void *block,int size);
	bool ReadLine(char *string,int bufsize);			// Reads whole line till '\n'
	};


////////////////////////////////////////////
// Support Functions
inline bool MIReaderRead(MIReader &reader,char *string,int bufsize)
	{
	return reader.Read(string,bufsize);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,char &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,unsigned char &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,bool &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,short &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,int &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,unsigned long &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,float &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,double &value)
	{
	return reader.Read(value);
	}


////////////////////////////////////////////
inline bool MIReaderRead(MIReader &reader,void *block,int size)
	{
	return reader.Read(block,size);
	}


////////////////////////////////////////////
inline bool MIReaderReadLine(MIReader &reader,char *string,int bufsize)
	{
	return reader.ReadLine(string,bufsize);
	}


#endif // MIREADER_H


