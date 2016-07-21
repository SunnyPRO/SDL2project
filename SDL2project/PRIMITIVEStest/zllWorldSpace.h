#pragma once
#ifndef _zllWorldSpace_H_
#define _zllWorldSpace_H_
#include"zllPrimitives.h"
#include"zllGeometricObj.h"

#define Round(a) ((int)(a+0.5));

#define TOP 0x8
#define LEFT 0x1
#define RIGHT 0x2
#define BOTTOM 0x4

#define INSCREEN(a) (!a)
#define OUTSCREEN(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

typedef enum {Left,Right,Bottom,Top} Edge;
#define N_EDGE 4

//classa care va face transfomarea window->viewport, decuparea
//coordonatele window sunt logice, coordonatele viewport sunt cele fizice
class DrawingToScreen
{
private:
	FILE *logFile;
	float windowXmin;
	float windowXmax;
	float windowYmin;
	float windowYmax;
	int VPxMin;
	int VPxMax;
	int VPyMin;
	int VPyMax;
	DrawingToScreen();
	static DrawingToScreen *m_sInstance;
	unsigned char SetCode(SDL_Point pt);
	void SwapPts(SDL_Point *pt1,SDL_Point *pt2);
	void SwapCodes(unsigned char *c1,unsigned char *c2);
	//int Inside(Point2D_int p,Edge b);
	//int Cross(Point2D_int p1,Point2D_int p2,Edge b);
	//Point2D_int Intersect(Point2D_int p1,Point2D_int p2,Edge b);
	//void ClipPoint(Point2D_int *p,Edge b,Point2D_int *pOut,int *cnt,Point2D_int *first[],Point2D_int *s);
	//void CloseClip(Point2D_int *pOut,int *cnt,Point2D_int *first[],Point2D_int *s);
public:
	~DrawingToScreen();
	static DrawingToScreen *Instance()
	{
		if(!m_sInstance)
			m_sInstance = new DrawingToScreen();
		return m_sInstance;
	}
	void SetViewPort(int xMin,int yMin,int xMax,int yMax);
	void SetWorldCoord(float xMin,float yMin,float xMax,float yMax);
	SDL_Point WorldToViewport(float p[]);
	void DrawViewportRect(SDL_Surface *surface);
	//>>functiile de decupare
	void ClippingPoint(SDL_Surface *surface,Point2D_int *p);
	char ClippingLine(SDL_Surface *surface,SDL_Point *A,SDL_Point *B);
	//>>Sutherland-Hodgeman algoritm
	//int ClippingPolygon(int n,Point2D_int *pIn,Point2D_int *pOut);
	void ZoomWorld(float Sx,float Sy);
};


#endif