#include "../include/MapManager.h"

MapManager :: MapManager(SDL_Renderer* renderer) 
	: renderer(renderer) 
	{
}

void MapManager :: loadMap() {
	mapGame = IMG_LoadTexture(renderer, "assets/TiledMap/map.png") ;
	
	if(!mapGame) {
		std :: cout << "Fail to load file : assets/TiledMap/Tiledset.png\n" << SDL_GetError() << std :: endl ; 
	} else std :: cout << "Loaded : assets/TiledMap/Tiledset.png" << std :: endl ;
}

void MapManager :: RenderMap() {
	SDL_RenderCopy(renderer, mapGame, NULL, NULL) ;
}
