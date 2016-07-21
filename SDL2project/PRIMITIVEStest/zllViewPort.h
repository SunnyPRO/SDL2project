#pragma once
#ifndef _zllViewPort_H
#define _zllViewPort_H
#include"../stdafx.h"

class ViewPort
{
public:
	int xMin;
	int xMax;
	int yMin;
	int yMax;

	ViewPort();
	void SetViewPort(int xMin,int xMax,int yMin,int yMax);
};

#endif