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


//v2.3 copyright Comine.com 20200603W2009
#ifndef TVector_h
#define TVector_h

////////////////////////////////////////////
#include "MStdLib.h"
#include "MIReader.h"
#include "MIWriter.h"

////////////////////////////////////////////
template <typename Data>
class TVector
	{
	Data *mArray;
	int mCount;

	/////////////////////////////////////////
	void ClearObject(void)
		{
		mArray=0;
		mCount=0;
		}	

	public:
	/////////////////////////////////////////
	TVector(void)
		{  ClearObject();  }

	/////////////////////////////////////////
	explicit TVector(int count)
		{
		ClearObject();
		if(Create(count)==false)
			{
			return;
			}
		}

	/////////////////////////////////////////
	explicit TVector(TVector<Data> &other)
		{
		ClearObject();
		if(Create(other)==false)
			{
			return;
			}
		}

	/////////////////////////////////////////
	explicit TVector(MIReader &reader)
		{
		ClearObject();
		if(Create(reader)==false)
			{
			return;
			}
		}

	/////////////////////////////////////////
	TVector(const Data *data,int len)
		{
		ClearObject();
		if(Create(data,len)==false)
			{
			}
		}

	/////////////////////////////////////////
	~TVector(void)
		{  Destroy();  }

	///////////////////////////////////////
	bool Create(int count)
		{
		Destroy();
		MStdAssert(count>0);
		mCount=count;
		mArray = new(std::nothrow) Data[mCount];
		if(mArray==NULL)
			{
			Destroy();
			return false;
			}

		return true;
		}

	///////////////////////////////////////
	bool Create(const TVector<Data> &other)
		{
		Destroy();
		if(Create(other.GetCount())==false)
			{
			return false;
			}

		// Now Copy the data elements
		const Data *src=other.Get();
		Data *target=mArray;
		int count=other.GetCount();

		int i;
		for(i=0;i<count;++i)
			{
			*target++ = *src++;
			}

		return true;
		}

	
	///////////////////////////////////////
	bool Create(MIReader &reader)
		{
		int count;
		if(reader.Read(count)==false)
			{
			Destroy();
			return false;
			}

		if(Create(count)==false)
			{  return false;  }

		// Now read the array
		int i;
		for(i=0;i<mCount;++i)
			{
			if(MIReaderRead(reader,mArray[i])==false)
				{
				Destroy();
				return false;
				}
			}
		
		return true;
		}

	////////////////////////////////////////
	bool Create(const Data *arr,int count)
		{
		if(Create(count)==false)
			{
			return false;
			}

		int i;
		for(i=0;i<count;++i)
			{
			mArray[i] = arr[i];
			}

		return true;
		}


	////////////////////////////////////////
	bool Destroy(void)
		{
		if(mArray!=0)
			{
			delete[] mArray;
			mArray=0;
			}

		ClearObject();
		return true;
		}


	////////////////////////////////////////
	inline Data *Get(void) const
		{
		return mArray;
		}

	///////////////////////////////////////
	inline int GetCount(void) const
		{
		return mCount;
		}

	////////////////////////////////////////
	// Fast Inline version for speed
	#ifdef NDEBUG
	/////////////////////////////////////////
	inline operator Data *(void)
		{
		return mArray;
		}
	#else
	////////////////////////////////////////
	inline Data &operator[](int index)
		{
		return mArray[index];
		}
	#endif // NDEBUG

	////////////////////////////////////////
	inline Data Get(int index) const
		{
		return mArray[index];
		}

	////////////////////////////////////////
	inline Data *GetItemPtr(int index) const
		{
		return mArray+index;
		}

	////////////////////////////////////////
	inline bool Set(int index,const Data &ref)
		{
		mArray[index]=ref;
		return true;
		}

	////////////////////////////////////////
	bool Set(const Data &ref)
		{
		int i;
		for(i=0;i<mCount;++i)
			{
			mArray[i]=ref;
			}

		return true;
		}

	////////////////////////////////////////
	bool Swap(TVector<Data> &ref)
		{
		Data *tmp=mArray;
		mArray=ref.mArray;
		ref.mArray=tmp;

		int tmplength=mCount;
		mCount = ref.mCount;
		ref.mCount = tmplength;
		return true;
		}


	/////////////////////////////////////////
	bool Swap(int index1,int index2)
		{
		Data tmp=mArray[index1];
		mArray[index1]=mArray[index2];
		mArray[index2]=tmp;
		return true;
		}


	/////////////////////////////////////////
	bool Write(MIWriter &writer) const
		{
		if(writer.Write(mCount)==false)
			{
			return false;
			}

		int i;
		for(i=0;i<mCount;++i)
			{
			if(MIWriterWrite(writer,mArray[i])==false)
				{
				return false;
				}
			}

		return true;
		}

	////////////////////////////////////////
	bool Copy(Data *target,int len)
		{
		MStdAssert(mCount<=len && target!=NULL );
		int i;
		for(i=0;i<mCount;++i)
			{
			target[i] = mArray[i];
			}

		return true;
		}

	///////////////////////////////////////
	// Reverse the array contents
	bool Reverse(void)
		{
		int begin,end;
		begin=0;
		end=mCount-1;
		while(begin<end)
			{
			if(Swap(begin,end)==false)
				{
				return false;
				}

			begin = begin + 1;
			end = end - 1;
			}

		return true;
		}


	///////////////////////////////////////
	bool Resize(int newsize)
		{
		MStdAssert(newsize>0);
		Data *newarray;
		newarray = new(std::nothrow) Data[newsize];
		if(newarray==NULL)
			{
			return false;
			}
		
		// Copy Old Data to new Memory
		const int mincopylength=MStdGetMin(newsize,mCount);
		int i;
		for(i=0;i<mincopylength;++i)
			{
			// Copy Constructor
			newarray[i] = mArray[i];
			}

		// Release old objects and memory
		delete[] mArray;

		// Point to new array
		mArray=newarray;
		mCount=newsize;

		return true;
		}
	};

#endif //TVector_h

