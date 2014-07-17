//
//  GUI.cpp
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//

#include "Font.h"


//=================================================================================================
//                    overloaded functions that generate texture from font
//                     put text and color , instead of loading file we use SDL_Surface
//=================================================================================================



bool CFont::generateFromSurface(std::string textureText, SDL_Color textColor,SDL_Renderer *renderer)
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



bool CFont::generateFromSurface(std::string textureText, SDL_Color textColor)
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



bool CFont::generateFromSurfaceEx(string textureText, SDL_Color fgColor, SDL_Color bkColor, int style, TTF_FontRenderTypeFlags typeflags, bool returnToNormal)
{
	//Get rid of preexisting texture
	free();
    
    this->fgColor = fgColor;
    this->bkColor = bkColor;
    this->style = style;
    
	//Render text surface
    TTF_SetFontStyle (Font, style);
    SDL_Surface* textSurface;
    switch(typeflags)
    {
        case TTF_TYPE_SOLID:
            textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), fgColor);
            break;
        case TTF_TYPE_SHADED:
            textSurface = TTF_RenderText_Shaded(Font, textureText.c_str(), fgColor, bkColor);
            break;
        case TTF_TYPE_BLENDED:
            textSurface = TTF_RenderText_Blended(Font, textureText.c_str(), fgColor);
            break;
    }
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
    
    //Return to normal Font;
    if ( returnToNormal == true )
    TTF_SetFontStyle (Font, TTF_STYLE_NORMAL);
	//Return success
	return mTexture != NULL;
}



bool CFont::generateFromFile(string path)
{
	//Get rid of preexisting texture
	free();
    
	//The final texture
	SDL_Texture* newTexture = NULL;
    
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
        
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
    
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}



//=================================================================================================
//                    overloaded functions for loading fonts
//=================================================================================================


bool CFont::loadFont(SDL_Renderer *renderer, string font,int fontsize)
{
	//Loading success flag
	bool success = true;
    this->fontSize = fontsize;
    
	//Open the font
	Font = TTF_OpenFont(font.c_str(), 28);
	if (Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}


bool CFont::loadFont(string font,int fontsize)
{
	//Loading success flag
	bool success = true;
    this->fontSize = fontsize;
    
	//Open the font
	Font = TTF_OpenFont(font.c_str(), fontsize);
	if (Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}




//=================================================================================================
//                    overloaded functions for update or render a texture on given points/angle..
//=================================================================================================


void CFont::render(int x, int y, SDL_Renderer *renderer,SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

void CFont::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

void CFont::render(int x, int y)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
	//Set clip rendering dimensions
    
	//Render to screen
	SDL_RenderCopyEx(this->renderer, mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}




//--------------------------------------------------------------------------------------------


bool CFont::setFontStyle(int style)
{
    if ( NULL != Font)
    {
        TTF_SetFontStyle(Font, style);
        return true;
    }
    else return false;
}

//--------------------------------------------------------------------------------------------


int CFont::getWidth()
{
	return mWidth;
}


int CFont::getHeight()
{
	return mHeight;
}

int CFont::getStyle()
{
    return style;
}

SDL_Color CFont::getfgColor()
{
    return fgColor;
}

SDL_Color CFont::getbkColor()
{
    return bkColor;
}

int CFont::getfontSize()
{
    return fontSize;
}


