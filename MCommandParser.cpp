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


//v2.0 copyright Comine.com 20150810M1158
#include "MStdLib.h"
#include "MString.h"
#include "MStringArray.h"
#include "MStringBuffer.h"
#include "MCommandParser.h"


//*********************************************************
//** Module Elements
//*********************************************************
static const int GMAXTOKENSIZE=1000;


//*********************************************************
//** MCommandParser
//*********************************************************
void MCommandParser::ClearObject(void)
	{
	}

/////////////////////////////////////////////////
bool MCommandParser::IsSeperator(char ch)
	{
	const char *seplist=mSeperatorList.Get();
	if(mSeperatorList.Get()==NULL)
		{  
		return false;
		}

	for(int i=0;seplist[i]!=0;++i)
		{
		if(seplist[i]==ch) { return true; }
		}

	return false;
	}


/////////////////////////////////////////////////
MCommandParser::MCommandParser(void)
	{ 
	ClearObject();
	}


/////////////////////////////////////////////////
MCommandParser::~MCommandParser(void)
	{
	Destroy();
	}


/////////////////////////////////////////////////
bool MCommandParser::Create(const char *seperators)
	{
	Destroy();
	if(seperators==NULL)
		{
		Destroy();
		return false;
		}

	if(mSeperatorList.Create(seperators)==false)
		{
		Destroy();
		return false;
		}

	if(mArray.Create()==false)
		{
		Destroy();
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////
bool MCommandParser::Destroy(void)
	{
	mArray.Destroy();
	mSeperatorList.Destroy();
	ClearObject();
	return true;
	}


/////////////////////////////////////////////////
bool MCommandParser::Clear(void)
	{
	return mArray.Clear();
	}


/////////////////////////////////////////////////
bool MCommandParser::ParseString(const char *string)
	{
	Clear();

	// Parser Routine
	enum GState { START,CMDSIMPLE,DQUOTE,DQUOTE_SLASH}; 
	GState state=START;

	MStringBuffer buffer;
	if(buffer.Create(GMAXTOKENSIZE)==false)
		{
		return false;
		}

	buffer.Clear();
	mArray.Clear();

	for(int i=0;string[i]!=0;++i)
		{
		char nextchar=string[i];
		
		//FSM Routine
		if(state==START)
			{
			if(nextchar=='\"'){  state=DQUOTE;  continue;  }
			else if(IsSeperator(nextchar)==true) { continue; }
			else {  buffer.Add(nextchar);  state=CMDSIMPLE;  continue;  }
			}
		else if(state==CMDSIMPLE)
			{
			if(IsSeperator(nextchar)==true)
				{
				state=START;  mArray.SetString(buffer.Get());
				buffer.Clear();  continue;
				}
			else if(nextchar=='"')
				{
				state=DQUOTE;  mArray.SetString(buffer.Get());
				buffer.Clear();  continue;
				}
			buffer.Add(nextchar); continue;
			}
		else if(state==DQUOTE)
			{
			if(nextchar=='\"')
				{
				state=START;  mArray.SetString(buffer.Get());
				buffer.Clear(); continue;
				}
			else if(nextchar=='\\')
				{  state=DQUOTE_SLASH; continue;  }
			else if(nextchar=='\n' || nextchar=='\r')
				{
				state=START;  mArray.SetString(buffer.Get());
				buffer.Clear();  continue;
				}
			else
				{  buffer.Add(nextchar);  continue; }
			}
		else if(state==DQUOTE_SLASH)
			{
			if(nextchar=='\\')
				{  state=DQUOTE;  buffer.Add('\\'); continue;  }
			else if(nextchar=='\"')
				{  state=DQUOTE;  buffer.Add('\"');  continue;  }
			else if(nextchar=='r')
				{  state=DQUOTE;  buffer.Add('\r');  continue;  }
			else if(nextchar=='n')
				{  state=DQUOTE;  buffer.Add('\n');  continue;  }
			else if(nextchar=='t')
				{  state=DQUOTE;  buffer.Add('\t');  continue;  }
			else if(nextchar=='a')
				{  state=DQUOTE;  buffer.Add('\a');  continue;  }
			else	// Unknown Escape character
				{  state=DQUOTE;  continue; }
			}
		else
			{
			return false;
			}
		}

	// Make sure that processed everything
	if(state!=START && buffer.GetStringLength()>0)
		{  mArray.SetString(buffer.Get());  }

	buffer.Destroy();
	return true;
	}


/////////////////////////////////////////////////
int MCommandParser::GetCount(void)
	{
	return mArray.GetCount();
	}


/////////////////////////////////////////////////
const char *MCommandParser::GetString(int index)
	{
	return mArray.GetString(index);
	}



