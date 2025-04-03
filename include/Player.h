#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <cmath>
#include "Constants.h"
#include <iostream>
#include "UtilityFunction.h"
#include "Item.h"

class UIManager;
class Boss ;
class BulletProcessing ;
class Monster;
class Player {
public : 
	bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight ;
	bool isAttacking ;
	double angleWeapon, anglePlayer;
	int level;
	int scores;
	int highScore ;
	int dame;
	int hp;
	int maxHp;
	int exp;
	int maxExpLevel;
	int x, y, speed;
	int currentMap ;
	bool keyBoss;
	Uint32 speedShot, lastTimeShot ;
	void UpdateAngleWeapon(int mouseX, int mouseY) ;
	void UpdateAnglePlayer() ;
	void UpdatePosition(int mouseX, int mouseY, Monster* MonstersOop, Boss* boss, UIManager* UI) ;
	void UpdatePower() ;
	void UpdateMap(BulletProcessing* bulletProcessor) ;
	void HandleHighScore() ;
	
	void Reset() ;
	Player(Item* itemProcessor) ;
private :
	Item* itemProcessor ;
};

#endif