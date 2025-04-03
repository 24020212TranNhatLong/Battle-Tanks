#include "../include/Item.h"

Item :: Item(SDL_Renderer* renderer) 
	: renderer(renderer)
	{
	}
	
void Item :: loadTexture() {
	for (int i = 0; i < 8; i++) {
        char filePath[50];
        if (i < 6) {
            sprintf(filePath, "assets/item/box/box%d.png", i);
            SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
            if (!texture) {
                printf("Failed to load texture: %s, Error: %s\n", filePath, SDL_GetError());
            } else {
                box.push_back(texture);
                printf("Loaded: %s\n", filePath);
            }
        }

        sprintf(filePath, "assets/item/hp/hp%d.png", i);
        SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
        if (!texture) {
               printf("Failed to load texture: %s, Error: %s\n", filePath, SDL_GetError());
        } else {
            hp.push_back(texture);
            printf("Loaded: %s\n", filePath);
        }


        sprintf(filePath, "assets/item/exp/exp%d.png", i);
        texture = IMG_LoadTexture(renderer, filePath);
        if (!texture) {
            printf("Failed to load texture: %s, Error: %s\n", filePath, SDL_GetError());
        } else {
            exp.push_back(texture);
            printf("Loaded: %s\n", filePath);
        }
	}
}


void Item :: updateAnimation() {
	Uint32 currentTime = SDL_GetTicks() ;
	for(auto& it : boxList) {
		if(currentTime >= it.lastTime + FRAME_ITEM_DELAY) {
			it.currentFrame = (it.currentFrame + 1) % 6 ;
			it.lastTime = currentTime ;
		}
	}
	
	for(auto& it : hpList) {
		if(currentTime >= it.lastTime + FRAME_ITEM_DELAY) {
			it.currentFrame = (it.currentFrame + 1) % 8 ;
			it.lastTime = currentTime ;
		}
	}
	
	for(auto& it : expList) {
		if(currentTime >= it.lastTime + FRAME_ITEM_DELAY) {
			it.currentFrame = (it.currentFrame + 1) % 8 ;
			it.lastTime = currentTime ;
		}
	}
}

void Item :: RenderHp() {
	for(auto& it : hpList) {
		SDL_Rect hpRect = {it.x, it.y, 32, 32} ;
		SDL_RenderCopy(renderer, hp[it.currentFrame], NULL, &hpRect) ;
	}
	
}

void Item :: RenderBox() {
	for(auto& it : boxList) {
		SDL_Rect boxRect = {it.x, it.y, 32, 32} ;
		SDL_RenderCopy(renderer, box[it.currentFrame], NULL, &boxRect) ;
	}
}

void Item :: RenderExp() {
	for(auto& it : expList) {
		SDL_Rect expRect = {it.x, it.y, 32, 32} ;
		SDL_RenderCopy(renderer, exp[it.currentFrame], NULL, &expRect) ;
	}
}