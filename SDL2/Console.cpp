#include "Console.h"


CConsole::CConsole(CSDL_Setup* passed_csdl_setup, valDates pA)
{
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
    
    Font = new CFont(csdl_setup->GetRenderer());
    Font->loadFont("Tahoma.ttf",12);
    
    cout << "Constructor Console" << endl;
}


CConsole::~CConsole()
{
	delete Font;
    cout<< " CConsole Destroyed! "<<endl;
}


void CConsole::render(int pX, int pY)
{
	if (mMode == ModeON)
	{
        
		TEMPstr = "Mouse X : ";
        Font->generateFromSurface(strcat((char*) TEMPstr.c_str(), mA.E), { 0 , 0 , 0} );
        Font->render(pX, pY + -15);
		TEMPstr = "Mouse Y : ";
        Font->generateFromSurface(strcat((char*) TEMPstr.c_str(), mA.F), { 0 , 0 , 0} );
        Font->render(pX, pY + 0);
		TEMPstr = "Collision X : ";
        Font->generateFromSurface(strcat((char*) TEMPstr.c_str(), mA.A), { 0 , 0 , 0} );
        Font->render(pX, pY + 15);
		TEMPstr = "Collision Y : ";
        Font->generateFromSurface(strcat((char*) TEMPstr.c_str(), mA.B), { 0 , 0 , 0} );
        Font->render(pX, pY + 30);
		TEMPstr = "Collision W : ";
        Font->generateFromSurface(strcat((char*) TEMPstr.c_str(), mA.C), { 0 , 0 , 0} );
        Font->render(pX, pY + 45);
		TEMPstr = "Collision H : ";
        Font->generateFromSurfaceEx(strcat((char*) TEMPstr.c_str(),mA.D), { 255 , 0 , 0} , { 0 , 0 , 0} , TTF_STYLE_ITALIC|TTF_STYLE_BOLD, TTF_TYPE_BLENDED , true);
        Font->render(pX, pY + 60);
	}
}

void CConsole::update()
{
	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{

		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_5)
		{
			if (mMode == ModeON)
			{
				t_cout(14) << "Console OFF";
				mMode = ModeOFF;
			}
			else
			{
				t_cout(14) << "Console ON" ;
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
