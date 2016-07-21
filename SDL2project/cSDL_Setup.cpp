#include "cSDL_Setup.h"


cSDL_Setup::cSDL_Setup(bool* quit,int ScreenWidth, int ScreenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		t_cout(12) << "SDL_Init couldn't be created " << SDL_GetError();
		*quit = true; //return iesire in caz de eroare
	}

	//declaram fereastra noastra
	mWindow = NULL;
	mWindow = SDL_CreateWindow("My first RPG", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	if (mWindow == NULL)
	{
		t_cout(12) << "Window couldn't be created " << SDL_GetError();
		*quit = true; //return iesire in caz de eroare
	}
	else
	{
		mMouseFocus = true;      //Mouse focus enabled
		mKeyboardFocus = true;   //Keyboard focus enabled
		mMinimized = false;
		mWidth = SCREEN_WIDTH;   //Set width to window
		mHeight = SCREEN_HEIGHT; //Set height to window
	}


	//Init render
	mRenderer = NULL;
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == NULL)
	{
		t_cout(12) << "Renderer couldn't be created :"<<SDL_GetError();
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
		*quit = true; //return iesire in caz de eroare
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //white

		//Grab window identifier
		mWindowID = SDL_GetWindowID(mWindow);

		//Flag as opened
		mShown = true;
	}


	//Init main event
	mMainEvent = new SDL_Event();

	if (mMainEvent == NULL)
	{
		t_cout(12) << "MAINEVENT couldn't be created " << SDL_GetError();
		*quit = true; //return iesire in caz de eroare
	}
    
    if(TTF_Init() != 0)
    {

		t_cout(12) << "TTF couldn't be initialized " << SDL_GetError();
       *quit = true; //return iesire in caz de eroare
    }

    cout << "Constructor SDL Setup" << endl;
}


cSDL_Setup::~cSDL_Setup()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	delete mMainEvent;
    TTF_Quit();
    cout<< " cSDL_Setup( mWindow/mRenderer/mainevent/TTF ) Destroyed! "<<endl;
}


SDL_Renderer* cSDL_Setup::GetRenderer()
{
	return mRenderer;
}

SDL_Event* cSDL_Setup::GetMainEvent()
{
	return mMainEvent;
}

SDL_Window* cSDL_Setup::GetWindow()
{
	return mWindow;
}

void cSDL_Setup::Begin()
{
	if (!mMinimized)
	{
		//Clear screen
		//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(mRenderer);
	}

}

void cSDL_Setup::End()
{
	if (!mMinimized)
		SDL_RenderPresent(mRenderer); //Update screen
}



void cSDL_Setup::handleEvent(SDL_Event& e)
{
	//If an event was detected for this window
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
	{
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event)
		{
			//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
				mShown = true;
				break;

				//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
				mShown = false;
				break;

				//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				mWidth = e.window.data1;
				mHeight = e.window.data2;
				SDL_RenderPresent(mRenderer);
				break;

				//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(mRenderer);
				break;

				//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
				mMouseFocus = true;
				updateCaption = true;
				break;

				//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
				mMouseFocus = false;
				updateCaption = true;
				break;

				//Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				mKeyboardFocus = true;
				updateCaption = true;
				break;

				//Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
				mKeyboardFocus = false;
				updateCaption = true;
				break;

				//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
				mMinimized = true;
				break;

				//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
				mMinimized = false;
				break;

				//Window restored
			case SDL_WINDOWEVENT_RESTORED:
				mMinimized = false;
				break;

				//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow(mWindow);
				break;
		}


	}
}

void cSDL_Setup::focus()
{
	//Restore window if needed
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}

	//Move window forward
	SDL_RaiseWindow(mWindow);
}

void cSDL_Setup::free()
{
	if (mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int cSDL_Setup::getWidth()
{
	return mWidth;
}

int cSDL_Setup::getHeight()
{
	return mHeight;
}

bool cSDL_Setup::hasMouseFocus()
{
	return mMouseFocus;
}

bool cSDL_Setup::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool cSDL_Setup::isMinimized()
{
	return mMinimized;
}

bool cSDL_Setup::isShown()
{
	return mShown;
}

