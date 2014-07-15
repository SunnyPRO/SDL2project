//
//  GUI.cpp
//  SDL2
//
//  Created by Art User on 10.07.14.
//  Copyright (c) 2014 Art User. All rights reserved.
//

#include "GUI.h"


// TTF_Init() must be called before using this function.
// Remember to call TTF_Quit() when done.
SDL_Texture *CGUI::renderText(const std::string &message,
 const std::string &fontFile,
 SDL_Color color,
 int fontSize,
 SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr){
		cout<<"TTF_OpenFont"<<endl;
		return nullptr;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		cout<<"TTF_RenderText"<<endl;
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		cout<<"CreateTexture"<<endl;
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

void CGUI::drawText(int x,int y)
{
    coords.x = x;
    coords.y = y;
}