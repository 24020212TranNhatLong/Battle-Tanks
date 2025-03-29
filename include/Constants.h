#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1024 ;
const int SCREEN_HEIGHT = 576 ;
const int FRAME_TANK_DELAY = 90 , FRAME_WEAPON_DELAY = 10 ;
const int sizePlayerX = 64, sizePlayerY = 64, sizeWeaponX = 64, sizeWeaponY = 64, sizeBulletX = 8, sizeBulletY = 8;
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

//tọa độ, kích thước vật cản
const SDL_Rect wall1 = {160, 250, 50, 30} ;
const SDL_Rect wall2 = {290, 370, 50, 40} ;
const SDL_Rect wall3 = {680, 185, 50, 35} ;
const SDL_Rect wall4 = {450, 240, 110, 110} ;

//phuong trinh duong xien cua ho nuoc
//duong xien 1 : -x-y+667
//duong xien 2 :  x-y-318
//duong xien 3 :  x-y-195
//duong xien 4 :  -x-y-901 
#endif				