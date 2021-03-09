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
#include <new>
#include "MStdLib.h"
#include "MIntList.h"


//********************************************************************
//** MIntList
//********************************************************************
void MIntList::ClearObject(void)
	{
	mFirstNode=NULL;
	mLastNode=NULL;
	mCurrent=NULL;
	mCount=0;
	}


//////////////////////////////////////////////////////////////
MIntList::MIntList(void)
	{  ClearObject();  }


//////////////////////////////////////////////////////////////
MIntList::MIntList(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


//////////////////////////////////////////////////////////////
MIntList::~MIntList(void)
	{  Destroy();  }


//////////////////////////////////////////////////////////////
bool MIntList::Create(void)
	{
	Destroy();
	return true;
	}


/////////////////////////////////////////////////////////////
bool MIntList::Destroy(void)
	{
	// Traverse and release all the data
	GIntListNode *pnode;
	for(pnode=mFirstNode;pnode!=NULL; )
		{	
		GIntListNode *tmp=pnode->Next;  
		delete pnode;
		pnode=tmp;
		}

	ClearObject();
	return true;
	}


//////////////////////////////////////////////////////////////
bool MIntList::Add(int value)			// Add to the end of the list
	{
	GIntListNode *newnode;
	newnode=new(std::nothrow) GIntListNode;
	if(newnode==NULL)
		{
		return false;
		}

	newnode->Data=value;
	newnode->Next=NULL;

	// Bump up count
	mCount=mCount+1;

	if(mFirstNode==NULL)
		{
		mCurrent=mFirstNode=mLastNode=newnode;
		return true;
		}

	mLastNode->Next=newnode;
	mLastNode=newnode;

	// Update mCurrent if at end to last node
	if(mCurrent==NULL)
		{
		mCurrent=mLastNode;
		}
		
	return true;
	}


//////////////////////////////////////////////////////////
bool MIntList::Add(MIntList &list)
	{
	int count=list.GetCount();

	if(list.ReadReset()==false)
		{
		return false;
		}

	int i;
	for(i=0;i<count;++i)
		{
		int val;
		if(list.Read(val)==false)
			{
			return false;
			}

		// Add list item
		if(Add(val)==false)
			{
			return false;
			}
		}
	
	return true;
	}

////////////////////////////////////////////////////////////
bool MIntList::ReadReset(void)  // Will Reset to the first item again
	{
	mCurrent=mFirstNode;
	return true;
	}


////////////////////////////////////////////////////////////
bool MIntList::Read(int &val)  
	{
	if(mCurrent==NULL) { return false; }
	val=mCurrent->Data;
	mCurrent=mCurrent->Next;
	return true;
	}


/////////////////////////////////////////////////////////////
bool MIntList::IsMember(int val)	// Check if val is member
	{
	// Search through all items
	GIntListNode *p;
	for(p=mFirstNode;p!=NULL;p=p->Next)
		{
		if(val==p->Data) { return true; }
		}

	return false;
	}


/////////////////////////////////////////////////////////
int MIntList::GetCount(void)
	{
	return mCount;
	}


////////////////////////////////////////////////////////
bool MIntList::Print(void)
	{
	MStdPrintf("MIntList : ");
	GIntListNode *p;
	for(p=mFirstNode;p!=NULL;p=p->Next)
		{
		MStdPrintf("%d ",p->Data);
		}

	MStdPrintf("\n");
	return true;
	}


/////////////////////////////////////////////////
bool MIntList::Reverse(void)
	{
	GIntListNode *reverselist=NULL;
	GIntListNode *next;
	for (GIntListNode *p=mFirstNode;p!=0; p = next)
		{
		next=p->Next;
		p->Next=reverselist;
		reverselist=p;
		}

	// Swap first and last pointers
	GIntListNode *tmp=mFirstNode;
	mFirstNode=mLastNode;
	mLastNode=tmp;	

	return true;
	}


