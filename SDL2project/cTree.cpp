#include "cTree.h"

cTree::cTree(int passed_x, int passed_y, float *passed_CameraX, float *passed_CameraY, cSDL_Setup* csdl_setup)
{
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;


	x = passed_x;
	y = passed_y;
	Trunk = new cSprite(csdl_setup->GetRenderer(), "Data/resources/environment/Trunk.png", x, y, 43, 145, CameraX, CameraY, cCollisionRectangle(0,110,43,36));
	Crown = new cSprite(csdl_setup->GetRenderer(), "Data/resources/environment/Crown.png", x - 72, y - 115, 183, 165, CameraX, CameraY, cCollisionRectangle());
    	cout << "Constructor cTree" << endl;
}


cTree::~cTree()
{
	delete Trunk;
	delete Crown;
    cout<< " cTree Destroyed! "<<endl;
}

void cTree::DrawCrown()
{
	if (97 <= *CameraY + Trunk->GetPositionRect().y)
	Trunk->Draw();
	Crown->Draw();
}

void cTree::DrawTrunk()
{
	if ( 103>= *CameraY + Trunk->GetPositionRect().y)
	Trunk->Draw();
}

int cTree::GetX()
{
	return x;
}

int cTree::GetY()
{
	return y;
}