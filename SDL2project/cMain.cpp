#include "cMain.h"



cMain::cMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	char* temp = "0";

	CameraX = 0;
	CameraY = 0;
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new cSDL_Setup(&quit, ScreenWidth, ScreenHeight);
	
	ForestArea = new cEnvironment(ScreenWidth, ScreenHeight, &CameraX, &CameraY, csdl_setup);

	MouseY = 0;
	MouseX = 0;
	bob = new cMainCharacter(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, ForestArea);

	Console = new cConsole(csdl_setup);
    
    cout << "Constructor cMain" << endl;
}


cMain::~cMain()
{
	delete csdl_setup;
	delete ForestArea;
	delete bob;
	delete Console;
    //delete GUI;
    cout<< " cMain Destroyed! "<<endl;
}



////------------------------------------GAME-LOOP------------------------------------------
void cMain::GameLoop()
{
	Console->setFPS(60);

	srand(time(NULL));
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		//==================== Logic part ======================
		SDL_GetMouseState(&MouseX, &MouseY); //primim datele de la coord mousului
		

		//============= PendingEvent - RenderClear =============
		//Handle events on queue
		while (SDL_PollEvent(csdl_setup->GetMainEvent()) != 0)
		{
			//User requests quit
			if (csdl_setup->GetMainEvent()->type == SDL_QUIT)
			{
				quit = true;
			}

			csdl_setup->handleEvent(*csdl_setup->GetMainEvent());

		}
		
		//Clearing the render and updates rests
		csdl_setup->Begin();


	

		//============= Draw level 1 ( Background ) ============
		ForestArea->DrawBack();
		//============= Draw level 2 ( Character ) =============
		bob->Draw();
		bob->Update();
		//============= Draw level 3 ( NPC/OBJECTS/STUFF ) =====
		ForestArea->Update();
		ForestArea->DrawFront();
		//============= Draw level 4 ( GUI / LAST ) ============
		Console->render(2, 20);
		Console->update();
		Console->showFps();

		//==================== Logic part ======================
		Console->calcFps();
		Console->delayFps();


		csdl_setup->End();


	}
}