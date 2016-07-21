#pragma once
#ifndef _zllPrimitives_H_
#define _zllPrimitives_H_
#include"../stdafx.h"

//functie [supraincarcata] care coloreaza un pixel
void PutPixel(SDL_Surface *surface,int x,int y,Uint8 red,Uint8 green,Uint8 blue);
void PutPixel(SDL_Surface *surface,int x,int y,Uint32 color);

//functie care returneaza culoarea unui pixel
Uint32 GetPixel(SDL_Surface *surface,int x,int y);
//functie implementata de mine dupa formula dreptei y = ax+b;
void LineDraw(SDL_Surface *surface,int x1,int y1,int x2,int y2);
//algoritmul digital diferential analyzer
void LineDrawDDA(SDL_Surface *surface,int x1,int y1,int x2,int y2);
void LineDrawDDA(SDL_Surface *surface,int x1,int y1,int x2,int y2,int color);
//algoritmul lui bresenham pentru linie
void LineDrawBres(SDL_Surface *surface,int x1,int y1,int x2,int y2);
//algoritmul lui bresenham pentru cerc
void CircleDrawBres(SDL_Surface *surface,int xc,int yc,int r);
// un dreptunghi doar linii
void RectangleDrawDDA(SDL_Surface *surface,int x,int y,int w,int h);


#endif