#pragma once
#include "stdafx.h"
#include "cSprite.h"
#include "cEnvironment.h"
#include "cSDL_Setup.h"
class cMainCharacter
{
public:
	cMainCharacter(cSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, cEnvironment* passed_Environment);
	~cMainCharacter();

	double GetDistance(int X1, int Y1, int X2, int Y2);

	void Update();
	void Draw();

private:
//Methods
	void UpdateAnimation();
	void UpdateControls();
	


//VARs
	cEnvironment* Environment;
	float *CameraX;
	float *CameraY;

	int *MouseX;
	int *MouseY;

	cSDL_Setup* csdl_setup;
	cSprite* bob;
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

