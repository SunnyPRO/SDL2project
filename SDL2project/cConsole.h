#pragma once
#include "cSDL_Setup.h"
#include "cFont.h"

class cConsole
{
public:
	cConsole(cSDL_Setup* passed_csdl_setup);
	~cConsole();
	friend ostream & operator <<(ostream &, cConsole &);

	enum ModeTypes
	{
		ModeON,
		ModeOFF
	};
	void render(int pX, int pY);
	void update();


	
	void calcFps();
	void showFps();
	void delayFps();
	void setFPS(Uint32 setFPS);
	
private:
    cSDL_Setup* csdl_setup;
    cFont* Font;
    
   
	int mMode;
	bool OnePressed;

	int fps_sec;
	int fps_ms;
	int frameCounter_sec;
	int frameCounter_ms;
	Uint32 current_ticks_sec;
	Uint32 current_ticks_ms;
};

