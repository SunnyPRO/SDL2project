//
//  GUI.h
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//

#ifndef __SDL2__GUI__
#define __SDL2__GUI__

#
#include "stdafx.h"
#include "SDL_Setup.h"


#endif /* defined(__SDL2__GUI__) */


class CGUI
{
public:
    
    CGUI()
    {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        Font = NULL;
        cout << "Constructor CGUI" << endl;
    }
    
    CGUI(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        Font = NULL;
        cout << "Constructor CGUI" << endl;
    }
    
    ~CGUI()
    {
        free();
        
       // TTF_CloseFont(Font);
        Font  = NULL;
        
        cout<< " CGUI Destroyed! "<<endl;
    }
    
    
    
    // Methods
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *renderer);
    void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    bool loadMedia(SDL_Renderer *renderer,string font);
    
    
    //no renderer ( init on create obj / init constructor )
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
    void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
    void render(int x, int y);
    bool loadMedia(string font,string text);
    
    
    int getWidth();
    int getHeight();
    
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

    
    
private:
    
    SDL_Texture* mTexture;
    CSDL_Setup *csdl_setup;
    SDL_Color color;
    SDL_Renderer *renderer;
    
    int mWidth;
	int mHeight;
    
    TTF_Font *Font;

    
};

