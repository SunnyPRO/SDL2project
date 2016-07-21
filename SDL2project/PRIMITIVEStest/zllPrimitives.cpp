#include"zllPrimitives.h"
#include"../stdafx.h"

#define Round(x) ((int)(x+0.5))

void PutPixel(SDL_Surface *surface,int x,int y,Uint8 red,Uint8 green,Uint8 blue)
{
	Uint32 color;
	//if(SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
	color = SDL_MapRGB(surface->format,red,green,blue);
	char *pPixel;
	pPixel = (char*)(surface->pixels);
	pPixel += (y*surface->pitch);
	pPixel += (x*surface->format->BytesPerPixel);
	memcpy(pPixel,&color,surface->format->BytesPerPixel);
	//SDL_UnlockSurface(surface);
}

void PutPixel(SDL_Surface *surface,int x,int y,Uint32 color)
{
	char *pPixel;
	Uint32 colorLoc; //negru
	colorLoc = SDL_MapRGB(surface->format,0,0,0);
	pPixel = (char*)(surface->pixels);
	pPixel += (y*surface->pitch);
	pPixel += (x*surface->format->BytesPerPixel);
	if(GetPixel(surface,x,y) != 0x000000)
		memcpy(pPixel,&color,surface->format->BytesPerPixel); //punem rosu
	else
		memcpy(pPixel,&colorLoc,surface->format->BytesPerPixel);//punem negru
}

Uint32 GetPixel(SDL_Surface *surface,int x,int y)
{
	char *pPixel;
	pPixel = (char*)(surface->pixels);
	pPixel += (y*surface->pitch);
	pPixel += (x*surface->format->BytesPerPixel);
	return(*(Uint32*)pPixel);
}

void LineDraw(SDL_Surface *surface,int x1,int y1,int x2,int y2)
{
	float m = x2-x1 != 0 ? (float)(y2-y1)/(float)(x2-x1) : float(y2-y1);
	float deltaX = 1;
	float deltaY = 1;
	float x  = x1;
	float y  = y1;
	int xMax = ((float)(x1+x2)*0.5+abs(float(x1-x2)*0.5));
	int yMax = ((float)(y1+y2)*0.5+abs(float(y1-y2)*0.5));
	if(abs(m) < 1)
	{
		x = x2 > x1 ? x1 : x2;
		y = x2 > x1 ? y1 : y2;
		deltaY = m*deltaX;
		for(;x<xMax;x++)
		{
			PutPixel(surface,(int)x,(int)y,255,255,255);
			y += deltaY;
		}
	}
	else if(abs(m) > 1)
	{
		y = y2 > y1 ? y1 : y2;
		x = y2 > y1 ? x1 : x2;
		deltaX = deltaY/m;
		for(;y<yMax;y++)
		{
			PutPixel(surface,(int)x,(int)y,255,255,255);
			x += deltaX;
		}
	}
	else
	{
		for(;x<xMax;x+=deltaX,y+=deltaY)
		{
			PutPixel(surface,(int)x,(int)y,255,255,255);
		}
	}
}

void LineDrawDDA(SDL_Surface *surface,int x1,int y1,int x2,int y2)
{
	int deltaX = x2-x1,deltaY = y2-y1,pas,k;
	float xInc,yInc,x = x1,y = y1;

	if(abs(deltaX) > abs(deltaY))
		pas = abs(deltaX);
	else
		pas = abs(deltaY);
	xInc = deltaX / (float)pas;
	yInc = deltaY / (float)pas;
	PutPixel(surface,Round(x),Round(y),0,0,0);
	for(k=0;k<pas;k++)
	{
		x += xInc;
		y += yInc;
		PutPixel(surface,Round(x),Round(y),0,0,0);
	}
}

