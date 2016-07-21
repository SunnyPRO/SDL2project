#pragma once
#ifndef _zllWorldCoord_H
#define _zllWorldCoord_H
#include"zllViewPort.h"


class World
{
private:
	float windowXmin;
	float windowXmax;
	float windowYmin;
	float windowYmax;

public:
	World();
	void SetWindowRect(float xmin,float xmax, float ymin,float ymax);
	ViewPort *vp;
	SDL_Point WorldToViewport(float x,float y);
};

#endif