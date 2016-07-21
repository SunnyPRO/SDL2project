#include"zllDodecaedru.h"
#include"zllPrimitives.h"

Dodecaedru::Dodecaedru()
{
	Pi = 3.141592653589;
	phiaa =  52.62263590;
	phibb = 10.81231754;
	radius = 5;
	phia = Pi*phiaa/180.0;
	phib = Pi*phibb/180.0;
	phic = Pi*(-phibb)/180.0;
	phid = Pi*(-phiaa)/180.0;
	theta72 = Pi*72.0/180.0;
	thetab = theta72*0.5;
	theta = 0;
}

void Dodecaedru::DrawFace(SDL_Surface *surface,int _1,int _2,int _3,int _4,int _5)
{
	float normalVect[3];
	float testVect3[3] = {0,0,1};
	float angle;
	//>>>calcularea vectorului normal la plan;
	normalVect[0] = (vertices[_2][1]-vertices[_1][1])*(vertices[_3][2]-vertices[_1][2]) - \
		(vertices[_2][2]-vertices[_1][2])*(vertices[_3][1]-vertices[_1][1]);
	normalVect[1] = (vertices[_2][2]-vertices[_1][2])*(vertices[_3][0]-vertices[_1][0]) - \
		(vertices[_2][0]-vertices[_1][0])*(vertices[_3][2]-vertices[_1][2]);
	normalVect[2] = (vertices[_2][0]-vertices[_1][0])*(vertices[_3][1]-vertices[_1][1]) - \
		(vertices[_2][1]-vertices[_1][1])*(vertices[_3][0]-vertices[_1][0]);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	angle = normalVect[2]/(sqrt(normalVect[0]*normalVect[0]+normalVect[1]*normalVect[1]+normalVect[2]*normalVect[2]));
	if(angle <= 0)
	{
		LineDrawDDA(surface,vpVerts[_1].x,vpVerts[_1].y,vpVerts[_2].x,vpVerts[_2].y);
		LineDrawDDA(surface,vpVerts[_2].x,vpVerts[_2].y,vpVerts[_3].x,vpVerts[_3].y);
		LineDrawDDA(surface,vpVerts[_3].x,vpVerts[_3].y,vpVerts[_4].x,vpVerts[_4].y);
		LineDrawDDA(surface,vpVerts[_4].x,vpVerts[_4].y,vpVerts[_5].x,vpVerts[_5].y);
		LineDrawDDA(surface,vpVerts[_5].x,vpVerts[_5].y,vpVerts[_1].x,vpVerts[_1].y);
		//LineDrawDDA(surface,vpVerts[_1].x,vpVerts[_1].y,vpVerts[_2].x,vpVerts[_2].y,0xFF0000);
		//LineDrawDDA(surface,vpVerts[_2].x,vpVerts[_2].y,vpVerts[_3].x,vpVerts[_3].y,0xFF0000);
		//LineDrawDDA(surface,vpVerts[_3].x,vpVerts[_3].y,vpVerts[_4].x,vpVerts[_4].y,0xFF0000);
		//LineDrawDDA(surface,vpVerts[_4].x,vpVerts[_4].y,vpVerts[_5].x,vpVerts[_5].y,0xFF0000);
		//LineDrawDDA(surface,vpVerts[_5].x,vpVerts[_5].y,vpVerts[_1].x,vpVerts[_1].y,0xFF0000);
	}
	else
	{
		LineDrawDDA(surface,vpVerts[_1].x,vpVerts[_1].y,vpVerts[_2].x,vpVerts[_2].y,0xAAAAAA);
		LineDrawDDA(surface,vpVerts[_2].x,vpVerts[_2].y,vpVerts[_3].x,vpVerts[_3].y,0xAAAAAA);
		LineDrawDDA(surface,vpVerts[_3].x,vpVerts[_3].y,vpVerts[_4].x,vpVerts[_4].y,0xAAAAAA);
		LineDrawDDA(surface,vpVerts[_4].x,vpVerts[_4].y,vpVerts[_5].x,vpVerts[_5].y,0xAAAAAA);
		LineDrawDDA(surface,vpVerts[_5].x,vpVerts[_5].y,vpVerts[_1].x,vpVerts[_1].y,0xAAAAAA);
	}
}

