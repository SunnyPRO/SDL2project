#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "Environment.h"
#include "SDL_Setup.h"
class MainCharacter
{
public:
	MainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, CEnvironment* passed_Environment);
	~MainCharacter();

	double GetDistance(int X1, int Y1, int X2, int Y2);

	void Update();
	void Draw();
	valDates returnDates(valDates tdates);

private:
//Methods
	void UpdateAnimation();
	void UpdateControls();
	


//VARs
	CEnvironment* Environment;
	float *CameraX;
	float *CameraY;

	int *MouseX;
	int *MouseY;

	CSDL_Setup* csdl_setup;
	CSprite* bob;
	char* shit;

	
	int timeCheck;//Primeste SDL_GetTicks();

	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	float angle;
	bool stopAnimation;
	double Distance;//variabila ce stie distanta 
	bool colliding;


};

