#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"
#include "stdafx.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class CEnvironment
{
public:
	CEnvironment(int ScreenWidth, int ScreenHeight, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~CEnvironment();

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

	vector<Tree*> GetTrees() { return trees; }
private:
	int Mode;
	CSDL_Setup* csdl_setup;
	float* CameraX;
	float* CameraY;

	bool OnePressed;

	CSprite* grass[4][7];
	vector<Tree*> trees;
};

