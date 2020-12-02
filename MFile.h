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


//v3.0 copyright Comine.com 20150810M0924
#ifndef MFile_h
#define MFile_h

///////////////////////////////////////////////////////
#include "MStdLib.h"

/////////////////////////////////////
#if ( defined(MSTDLIB_OS_WINDOWS) || defined(MSTDLIB_OS_WINDOWSOLD) || defined(MSTDLIB_OS_MINGW) ) 
#undef UNICODE
#include <windows.h>

#endif // MSTDLIB_OS_WINDOWS

//////////////////////////////////////////////////////
#include "MIReader.h"
#include "MIWriter.h"

//******************************************************
//**  MFileOutput class for binary output
//******************************************************
class MFileOutput:public MIWriter
	{
	////////////////////////////////
	#if ( defined(MSTDLIB_OS_WINDOWS) || defined(MSTDLIB_OS_WINDOWSOLD) || defined(MSTDLIB_OS_MINGW) ) 
	HANDLE mFile;												// Handle to file

	///////////////////////////////
	#else
	MStdFileHandle mFile;										// StdInput File

	#endif	// MSTDLIB_OS_WINDOWS

	//////////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////////
	public:
	MFileOutput(void);
	MFileOutput(const char *filename,bool append=false);
	~MFileOutput(void);
	bool Create(const char *filename,bool append=false);
	bool Destroy(void);
	bool OnWrite(const void *buffer,int length);		// Callback Handler for MIWriter
	int Tell(void);										// =Current position

	////////////////////////////////////////////////
	#if ( defined(MSTDLIB_OS_WINDOWS) || defined(MSTDLIB_OS_WINDOWSOLD) || defined(MSTDLIB_OS_MINGW) ) 
	HANDLE GetHandle(void);

	////////////////////////////////////////////////
	#else
	MStdFileHandle GetHandle(void);

	#endif // MSTDLIB_OS_WINDOWS
	};


//******************************************************
//**  MFileInput class for binary input
//******************************************************
class MFileInput:public MIReader
	{
	///////////////////////////////////////////////
	#if ( defined(MSTDLIB_OS_WINDOWS) || defined(MSTDLIB_OS_WINDOWSOLD) || defined(MSTDLIB_OS_MINGW) ) 
	HANDLE mFile;

	//////////////////////////////////////////////
	#else
	MStdFileHandle mFile;

	#endif // MSTDLIB_OS_WINDOWS

	//////////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////////
	public:
	MFileInput(void);
	MFileInput(const char *filename);
	~MFileInput(void);
	bool Create(const char *filename);
	bool Destroy(void);
	bool OnRead(void *block,int size);						// Callback Handler for MIReader
	int ReadToBuffer(void *buffer,int size);
	bool Seek(int offset,int relative=0);					// relative=0(beginning) 1(current) 2(end)
	int Tell(void);											// =Current position

	////////////////////////////////////////////////
	#if ( defined(MSTDLIB_OS_WINDOWS) || defined(MSTDLIB_OS_WINDOWSOLD) || defined(MSTDLIB_OS_MINGW) ) 
	HANDLE GetHandle(void);

	#else
	MStdFileHandle GetHandle(void);

	#endif // MSTDLIB_OS_WINDOWS
	};

#endif	// MFile_h
