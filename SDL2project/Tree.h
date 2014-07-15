#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"

class Tree
{
public:
	// x,y - coord of obj,
	Tree(int x, int y, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* csdl_setup);
	~Tree();

	void DrawCrown();
	void DrawTrunk();

	//pentru a lua poziitile in savefile
	int GetX();
	int GetY();

	CSprite* GetCrown() { return Crown; }
	CSprite* GetTrunk() { return Trunk; }


private:

	float *CameraX;
	float *CameraY;

	int x, y;
	CSprite* Crown;
	CSprite* Trunk;
};

