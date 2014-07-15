#include "SDL_Setup.h"


CSDL_Setup::CSDL_Setup(bool* quit,int ScreenWidth, int ScreenHeight)
{
	cout << "Constructor SDL Setup" << endl;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		t_cout(12) << "SDL_Init couldn't be created";
		*quit = true; //return iesire in caz de eroare
	}

	//declaram fereastra noastra
	window = NULL;
	window = SDL_CreateWindow("My first RPG", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		t_cout(12) << "Window couldn't be created";
		*quit = true; //return iesire in caz de eroare
	}


	//declaram renderul
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		t_cout(12) << "Renderer couldn't be created";
		*quit = true; //return iesire in caz de eroare
	}


	//cream evenimentul
	mainEvent = new SDL_Event();

	if (mainEvent == NULL)
	{
		t_cout(12) << "MAINEVENT couldn't be created";
		*quit = true; //return iesire in caz de eroare
	}
    
    if(TTF_Init() != 0)
    {

        t_cout(12) << "TTF couldn't be initialized";
       *quit = true;
    }
}


CSDL_Setup::~CSDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
    TTF_Quit();
}


SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(mainEvent); // pending event
	SDL_RenderClear(renderer); //sterge
}

void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer); // face refresh sau update la screen
}