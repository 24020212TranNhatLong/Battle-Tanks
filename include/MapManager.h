#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include "Player.h"
#include "Constants.h"

class MapManager {
public :
	MapManager(SDL_Renderer* renderer, Player* player) ;
	void loadMap() ;
	void RenderMap() ;
private :
	SDL_Renderer* renderer ;
	SDL_Texture* mapGame ;
	SDL_Texture* mapGame0 ;
	SDL_Texture* mapGame1 ; 
	SDL_Texture* mapGame2 ;
	SDL_Texture* mapGame3 ; //boss
	Player* player ;
};
#endif