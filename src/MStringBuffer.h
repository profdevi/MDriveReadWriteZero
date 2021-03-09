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


//v3.0 copyright Comine.com 20150810M1144
#ifndef MStringBuffer_h
#define MStringBuffer_h

//////////////////////////////////////////////////////
#include "MStdLib.h"
#include "TVector.h"

//////////////////////////////////////////////////////////////
class MStringBuffer
	{
	TVector<char> mBuffer;					// TVector
	int mEndPos;							// location of '\0'

	/////////////////////////////////////////////////////////
	void ClearObject(void);

	/////////////////////////////////////////////////////////
	public:
	MStringBuffer(void);
	explicit MStringBuffer(int length);		// length=maximum strlen of string
	~MStringBuffer(void);
	bool Create(int length);				// length=maximum strlen of string
	bool Create(const char *string);		// allocate space for string
	bool Destroy(void);
	bool Clear(void);						// Reset string to NULL
	const char *Get(void);					// Get string
	bool Add(char ch);						// Add a char to end of buffer
	bool Add(const char *st);				// Add str to buffer
	bool Add(int index,char ch);			// Insert a char at index
	bool Set(int index,char ch);			// Set char at index
	bool Set(const char *string);			// Set a string in space
	char Get(int index);					// returns char at index
	int GetStringLength(void);				// Get string length
	char operator[](int index);				// Efficient way of accessing  a character
	bool TrimLeft(void);					// Trim extra spaces from left
	bool TrimRight(void);					// Trim Extra spaces from right
	bool Trim(void);						// Trim all unnecessary spaces
	bool Compare(const char *string);		// Compare string with buffer content
	bool ICompare(const char *string);		// Case Insensitive Compare
	bool CutLeft(int length);				// Cut length characters
	bool CompareLeft(const char *string);	// Check if left portion of string matchs
	bool CapitilizeFirstLetter(void);		// Capitilize First Letter: this is a test -> This Is A Test
	bool ToUpperCase(void);					// Convert to Upper case
	bool ToLowerCase(void);					// Convert to Lower case
	};

#endif // MStringBuffer_h

