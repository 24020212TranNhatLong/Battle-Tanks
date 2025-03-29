#ifndef MONSTER_H
#define MONSTER_H

#include "Player.h"
//#include "BulletProcessing.h"
#include <vector>
#include <cmath>
#include <ctime>
#include "Constants.h" 

class BulletProcessing ;

struct Monsters {
    int hp, maxHp, dame, speed;
    int x, y;
    double angleWeapon, angleTank, targetAngleTank, targetAngleWeapon ;
    bool isAttacking, changeDirection, isShotting ;
	Uint32 lastChangeTime, lastTimeAttack, speedShot ;
	int currentFrameWeapon, attackRange;
	Uint32 lastFrameWeaponTime ;
    Monsters(int _x, int _y, Player* player) {
        maxHp = 50 + player->level * 50;
        hp = maxHp ;
        dame = 10 + player->level * 2;
        speed = 2 ;
        x = _x;
        y = _y;
        angleWeapon = 0 ;
        angleTank = 0 ;
        targetAngleTank = 0 ;
        targetAngleWeapon = 0 ;
        attackRange = 495 + player->level * 5 ;
        lastChangeTime = 0 ;
        lastTimeAttack = 0 ;
        isAttacking = false ;
        isShotting = false ;
        changeDirection = false ;
        currentFrameWeapon = 0 ;
        lastFrameWeaponTime = 0 ;
       	if(2500 - player->level*200 > 1000) speedShot = 2500 - player->level*200 ;
       		else speedShot = 1;
    }
};

class Monster {
public:
    Player* player;
    std::vector<Monsters> monsters;
    Monster(Player* player);
	void spawnMonster() ; //tạo ra quái vật mới
	void updateAngleTank() ; //cập nhật góc quay của súng
    void moveMonster(); //di chuyển quái vật
    void attackPlayer(); // Quái tấn công người chơi
	void Reset() ; //đặt lại quái vật
};

#endif
