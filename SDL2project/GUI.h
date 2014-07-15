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
        const std::string resPath = "Date/fonts/";
        //We'll render the string "TTF fonts are cool!" in white
        //Color is in RGBA format
        color = { 255, 255, 255, 255 };
        image = renderText("TTF fonts are cool!", resPath + "FreeSans.ttf",
                                        color, 64, csdl_setup->GetRenderer());
        if (image == nullptr){
            cout << " ERROR ON INITIALIZING TEXTURE IMAGE FOR TEXT/FONT ! ! ! "<<endl;
        }
        //Get the texture w/h so we can center it in the screen
        iW=100;
        iH=100;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        
        coords = { 0,0 };
        
    }
    
    
    
    // Methods
    
    SDL_Texture  *renderText(const std::string &message,
                            const std::string &fontFile,
                            SDL_Color color,
                            int fontSize,
                            SDL_Renderer *renderer);
    
    void drawText(int x,int y);
    
    
private:
    
    typedef struct coord2D
    {
        int x;
        int y;
    } coord2D; // x, y
    
    CSDL_Setup* csdl_setup;
    SDL_Texture *image;
    SDL_Color color;
    int iW;
    int iH;
    
    coord2D coords;
    
};

