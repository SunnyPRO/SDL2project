#include "cConsole.h"


cConsole::cConsole(cSDL_Setup* passed_csdl_setup)
{
	csdl_setup = passed_csdl_setup;
	 mMode = ModeOFF;
	 OnePressed = false;
    
    Font = new cFont(csdl_setup->GetRenderer());
	Font->loadFontMap("Tahoma.ttf", 12);

	fps_sec = 0;
	fps_ms = 0;
	frameCounter_sec = 0;
	current_ticks_sec = SDL_GetTicks() + 1000;
	current_ticks_ms = 0;
    
    cout << "Constructor Console" << endl;
}


cConsole::~cConsole()
{
	delete Font;
    cout<< " cConsole Destroyed! "<<endl;
}


void cConsole::render(int pX, int pY)
{
	if (mMode == ModeON)
	{
		int x, y;
		string tempSTR;
		SDL_GetMouseState(&x, &y);



		tempSTR = "Mouse X: ";
		Font->render(strcat((char*)tempSTR.c_str(), to_string(x).c_str()), pX, pY + 15);
		tempSTR = "Mouse Y: ";
		Font->render(strcat((char*)tempSTR.c_str(), to_string(y).c_str()), pX, pY + 30);
		tempSTR = "RAM: ";
		Font->render(strcat((char*)tempSTR.c_str(), to_string(SDL_GetSystemRAM()).c_str()), pX, pY + 45);
		tempSTR = "PLATFORM: ";
		Font->render(strcat((char*)tempSTR.c_str(), SDL_GetPlatform()), pX, pY + 60);
		tempSTR.erase();
	}
}

void cConsole::update()
{
	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{

		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F5)
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
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F5) //key send
		{
			OnePressed = false;
		}
	}
}


void cConsole::calcFps()
{
	
	++frameCounter_sec;
	if(SDL_TICKS_PASSED(SDL_GetTicks(), current_ticks_sec))
	{
		fps_sec = frameCounter_sec;
		frameCounter_sec = 0;
		current_ticks_sec = SDL_GetTicks() + 1000;
	}

	++frameCounter_ms;
	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_ticks_ms))
	{
		fps_ms = frameCounter_ms;
		frameCounter_ms = 0;
		current_ticks_ms = SDL_GetTicks() + 1;
	}
}

void cConsole::showFps()
{
	simpledrawText(to_string(fps_sec), 16, 20, 350, csdl_setup->GetRenderer());
	simpledrawText(to_string(fps_ms), 16, 20, 20, csdl_setup->GetRenderer());
}

void cConsole::delayFps()
{
	Uint32 ms = 1000;
	SDL_Delay(ms / FRAMES_PER_SECOND);
}

void cConsole::setFPS(Uint32 setFPS)
{
		FRAMES_PER_SECOND = setFPS;
		if (FRAMES_PER_SECOND == 0)
			FRAMES_PER_SECOND = 60;

}