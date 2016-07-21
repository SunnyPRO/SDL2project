#include "cSprite.h"

cSprite::cSprite(SDL_Renderer* passed_renderer, string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY, cCollisionRectangle passed_CollisionRect)
{

	CollisionRect = passed_CollisionRect;

	//crearea texturelor si formele pentru ele
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());
	//.c_str Returns a pointer to an array that contains a null-terminated sequence of characters 
	//(i.e., a C-string) representing the current value of the string object.
	if (image == NULL)
	{
		t_cout(12) << " Couldn't find image! -> " << FilePath.c_str();
	}


	CollisionImage = NULL;
	CollisionImage = IMG_LoadTexture(renderer, "Data/resources/debug/collisionbox.png");
	if (CollisionImage == NULL)
	{
		t_cout(12) << " Couldn't find image! -> " << "CollisionImage";
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);
	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;  //daca divide la 2 atunci toate se deseana pe jum
	crop.h = img_height;

	X_pos = x;
	Y_pos = y;

	Origin_X = 0;// Originea
	Origin_Y = 0;



	CurrentFrame = 0;
	Amount_Frame_X = 0;
	Amount_Frame_Y = 0;

	//--------Camera follow---------
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;
	Camera.w = rect.w;
	Camera.h = rect.h;


    
    cout << "Constructor Sprite" << endl;
}

cSprite::~cSprite()
{
	SDL_DestroyTexture(image);
    cout<< " cSprite Destroyed! "<<endl;
}


void cSprite::Draw()
{
	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;

	CollisionRect.SetX(rect.x + *CameraX);
	CollisionRect.SetY(rect.y + *CameraY);

	SDL_RenderCopy(renderer, image, &crop, &Camera);

    
    const SDL_Rect &GetRectangle = CollisionRect.GetRectangle();

	SDL_RenderCopy(renderer, CollisionImage, NULL, &GetRectangle);
}

void cSprite::DrawSteady()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
    
    const SDL_Rect &GetRectangle = CollisionRect.GetRectangle();
	SDL_RenderCopy(renderer, CollisionImage, NULL, &GetRectangle);
}

void cSprite::SetX(float X)
{
	X_pos = X;

	rect.x = int(X_pos - Origin_X);
}

void cSprite::SetY(float Y)
{
	Y_pos = Y;

	rect.y = int(Y_pos - Origin_Y);
}

void cSprite::SetPosition(float X, float Y)
{
	X_pos = X;
	Y_pos = Y;

	rect.x = int(X_pos - Origin_X);
	rect.y = int(Y_pos - Origin_Y);
}

float cSprite::GetX()
{
	return X_pos;
}

float cSprite::GetY()
{
	return Y_pos;
}

//-------------Setarea originii pentru obiect----------
void cSprite::SetOrigin(float X, float Y)
{
	Origin_X = X;
	Origin_Y = Y;

	SetPosition(GetX(), GetY());
}

void cSprite::SetWidth(int W)
{
	rect.w = W;
}

void cSprite::SetHeight(int H)
{
	rect.h = H;
}

int cSprite::GetWidth()
{
	return rect.w;
}

int cSprite::GetHeight()
{
	return rect.h;
}

//--------------Animatie------------------------------

void cSprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
	if (animationDelay + Speed < SDL_GetTicks())
	{

		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;
		crop.x = CurrentFrame * (img_width / Amount_Frame_X);
		crop.y = Row * (img_height / Amount_Frame_Y);
		crop.w = img_width / Amount_Frame_X;
		crop.h = img_height / Amount_Frame_Y;

		animationDelay = SDL_GetTicks();
	}
}

void cSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
	Amount_Frame_X = passed_Amount_X;
	Amount_Frame_Y = passed_Amount_Y;
}

bool cSprite::isColliding(cCollisionRectangle theCollider)
{

	return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x
			 || CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y
			 || CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w
			 || CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h);
	//return (SDL_IntersectRect(&CollisionRect.GetRectangle(), &theCollider.GetRectangle(), &TEMPrect.GetRectangle()));
	//return (SDL_HasIntersection(&CollisionRect.GetRectangle(), &theCollider.GetRectangle()));
}