void Dodecaedru::CalcVertsPos()
{
	float tempTheta = theta;
	int i = 0;
	for(;i<5;i++)
	{
		vertices[i][0]=radius*cos(tempTheta)*cos(phia);
		vertices[i][1]=radius*sin(tempTheta)*cos(phia);
		vertices[i][2]=radius*sin(phia);
		tempTheta = tempTheta+theta72;
	}
	tempTheta = theta;
	for(;i<10;i++)
	{
		vertices[i][0]=radius*cos(tempTheta)*cos(phib);
		vertices[i][1]=radius*sin(tempTheta)*cos(phib);
		vertices[i][2]=radius*sin(phib);
		tempTheta = tempTheta+theta72;
	}
	tempTheta = thetab;
	for(;i<15;i++)
	{
		vertices[i][0]=radius*cos(tempTheta)*cos(phic);
		vertices[i][1]=radius*sin(tempTheta)*cos(phic);
		vertices[i][2]=radius*sin(phic);
		tempTheta = tempTheta+theta72;
	}
	tempTheta = thetab;
	for(;i<20;i++)
	{
		vertices[i][0]=radius*cos(tempTheta)*cos(phid);
		vertices[i][1]=radius*sin(tempTheta)*cos(phid);
		vertices[i][2]=radius*sin(phid);
		tempTheta = tempTheta+theta72;
	}
	for(int i=0;i<20;i++)
	{
		vpVerts[i] = DrawingToScreen::Instance()->WorldToViewport(vertices[i]);
	}
}

void Dodecaedru::RotateX(float angle)
{
	float tempVerts[3];
	float rad = angle*Pi/180.0;
	if(angle != 0)
	{
		for(int i=0;i<20;i++)
		{
			tempVerts[1] = vertices[i][1]*cos(rad)-vertices[i][2]*sin(rad);
			tempVerts[2] = vertices[i][1]*sin(rad)+vertices[i][2]*cos(rad);
			tempVerts[0] = vertices[i][0];
			vertices[i][0] = tempVerts[0];
			vertices[i][1] = tempVerts[1];
			vertices[i][2] = tempVerts[2];
		}
		for(int i=0;i<20;i++)
		{
			vpVerts[i] = DrawingToScreen::Instance()->WorldToViewport(vertices[i]);
		}
	}
}

void Dodecaedru::RotateZ(float angle)
{
	float tempVerts[3];
	float rad = angle*Pi/180.0;
	if(angle != 0)
	{
		for(int i=0;i<20;i++)
		{
			tempVerts[0] = vertices[i][0]*cos(rad)-vertices[i][1]*sin(rad);
			tempVerts[1] = vertices[i][0]*sin(rad)+vertices[i][1]*cos(rad);
			tempVerts[2] = vertices[i][2];
			vertices[i][0] = tempVerts[0];
			vertices[i][1] = tempVerts[1];
			vertices[i][2] = tempVerts[2];
		}
		for(int i=0;i<20;i++)
		{
			vpVerts[i] = DrawingToScreen::Instance()->WorldToViewport(vertices[i]);
		}
	}
}

void Dodecaedru::RotateY(float angle)
{
	float tempVerts[3];
	float rad = angle*Pi/180.0;
	if(angle != 0)
	{
		for(int i=0;i<20;i++)
		{
			tempVerts[2] = vertices[i][2]*cos(rad)-vertices[i][0]*sin(rad);
			tempVerts[0] = vertices[i][2]*sin(rad)+vertices[i][0]*cos(rad);
			tempVerts[1] = vertices[i][1];
			vertices[i][0] = tempVerts[0];
			vertices[i][1] = tempVerts[1];
			vertices[i][2] = tempVerts[2];
		}
		for(int i=0;i<20;i++)
		{
			vpVerts[i] = DrawingToScreen::Instance()->WorldToViewport(vertices[i]);
		}
	}
}

void Dodecaedru::Draw(SDL_Surface *surface)
{
	//SDL_Point vpVerts[20];
	//for(int i=0;i<20;i++)
	//{
	//	vpVerts[i] = DrawingToScreen::Instance()->WorldToViewport(vertices[i]);
	//}
	//for(int i=0;i<19;i++)
	//{
	//	LineDrawDDA(surface,vpVerts[i].x,vpVerts[i].y,vpVerts[i+1].x,vpVerts[i+1].y);
	//	//LineDrawDDA(surface,vertices[i][0],vertices[i][1],vertices[i+1][0],vertices[i+1][1]);
	//}
	DrawFace(surface,0,1,2,3,4);
	//DrawFace(surface,0,1,6,10,5);
	DrawFace(surface,5,10,6,1,0);
	//DrawFace(surface,1,2,7,11,6);
	DrawFace(surface,6,11,7,2,1);
	//DrawFace(surface,2,3,8,12,7);
	DrawFace(surface,7,12,8,3,2);
	//DrawFace(surface,3,4,9,13,8);
	DrawFace(surface,8,13,9,4,3);
	//DrawFace(surface,4,0,5,14,9);
	DrawFace(surface,9,14,5,0,4);
	DrawFace(surface,15,16,11,6,10);
	DrawFace(surface,16,17,12,7,11);
	DrawFace(surface,17,18,13,8,12);
	DrawFace(surface,18,19,14,9,13);
	DrawFace(surface,19,15,10,5,14);
	//DrawFace(surface,15,16,17,18,19);
	DrawFace(surface,19,18,17,16,15);
}