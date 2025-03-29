#include "../include/Monster.h"
#include "../include/BulletProcessing.h"

Monster :: Monster(Player* player) 
	: player(player)
	{
} 

void Monster :: spawnMonster() {
	if(monsters.size() == 0) { //nếu không có con quái nào
		monsters.push_back(Monsters(462, 90, player)) ; //spawn ra 1 con ở giữa
		if(player->level >= 3) monsters.push_back(Monsters(176, 90, player)) ;  //spawn 1 con ở bên trái
		if(player->level >= 6) monsters.push_back(Monsters(785, 90, player)) ;  //spawn 1 con ở bên phải
		
		//đặt lại vị trí của người chơi
		player->x = 446 ;
		player->y = 434 ;
	}
}

void Monster :: updateAngleTank() {
	Uint32 currentTime = SDL_GetTicks() ; //lấy thời gian
	
	//duyệt từng quái vật
	for(auto &monster : monsters) {
		if( currentTime-monster.lastChangeTime >= 5000 || monster.changeDirection) {
			if(rand() % 2 == 1) monster.targetAngleTank = fmod(monster.targetAngleTank - 90 + 360, 360);
				else monster.targetAngleTank = fmod(monster.targetAngleTank + 90, 360) ;  
			monster.lastChangeTime = currentTime ;
			monster.changeDirection = false ;
		}
		
		 // Tính góc quay ngắn nhất
    	float optimalAngleTank = shortestRotation(monster.angleTank, monster.targetAngleTank);

    	// Dùng lerp để chuyển dần
    	monster.angleTank = lerp(monster.angleTank, optimalAngleTank, 0.2f);
    	
    	if (fabs(monster.angleTank - monster.targetAngleTank) < 1.0f) {
            monster.angleTank = round(monster.angleTank / 90) * 90;
        }
        
//    	std :: cout << monster.angleTank << std :: endl;
	}
}

void Monster::moveMonster() {
    for (auto &monster : monsters) {
//    	std :: cout << monster.hp << std :: endl;

		//lưu tọa độ cũ
    	int oldX = monster.x ;
    	int oldY = monster.y ;
    	
    	//lấy phần dư
    	monster.angleTank = fmod(monster.angleTank + 360, 360) ;  
    	
    	//xét các trường hợp góc 
        switch (int(monster.angleTank)) {
            case 0:
                monster.y -= monster.speed;
                break;
            case 90:
                monster.x += monster.speed;
                break;
            case 180:
                monster.y += monster.speed;
                break;
            case 270:
                monster.x -= monster.speed;
                break;
        }
        
        bool collision = false ;
        bool collisionPlayer = false ;
        SDL_Rect monsterRect = {monster.x, monster.y, sizePlayerX - 10, sizePlayerY - 10};
        SDL_Rect playerRect = {player->x, player->y, sizePlayerX - 10, sizePlayerY - 10} ;
        
        
        //kiểm tra va chạm
        if(checkTankOutOfMap(monsterRect))  collision = true ;
        if(checkCollision(playerRect, monsterRect) || checkCollision(monsterRect, wall1) ||
			checkCollision(monsterRect, wall1) || checkCollision(monsterRect, wall2) ||
			checkCollision(monsterRect, wall3) || checkCollision(monsterRect, wall4)) collision = true ;

        for(auto &other : monsters) {
        	if(&monster == &other) continue ;
        	SDL_Rect otherRect = {other.x, other.y, sizePlayerX - 10, sizePlayerY - 10};
        	
        	if(checkCollision(monsterRect, otherRect)) collision = true ;
		}
		
		if(collision) {
		 	monster.changeDirection = true ;
			monster.x = oldX ;
			monster.y = oldY ;
		}
		
    }
}

void Monster :: attackPlayer() {
	for(auto &monster : monsters) {
		Uint32 currentTime = SDL_GetTicks() ;
		
	    int centerX = monster.x ;
	    int centerY = monster.y ;
		
		if(sqrt(pow(player->x - monster.x, 2) + pow(player->y - monster.y, 2)) <= monster.attackRange &&
			currentTime - monster.lastTimeAttack >= monster.speedShot) {
			monster.isAttacking = true ;
	   		monster.lastTimeAttack = currentTime ;
		} else monster.isAttacking = false ;
		
		//nếu khoảng cách giữa quái và player <= attackRange thì tính toán góc của vũ khí
		if(sqrt(pow(player->x - monster.x, 2) + pow(player->y - monster.y, 2)) <= monster.attackRange) {
	    	monster.targetAngleWeapon = atan2(player->y - centerY, player->x - centerX) * (180.0 / PI) + 90.0 ;
	   		if(fmod(monster.targetAngleWeapon, 90) == 0 ) monster.angleWeapon = monster.targetAngleWeapon ;
	   			else monster.angleWeapon = monster.targetAngleWeapon + 2 ;
		}
	}
}

void Monster :: Reset() {
	monsters.clear() ;
}