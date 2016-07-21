#include"zllGeometricObj.h"
#include"zllWorldSpace.h"
#include"zllPrimitives.h"
#include"../stdafx.h"
#define PI 3.14

wLine::wLine(float x1,float y1,float x2,float y2) : Geometric((x1+x2)*0.5,(y1+y2)*0.5)
{
	m_A.x = x1;
	m_A.y = y1;
	m_B.x = x2;
	m_B.y = y2;
}

wLine::wLine(Point2D A,Point2D B,Point2D C) : Geometric(C)
{
	m_A = A;
	m_B = B;
}

void wLine::RotatePosition(float angle)
{
	Point2D tempA;
	Point2D tempB;
	float angle_rad = angle*PI/180;
	tempA.x = center.x + (m_A.x - center.x)*cosf(angle_rad) - (m_A.y - center.y)*sinf(angle_rad);
	tempA.y = center.y + (m_A.x - center.x)*sinf(angle_rad) + (m_A.y - center.y)*cosf(angle_rad);

	tempB.x = center.x + (m_B.x - center.x)*cosf(angle_rad) - (m_B.y - center.y)*sinf(angle_rad);
	tempB.y = center.y + (m_B.x - center.x)*sinf(angle_rad) + (m_B.y - center.y)*cosf(angle_rad);
	m_A = tempA;
	m_B = tempB;
}

void wLine::RotatePoint(Point2D point,float angle)
{
	Point2D tempA;
	Point2D tempB;
	float angle_rad = angle*PI/180;
	tempA.x = point.x + (m_A.x - point.x)*cosf(angle_rad) - (m_A.y - point.y)*sinf(angle_rad);
	tempA.y = point.y + (m_A.x - point.x)*sinf(angle_rad) + (m_A.y - point.y)*cosf(angle_rad);

	tempB.x = point.x + (m_B.x - point.x)*cosf(angle_rad) - (m_B.y - point.y)*sinf(angle_rad);
	tempB.y = point.y + (m_B.x - point.x)*sinf(angle_rad) + (m_B.y - point.y)*cosf(angle_rad);
	m_A = tempA;
	m_B = tempB;

	tempA.x = point.x + (center.x - point.x)*cosf(angle_rad) - (center.y - point.y)*sinf(angle_rad);
	tempA.y = point.y + (center.x - point.x)*sinf(angle_rad) + (center.y - point.y)*cosf(angle_rad);
	center = tempA;
}

void wLine::Translate(float Tx,float Ty)
{
	m_A.x += Tx;
	m_A.y += Ty;
	m_B.x += Tx;
	m_B.y += Ty;
	center.x += Tx;
	center.y += Ty;
}

void wLine::ScalePosition(float Sx,float Sy)
{
	m_A.x = (m_A.x-center.x)*Sx + center.x;
	m_A.y = (m_A.y-center.y)*Sy + center.y;
	m_B.x = (m_B.x-center.x)*Sx + center.x;
	m_B.y = (m_B.y-center.y)*Sy + center.y;
}

void wLine::ScalePoint(Point2D point,float Sx,float Sy)
{
	m_A.x = (m_A.x-point.x)*Sx + point.x;
	m_A.y = (m_A.y-point.y)*Sy + point.y;
	m_B.x = (m_B.x-point.x)*Sx + point.x;
	m_B.y = (m_B.y-point.y)*Sy + point.y;
	center.x = (center.x-point.x)*Sx + point.x;
	center.y = (center.y-point.y)*Sy + point.y;
}

void wLine::Draw(SDL_Surface *surface)
{
	SDL_Point vp_A,vp_B;
	float pA[3],pB[3];
	pA[0] = m_A.x;
	pA[1] = m_A.y;
	pA[2] =0;
	pB[0] = m_B.x;
	pB[1] = m_B.y;
	pB[2] = 0;
	//>>color used to draw line
	//Uint8 r,g,b,a;
	//SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
	vp_A = DrawingToScreen::Instance()->WorldToViewport(pA);
	vp_B = DrawingToScreen::Instance()->WorldToViewport(pB);
	if(DrawingToScreen::Instance()->ClippingLine(surface,&vp_A,&vp_B))
		LineDrawDDA(surface,vp_A.x,vp_A.y,vp_B.x,vp_B.y,this->color);
	//LineDrawBres(renderer,vp_A.x,vp_A.y,vp_B.x,vp_B.y);
	//vp_A = DrawingToScreen::Instance()->WorldToViewport(pC);
	//SDL_SetRenderDrawColor(renderer,255,0,0,255);
	//DrawingToScreen::Instance()->ClippingPoint(surface,&vp_A);
	//SDL_SetRenderDrawColor(renderer,r,g,b,a);
}

