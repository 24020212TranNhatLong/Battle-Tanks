#ifndef BOSS_H
#define BOSS_H

#include <SDL2/SDL.h>
#include "UtilityFunction.h"
#include "Constants.h"
#include "Player.h"

class Player;
class Boss {
public :
	int x, y, hp, maxHp , dame, speed, speedBullet, speedShot;
	float angleBody, angleWeapon, targetAngle ;
	int lastTimeShot;
	Boss(Player* player) ;
	void move() ;
	void attack() ;
	void updateAngle() ;
	void Reset() ;
	Uint32 lastChangeTime;
	bool changeDirection, isShot;
private :
	Player* player ;
};
#endif 