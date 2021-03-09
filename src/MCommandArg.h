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


//v2.3 copyright Comine.com 20170412W1700
#ifndef MCommandArg_h
#define MCommandArg_h

///////////////////////////////////////////////////////
class MCommandArg
	{
	int mArg;											// Total Number of argum
	char **mArgv;										// Argument List
	char *mBlock;										// Block of memory for all args
	int mStartIndex;									// starting index
	bool mUnitTestOutput;								// unit test output

	////////////////////////////////////////////////
	void ClearObject(void);

	////////////////////////////////////////////////
	public:
	MCommandArg(void);
	MCommandArg(int arg,const char *argv[]);	// AutoCreate
	MCommandArg(int arg,char **argv);
	MCommandArg(const char *arguments);
	~MCommandArg(void);
	bool Create(int arg,const char *argv[]);
	bool Create(int arg,char **argv);
	bool Create(const char *arguments);
	bool Destroy(void);
	bool CheckArgHelp(void);
	bool CheckRemoveHelp(void);							// Check If Help Is Called
	bool RemoveArg(int index);
	int GetArgCount(void);
	const char *GetArg(int index);
	bool IsArgument(const char *argvalue,bool casesensitive=false);
	bool RemoveArg(const char *argvalue,bool casesensitive=false);
	bool CheckRemoveArg(const char *argvalue,bool casesense=false);
	bool GetNameValue(const char *name,const char *&value
			,int &index,bool casesense=false);//name="-size="
	bool Show(void);									// Show all the arguments
	};


#endif // MCommandArg_h


