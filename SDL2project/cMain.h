#pragma once
#ifndef __SDL2__cMain__
#define __SDL2__cMain__
#include "stdafx.h"
#include "cSDL_Setup.h"
#include "cSprite.h"
#include "cMainCharacter.h"
#include "cEnvironment.h"
#include "cConsole.h"
#include "cFont.h"
#include "PRIMITIVEStest/zllTest.h"
#endif /* defined(__SDL2__cMain__) */



class cMain
{
public:
	cMain(int passed_ScreenWidth, int passed_ScreenHeight);
	~cMain();

//---------Methods-----------
	void GameLoop();
	void PendingEvent();

private:
	float CameraX;
	float CameraY;

	cMainCharacter* bob;
	cEnvironment* ForestArea;
	//Datele primite de latimea si lungimea ecranului
	int ScreenWidth;
	int ScreenHeight;

	//var ce primeste val in caz de esuare 1 si rest 0;
	bool quit;
	
	//obiect ce initializeaza totul(ecran,render,event)
	cSDL_Setup* csdl_setup;
	cSDL_Setup* multipleWindow[1];

	//Coord mousului
	int MouseX;
	int MouseY;

	cConsole *Console;


};

