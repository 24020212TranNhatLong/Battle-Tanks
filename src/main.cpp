#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../include/Game.h"
#include "../include/MapManager.h"

int main(int argc, char* argv[]) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std :: cerr << "Error!" << SDL_GetError() << std :: endl;
		return -1 ;
	}
	
	SDL_Window* window = SDL_CreateWindow("TankGame by TNL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) ;
	if(!window) {
		std :: cerr << "Error!" << SDL_GetError() << std :: endl;
		SDL_Quit() ;
		return -1 ;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer) {
		std :: cerr << "Error!" << SDL_GetError() << std :: endl ;
		SDL_DestroyWindow(window) ;
		SDL_Quit() ;
		return -1 ;
	}
	
	//khởi tạo SDL_ttf 
	if (TTF_Init() == -1) {
    	std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    	return -1;
	}

	TTF_Font* font = TTF_OpenFont("font/arialbd.ttf", 30);
    if (!font) {
        std :: cerr << "Fail to load font: font/arialbd.ttf" << std :: endl;
        return -1;
    }
	
	//khởi tạo SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
        return -1;
    }
    
    int volume = 40 ;
    Mix_VolumeMusic(volume); //chỉnh âm lượng
    
	
    Mix_Chunk* gameOverMusic = Mix_LoadWAV("sound/gameOver.wav");
    if (!gameOverMusic) {
	    std::cerr << "Failed to load gameOver music! Error: " << Mix_GetError() << std::endl;
	} 
	
	Mix_Chunk* shotSound = Mix_LoadWAV("sound/shot.wav");
	if (!shotSound) {
	    std::cerr << "Failed to load shot sound! Error: " << Mix_GetError() << std::endl;
	}
	
	Mix_Chunk* buttonMusic = Mix_LoadWAV("sound/button.wav");
    if (!buttonMusic) {
	    std::cerr << "Failed to load button music! Error: " << Mix_GetError() << std::endl;
	} 
	
    Mix_Music* backgroundMusic = Mix_LoadMUS("sound/backgroundMusic.mp3");
    if (!backgroundMusic) {
	    std::cerr << "Failed to load background music! Error: " << Mix_GetError() << std::endl;
	} 
    
	SDL_Event event ;
	Item itemProcessor(renderer) ;
	Player player(&itemProcessor);
	player.HandleHighScore() ;
	
	Monster MonstersOop (&player);
	Boss boss(&player) ;
	BulletProcessing bulletProcessor(&player, &MonstersOop, shotSound, &boss);
	ImageProcessing imageProcessor(renderer, &player, &bulletProcessor, &MonstersOop, &boss) ;	
	UIManager UI(renderer, &player, &MonstersOop, font, &boss) ;
	CollisionDetection collisionDetection(&player, &MonstersOop, &bulletProcessor, &itemProcessor, &boss, &UI) ;

	
	imageProcessor.LoadTexture() ;
	UI.loadTexture() ;

	MapManager Map(renderer, &player) ;
	Map.loadMap() ;
	
	itemProcessor.loadTexture() ;
	Game game(renderer, &player, &MonstersOop, buttonMusic, gameOverMusic, backgroundMusic, &bulletProcessor,
			 &collisionDetection, &imageProcessor, &UI, &Map, &itemProcessor, &boss) ;
	
	srand(time(0)) ;
		
	game.Run() ;
	
	TTF_Quit() ;
	SDL_DestroyRenderer(renderer) ;
	SDL_DestroyWindow(window) ;
	Mix_CloseAudio() ;
	SDL_Quit() ;
	return 1 ; 
}