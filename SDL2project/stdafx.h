#pragma once


#include "cVariables.hpp"

#ifndef __SDL__INCLUDES__
#define __SDL__INCLUDES__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#endif

// if we're compiling for iOS (iPhone/iPad)
#ifdef __IPHONEOS__
#	include <SDL_opengles.h> // we want to use OpenGL ES
#else
#	include <SDL_opengl.h> // otherwise we want to use OpenGL
#endif

#ifndef __DEFAULT__INCLUDES__
#define __DEFAULT__INCLUDES__
#include <iostream> //Project made tools
#include <time.h>
#include <string>
#include <stdio.h> 
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;
#endif


#include "_tools.h"






