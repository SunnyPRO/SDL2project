#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer, string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY, CCollisionRectangle passed_CollisionRect)
{

	CollisionRect = passed_CollisionRect;
	TEMPrect = passed_CollisionRect;

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

	
	TEMPchar.A = new char;
	TEMPchar.B = new char;
	TEMPchar.D = new char;
	TEMPchar.C = new char;
	TEMPchar.E = new char;
	TEMPchar.F = new char;
	for (int i = 0; i < 4; i++)
		TEMPint[i] = 0;
    
    cout << "Constructor Sprite" << endl;
}

CSprite::~CSprite()
{
	SDL_DestroyTexture(image);
    cout<< " CSprite Destroyed! "<<endl;
}


void CSprite::Draw()
{
	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;

	CollisionRect.SetX(rect.x + *CameraX);
	CollisionRect.SetY(rect.y + *CameraY);

	SDL_RenderCopy(renderer, image, &crop, &Camera);

    
    const SDL_Rect &GetRectangle = CollisionRect.GetRectangle();

	SDL_RenderCopy(renderer, CollisionImage, NULL, &GetRectangle);
}

void CSprite::DrawSteady()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
    
    const SDL_Rect &GetRectangle = CollisionRect.GetRectangle();
	SDL_RenderCopy(renderer, CollisionImage, NULL, &GetRectangle);
}

void CSprite::SetX(float X)
{
	X_pos = X;

	rect.x = int(X_pos - Origin_X);
}

void CSprite::SetY(float Y)
{
	Y_pos = Y;

	rect.y = int(Y_pos - Origin_Y);
}

void CSprite::SetPosition(float X, float Y)
{
	X_pos = X;
	Y_pos = Y;

	rect.x = int(X_pos - Origin_X);
	rect.y = int(Y_pos - Origin_Y);
}

float CSprite::GetX()
{
	return X_pos;
}

float CSprite::GetY()
{
	return Y_pos;
}

//-------------Setarea originii pentru obiect----------
void CSprite::SetOrigin(float X, float Y)
{
	Origin_X = X;
	Origin_Y = Y;

	SetPosition(GetX(), GetY());
}

void CSprite::SetWidth(int W)
{
	rect.w = W;
}

void CSprite::SetHeight(int H)
{
	rect.h = H;
}

int CSprite::GetWidth()
{
	return rect.w;
}

int CSprite::GetHeight()
{
	return rect.h;
}

//--------------Animatie------------------------------

void CSprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
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

void CSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
	Amount_Frame_X = passed_Amount_X;
	Amount_Frame_Y = passed_Amount_Y;
}

bool CSprite::isColliding(CCollisionRectangle theCollider)
{
	TEMPint[0] = theCollider.GetRectangle().x;
	TEMPint[1] = theCollider.GetRectangle().y;
	TEMPint[2] = theCollider.GetRectangle().w;
	TEMPint[3] = theCollider.GetRectangle().h;
	
	cout << endl << " X : " << CollisionRect.GetRectangle().x << " Y: " << CollisionRect.GetRectangle().y << endl
		<< " W : " << CollisionRect.GetRectangle().w << " H: " << CollisionRect.GetRectangle().h << endl;



	return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x
			 || CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y
			 || CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w
			 || CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h);
	//return (SDL_IntersectRect(&CollisionRect.GetRectangle(), &theCollider.GetRectangle(), &TEMPrect.GetRectangle()));
	//return (SDL_HasIntersection(&CollisionRect.GetRectangle(), &theCollider.GetRectangle()));
}

valDates CSprite::returnDates(valDates tdates)
{
	sprintf(TEMPchar.A, "%d" , TEMPint[0]);
    tdates.A = TEMPchar.A;
    sprintf(TEMPchar.B, "%d" , TEMPint[1]);
    tdates.B = TEMPchar.B;
    sprintf(TEMPchar.C, "%d" , TEMPint[2]);
    tdates.C = TEMPchar.C;
    sprintf(TEMPchar.D, "%d" , TEMPint[3]);
    tdates.D = TEMPchar.D;
    sprintf(TEMPchar.E, "%d" , (int)*CameraX);
    tdates.E = TEMPchar.E;
    sprintf(TEMPchar.F, "%d" , (int)*CameraY);
    tdates.F = TEMPchar.F;


	return tdates;
}
