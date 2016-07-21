//
//  GUI.h
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//
#pragma once

#ifndef __SDL2__cFont__
#define __SDL2__cFont__

#include "stdafx.h"
#include "cSDL_Setup.h"

#endif /* defined(__SDL2__cFont__) */

enum TTF_FontRenderTypeFlags
{
	TTF_TYPE_SOLID,
	TTF_TYPE_SHADED,
	TTF_TYPE_BLENDED
};



class cFont
{
public:

	cFont();
	cFont(SDL_Renderer *renderer);

	void free();
	~cFont();


	//=================================================================================================
	//                                            METHODS
	//=================================================================================================
	//                                             SLOW 
	//=================================================================================================
	//    RENDERER NEEDED
	bool loadFont(SDL_Renderer *renderer, string font, int fontsize);
	bool generateFromSurface(string textureText, SDL_Color textColor, SDL_Renderer *renderer);
	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	//    NO RENDERER ( copied on creation obj / init. constructor )
	bool loadFont(string font, int fontsize);
	bool generateFromSurface(string textureText, SDL_Color textColor); //suffer from changing the mStyle and other exterior TTF modifiers
	bool generateFromSurfaceEx(string textureText, SDL_Color fgColor, SDL_Color bkColor, int style, TTF_FontRenderTypeFlags typeflags, bool returnToNormal);  // don't suffer from changing the mStyle, can return (T/F) normal mStyle to other surfaces after generation
	void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void render(int x, int y);
	bool generateFromFile(string path);


	int getWidth();
	int getHeight();
	int getStyle();
	SDL_Color getfgColor();
	SDL_Color getbkColor();
	int getfontSize();

	bool setFontStyle(int style);
	inline void setRenderer(SDL_Renderer* renderer)
	{
		this->renderer = renderer;
	}

	//=================================================================================================
	//                                            FAST
	//=================================================================================================

	//       Map with characters saved in texture and surfaces , 128 pieces
	class GLYPH_MAP
	{
	public:
		GLYPH_MAP()
		{
			for (int i = 0; i < 128; i++)
			{
				Surface[i] = NULL;
				Texture[i] = NULL;
			}
		}
		~GLYPH_MAP()
		{
			for (int i = 0; i < 128; i++)
			{
				if (Surface[i] != NULL)
				{
					SDL_FreeSurface(Surface[i]);
					Surface[i] = NULL;
				}
				if (Texture[i] != NULL)
				{
					SDL_DestroyTexture(Texture[i]);
					Texture[i] = NULL;
				}
			}

			cout << " GLYPH MAP Destroyed!";
		}


		SDL_Texture *Texture[128];   // 128 pieces of ch. saved in textures
		SDL_Surface *Surface[128];   // 128 surfaces that know every ch. size
	};

	bool loadFontMap(string dir, int fontsize);
	bool render(string text, int x, int y);



private:
	SDL_Texture* mTexture;
	SDL_Color fgColor;
	SDL_Color bkColor;
	SDL_Renderer *renderer;
	SDL_Surface* mTextSurface;

	cSDL_Setup *csdl_setup;
	GLYPH_MAP glyph_map;

	int mStyle;
	int mWidth;
	int mHeight;
	int mFontSize;

	TTF_Font *Font;



};


//=================================================================================================
//                                             Global 
//=================================================================================================

/*  -text
	-fontsize
	-coord. x
	-coord. y
	*/
static void simpledrawText(string text, int fontsize, int x, int y, SDL_Renderer* renderer)
{
	static cFont staticFont(renderer);
	static bool runOnce = true;
	if (runOnce)
	{
		staticFont.loadFontMap("Tahoma.ttf", fontsize);
		runOnce = false;
	}
	staticFont.render(text, x, y);
}

