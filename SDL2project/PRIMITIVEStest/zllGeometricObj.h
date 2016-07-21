#pragma once
#ifndef _zllGeometricObj_H_
#define _zllGeometricObj_H_
#include"../stdafx.h"

struct Point2D
{
	float x;
	float y;
};

struct Point2D_int
{
	int x;
	int y;
};

class Geometric
{
protected:
	Point2D center;
public:
	Geometric(float x,float y){center.x = x;center.y = y;}
	Geometric(Point2D c){ center.x = c.x; center.y = c.y;}
	//rotatia fata de cenntrul obiectului
	virtual void RotatePosition(float angle) = 0;
	//rotatia fata de un punct oarecare
	virtual void RotatePoint(Point2D point,float angle) = 0;
	//translarea
	virtual void Translate(float Tx,float Ty) = 0;
	//sclarea fata de centrul obiectului
	virtual void ScalePosition(float Sx,float Sy) = 0;
	//scalarea fata de un punct oarecare din spatiu
	virtual void ScalePoint(Point2D point,float Sx,float Sy) = 0;
};


class wLine : public Geometric
{
	Point2D m_A;
	Point2D m_B;
	int color;
public:
	wLine(float x1,float y1,float x2,float y2);
	wLine(Point2D A,Point2D B,Point2D C);
	~wLine(){}
	void RotatePosition(float angle);
	void RotatePoint(Point2D point,float angle);
	void Translate(float Tx,float Ty);
	void ScalePosition(float Sx,float Sy);
	void ScalePoint(Point2D point,float Sx,float Sy);
	void Draw(SDL_Surface *surface);
	void Draw(SDL_Surface *surface,float x1,float y1,float x2,float y2);
	void SetColor(int newColor);
};

//class wPolygon : public Geometric
//{
//protected:
//	Point2D *m_Pts;
//	int m_iVertsCount;
//	void BoundaryFill(SDL_Surface *surface,int x,int y,Uint32 fillColor,Uint32 b_Color,Uint32 c_Color);
//public:
//	wPolygon(float centerX,float centerY,int vertsNr);
//	wPolygon(int vertsNr);
//	~wPolygon(){}
//	void AsignPts(Point2D *pts,int n);
//	void SetCenter(Point2D center);
//	void RotatePosition(float angle);
//	void RotatePoint(Point2D point,float angle);
//	void Translate(float Tx,float Ty);
//	void ScalePosition(float Sx,float Sy);
//	void ScalePoint(Point2D point,float Sx,float Sy);
//	void Draw(SDL_Surface *surface);
//	void DrawFilled(SDL_Surface *surface,Uint8 red,Uint8 green,Uint8 blue);
//};
//
//class wRectangle : public wPolygon
//{
//public:
//	wRectangle();
//	wRectangle(float x0,float y0,float w,float h);
//	~wRectangle(){}
//};



#endif