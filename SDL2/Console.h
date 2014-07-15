#pragma once
#include "SDL_Setup.h"


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
	void cDrawText(int pX, int pY);
	void cgetDates(valDates pA);
	void cUpdate();

private:
	int mMode;
	valDates mA;

	CSDL_Setup* csdl_setup;

	bool OnePressed;

	string TEMPstr;
};

