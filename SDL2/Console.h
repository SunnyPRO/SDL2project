#pragma once
#include "SDL_Setup.h"
#include "Font.h"


class CConsole
{
public:
	CConsole(CSDL_Setup* passed_csdl_setup, valDates pA);
	~CConsole();
	friend ostream & operator <<(ostream &, CConsole &);

	enum ModeTypes
	{
		ModeON,
		ModeOFF
	};
	void render(int pX, int pY);
	void cgetDates(valDates pA);
	void update();

private:
    CSDL_Setup* csdl_setup;
    CFont* Font;
    
    
	int mMode;
	valDates mA;
	bool OnePressed;
	string TEMPstr;
    
};

