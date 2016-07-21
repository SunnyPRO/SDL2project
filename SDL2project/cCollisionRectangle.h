#pragma once
#include "stdafx.h"


class cCollisionRectangle
{
public:
	cCollisionRectangle();
	cCollisionRectangle(int x, int y, int w, int h);
	~cCollisionRectangle();

	void SetRectangle(int x, int y, int w, int h);
	SDL_Rect GetRectangle() { return CollisionRect; }

	void SetX(int x) { CollisionRect.x = x + OffsetX; }
	void SetY(int y) { CollisionRect.y = y + OffsetY; }

private:
	int OffsetX;
	int OffsetY;
	SDL_Rect CollisionRect;
};

