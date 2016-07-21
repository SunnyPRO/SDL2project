#include"zllViewPort.h"

ViewPort::ViewPort()
{
	this->xMax = 0;
	this->xMin = 0;
	this->yMax = 0;
	this->yMin = 0;
}

void ViewPort::SetViewPort(int xMin,int xMax,int yMin,int yMax)
{
	this->xMax = xMax;
	this->xMin = xMin;
	this->yMax = yMax;
	this->yMin = yMin;
}