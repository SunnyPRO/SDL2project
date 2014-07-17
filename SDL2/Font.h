//
//  GUI.h
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//
#pragma once

#ifndef __SDL2__FONT__
#define __SDL2__FONT__

#include "stdafx.h"
#include "SDL_Setup.h"


#endif /* defined(__SDL2__GUI__) */

enum TTF_FontRenderTypeFlags
{
    TTF_TYPE_SOLID,
    TTF_TYPE_SHADED,
    TTF_TYPE_BLENDED
};


class CFont
{
public:
    
    CFont()
    {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        Font = NULL;
        style = 0;
        mWidth = 0;
        mHeight = 0;
        fontSize = 0;
        fgColor = { 0 , 0 , 0};
        bkColor = { 0 , 0 , 0};
        cout << "Constructor CFont" << endl;
    }
    
    CFont(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        Font = NULL;
        style = 0;
        mWidth = 0;
        mHeight = 0;
        fontSize = 0;
        fgColor = { 0 , 0 , 0};
        bkColor = { 0 , 0 , 0};
        cout << "Constructor CFont" << endl;
    }
    
    void free()
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
    
    ~CFont()
    {
        free();
        Font  = NULL;
        
        cout<< " CFont Destroyed! "<<endl;
    }
    
    
    
    //     METHODS
    //    RENDERER NEEDED
    bool generateFromSurface(string textureText, SDL_Color textColor, SDL_Renderer *renderer);
    
    void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    bool loadFont(SDL_Renderer *renderer,string font,int fontsize);
    
    
    //    NO RENDERER ( copied on creation obj / init. constructor )
    
    //suffer from changing the style and other exterior TTF modifiers
    bool generateFromSurface(string textureText, SDL_Color textColor); 
    // don't suffer from changing the style, can return (T/F) normal style to other surfaces after generation
    bool generateFromSurfaceEx(string textureText, SDL_Color fgColor, SDL_Color bkColor, int style, TTF_FontRenderTypeFlags typeflags, bool returnToNormal);
    
    void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
    void render(int x, int y);
    
    bool loadFont(string font,int fontsize);
    
    bool generateFromFile(string path);
    
    
    int getWidth();
    int getHeight();
    int getStyle();
    SDL_Color getfgColor();
    SDL_Color getbkColor();
    int getfontSize();
    
    bool setFontStyle(int style);


    
    
private:

    SDL_Texture* mTexture;
    CSDL_Setup *csdl_setup;
    SDL_Color fgColor;
    SDL_Color bkColor;
    SDL_Renderer *renderer;

    int style;
    int mWidth;
	int mHeight;
    int fontSize;
    
    TTF_Font *Font;
    

    
};

