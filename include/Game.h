#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Constants.h"
#include "ImageProcessing.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "UIManager.h"
#include <iostream>
#include "UtilityFunction.h"
#include "MapManager.h"
#include "Item.h"
#include "Boss.h"

class Game {
public:
    Game(SDL_Renderer* renderer, Player* player, Monster* MonstersOop, 	Mix_Chunk* buttonMusic,	Mix_Chunk* gameOverMusic, Mix_Music* backgroundMusic,
		 BulletProcessing* bulletProcessor, CollisionDetection* collisionDetection,
		 ImageProcessing* imageProcessor, UIManager* UI, MapManager* Map, Item*  itemProcessor, Boss* boss) ;
		
    void Run() ; //vòng lặp chính của game
    void HandleEvents() ; //xử lí sự kiện
    void Update() ; //cập nhật các thuộc tính, đối tượng của game
    void RenderGame() ; //vẽ đồ họa của game
    void RenderBackGround() ; //vẽ ảnh nền
    void RenderMenu() ; //vẽ các menu chức năng
    void UpdateMusic() ;
private:
    SDL_Renderer* renderer ;
    bool running ;
    bool isWaitting ;	
    bool isPlaying ;
    bool isSetting ;
    bool isPause ;
    bool isDead ;
    bool isWin ;
    Player* player ;
    Monster* MonstersOop ;
    BulletProcessing* bulletProcessor ;
    CollisionDetection* collisionDetection ;
    ImageProcessing* imageProcessor ; 
    UIManager* UI ;
    MapManager* Map ;
    Item* itemProcessor ;
    Mix_Chunk* buttonMusic ;
    Mix_Chunk* gameOverMusic ;
    Mix_Music* backgroundMusic ;
    Boss* boss ;
};

#endif
