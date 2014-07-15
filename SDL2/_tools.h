#pragma once
#include "stdafx.h"

#define t_cout _tools::t_ostream 

class _tools
{

public:
		_tools();
		~_tools();
		
   
	/* **Class of ostream custom cout**/
	/*//Color - Formula:
	Color=(16*backgroundcolor)+textcolor;
	----List----
	Black                   0
	Blue                    1
	Green                   2
	Cyan                    3
	Red                     4
	Magenta                 5
	Brown                   6
	White                   7
	Gray                    8
	Intense Blue            9
	Intense Green           10
	Intense Cyan            11
	Intense Red             12
	Intense Magenta         13
	Yellow                  14
	Intense White           15
	*/
	class t_ostream
	{
	public:
		int color;
		t_ostream();
		t_ostream(int color);
		~t_ostream();
		t_ostream &operator = (int obj);
	//-----Methods----------------

		/////////sunt probleme in difenirea functiei in afara headerului/////////
		template<typename T>
		t_ostream &operator<<(const T &x)
		{
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			cout << x;
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			return *this;
		}
		////////////////////////////////////////////////////////////////////
	};
	/* **Class of ostream custom cout**/
};



