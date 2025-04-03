#include "../include/MapManager.h"


MapManager :: MapManager(SDL_Renderer* renderer, Player* player) 
	: renderer(renderer), player(player) 
}

void MapManager :: loadMap() {
	
	mapGame0 = IMG_LoadTexture(renderer, "assets/TiledMap/map0.png") ;
	
	if(!mapGame0) {
		std :: cout << "Fail to load file : assets/TiledMap/Tiledset.png\n" << SDL_GetError() << std :: endl ; 
	} else std :: cout << "Loaded : assets/TiledMap/map0.png" << std :: endl ;
	
	mapGame1 = IMG_LoadTexture(renderer, "assets/TiledMap/map1.png") ;
	
	if(!mapGame1) {
		std :: cout << "Fail to load file : assets/TiledMap/Tiledset.png\n" << SDL_GetError() << std :: endl ; 
	} else std :: cout << "Loaded : assets/TiledMap/map1.png" << std :: endl ;
	
	mapGame2 = IMG_LoadTexture(renderer, "assets/TiledMap/map2.png") ;
	
	if(!mapGame2) {
		std :: cout << "Fail to load file : assets/TiledMap/Tiledset.png\n" << SDL_GetError() << std :: endl ; 
	} else std :: cout << "Loaded : assets/TiledMap/map2.png" << std :: endl ;
	
	mapGame3 = IMG_LoadTexture(renderer, "assets/TiledMap/map3.png") ;
	
	if(!mapGame3) {
		std :: cout << "Fail to load file : assets/TiledMap/Tiledset.png\n" << SDL_GetError() << std :: endl ; 
	} else std :: cout << "Loaded : assets/TiledMap/map3.png" << std :: endl ;
	
}

void MapManager::RenderMap() {
    switch (player->currentMap) {
        case 0:
            if (mapGame0) SDL_RenderCopy(renderer, mapGame0, NULL, NULL);
            break;
        case 1:
            if (mapGame1) SDL_RenderCopy(renderer, mapGame1, NULL, NULL);
            break;
        case 2:
            if (mapGame2) SDL_RenderCopy(renderer, mapGame2, NULL, NULL);
            break;
        case 3:
            if (mapGame3) SDL_RenderCopy(renderer, mapGame3, NULL, NULL);
            break;
    }
}