void LineDrawDDA(SDL_Surface *surface,int x1,int y1,int x2,int y2,int color)
{
	int deltaX = x2-x1,deltaY = y2-y1,pas,k;
	float xInc,yInc,x = x1,y = y1;

	if(abs(deltaX) > abs(deltaY))
		pas = abs(deltaX);
	else
		pas = abs(deltaY);
	xInc = deltaX / (float)pas;
	yInc = deltaY / (float)pas;
	PutPixel(surface,Round(x),Round(y),color);
	for(k=0;k<pas;k++)
	{
		x += xInc;
		y += yInc;
		PutPixel(surface,Round(x),Round(y),color);
	}
}

void LineDrawBres(SDL_Surface *surface,int x1,int y1,int x2,int y2)
{
	int dx(abs(x1-x2)),dy(abs(y1-y2));
	int p(2*dy - dx);
	int _2dy(2*dy), _2dydx(2*(dy-dx)),_2dx(2*dx),_2dxdy(2*(dx-dy));
	int x(x1),y(y1),xEnd;
	//se determina care punct se foloseste pentru inceput si care pentru sfirsit

	PutPixel(surface,x,y,0,0,0);
	//daca dy > dx, y se va mari(micsora) cu o unitate iar x se va calcula
	if(dy > dx)
	{
		if(y1 > y2)
		{
			while(y > y2)
			{
				y--;
				if(p < 0)
					p += _2dx;
				else
				{
					x += (x2 - x1)/dx;
					p += _2dxdy;
				}
				PutPixel(surface,x,y,255,255,255);
			}
		}
		else
		{
			while(y < y2)
			{
				y++;
				if(p < 0)
					p += _2dx;
				else
				{
					x += (x2 - x1)/dx;
					p += _2dxdy;
				}
				PutPixel(surface,x,y,255,255,255);
			}
		}
	}
	else
	{
		if(x1 > x2)
		{
			while(x > x2)
			{
				x--;
				if(p < 0)
					p += _2dy;
				else
				{
					y += (y2-y1)/dy;
					p += _2dydx;
				}
				PutPixel(surface,x,y,255,255,255);
			}
		}
		else
		{
			while(x < x2)
			{
				x++;
				if(p < 0)
					p += _2dy;
				else
				{
					y += (y2-y1)/dy;
					p += _2dydx;
				}
				PutPixel(surface,x,y,255,255,255);
			}
		}
	}
}

//functia care pune puncte simetrice pe octantele de la cerc
void CircleSimetricPoints(SDL_Surface *surface,int xc,int yc,int x,int y)
{
	PutPixel(surface,xc+x,yc+y,255,255,255);
	PutPixel(surface,xc-x,yc+y,255,255,255);
	PutPixel(surface,xc+x,yc-y,255,255,255);
	PutPixel(surface,xc-x,yc-y,255,255,255);
	PutPixel(surface,xc+y,yc+x,255,255,255);
	PutPixel(surface,xc-y,yc+x,255,255,255);
	PutPixel(surface,xc+y,yc-x,255,255,255);
	PutPixel(surface,xc-y,yc-x,255,255,255);
}

void CircleDrawBres(SDL_Surface *surface,int xc,int yc,int r)
{
	//setam x si y
	int x =0,y=r;
	//parametrul de decizie 'd'
	int d = 3-r<<1;
	while(x < y)
	{
		CircleSimetricPoints(surface,xc,yc,x,y);
		//incrementam x
		x++;
		//in dependenta de semnul lui 'd' calculam pe y
		if(d < 0)
			d += 6+(x<<2);
		else
		{
			y--;
			d += 10+((x-y)<<2);
		}
		CircleSimetricPoints(surface,xc,yc,x,y);
	}
}

void RectangleDrawDDA(SDL_Surface *surface,int x,int y,int w,int h)
{
	LineDrawDDA(surface,x,y,x+w,y);
	LineDrawDDA(surface,x+w,y,x+w,y+h);
	LineDrawDDA(surface,x+w,y+h,x,y+h);
	LineDrawDDA(surface,x,y+h,x,y);
}