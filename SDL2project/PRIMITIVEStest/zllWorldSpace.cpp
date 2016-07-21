#include"zllWorldSpace.h"

DrawingToScreen::DrawingToScreen()
{
	windowXmin =0;
	windowXmax=0;
	windowYmin=0;
	windowYmax=0;
	VPxMin=0;
	VPxMax=0;
	VPyMin=0;
	VPyMax=0;
	logFile = fopen("D://logFile1.txt","w");
}

DrawingToScreen::~DrawingToScreen()
{
	fclose(logFile);
}

DrawingToScreen *DrawingToScreen::m_sInstance = 0;

void DrawingToScreen::SetViewPort(int xMin,int yMin,int xMax,int yMax)
{
	VPxMin = xMin;
	VPxMax = xMax;
	VPyMin = yMin;
	VPyMax = yMax;
}

void DrawingToScreen::SetWorldCoord(float xMin,float yMin,float xMax,float yMax)
{
	windowXmin = xMin;
	windowXmax = xMax;
	windowYmin = yMin;
	windowYmax = yMax;
}

SDL_Point DrawingToScreen::WorldToViewport(float p[])
{
	SDL_Point vpPoint;
	float Sx,Sy;
	Sx = (this->VPxMax - this->VPxMin)/(this->windowXmax - this->windowXmin);
	Sy = (this->VPyMax - this->VPyMin)/(this->windowYmax - this->windowYmin);
	vpPoint.x = Round(this->VPxMin + (p[0] - this->windowXmin) * Sx);
	vpPoint.y = Round(this->VPyMin + (p[1] - this->windowYmin) * Sy);
	return vpPoint;
}

void DrawingToScreen::DrawViewportRect(SDL_Surface *surface)
{
	RectangleDrawDDA(surface,VPxMin,VPyMin,VPxMax-VPxMin,VPyMax-VPyMin);
}

void DrawingToScreen::ClippingPoint(SDL_Surface *surface,Point2D_int *p)
{
	if(p->x >= VPxMin && p->x <= VPxMax)
	{
		if(p->y >= VPyMin && p->y <= VPyMax)
		{
			CircleDrawBres(surface,p->x,p->y,2);
		}
	}
}

unsigned char DrawingToScreen::SetCode(SDL_Point pt)
{
	unsigned char code = 0x0;
	if(pt.x < VPxMin)
		code = code|LEFT;
	if(pt.x > VPxMax)
		code = code|RIGHT;
	if(pt.y < VPyMin)
		code = code|BOTTOM;
	if(pt.y > VPyMax)
		code = code|TOP;
	return(code);
}

void DrawingToScreen::SwapPts(SDL_Point *pt1,SDL_Point *pt2)
{
	SDL_Point temp;
	temp = *pt1; *pt1 = *pt2; *pt2 = temp;
}

void DrawingToScreen::SwapCodes(unsigned char *c1,unsigned char *c2)
{
	unsigned char tempC;
	tempC = *c1; *c1 = *c2; *c2 = tempC;
}

char DrawingToScreen::ClippingLine(SDL_Surface *surface,SDL_Point *A,SDL_Point *B)
{
	unsigned char line1Code;
	unsigned char line2Code;
	bool done = 0,draw = 0;
	float m;

	while(!done)
	{
		line1Code = SetCode(*A);
		line2Code = SetCode(*B);
		if(ACCEPT(line1Code,line2Code))
		{
			done = 1;
			draw = 1;
		}
		else if(OUTSCREEN(line1Code,line2Code))
			done = 1;
		else
		{
			//>>calculam intersectia doar pentru capatul ce se afla in afara
			if(INSCREEN(line1Code))
			{
				SwapPts(A,B);
				SwapCodes(&line1Code,&line2Code);
			}
			//>>folosim panta 'm' pentru a gasi intersectia
			if(B->x != A->x)
				m = (float)(B->y-A->y)/(float)(B->x-A->x);
			if(line1Code & LEFT)
			{
				A->y += Round((VPxMin-A->x)*m);
				A->x = VPxMin;
			}
			else if(line1Code & RIGHT)
			{
				A->y += Round((VPxMax-A->x)*m);
				A->x = VPxMax;
			}
			else if(line1Code & BOTTOM)
			{
				//>>avem nevoie sa schimbam coordonata x doar pentru liniile nonverticale
				if(B->x != A->x)
					A->x += Round((float)(VPyMin - A->y)/m);
				A->y = VPyMin;
			}
			else if(line1Code & TOP)
			{
				if(B->x != A->x)
					A->x += Round((float)(VPyMax-A->y)/m);
				A->y = VPyMax;
			}
		}
	}
	if(draw)
		return 1;
	return 0;
		//LineDrawDDA(surface,A.x,A.y,B.x,B.y);
}

