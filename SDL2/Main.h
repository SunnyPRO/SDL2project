#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include "Console.h"
#include "Font.h"



class CMain
{
public:
	CMain(int passed_ScreenWidth, int passed_ScreenHeight);
	~CMain();

//---------Methods-----------
	void GameLoop();

private:
	float CameraX;
	float CameraY;

	MainCharacter* bob;
	CEnvironment* ForestArea;
	//Datele primite de latimea si lungimea ecranului
	int ScreenWidth;
	int ScreenHeight;

	//var ce primeste val in caz de esuare 1 si rest 0;
	bool quit;
	


	//obiect ce initializeaza totul(ecran,render,event)
	CSDL_Setup* csdl_setup;

	//Coord mousului
	int MouseX;
	int MouseY;

	valDates tdates;
	CConsole *Console;
    
    CFont *GUI;

};