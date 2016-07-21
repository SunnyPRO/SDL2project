#include "cCollisionRectangle.h"


cCollisionRectangle::cCollisionRectangle()
{
	OffsetX = 0;
	OffsetY = 0;
	SetRectangle(0, 0, 0, 0);
    cout << "Constructor CollisionRectangle" << endl;
}

cCollisionRectangle::cCollisionRectangle(int x, int y, int w, int h)
{
	OffsetX = x;
	OffsetY = y;
	SetRectangle(0, 0, w, h);
}


cCollisionRectangle::~cCollisionRectangle()
{
    //cout<< " cCollisionRectangle Destroyed! "<<endl;
}


void cCollisionRectangle::SetRectangle(int x, int y, int w, int h)
{
	CollisionRect.x = x + OffsetX;
	CollisionRect.y = y + OffsetY;
	CollisionRect.w = w;
	CollisionRect.h = h;
}