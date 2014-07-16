//
//  GUI.cpp
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//

#include "GUI.h"


bool CGUI::loadFromRenderedText(std::string textureText, SDL_Color textColor,SDL_Renderer *renderer)
{
	//Get rid of preexisting texture
	free();
    
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
        
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
    
	//Return success
	return mTexture != NULL;
}

bool CGUI::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();
    
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
        
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
    
	//Return success
	return mTexture != NULL;
}



void CGUI::render(int x, int y, SDL_Renderer *renderer,SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
    
	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void CGUI::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
    
	//Render to screen
	SDL_RenderCopyEx(this->renderer, mTexture, clip, &renderQuad, angle, center, flip);
}



bool CGUI::loadMedia(SDL_Renderer *renderer)
{
	//Loading success flag
	bool success = true;
    
	//Open the font
	Font = TTF_OpenFont("Tahoma.ttf", 28);
	if (Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!this->loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, renderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
    
	return success;
}

bool CGUI::loadMedia()
{
	//Loading success flag
	bool success = true;
    
	//Open the font
	Font = TTF_OpenFont("Tahoma.ttf", 28);
	if (Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!this->loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, this->renderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
    
	return success;
}


//--------------------------------

int CGUI::getWidth()
{
	return mWidth;
}


int CGUI::getHeight()
{
	return mHeight;
}