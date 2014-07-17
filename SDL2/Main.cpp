#include "Main.h"


CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	char* temp = "0";

	CameraX = 0;
	CameraY = 0;
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);
	
	ForestArea = new CEnvironment(ScreenWidth, ScreenHeight, &CameraX, &CameraY, csdl_setup);

	MouseY = 0;
	MouseX = 0;
	bob = new MainCharacter(csdl_setup, &MouseX, &MouseY, &CameraX, &CameraY, ForestArea);


	tdates.A = "0";
	tdates.B = "0";
	tdates.C = "0";
	tdates.D = "0";
    

	Console = new CConsole(csdl_setup, tdates);
    
    GUI = new CFont(csdl_setup->GetRenderer());
    GUI->loadFont("Tahoma.ttf",14);
    
    cout << "Constructor CMain" << endl;
}


CMain::~CMain()
{
	delete csdl_setup;
	delete ForestArea;
	delete bob;
	delete Console;
    delete GUI;
    cout<< " CMain Destroyed! "<<endl;
}



////------------------------------------GAME-LOOP------------------------------------------
void CMain::GameLoop()
{
	srand(time(NULL));
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX, &MouseY); //primim datele de la coord mousului

		//Draw level 1
		ForestArea->DrawBack();



		//Draw level 2
		bob->Draw();    
		bob->Update();


		//Draw level 3
		ForestArea->Update();
		ForestArea->DrawFront();
		
		Console->cgetDates(bob->returnDates(tdates));
		Console->render(2, 20);
		Console->update();
		
        SDL_SetRenderDrawColor(csdl_setup->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF); //white
        {
            GUI->generateFromSurface("X:"+to_string(MouseX), { 0 , 0 , 0 } );
            GUI->render(MouseX+15,MouseY-10);
            GUI->generateFromSurface("Y:"+to_string(MouseY), { 0 , 0 , 0 } );
            GUI->render(MouseX+15,MouseY);
        }
        

		csdl_setup->End();
	}
}


