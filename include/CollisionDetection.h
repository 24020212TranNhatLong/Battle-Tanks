#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "UtilityFunction.h"
#include "Monster.h"
#include "Player.h"
#include "BulletProcessing.h"
#include "Constants.h"

class CollisionDetection {
public :
	CollisionDetection(Player* player, Monster* MonsterOop, BulletProcessing* bulletProcessor) ;
	
	void PlayerAndMonster() ; //hàm xử lí va chạm giữa người chơi và quái vật
	void BulletMonsterAndPlayer() ; //hàm xử lí va chạm giữa người chơi và đạn của quái vật
	void BulletPlayerAndMonster() ; //hàm xử lí va chạm giữa đạn của người chơi và quái vật
	void BulletMonsterAndWall() ; //hàm xử lí va chạm giữa đạn của quái vật và vật cản
	void BulletPlayerAndWall() ; //hàm xử lí va chạm giữa đạn của người chơi và vật cản
private :
	Player* player ;
	Monster* MonsterOop ;
	BulletProcessing* bulletProcessor ;
};

#endif