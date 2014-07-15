#pragma once
#include "stdafx.h"
#include "CollisionRectangle.h"

class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY, CCollisionRectangle passed_CollisionRect);
	~CSprite();
	void Draw();
	void DrawSteady();

	void SetX(float X);
	void SetY(float Y);
	void SetPosition(float X, float Y);//FOR SET WE NEED TO OFFSET POS(GET IT)

	float GetX();
	float GetY();

	void SetOrigin(float X, float Y); //setarea originii
	int  GetWidth(); //trebue sa aflam ce dimensiuni are obiectul
	int  GetHeight();
	void SetWidth(int W); //si doar apoi sa setam originea pentru dimens date
	void SetHeight(int H);

	void PlayAnimation(int BeginFrame, int EndFrame,int Row,float Speed); //anim func
	void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y); // seteaza cate desene vor trebui

	bool isColliding(CCollisionRectangle theCollider);

	CCollisionRectangle GetCollisionRect() { return CollisionRect; }

	SDL_Rect GetPositionRect() { return rect; }



	valDates returnDates(valDates tdates);

private:
	CCollisionRectangle CollisionRect;

	float *CameraX;
	float *CameraY;

	float Origin_X; //Puncte de origine
	float Origin_Y; //si anume originea mousului in riferinta cu obj

	float X_pos;
	float Y_pos;


	SDL_Texture* image;
	SDL_Rect rect;//crearea patratului(obj) pentru textura
	SDL_Rect crop;// taierea imaginii
	SDL_Rect Camera;

	SDL_Texture* CollisionImage;

	//vars for animations
	int img_width;
	int img_height;
	int CurrentFrame;
	int animationDelay;

	int Amount_Frame_X;//var in cate parti se imparte spritul
	int Amount_Frame_Y;//sprite cu 4 desene, se imparte la 4

	SDL_Renderer* renderer;

	//Miscellaneous
	//tools_ tool;

	CCollisionRectangle TEMPrect;

	valDates TEMPchar;
	int  TEMPint[4];
};
