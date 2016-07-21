#pragma once
#ifndef _zllDodecaedru_H
#define _zllDodecaedru_H
#include"zllWorldSpace.h"
#define Round(a) ((int)(a+0.5))

class Dodecaedru
{
private:
	float vertices[20][3];
	SDL_Point vpVerts[20];
	float Pi;
	float phiaa;
	float phibb;
	float radius;
	float phia;
	float phib;
	float phic;
	float phid;
	float theta72;
	float thetab;
	void DrawFace(SDL_Surface *surface,int _1,int _2,int _3,int _4,int _5);
public:
	float theta;
	Dodecaedru();
	void CalcVertsPos();
	void RotateY(float angle);
	void RotateX(float angle);
	void RotateZ(float angle);
	void Draw(SDL_Surface *surface);
};
#endif