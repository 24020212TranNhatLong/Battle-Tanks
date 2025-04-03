#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include <vector>

const int SCREEN_WIDTH = 1024 ;
const int SCREEN_HEIGHT = 576 ;
const int BAR_WIDTH = 600;
const int BAR_HEIGHT = 30;
const int SLIDER_WIDTH = 15;
const int SLIDER_HEIGHT = 40;

const int FRAME_TANK_DELAY = 90 , FRAME_WEAPON_DELAY = 10, FRAME_ITEM_DELAY = 20, FRAME_BULLET_DELAY = 100 ;
const int FRAME_COUNT_BODYBOSS = 2, FRAME_COUNT_WEAPONBOSS = 11, FRAME_COUNT_BULLETBOSS = 6 ;
const int sizePlayerX = 64, sizePlayerY = 64,
 		sizeWeaponX = 64, sizeWeaponY = 64,
  		sizeBulletX = 8, sizeBulletY = 8,
  		sizeBodyBossX = 128, sizeBodyBossY = 128 ,
  		sizeBulletBossX = 24, sizeBulletBossY = 24 ;
const int sizeHpX = 48, sizeHpY = 16;
const double PI =  3.1415926535897932384626 ;

const SDL_Rect btnPlay = { 450, 190, 150, 40 };  //nút play
const SDL_Rect btnExit = { 450, 310, 150, 40 };  //nút exit
const SDL_Rect btnSetting = {450, 250, 150, 40}; //nút setting
const SDL_Rect btnPause = {983, 11, 33, 36} ;  //nút pause
const SDL_Rect btnResume = {362, 186, 300, 100};  //nút resume
const SDL_Rect btnQuitPause = {362, 290, 300, 100} ;  //nút quit ở pause menu  
const SDL_Rect btnQuitGameOver = {447, 320, 150, 50} ;  //nút quit ở game over
const SDL_Rect btnQuitSetting = {945, 7, 70, 70} ;  //nút quit ở setting

const SDL_Rect m0wall1 = {0, 0, 64, 224} ;
const SDL_Rect m0wall2 = {608, 0, 416, 64} ;
const SDL_Rect m0wall3 = {960, 64, 64, 160} ;
const SDL_Rect m0wall4 = {960, 352, 64, 160} ;
const SDL_Rect m0wall5 = {0, 512, 1024, 64} ;
const SDL_Rect m0wall6 = {0, 352, 64, 160} ;
const SDL_Rect m0wall7 = {0, 0, 448, 64} ;

const SDL_Rect m1wall1 = {0, 0, 1024, 64} ;
const SDL_Rect m1wall2 = {0, 0, 64, 1024} ;
const SDL_Rect m1wall3 = {960, 0, 64, 576} ;
const SDL_Rect m1wall4 = {0, 512, 384, 64} ;
const SDL_Rect m1wall5 = {640, 512, 384, 64} ;


const SDL_Rect m2wall1 = {0, 0, 1024, 64} ;
const SDL_Rect m2wall2 = {0, 0, 64, 576} ;
const SDL_Rect m2wall3 = {0, 512, 1024, 64} ;
const SDL_Rect m2wall4 = {960, 0, 64, 224} ;
const SDL_Rect m2wall5 = {960, 352, 64, 224} ;
const SDL_Rect m2wall6 = {192, 256, 192, 64} ;
const SDL_Rect m2wall7 = {640, 256, 192, 64} ;

const SDL_Rect m3wall1 = {0, 0, 1024, 64} ;
const SDL_Rect m3wall2 = {0, 512, 1024, 64} ;
const SDL_Rect m3wall3 = {0, 0, 64, 224} ;
const SDL_Rect m3wall4 = {0, 352, 64, 224} ;
const SDL_Rect m3wall5 = {960, 0, 64, 576} ;
const SDL_Rect m3wall6 = {224, 192, 64, 192} ;
const SDL_Rect m3wall7 = {480, 192, 64, 192} ;
const SDL_Rect m3wall8 = {736, 192, 64, 192} ;

//std :: vector<SDL_Rect> wallMap0 = {m0wall1, m0wall2, m0wall3, m0wall4, m0wall5, m0wall6, m0wall7} ;
extern std :: vector<SDL_Rect> wallMap0 ;
extern std :: vector<SDL_Rect> wallMap1 ;
extern std :: vector<SDL_Rect> wallMap2 ;
extern std :: vector<SDL_Rect> wallMap3 ;

#endif				