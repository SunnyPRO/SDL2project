#pragma once
#include "cSprite.h"
#include "cSDL_Setup.h"
#include "stdafx.h"
#include "cTree.h"



class cEnvironment
{
public:
	cEnvironment(int ScreenWidth, int ScreenHeight, float *CameraX, float *CameraY, cSDL_Setup* csdl_setup);
	~cEnvironment();

	void DrawBack();
	void DrawFront();

	void Update();

	void SaveToFile();
	void generateFromFile();

	enum ModeType
	{
		GamePlay,
		LevelCreation
	};

	vector<cTree*> GetTrees() { return trees; }
private:
	int Mode;
	cSDL_Setup* csdl_setup;
	float* CameraX;
	float* CameraY;

	bool OnePressed;


	cSprite* grass[2][2];
	vector<cTree*> trees;
};

