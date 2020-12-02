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
#ifndef MIWRITER_H
#define MIWRITER_H

////////////////////////////////////////////
#include "MStdLib.h"

////////////////////////////////////////////
struct MIWriter
	{
	/////////////////////////////////////////////////////////
	virtual bool OnWrite(const void *buffer,int length)=0;

	// Support Functions
	bool Write(const void *buffer,int length);
	bool Write(const char *string);			// Writes a string with 0 at end
	bool Write(short value);				// Write 16 bit short
	bool Write(int value);
	bool Write(unsigned long value);
	bool Write(char value);
	bool Write(unsigned char value);
	bool Write(bool value);					// Write a boolean
	bool Write(float value);
	bool Write(double value);
	bool WriteChars(const char *string);	// Write all chars of except zero
	bool WriteChars(const char *str1,const char *str2,const char *str3=NULL
			,const char *str4=NULL,const char *str5=NULL,const char *str6=NULL);
	};


///////////////////////////////////////////////////////////////
// Support Functions
inline bool MIWriterWrite(MIWriter &writer,const void *buffer,int length)
	{
	return writer.Write(buffer,length);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,const char *string)
	{
	return writer.Write(string);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,short value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,int value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,unsigned long value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,char value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,unsigned char value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,bool value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,float value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWrite(MIWriter &writer,double value)
	{
	return writer.Write(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWriteChars(MIWriter &writer,const char *value)
	{
	return writer.WriteChars(value);
	}


///////////////////////////////////////////////////////////////
inline bool MIWriterWriteChars(MIWriter &writer,const char *str1,const char *str2,const char *str3=NULL
		,const char *str4=NULL,const char *str5=NULL,const char *str6=NULL)
	{
	return writer.WriteChars(str1,str2,str3,str4,str5,str6);
	}

#endif // MIWRITER_H

