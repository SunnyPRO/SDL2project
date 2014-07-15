#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//#include <SDL2_gfxPrimitives.h>
//#include <SDL2_gfxPrimitives_font.h>
#include <SDL_ttf.h>

// if we're compiling for iOS (iPhone/iPad)
#ifdef __IPHONEOS__
#	include <SDL_opengles.h> // we want to use OpenGL ES
#else
#	include <SDL_opengl.h> // otherwise we want to use OpenGL
#endif


#include <iostream> //Project made tools
using namespace std;

//#include <windows.h>
#include <string>

#include <stdio.h> 
//#include <conio.h>
#include <time.h>
#include <stdlib.h>

#include "_tools.h"


struct valDates
{
	char* A;
	char* B;
	char* C;
	char* D;
	char* E;
	char* F;
};



