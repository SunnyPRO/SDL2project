//
//  GUI.cpp
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//

#include "cFont.h"


cFont::cFont()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	Font = NULL;
	mStyle = 0;
	mWidth = 0;
	mHeight = 0;
	mFontSize = 0;
	fgColor = { 0, 0, 0 };
	bkColor = { 0, 0, 0 };
	mTextSurface = NULL;
	cout << "Constructor cFont" << endl;
}

cFont::cFont(SDL_Renderer *renderer)
{
	this->renderer = renderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	Font = NULL;
	mStyle = 0;
	mWidth = 0;
	mHeight = 0;
	mFontSize = 0;
	fgColor = { 0, 0, 0 };
	bkColor = { 0, 0, 0 };
	mTextSurface = NULL;

	cout << "Constructor cFont" << endl;
}

cFont::~cFont()
{
	free();
	Font = NULL;

	cout << " cFont Destroyed! " << endl;
}

void cFont::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

//=================================================================================================
//                    overloaded functions that generate texture from font
//                     put text and color , instead of loading file we use SDL_Surface
//=================================================================================================


bool cFont::generateFromSurface(std::string textureText, SDL_Color textColor,SDL_Renderer *renderer)
{
	//Get rid of preexisting texture
	free();
    
	//Render text surface
	SDL_Surface* mTextSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
	if (mTextSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, mTextSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = mTextSurface->w;
			mHeight = mTextSurface->h;
		}
        
		//Get rid of old surface
		SDL_FreeSurface(mTextSurface);
	}
    
	//Return success
	return mTexture != NULL;
}

bool cFont::generateFromSurface(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();
    
	//Render text surface
	SDL_Surface* mTextSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
	if (mTextSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(this->renderer, mTextSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = mTextSurface->w;
			mHeight = mTextSurface->h;
		}
        
		//Get rid of old surface
		SDL_FreeSurface(mTextSurface);
	}
    
	//Return success
	return mTexture != NULL;
}

bool cFont::generateFromSurfaceEx(string textureText, SDL_Color fgColor, SDL_Color bkColor, int style, TTF_FontRenderTypeFlags typeflags, bool returnToNormal)
{
	//Get rid of preexisting texture
	free();
    
    this->fgColor = fgColor;
    this->bkColor = bkColor;
    this->mStyle = style;
    
	//Render text surface
    TTF_SetFontStyle (Font, style);
    switch(typeflags)
    {
        case TTF_TYPE_SOLID:
            mTextSurface = TTF_RenderText_Solid(Font, textureText.c_str(), fgColor);
            break;
        case TTF_TYPE_SHADED:
            mTextSurface = TTF_RenderText_Shaded(Font, textureText.c_str(), fgColor, bkColor);
            break;
        case TTF_TYPE_BLENDED:
            mTextSurface = TTF_RenderText_Blended(Font, textureText.c_str(), fgColor);
            break;
    }
	if (mTextSurface == NULL)
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(this->renderer, mTextSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = mTextSurface->w;
			mHeight = mTextSurface->h;
		}
        
		//Get rid of old surface
		SDL_FreeSurface(mTextSurface);
	}
    
    //Return to normal Font;
    if ( returnToNormal == true )
    TTF_SetFontStyle (Font, TTF_STYLE_NORMAL);
	//Return success
	return mTexture != NULL;
}

bool cFont::generateFromFile(string path)
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


bool cFont::loadFont(SDL_Renderer *renderer, string font,int fontsize)
{
	//Loading success flag
	bool success = true;
    this->mFontSize = fontsize;
    
	//Open the font
	Font = TTF_OpenFont(font.c_str(), 28);
	if (Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}

bool cFont::loadFont(string font,int fontsize)
{
	//Loading success flag
	bool success = true;
    this->mFontSize = fontsize;
    
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



void cFont::render(int x, int y, SDL_Renderer *renderer,SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

void cFont::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

void cFont::render(int x, int y)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
	//Set clip rendering dimensions
    
	//Render to screen
	SDL_RenderCopyEx(this->renderer, mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}



//--------------------------------------------------------------------------------------------
//                                    Fast
//--------------------------------------------------------------------------------------------



bool cFont::loadFontMap(string dir, int fontsize)
{
	//Loading success flag
	this->mFontSize = fontsize;


	//Open the font
	Font = TTF_OpenFont(dir.c_str(), fontsize);
	if (Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// character and temp rect
	Uint16 ch;

	// we use only ch. from 32 ( see ASCII table )
	for (ch = 32; ch < 128; ch++)
	{
		//  Surface - save a ch. glyphs from TypeFont to personal surface
		glyph_map.Surface[ch] = TTF_RenderGlyph_Solid(Font, ch, { 255, 255, 255 }); // white color for color change 
		if (glyph_map.Surface[ch] == NULL)
		{
			cout << "Surface: " << SDL_GetError() << endl;
			return false;
		}
		
		//  Texture - generating a texture from a surface
		glyph_map.Texture[ch] = SDL_CreateTextureFromSurface(renderer, glyph_map.Surface[ch]);
		if (glyph_map.Texture[ch] == NULL)
		{
			cout << "TEXTURE: " << SDL_GetError() << endl;
			return false;
		}

      }

	return true;
}

bool cFont::render(string text, int x, int y)
{
	int textsize = text.length(); // get a text size
	SDL_Rect rect;
	int cx = x; 
	int cy = y;
	
	for (int ch = 0; ch < textsize ; ++ch)
	{   
		if ((32 >(int)text[ch]) || (128 < (int)text[ch]))
		{
			cout << (int)text[ch] << endl;
			return false;
		}
		// Create a temp rect for every ch. texture , ex. text[ch] = "A" :: (int).. = 65 , (see ASCII table)
		rect = { cx, cy, glyph_map.Surface[(int)text[ch]]->w, glyph_map.Surface[(int)text[ch]]->h };
		if (SDL_RenderCopy(renderer, glyph_map.Texture[(int)text[ch]], NULL, &rect))
		{
			cout << " render : " << SDL_GetError() << endl;
			return false;
		}

		cx = cx + glyph_map.Surface[(int)text[ch]]->w;
	}

	return true;
}


//--------------------------------------------------------------------------------------------


bool cFont::setFontStyle(int style)
{
    if ( NULL != Font)
    {
        TTF_SetFontStyle(Font, style);
        return true;
    }
    return false;
}


//--------------------------------------------------------------------------------------------
//                                   Encapsulates
//--------------------------------------------------------------------------------------------


int cFont::getWidth()
{
	return mWidth;
}

int cFont::getHeight()
{
	return mHeight;
}

int cFont::getStyle()
{
    return mStyle;
}

SDL_Color cFont::getfgColor()
{
    return fgColor;
}

SDL_Color cFont::getbkColor()
{
    return bkColor;
}

int cFont::getfontSize()
{
    return mFontSize;
}


//=================================================================================================
//                                             Global 
//=================================================================================================

