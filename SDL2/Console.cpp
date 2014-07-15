#include "Console.h"


CConsole::CConsole(CSDL_Setup* passed_csdl_setup, valDates pA)
{
	cout << "Constructor Console" << endl;

	csdl_setup = passed_csdl_setup;
	 mMode = ModeOFF;
	 mA.A = new char;
	 mA.B = new char;
	 mA.C = new char;
	 mA.D = new char;
	 mA.E = new char;
	 mA.F = new char;
	 mA = pA;
	 OnePressed = false;
	 TEMPstr = '\0';
}


CConsole::~CConsole()
{
	//delete csdl_setup;
}


void CConsole::cDrawText(int pX, int pY)
{
	if (mMode == ModeON)
	{
		TEMPstr = "Mouse X : ";
		//stringColor(csdl_setup->GetRenderer(), pX, pY + -30, strcat((char*) TEMPstr.c_str(), mA.E), 0xFF3F3F3F);
		TEMPstr = "Mouse Y : ";
		//stringColor(csdl_setup->GetRenderer(), pX, pY + 0, strcat((char*) TEMPstr.c_str(), mA.F), 0xFF3F3F3F);
		TEMPstr = "Collision X : ";
		//stringColor(csdl_setup->GetRenderer(), pX, pY + 30, strcat((char*) TEMPstr.c_str(), mA.A), 0xFF3F3F3F);
		TEMPstr = "Collision Y : ";
		//stringColor(csdl_setup->GetRenderer(), pX, pY + 60, strcat((char*) TEMPstr.c_str(), mA.B), 0xFF3F3F3F);
		TEMPstr = "Collision W : ";
		//stringColor(csdl_setup->GetRenderer(), pX, pY + 90, strcat((char*) TEMPstr.c_str(), mA.C), 0xFF3F3F3F);
		TEMPstr = "Collision H : ";
		//stringColor(csdl_setup->GetRenderer(), pX, pY + 120, strcat((char*) TEMPstr.c_str(), mA.D), 0xFF3F3F3F);
	}
}

void CConsole::cUpdate()
{
	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{

		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_5)
		{
			if (mMode == ModeON)
			{
				t_cout(14) << "Draw Text OFF";
				mMode = ModeOFF;
			}
			else
			{
				t_cout(14) << "Draw Text ON" ;
				mMode = ModeON;
			}
				
			OnePressed = true;
		}
	}
	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
	{
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_5) //key send
		{
			OnePressed = false;
		}
	}
}


void CConsole::cgetDates(valDates tDates)
{
	mA = tDates;
}

ostream &operator << (ostream &out, CConsole &obj)
{
	return out << " A: "<< obj.mA.A<< endl
		<< " B: " << obj.mA.B << endl
		<< " C: " << obj.mA.C << endl
		<< " D: " << obj.mA.D << endl
		<< " C: " << obj.mA.E << endl
		<< " D: " << obj.mA.F << endl
		<<"Mode: "<< obj.mMode;
}
