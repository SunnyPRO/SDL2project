#pragma once
#include "stdafx.h"

class CSDL_Setup
{
public:
	CSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight);
	~CSDL_Setup();

//-------Methods-------------
	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();

	void Begin();
	void End();
    
    
    //test
    SDL_Window* window;
    //
    
private:
	
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
};

