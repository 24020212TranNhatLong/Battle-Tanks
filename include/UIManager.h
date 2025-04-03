#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Monster.h"
#include "UtilityFunction.h"

#include "Boss.h"

class UIManager {
public :
	UIManager(SDL_Renderer* renderer, Player* player, Monster* MonstersOop, TTF_Font* font, Boss* boss) ;
	void loadTexture() ;
	void RenderHP() ;
	void RenderEXP() ;
	void RenderBGR() ;
	void RenderTable() ;
	void RenderPauseMenu() ;
	void RenderButtonPause() ;
	void RenderScores() ;
	void RenderGameOver() ;
	void RenderSetting() ;
	void RenderWin() ;
	void RenderNotificationBoss() ;
	void RenderNotificationWhenCollectBox() ;
	void HandleInput(SDL_Event event) ;	
	char message[50];
	bool notiBox ;
	Uint32 startTime ;
private :
	SDL_Renderer* renderer ;
	SDL_Texture* background ;
	SDL_Texture* table ;
	SDL_Texture* menuPause;
	SDL_Texture* buttonPause ;
	SDL_Texture* pause_Resume ;
	SDL_Texture* pause_Quit ;
	SDL_Texture* scoreTexture ;
	SDL_Texture* gameOver ;
	SDL_Texture* win ;
	SDL_Texture* setting ;
	std :: vector<SDL_Texture*> framesHP ;
	std :: vector<SDL_Texture*> framesEXP ;
	Player* player;
	Monster* MonstersOop ;
	TTF_Font* font ;
	int lastScore;
	bool notiBoss;
	Uint32 startTimeBoss ;
	Boss* boss ;
};

#endif