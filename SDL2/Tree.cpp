#include "Tree.h"

Tree::Tree(int passed_x, int passed_y, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* csdl_setup)
{
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;


	x = passed_x;
	y = passed_y;
	Trunk = new CSprite(csdl_setup->GetRenderer(), "Data/resources/environment/Trunk.png", x, y, 43, 145, CameraX, CameraY, CCollisionRectangle(0,110,43,36));
	Crown = new CSprite(csdl_setup->GetRenderer(), "Data/resources/environment/Crown.png", x - 72, y - 115, 183, 165, CameraX, CameraY, CCollisionRectangle());
    	cout << "Constructor Tree" << endl;
}


Tree::~Tree()
{
	delete Trunk;
	delete Crown;
    cout<< " Tree Destroyed! "<<endl;
}

void Tree::DrawCrown()
{
	if (97 <= *CameraY + Trunk->GetPositionRect().y)
	Trunk->Draw();
	Crown->Draw();
}

void Tree::DrawTrunk()
{
	if ( 103>= *CameraY + Trunk->GetPositionRect().y)
	Trunk->Draw();
}

int Tree::GetX()
{
	return x;
}

int Tree::GetY()
{
	return y;
}