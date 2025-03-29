#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <cmath>
#include "Constants.h"
#include <iostream>
#include "UtilityFunction.h"

class Monster ;
class Player {
public : 
	bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight ;
	bool isAttacking ;
	double angleWeapon, anglePlayer;
	int level;
	int scores;
	int dame;
	int hp;
	int maxHp;
	int exp;
	int maxExpLevel;
	int x, y, speed;
	Uint32 speedShot, lastTimeShot ;
	void UpdateAngleWeapon(int mouseX, int mouseY) ;
	void UpdateAnglePlayer() ;
	void UpdatePosition(int mouseX, int mouseY, Monster* MonstersOop) ;
	void UpdatePower() ;
	void Reset() ;
	Player() ;
};

#endif