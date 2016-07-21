#include "cMainCharacter.h"


cMainCharacter::cMainCharacter(cSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, cEnvironment* passed_Environment)
{
	Environment = passed_Environment;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	csdl_setup = passed_SDL_Setup;

	MouseX = passed_MouseX;
	MouseY = passed_MouseY;

	bob = new cSprite(csdl_setup->GetRenderer(), "Data/resources/tom.png", 300, 250, 100, 120, CameraX, CameraY, cCollisionRectangle(275, 220, 50, 30));
	bob->SetUpAnimation(4, 4);// matricele cu animatii, coloane/rinduri
	bob->SetOrigin(bob->GetWidth() / 2.0f, bob->GetHeight());//setarea originii pentru obiect

	timeCheck = SDL_GetTicks();
	Distance = 0;
	Follow = false;
	angle = 0;
	stopAnimation = false;
    
    cout << "Constructor cMainCharacter" << endl;
}


cMainCharacter::~cMainCharacter()
{
	delete bob;
    cout<< " cMainCharacter Destroyed! "<<endl;
}

void cMainCharacter::Draw()
{
	bob->DrawSteady();
}


double cMainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	Distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return Distance;
}

void cMainCharacter::UpdateAnimation()
{
	angle = (atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX)) * (180 / 3.14) + 180;//transform in degress

	if (!stopAnimation)
	if (angle >= 45 && angle <= 135)
	{
		//down
		if (Distance > 15)
			bob->PlayAnimation(0, 3, 0, 200);
		else
			bob->PlayAnimation(1, 1, 0, 200); //idle
	}
	else if (angle >= 135 && angle <= 225)
	{
		//left
		if (Distance > 15)
			bob->PlayAnimation(0, 3, 1, 200);
		else
			bob->PlayAnimation(1, 1, 1, 200); //idle
	}
	else if (angle >= 225 && angle <= 315)
	{
		//up
		if (Distance > 15)
			bob->PlayAnimation(0, 3, 3, 200);
		else
			bob->PlayAnimation(1, 1, 3, 200); //idle
	}
	else if ((angle >= 315 && angle <= 360) || (angle >= 0 && angle <= 45))
	{
		//right
		if (Distance > 15)
			bob->PlayAnimation(0, 3, 2, 200);
		else
			bob->PlayAnimation(1, 1, 2, 200); //idle
	}
}

void cMainCharacter::UpdateControls()
{
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
	{
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			Follow_Point_X = *CameraX - *MouseX + 300;
			Follow_Point_Y = *CameraY - *MouseY + 250;
			Follow = true;
		}
	}

	if ((timeCheck + 10) < SDL_GetTicks() && Follow)
	{
		Distance = GetDistance(*CameraX, *CameraY, Follow_Point_X, Follow_Point_Y);

		if (Distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;


		if (Distance > 15)   //distance maybe 0 , divide by 0 -> Error
		{
			colliding = false;
			for (int i = 0; i<Environment->GetTrees().size(); i++)
			{
				//if (Environment->GetTrees()[i]->GetTrunk()->GetCollisionRect().GetRectangle().x+
				//	Environment->GetTrees()[i]->GetTrunk()->GetCollisionRect().GetRectangle().w >
				//	)
				if (bob->isColliding(Environment->GetTrees()[i]->GetTrunk()->GetCollisionRect()))
				{
					//if (*CameraX != Follow_Point_X)
					//{
					// *CameraX = *CameraX + 1;
					// *CameraY = *CameraY + 1;
					//}
					//if (*CameraY != Follow_Point_Y)
					//{
					// *CameraX = *CameraX + 1;
					// *CameraY = *CameraY + 1;
					//}
						if (*CameraX > Follow_Point_X)
						{
							*CameraX = *CameraX + 1;
						}
						if (*CameraX < Follow_Point_X)
						{
							*CameraX = *CameraX - 1;
						}
						if (*CameraY > Follow_Point_Y)
						{
							*CameraY = *CameraY + 1;
						}
						if (*CameraY < Follow_Point_Y)
						{
							*CameraY = *CameraY - 1;
						}
					Follow_Point_X = *CameraX; 
					Follow_Point_Y = *CameraY;
					Distance = 0;
					Follow = false;
					colliding = true;
				}
			}
			if (!colliding)
			{
				if (*CameraX > Follow_Point_X)
				{
					*CameraX = *CameraX - ((*CameraX - Follow_Point_X) / Distance) * 1.5f;
				}
				if (*CameraX < Follow_Point_X)
				{
					*CameraX = *CameraX - ((*CameraX - Follow_Point_X) / Distance) * 1.5f;
				}
				if (*CameraY > Follow_Point_Y)
				{
					*CameraY = *CameraY - ((*CameraY - Follow_Point_Y) / Distance) * 1.5f;
				}
				if (*CameraY < Follow_Point_Y)
				{
					*CameraY = *CameraY - ((*CameraY - Follow_Point_Y) / Distance) * 1.5f;
				}
			}
		}
		else Follow = false;
		timeCheck = SDL_GetTicks();
	}
	//else Follow = false;     //cat apasa atita si merge
}

void cMainCharacter::Update()
{
	UpdateAnimation();
	UpdateControls();

	//for (int i = 0; i < Environment->GetTrees().size(); i++)
	//{
	//	if (bob->isColliding(Environment->GetTrees()[i]->GetTrunk()->GetCollisionRect()))
	//	{
	//		t_cout(15) << "Colliding with a tree";
	//	}
	//}
}