//int DrawingToScreen::Inside(Point2D_int p,Edge b)
//{
//	switch(b)
//	{
//	case Left: if(p.x < VPxMin) return(0); break;
//	case Right: if(p.x > VPxMax) return(0); break;
//	case Bottom: if(p.y < VPyMin) return(0); break;
//	case Top: if(p.y > VPyMax) return(0); break;
//	}
//	return 1;
//}

//int DrawingToScreen::Cross(Point2D_int p1,Point2D_int p2,Edge b)
//{
//	if(Inside(p1,b) == Inside(p2,b))
//	{
//		return(0);
//	}
//	else
//	{
//		return(1);
//	}
//}

//Point2D_int DrawingToScreen::Intersect(Point2D_int p1,Point2D_int p2,Edge b)
//{
//	Point2D_int tempP;
//	float m;
//	if(p1.x != p2.x)
//		m = (float)(p1.y - p2.y)/(float)(p1.x-p2.x);
//	switch(b)
//	{
//	case Left:
//		tempP.x = VPxMin;
//		tempP.y = Round(p2.y + static_cast<float>(VPxMin - p2.x)*m);
//		break;
//	case Right:
//		tempP.x = VPxMax;
//		tempP.y = Round(p2.y + static_cast<float>(VPxMax - p2.x)*m);
//		break;
//	case Bottom:
//		tempP.y = VPyMin;
//		if(p1.x != p2.x)
//		{
//			tempP.x = Round(p2.x + static_cast<float>(VPyMin - p2.y)/m);
//		}
//		else
//			tempP.x = p2.x;
//		break;
//	case Top:
//		tempP.y = VPyMax;
//		if(p1.x != p2.x)
//		{
//			tempP.x = Round(p2.x + static_cast<float>(VPyMax - p2.y)/m);
//		}
//		else
//			tempP.x = p2.x;
//		break;
//	}
//	return(tempP);
//}

//void DrawingToScreen::ClipPoint(Point2D_int *p,Edge b,Point2D_int *pOut,int *cnt,Point2D_int *first[],Point2D_int *s)
//{
//	Point2D_int tempP;
//	if(!first[b])
//	{
//		first[b] = (Point2D_int*)malloc(sizeof(Point2D_int));
//		first[b]->x = p->x;
//		first[b]->y = p->y;
//	}
//	else if(Cross(*p,s[b],b))
//	{
//		tempP = Intersect(*p,s[b],b);
//		fprintf(logFile,"Intersectia dintre(%i,%i)si(%i,%i)cu|%i|este(%i,%i)\n",p->x,p->y,s[b].x,s[b].y,b,tempP.x,tempP.y);
//		if(b < Top)
//			ClipPoint(&tempP,static_cast<Edge>(b+1),pOut,cnt,first,s);
//		else
//		{
//			pOut[*cnt] = tempP;
//			(*cnt)++;
//		}
//	}
//	s[b] = *p;
//	if(Inside(*p,b))
//	{
//		if(b < Top)
//		{
//			ClipPoint(p,static_cast<Edge>(b+1),pOut,cnt,first,s);
//		}
//		else
//		{
//			pOut[*cnt] = *p;
//			(*cnt)++;
//		}
//	}
//}


//void DrawingToScreen::CloseClip(Point2D_int *pOut,int *cnt,Point2D_int *first[],Point2D_int *s)
//{
//	Point2D_int tempP;
//	Edge b;
//	for(b = Left;b<=Top;b= static_cast<Edge>(b+1))
//	{
//		if(Cross(s[b],*first[b],b))
//		{
//			tempP = Intersect(s[b],*first[b],b);
//			if(b < Top)
//				ClipPoint(&tempP,static_cast<Edge>(b+1),pOut,cnt,first,s);
//			else
//			{
//				pOut[*cnt] = tempP;
//				(*cnt)++;
//			}
//		}
//	}
//}

//int DrawingToScreen::ClippingPolygon(int n,Point2D_int *pIn,Point2D_int *pOut)
//{
//	fprintf(logFile,"Incepe algoritmul/*********************************\n");
//	Point2D_int *first[N_EDGE] = {0,0,0,0};
//	Point2D_int s[N_EDGE];
//	int i,cnt = 0;
//	for(i=0;i<n;i++)
//	{
//		ClipPoint(&pIn[i],static_cast<Edge>(0),pOut,&cnt,first,s);
//	}
//	//for(i=0;i<cnt;i++)
//	//{
//	//	fprintf(logFile,"out[%i] = (%i,%i)\n",i,pOut[i].x,pOut[i].y);
//	//}
//	if(cnt != 0)
//		CloseClip(pOut,&cnt,first,s);
//	fprintf(logFile,"Sfirsit de algoritm/********************************\n");
//	return(cnt);
//}

void DrawingToScreen::ZoomWorld(float Sx,float Sy)
{
	windowXmin *= Sx;
	windowXmax *= Sx;
	windowYmin *= Sy;
	windowYmax *= Sy;
}