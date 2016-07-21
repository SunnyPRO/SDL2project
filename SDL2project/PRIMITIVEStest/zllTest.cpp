#include "zllTest.h"
#define TWOPI       (2 * 3.14159)
#define ViewPort_W 800
#define ViewPort_H 600


World g_world;
ViewPort g_viewPort;

SDL_Surface *pSurface;
Dodecaedru *pDodecaedru;
std::ofstream logFile;
Uint8 b_Red = 0, b_Green = 0, b_Blue = 0;
Uint32 mappedColor;
int scree_w, screen_h;
wLine *aLine;
char axisToRotate;
static bool runOnce = false;

	void testPrimitive(cSDL_Setup *csdl_setup)
	{
		SDL_Window *pWindow = csdl_setup->GetWindow();
		

				if (runOnce == false)
				{
					logFile.open("lab4 GC log.txt");

					pSurface = SDL_GetWindowSurface(pWindow);
					if (!pSurface)
					{
						if (logFile.is_open())
							logFile << "(!)eroare : " << SDL_GetError() << "\n";
					}

					SDL_GetWindowSize(pWindow, &scree_w, &screen_h);
					pDodecaedru = new Dodecaedru();
					b_Blue = b_Green = b_Red = 255;
					mappedColor = SDL_MapRGB(pSurface->format, b_Red, b_Green, b_Blue);
					DrawingToScreen::Instance()->SetWorldCoord(-10, -10, 20, 15);
					DrawingToScreen::Instance()->SetViewPort(10, 10, scree_w - 10, screen_h - 10);
					pDodecaedru->CalcVertsPos();
					aLine = new wLine(0, 0, 0, 0);
					axisToRotate = 0;
					runOnce = true;
				}

			

			//>>preluam mesajele din firul de asteptare
			while (SDL_PollEvent(csdl_setup->GetMainEvent()))
			{
				if (csdl_setup->GetMainEvent()->type == SDL_QUIT)
				{
					logFile.close();
				}
				else if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
				{
					if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F6)
						if (axisToRotate != 0)
							axisToRotate = 0;
						else
							;
					else if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F7)
						if (axisToRotate != 1)
							axisToRotate = 1;
						else
							;
					else if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F8)
						if (axisToRotate != 2)
							axisToRotate = 2;
						else
							;
					else if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F9)
						axisToRotate = 3;
				}
			}
			//>>lock surface if needed
			if (SDL_MUSTLOCK(pSurface)) SDL_LockSurface(pSurface);
			SDL_FillRect(pSurface, 0, mappedColor);

			DrawingToScreen::Instance()->DrawViewportRect(pSurface);
			aLine->SetColor(0xFF0000);
			aLine->Draw(pSurface, 0, 0, 15, 0);
			aLine->SetColor(0x00FF00);
			aLine->Draw(pSurface, 0, 0, 0, -15);
			aLine->SetColor(0x0000FF);
			aLine->Draw(pSurface, 0, 0, -4, 5);
			//>>facem update la figura
			if (axisToRotate == 0)
				pDodecaedru->RotateY(1.5);
			else if (axisToRotate == 1)
				pDodecaedru->RotateX(1.5);
			else if (axisToRotate == 2)
				pDodecaedru->RotateZ(1.5);
			//>>desenam figura
			pDodecaedru->Draw(pSurface);
			//>>unlock surface if it was locked
			if (pSurface->locked)
				SDL_UnlockSurface(pSurface);
			SDL_UpdateWindowSurface(pWindow);
		
	}