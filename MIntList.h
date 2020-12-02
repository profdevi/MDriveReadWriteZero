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


//v2.9 copyright Comine.com 20190819M0850
#ifndef MIntList_h
#define MIntList_h

///////////////////////////////////////////////////
class MIntList
	{
	struct GIntListNode
		{
		int Data;
		GIntListNode *Next;
		};

	/////////////////////////////////////////////
	GIntListNode *mFirstNode;
	GIntListNode *mLastNode;
	GIntListNode *mCurrent;				// Current Read Item
	int mCount;							// # of items in linked list

	//////////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////////
	public:
	MIntList(void);
	MIntList(bool create);
	~MIntList(void);
	bool Create(void);
	bool Destroy(void);
	bool Add(int data);					// Add to the end of the list
	bool Add(MIntList &list);			// Add a fresh list(resets the reader position)
	bool ReadReset(void);				// Will Reset to the first item again
	bool Read(int &val);				// Read an item
	bool IsMember(int val);				// Check if val is a member
	int GetCount(void);					// Get Count of items
	bool Print(void);					// Print out the integers in list
	bool Reverse(void);					// Reverse the list
	};

#endif // MIntList_h

