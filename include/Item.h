#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL_Image.h>
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "Constants.h"

struct item {
	int x, y, currentFrame;
	Uint32 lastTime = 0 ;	
	item(int _x, int _y) {
		x = _x ;
		y = _y ;
		currentFrame = 0;
		lastTime = 0 ;
	}
};

class Item {
public :
	Item(SDL_Renderer* renderer) ;
	void loadTexture() ;
	void updateAnimation() ;
	void RenderHp() ;
	void RenderExp() ;
	void RenderBox() ;
	std :: vector<item> hpList;
	std :: vector<item> expList;
	std :: vector<item> boxList;
private :
	std :: vector<SDL_Texture*> hp;
	std :: vector<SDL_Texture*> exp;
	std :: vector<SDL_Texture*> box;
	SDL_Renderer* renderer ;
};

#endif