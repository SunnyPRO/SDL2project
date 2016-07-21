#pragma once
#include "stdafx.h"

class cSDL_Setup
{
public:
	//Creates mWindow
	cSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight);
	~cSDL_Setup();

//-------Methods-------------
	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();
	SDL_Window* GetWindow();


	//Shows windows contents
	void Begin();
	void End();

	//Handles mWindow events
	void handleEvent(SDL_Event& e);

	//Focuses on mWindow
	void focus();

	//Deallocates internals
	void free();

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
    
    
private:
	
	SDL_Renderer* mRenderer;
	SDL_Event* mMainEvent;
	SDL_Window* mWindow;

	//Window data
	int mWindowID;

	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};

