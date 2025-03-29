#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include "Constants.h"

class MapManager {
public :
	MapManager(SDL_Renderer* renderer) ;
	void loadMap() ;
	void RenderMap() ;
private :
	SDL_Renderer* renderer ;
	SDL_Texture* mapGame ;
};
#endif