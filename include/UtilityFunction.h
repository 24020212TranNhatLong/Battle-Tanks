#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

float lerp(float a, float b, float t) ;

float shortestRotation(float currentAngle, float targetAngle) ;

bool checkCollision(SDL_Rect a, SDL_Rect b) ;

bool isMouseInside(SDL_Rect button, int mouseX, int mouseY) ;

bool checkBulletOutOfScreen(int x, int y) ;

bool checkTankOutOfMap(SDL_Rect a) ;
#endif