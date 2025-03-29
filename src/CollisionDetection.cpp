#include "../include/CollisionDetection.h"

CollisionDetection :: CollisionDetection(Player* player, Monster* MonsterOop, BulletProcessing* bulletProcessor) 
	: player(player), MonsterOop(MonsterOop), bulletProcessor(bulletProcessor) 
	{
}


void CollisionDetection::BulletPlayerAndMonster() {
    for (auto bulletIt = bulletProcessor->bulletsPlayer.begin(); bulletIt != bulletProcessor->bulletsPlayer.end(); ) {
        SDL_Rect bulletRect = {bulletIt->x , bulletIt->y , sizeBulletX, sizeBulletY}; //vị trí, kích thước của đạn

        if (checkBulletOutOfScreen(bulletIt->x, bulletIt->y)) {
            bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
            continue; // chuyen sang vien dan tiep theo
        }

        bool bulletErased = false;

        for (auto monsterIt = MonsterOop->monsters.begin(); monsterIt != MonsterOop->monsters.end(); ) {
        	//vị trí, kích thước của đạn
            SDL_Rect monsterRect = {monsterIt->x, monsterIt->y, sizePlayerX - 15, sizePlayerY - 15}; 

            if (checkCollision(bulletRect, monsterRect)) {
            	//xóa đạn
                bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
                bulletErased = true;

                if (monsterIt->hp - player->dame <= 0) { // quái vật hết máu
                    monsterIt = MonsterOop->monsters.erase(monsterIt);
                    player->exp++; //tăng kinh nghiệm của người chơi
                    player->scores++; //cộng thêm 1 điểm
                    if(player->hp + 50 > player->maxHp) player->hp = player->maxHp ;  //hồi đầy máu cho người chơi
                    	else player->hp += 50 ; //hồi 50 máu cho người chơi
                    if (player->exp == player->maxExpLevel) { //kinh nghiệm đạt giá trị max
                    	//tăng level
                        player->level++;
                        //tăng năng lượng max
                        player->maxExpLevel += 2; //
                        if(player->hp + 100 > player->maxHp) player->hp = player->maxHp ;  
                        	else player->hp += 100 ; 
                        player->exp = 0; 
                    }
                } else {
                    monsterIt->hp -= bulletIt->dame; //giảm máu kẻ địch
                    ++monsterIt;  //kiểm tra kẻ địch tiếp theo
                }

                break; 
            } else {
                ++monsterIt; //kiểm tra kẻ địch tiếp theo
            }
        }

        if (!bulletErased) {
            ++bulletIt;
        }
    }
}


void CollisionDetection::BulletMonsterAndPlayer() {
    for (auto bulletIt = bulletProcessor->bulletsMonster.begin(); bulletIt != bulletProcessor->bulletsMonster.end(); ) {
        SDL_Rect bulletRect = {bulletIt->x , bulletIt->y , sizeBulletX, sizeBulletY}; //vị trí, kích thước của đạn
		
		if (checkBulletOutOfScreen(bulletIt->x, bulletIt->y)) {
            bulletIt = bulletProcessor->bulletsMonster.erase(bulletIt); 
            continue; // chuyen sang vien dan tiep theo
        }
        
        bool bulletErased = false;
        
        SDL_Rect playerRect = {player->x, player->y, sizePlayerX - 10, sizePlayerY - 10};  //vị trí, kích thước của đạn
            
    	//kiểm tra va chạm giữa đạn và người chơi
        if (checkCollision(bulletRect, playerRect)) {
            bulletIt = bulletProcessor->bulletsMonster.erase(bulletIt);   //xóa đạn
            player->hp -= bulletIt->dame; //giảm máu người chơi
            bulletErased = true; 
            break; 
        }
				
        if (!bulletErased) { 
            ++bulletIt; //kiểm tra viên đạn tiếp theo
        }
    }
}

void CollisionDetection::BulletMonsterAndWall() {
	for (auto bulletIt = bulletProcessor->bulletsMonster.begin(); bulletIt != bulletProcessor->bulletsMonster.end(); ) {
		SDL_Rect bulletRect = {bulletIt->x , bulletIt->y , sizeBulletX, sizeBulletY};  //vị trí, kích thước của đạn
		
		//kiểm tra va chạm
		if( (-bulletIt->x - bulletIt->y + 630 <= 0 && bulletIt->x - bulletIt->y - 318 <= 0 &&
			bulletIt->x - bulletIt->y -180 >= 0 && - bulletIt->x - bulletIt->y + 880 >= 0 &&
			bulletIt->x < 555 && bulletIt->x > 410 && bulletIt->y > 220 && bulletIt->y < 347 ) ||
			checkCollision(bulletRect, wall1) || checkCollision(bulletRect, wall2) ||
			checkCollision(bulletRect, wall3) ) {
				
			bulletIt = bulletProcessor->bulletsMonster.erase(bulletIt); //xóa đạn
		} else bulletIt++ ; //kiểm tra viên đạn tiếp theo
	}	 
}

void CollisionDetection::BulletPlayerAndWall() {
	for (auto bulletIt = bulletProcessor->bulletsPlayer.begin(); bulletIt != bulletProcessor->bulletsPlayer.end(); ) {
		SDL_Rect bulletRect = {bulletIt->x , bulletIt->y , sizeBulletX, sizeBulletY};
		
		//kiểm tra va chạm
		if( (-bulletIt->x - bulletIt->y + 630 <= 0 && bulletIt->x - bulletIt->y - 318 <= 0 &&
			bulletIt->x - bulletIt->y -180 >= 0 && - bulletIt->x - bulletIt->y + 880 >= 0 &&
			bulletIt->x < 555 && bulletIt->x > 410 && bulletIt->y > 220 && bulletIt->y < 347 ) ||
			checkCollision(bulletRect, wall1) || checkCollision(bulletRect, wall2) ||
			checkCollision(bulletRect, wall3) ) {
				
		//xóa đạn
			bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
		} else bulletIt++ ; //kiểm tra viên đạn tiếp theo
	}	 
}


