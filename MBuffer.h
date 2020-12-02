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
#ifndef MBuffer_h
#define MBuffer_h

/////////////////////////////////////////////////////
#include "MStdLib.h"

/////////////////////////////////////////////////////
class MBuffer
	{
	char *mBuffer;								// Buffer start
	int mSize;									// Maximum Size of buffer

	/////////////////////////////////////////////////
	void ClearObject(void);

	/////////////////////////////////////////////////
	public:
	MBuffer(void);
	explicit MBuffer(int size);					// Auto allocate buffer in construction
	explicit MBuffer(const MBuffer &ref);		// Copy Constructor
	~MBuffer(void);								// Destructor
	bool Create(int n);							// Create a buffer of size n bytes
	bool Create(const MBuffer &ref);			// Create a copy of another buffer
	bool Destroy(void);							// Destroys the current buffer
	char *GetBuffer(void);						// Gets buffer
	wchar_t *GetWideBuffer(void);				// Returns the buffer as wide string
	char *operator()(void);						// Auto casting operator
	operator char *(void);						// String casting operator
	int GetSize(void);							// Get S
	bool SetString(const char *string);			// Set a known string
	bool SetString(const wchar_t *string);		// Set a known string
	bool SetData(void *data,int length);		// Copy Data into buffer
	char &operator [](int index);				// Array [] operator
	bool StringClear(void);						// Sets ""
	bool StringAppend(const char *string);		// Append a string
	bool CharAppend(char data);					// Append a char data
	bool StringPrepend(const char *string);		// Prepend String before string
	bool CharPrepend(char data);				// Prepend data before string
	bool operator=(const MBuffer &ref);			// Assignment operator
	bool ConvertWideToAscii(void);				// Convert the string from Wide to Ascii
	bool ConvertAsciiToWide(void);				// COnvert the string from ascii to wide
	bool Clear(int val=0);						// Clear buffer with val
	bool Compare(const char *string);			// =true if strings match
	bool Compare(const wchar_t *string);		// =true if strings match
	int GetStringLength(void);					// =length of ascii string
	int GetWideStringLength(void);				// =length of unicode string
	int Search(int start,const char *value,int len);	// =Return index of search value and len
	int ISearch(int start,const char *value,int len);	// =Return index of search value and len
	bool TrimRight(void);						// Remove Extra Spaces on right side
	bool GetSubString(int start,int length,MBuffer &out,int requestoutsize=0);	// Get Sub String and place into new MBuffer
	bool StrRemove(int length);					// Remove the first n characters
	};

#endif // MBuffer_h


