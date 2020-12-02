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


//v2.0 copyright Comine.com 20150810M1103
#ifndef TAutoPtr_h
#define TAutoPtr_h

///////////////////////////////////////////
#include "MStdLib.h"

//******************************************************
//**  TAutoPtr Template
//******************************************************
template<class RefObject>
class TAutoPtr
	{
	////////////////////////////////////////
	RefObject *mRefObject;

	////////////////////////////////////////
	void ClearObject(void)
		{
		mRefObject=NULL;
		}

	////////////////////////////////////////
	TAutoPtr(const TAutoPtr &ref)
		{
		}

	////////////////////////////////////////
	public:
	TAutoPtr(bool create=false)
		{
		ClearObject();
		if(create==true && Create()==false)
			{
			return;
			}
		}

	///////////////////////////////////////
	~TAutoPtr(void)
		{
		Destroy();
		}

	///////////////////////////////////////
	bool Create(void)
		{
		// Allocate heap object
		RefObject *newobj=new RefObject;
		if(newobj==NULL)
			{
			Destroy();
			return false;
			}

		// Destroy exisiting reference
		Destroy();
		
		mRefObject=newobj;
		return true;
		}


	////////////////////////////////////////
	bool Destroy(void)
		{
		if(mRefObject!=NULL)
			{
			delete mRefObject;
			mRefObject=NULL;
			}

		return true;
		}


	/////////////////////////////////////////
	RefObject *operator ->(void)
		{
		return mRefObject;
		}

	/////////////////////////////////////////
	RefObject& operator *(void)
		{
		return *mRefObject;
		}


	/////////////////////////////////////////
	RefObject *Get(void)
		{
		// Return internal pointer
		return mRefObject;
		}

	/////////////////////////////////////////
	bool Swap(TAutoPtr<RefObject> &ref)
		{
		// Swap Referenced Memory
		RefObject *tmpobj=mRefObject;
		mRefObject = ref.mRefObject;
		ref.mRefObject=tmpobj;

		return true;
		}

	//////////////////////////////////////////
	bool operator=(TAutoPtr<RefObject> &ref)
		{
		if(ref.Get()==NULL)
			{
			Destroy();
			return true;
			}
		
		if(Create()==false)
			{
			return false;
			}

		// Assume Copy Sematics for type
		(*mRefObject) = (* ref.mRefObject);

		return true;
		}
	};

#endif // TAutoPtr_h