void wLine::Draw(SDL_Surface *surface,float x1,float y1,float x2,float y2)
{
	m_A.x = x1;
	m_A.y = y1;
	m_B.x = x2;
	m_B.y = y2;
	Draw(surface);
}

void wLine::SetColor(int newColor)
{
	this->color = newColor;
}

//wPolygon::wPolygon(float centerX,float centerY,int vertsNr) : Geometric(centerX,centerY)
//{
//	m_iVertsCount = vertsNr;
//	m_Pts = 0;
//}
//
//wPolygon::wPolygon(int vertsNr) : Geometric(0,0)
//{
//	m_iVertsCount = vertsNr;
//	m_Pts = 0;
//}
//
//wRectangle::wRectangle() : wPolygon(0.5,0.5,4)
//{
//	m_Pts = (Point2D*)malloc(4*sizeof(Point2D));
//	m_Pts[0].x = m_Pts[0].y = 0;
//	m_Pts[1].y = m_Pts[3].x = 0;
//	m_Pts[1].x = m_Pts[2].x = m_Pts[2].y = m_Pts[3].y = 1;
//}
//
//wRectangle::wRectangle(float x0,float y0,float w,float h) : wPolygon(w*0.5+x0,h*0.5+y0,4)
//{
//	m_Pts = (Point2D*)malloc(4*sizeof(Point2D));
//	m_Pts[0].x = m_Pts[3].x = x0;
//	m_Pts[0].y = m_Pts[1].y = y0;
//	m_Pts[1].x = m_Pts[2].x = x0+w;
//	m_Pts[2].y = m_Pts[3].y = y0+h;
//}
//
//void wPolygon::AsignPts(Point2D *pts,int n)
//{
//	if(m_Pts)
//		free(m_Pts);
//	m_Pts = (Point2D*)malloc(n*sizeof(Point2D));
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		m_Pts[i].x = pts[i].x;
//		m_Pts[i].y = pts[i].y;
//	}
//}
//
//void wPolygon::SetCenter(Point2D f_center)
//{
//	this->center = f_center;
//}
//
//void wPolygon::RotatePosition(float angle)
//{
//	Point2D tempP;
//	float angle_rad = angle*PI/180;
//
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		tempP.x = center.x + (m_Pts[i].x - center.x)*cosf(angle_rad) - (m_Pts[i].y - center.y)*sinf(angle_rad);
//		tempP.y = center.y + (m_Pts[i].x - center.x)*sinf(angle_rad) + (m_Pts[i].y - center.y)*cosf(angle_rad);
//		m_Pts[i] = tempP;
//	}
//}
//
//void wPolygon::RotatePoint(Point2D point,float angle)
//{
//	Point2D tempP;
//	float angle_rad = angle*PI/180;
//
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		tempP.x = point.x + (m_Pts[i].x - point.x)*cosf(angle_rad) - (m_Pts[i].y - point.y)*sinf(angle_rad);
//		tempP.y = point.y + (m_Pts[i].x - point.x)*sinf(angle_rad) + (m_Pts[i].y - point.y)*cosf(angle_rad);
//		m_Pts[i] = tempP;
//	}
//	tempP.x = point.x + (center.x - point.x)*cosf(angle_rad) - (center.y - point.y)*sinf(angle_rad);
//	tempP.y = point.y + (center.x - point.x)*sinf(angle_rad) + (center.y - point.y)*cosf(angle_rad);
//	center = tempP;
//}
//
//void wPolygon::Translate(float Tx,float Ty)
//{
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		m_Pts[i].x += Tx;
//		m_Pts[i].y += Ty;
//	}
//	center.x += Tx;
//	center.y += Ty;
//}
//
//void wPolygon::ScalePosition(float Sx,float Sy)
//{
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		m_Pts[i].x = (m_Pts[i].x-center.x)*Sx + center.x;
//		m_Pts[i].y = (m_Pts[i].y-center.y)*Sy + center.y;
//	}
//}
//
//void wPolygon::ScalePoint(Point2D point,float Sx,float Sy)
//{
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		m_Pts[i].x = (m_Pts[i].x-point.x)*Sx + point.x;
//		m_Pts[i].y = (m_Pts[i].y-point.y)*Sy + point.y;
//	}
//	center.x = (center.x-point.x)*Sx + point.x;
//	center.y = (center.y-point.y)*Sy + point.y;
//}
//
//void wPolygon::BoundaryFill(SDL_Surface *surface,int x,int y,Uint32 fillColor,Uint32 b_Color,Uint32 c_Color)
//{
//	c_Color = GetPixel(surface,x,y);
//	if(c_Color != fillColor && c_Color != b_Color)
//	{
//		PutPixel(surface,x,y,fillColor);
//		BoundaryFill(surface,x+1,y,fillColor,b_Color,0);
//		//BoundaryFill(surface,x+1,y+1,fillColor,b_Color,0);
//		BoundaryFill(surface,x,y+1,fillColor,b_Color,0);
//		//BoundaryFill(surface,x-1,y+1,fillColor,b_Color,0);
//		BoundaryFill(surface,x-1,y,fillColor,b_Color,0);
//		//BoundaryFill(surface,x-1,y-1,fillColor,b_Color,0);
//		BoundaryFill(surface,x,y-1,fillColor,b_Color,0);
//		//BoundaryFill(surface,x+1,y-1,fillColor,b_Color,0);
//	}
//}
//
//void wPolygon::Draw(SDL_Surface *surface)
//{
//	Point2D_int *vpPoint = new Point2D_int[m_iVertsCount];
//	//>>color used to draw line
//	//Uint8 r,g,b,a;
//	//>>numarul de puncte dupa decupare
//	int vertsNr_2; // count number after clipping
//	Point2D_int *pOut = (Point2D_int*)malloc(2*m_iVertsCount*sizeof(Point2D_int));
//	//----------------------------------------------------------------------------//
//	//SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
//
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		vpPoint[i] = DrawingToScreen::Instance()->WorldToViewport(m_Pts[i]);
//	}
//	vertsNr_2 = DrawingToScreen::Instance()->ClippingPolygon(m_iVertsCount,vpPoint,pOut);
//	//for(int i=0;i<m_iVertsCount;i++)
//	//{
//	//	DrawingToScreen::Instance()->ClippingLine(renderer,vpPoint[i],vpPoint[(i+1)%m_iVertsCount]);
//	//	//LineDrawDDA(renderer,vpPoint[i].x,vpPoint[i].y,vpPoint[(i+1)%4].x,vpPoint[(i+1)%4].y);
//	//}
//	for(int i=0;i<vertsNr_2;i++)
//		LineDrawDDA(surface,pOut[i].x,pOut[i].y,pOut[(i+1)%vertsNr_2].x,pOut[(i+1)%vertsNr_2].y);
//
//	vpPoint[0] = DrawingToScreen::Instance()->WorldToViewport(center);
//	//SDL_SetRenderDrawColor(renderer,255,0,0,255);
//	DrawingToScreen::Instance()->ClippingPoint(surface,vpPoint);
//	//SDL_SetRenderDrawColor(renderer,r,g,b,a);
//	free(vpPoint);
//}
//
//void wPolygon::DrawFilled(SDL_Surface *surface,Uint8 red,Uint8 green,Uint8 blue)
//{
//	Point2D_int *vpPoint = new Point2D_int[m_iVertsCount];
//	//>>color used to fill polygon
//	Uint32 fillColor = SDL_MapRGB(surface->format,red,green,blue);
//	Uint32 bound_Color = SDL_MapRGB(surface->format,255,255,255);
//	//>>numarul de puncte dupa decupare
//	int vertsNr_2; // count number after clipping
//	Point2D_int *pOut = (Point2D_int*)malloc(2*m_iVertsCount*sizeof(Point2D_int));
//	//----------------------------------------------------------------------------//
//	//SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
//
//	for(int i=0;i<m_iVertsCount;i++)
//	{
//		vpPoint[i] = DrawingToScreen::Instance()->WorldToViewport(m_Pts[i]);
//	}
//	vertsNr_2 = DrawingToScreen::Instance()->ClippingPolygon(m_iVertsCount,vpPoint,pOut);
//	//for(int i=0;i<m_iVertsCount;i++)
//	//{
//	//	DrawingToScreen::Instance()->ClippingLine(renderer,vpPoint[i],vpPoint[(i+1)%m_iVertsCount]);
//	//	//LineDrawDDA(renderer,vpPoint[i].x,vpPoint[i].y,vpPoint[(i+1)%4].x,vpPoint[(i+1)%4].y);
//	//}
//	for(int i=0;i<vertsNr_2;i++)
//		LineDrawDDA(surface,pOut[i].x,pOut[i].y,pOut[(i+1)%vertsNr_2].x,pOut[(i+1)%vertsNr_2].y);
//
//	vpPoint[0] = DrawingToScreen::Instance()->WorldToViewport(center);
//	BoundaryFill(surface,vpPoint[0].x,vpPoint[0].y,fillColor,bound_Color,0x0);
//	//SDL_SetRenderDrawColor(renderer,255,0,0,255);
//	//SDL_SetRenderDrawColor(renderer,r,g,b,a);
//	free(vpPoint);
//}
