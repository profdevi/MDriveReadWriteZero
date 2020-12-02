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


//v3.0 copyright Comine.com 20150810M1138
#ifndef MStringArray_h
#define MStringArray_h

/////////////////////////////////////////////////
#include "MStdLib.h"
#include "MString.h"
#include "TVector.h"
#include "TAutoPtr.h"

/////////////////////////////////////////////////
class MStringArray
	{
	/////////////////////////////////////////////////
	bool mNullStringsAllowed;
	TVector<TAutoPtr<MString> > mList;
	int mCount;

	/////////////////////////////////////////////////
	void ClearObject(void);
	bool UpdateString(int index,const char *string);
	bool ResizeArray(int size);
	
	/////////////////////////////////////////////////
	public:
	MStringArray(bool create=false,bool nullstrings=false);
	~MStringArray(void);
	bool Create(bool nullstrings=false);
	bool Destroy(void);
	bool Clear(void);									// Clear all the strings
	int GetCount(void);									// Get Count in Array
	const char *GetString(int index);					// Get String
	bool SetString(int index,const char *string);		// Add string at position
	bool SetString(const char *string);					// Add string to end
	bool Remove(int index);								// Remove string at index
	bool IsMember(const char *string);					// Check if string is a member
	bool Print(void);									// Print out the Array List
	};

#endif // MStringArray_h

