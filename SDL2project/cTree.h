#pragma once
#include "stdafx.h"
#include "cSDL_Setup.h"
#include "cSprite.h"

class cTree
{
public:
	// x,y - coord of obj,
	cTree(int x, int y, float *passed_CameraX, float *passed_CameraY, cSDL_Setup* csdl_setup);
	~cTree();

	void DrawCrown();
	void DrawTrunk();

	//pentru a lua poziitile in savefile
	int GetX();
	int GetY();

	cSprite* GetCrown() { return Crown; }
	cSprite* GetTrunk() { return Trunk; }


private:

	float *CameraX;
	float *CameraY;

	int x, y;
	cSprite* Crown;
	cSprite* Trunk;
};

