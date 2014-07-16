#include "CollisionRectangle.h"


CCollisionRectangle::CCollisionRectangle()
{
	OffsetX = 0;
	OffsetY = 0;
	SetRectangle(0, 0, 0, 0);
    cout << "Constructor CollisionRectangle" << endl;
}

CCollisionRectangle::CCollisionRectangle(int x, int y, int w, int h)
{
	OffsetX = x;
	OffsetY = y;
	SetRectangle(0, 0, w, h);
}


CCollisionRectangle::~CCollisionRectangle()
{
    cout<< " CCollisionRectangle Destroyed! "<<endl;
}


void CCollisionRectangle::SetRectangle(int x, int y, int w, int h)
{
	CollisionRect.x = x + OffsetX;
	CollisionRect.y = y + OffsetY;
	CollisionRect.w = w;
	CollisionRect.h = h;
}