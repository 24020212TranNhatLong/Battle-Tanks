#include "../include/CollisionDetection.h"
#include <cstdlib>  
#include <ctime>

CollisionDetection :: CollisionDetection(Player* player, Monster* MonsterOop, BulletProcessing* bulletProcessor, Item* itemProcessor, Boss* boss, UIManager* UI) 
	: player(player), MonsterOop(MonsterOop), bulletProcessor(bulletProcessor), itemProcessor(itemProcessor), boss(boss), UI(UI) 

	{
}




void CollisionDetection::BulletPlayerAndMonster() {
	//map 1 không có quái
	if(player->currentMap == 1) return ;
	
    for (auto bulletIt = bulletProcessor->bulletsPlayer.begin(); bulletIt != bulletProcessor->bulletsPlayer.end(); ) {
        SDL_Rect bulletRect = {bulletIt->x , bulletIt->y , sizeBulletX, sizeBulletY}; 
		
        // 🔥 Kiểm tra nếu đạn bay ra khỏi màn hình thì xóa
        if (checkBulletOutOfScreen(bulletIt->x, bulletIt->y)) {
            bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
            continue; // Chuyển sang viên đạn tiếp theo

        }

        bool bulletErased = false;

        // Lấy danh sách quái vật theo map
        std::vector<Monsters>* currentMonster = nullptr;
        switch (player->currentMap) {
            case 0: currentMonster = &MonsterOop->m0monsters; break;
            case 2: currentMonster = &MonsterOop->m2monsters; break;
            case 3: currentMonster = &MonsterOop->m3monsters; break;
        }

        auto& monsters = *currentMonster; // Tham chiếu đến danh sách quái của map hiện tại
        for (auto monsterIt = monsters.begin(); monsterIt != monsters.end(); ) {
            SDL_Rect monsterRect = {monsterIt->x, monsterIt->y, sizePlayerX - 15, sizePlayerY - 15}; 
			
            if (checkCollision(bulletRect, monsterRect)) {
                int dame = bulletIt->dame;  // Lưu sát thương trước khi xóa đạn
                bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
                bulletErased = true;

                //  Giảm máu quái
                monsterIt->hp -= dame; 

                if (monsterIt->hp <= 0) { // Quái chết
                	int dropChance = rand() % 100;  

				    if (dropChance < 30 && player->currentMap >= 2) {  // 30% rơi exp
				        itemProcessor->expList.push_back({monsterIt->x, monsterIt->y});
				    } else if (dropChance < 60 && player->currentMap >= 0) {  // 30% rơi bình HP
				        itemProcessor->hpList.push_back({monsterIt->x, monsterIt->y});
				    } else if (dropChance < 80 && player->currentMap == 3) {  // 20=% rơi hộp đồ (box)
				        itemProcessor->boxList.push_back({monsterIt->x, monsterIt->y});
				    } else {
				        // 45% không rơi gì cả
				    }
				    
                    monsterIt = monsters.erase(monsterIt);
                    player->exp++;  
                    player->scores++;  
                    player->HandleHighScore() ;
                    //  Hồi máu cho người chơi
                    player->hp = std::min(player->hp + 50, player->maxHp);  

                    //  Kiểm tra lên cấp
                    if (player->exp >= player->maxExpLevel) { 
                        player->level++;
                        player->exp = player->exp - player->maxExpLevel ;
                        player->maxExpLevel += 2; 
                        player->hp = std::min(player->hp + 100, player->maxHp);
                         
                    }
                } else {
                    ++monsterIt;  // Kiểm tra quái tiếp theo
                }
                break; 
            } else {
                ++monsterIt; 
            }
        }

        if (!bulletErased) {
            ++bulletIt;
        }
    }
}




void CollisionDetection::BulletMonsterAndPlayer() {
	//map 1 không có quái
	if(player->currentMap == 1) return ;
	
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
	//map 1 không có quái
	if(player->currentMap == 1) return ;
	
    for (auto bulletIt = bulletProcessor->bulletsMonster.begin(); bulletIt != bulletProcessor->bulletsMonster.end(); ) {
        // Xác định hình chữ nhật của viên đạn
        SDL_Rect bulletRect = { bulletIt->x, bulletIt->y, sizeBulletX, sizeBulletY };
        // Kiểm tra va chạm theo bản đồ hiện tại của nhân vật
        bool collided = false;
        switch (player->currentMap) {
            case 0: // Map 0
                for (auto& wall : wallMap0) {
                    if (checkCollision(bulletRect, wall)) {
                        collided = true;
                        break;
                    }
                }
                break;
            case 2: // Map 2
                for (auto& wall : wallMap2) {
                    if (checkCollision(bulletRect, wall)) {
                        collided = true;
                        break;
                    }
                }
                break;
            case 3: // Map 3
                for (auto& wall : wallMap3) {
                    if (checkCollision(bulletRect, wall)) {
                        collided = true;
                        break;
                    }
                }
                break;
        }

        // Nếu có va chạm với tường, xóa đạn
        if (collided) {
            bulletIt = bulletProcessor->bulletsMonster.erase(bulletIt);
        } else {
            ++bulletIt; // Nếu không, kiểm tra viên đạn tiếp theo
        }
    }
}


void CollisionDetection::BulletPlayerAndWall() {
    // Duyệt từng viên đạn trong danh sách đạn của người chơi
    for (auto bulletIt = bulletProcessor->bulletsPlayer.begin(); bulletIt != bulletProcessor->bulletsPlayer.end(); ) {
        // Tạo hình chữ nhật đại diện cho viên đạn
        SDL_Rect bulletRect = { bulletIt->x, bulletIt->y, sizeBulletX, sizeBulletY };

        // Xác định danh sách tường theo bản đồ hiện tại
        std::vector<SDL_Rect>* currentWalls = nullptr;
        switch (player->currentMap) {
            case 0: currentWalls = &wallMap0; break;
            case 1: currentWalls = &wallMap1; break;
            case 2: currentWalls = &wallMap2; break;
            case 3: currentWalls = &wallMap3; break;
            default: continue; // Nếu map không hợp lệ, bỏ qua đạn này
        }

        // Kiểm tra va chạm với tường
        bool erased = false;
        for (auto& wall : *currentWalls) {
            if (checkCollision(bulletRect, wall)) {
                bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
                erased = true;
                break; // Dừng vòng lặp khi đạn bị xóa
            }
        }

        // Nếu đạn bị xóa, không cần tăng iterator
        if (!erased) {
            ++bulletIt;
        }
    }
}


void CollisionDetection::PlayerAndHp() {
	if(player->currentMap == 1) return ;
    for (auto it = itemProcessor->hpList.begin(); it != itemProcessor->hpList.end(); ) {
        SDL_Rect hpRect = {it->x, it->y, 32, 32};
        SDL_Rect playerRect = {player->x, player->y, sizePlayerX, sizePlayerY};

        if (checkCollision(playerRect, hpRect)) {
			if(player->hp + 50 <= player->maxHp) player->hp += 50 ;
				else player->hp = player->maxHp ;
            it = itemProcessor->hpList.erase(it); // Xóa bình HP và cập nhật iterator
        } else {
            ++it; // Chỉ tăng iterator nếu không xóa phần tử
        }
    }
}

void CollisionDetection::PlayerAndExp() {
    for (auto it = itemProcessor->expList.begin(); it != itemProcessor->expList.end(); ) {
        SDL_Rect expRect = {it->x, it->y, 32, 32};
        SDL_Rect playerRect = {player->x, player->y, sizePlayerX, sizePlayerY};

        if (checkCollision(playerRect, expRect)) {
		    player->exp += 3;  // Cộng exp trước
		
		    while (player->exp >= player->maxExpLevel) {  // Kiểm tra nếu exp đạt mức tối đa
		        player->exp -= player->maxExpLevel;  // Trừ đi mức exp cần để lên cấp
		        player->level++;  // Tăng cấp
		        player->maxExpLevel += 2;  // Tăng giới hạn exp cần thiết cho cấp tiếp theo
		    }
		
		    it = itemProcessor->expList.erase(it);  // Xóa bình exp sau khi nhặt
		} else {
		    ++it;
		}

    }
}

void CollisionDetection::PlayerAndBox() {
    for (auto it = itemProcessor->boxList.begin(); it != itemProcessor->boxList.end(); ) {
        SDL_Rect boxRect = {it->x, it->y, 32, 32};  // Kích thước hộp
        SDL_Rect playerRect = {player->x, player->y, sizePlayerX, sizePlayerY};  // Kích thước người chơi

        if (checkCollision(playerRect, boxRect)) {
            int reward = rand() % 100;  // Random số từ 0 -> 99

            if (reward < 30) {  // 30%: Nhận 70 máu
                player->hp = std::min(player->hp + 70, player->maxHp);
                strcpy(UI->message, "You have gained 70 health points!");
                UI->startTime = SDL_GetTicks() ;
                UI->notiBox = true ;
            } 
            else if (reward < 30) {  // 30%: Nhận 4 exp
                if (player->exp + 4 < player->maxExpLevel) {
                    player->exp += 4;
                    strcpy(UI->message, "You have gained 4 experience points!") ; 
                    UI->startTime = SDL_GetTicks() ;
                    UI->notiBox = true ;
                } else {
                    player->exp = (player->exp + 4) % player->maxExpLevel;
                    player->level++;
                }
            } 
            else if(reward < 80) {  // 20%: Nhận chìa khóa vào boss
                player->keyBoss = true ;
                strcpy(UI->message, "You have obtained the Boss Key!") ;
                UI->startTime = SDL_GetTicks() ;
                UI->notiBox = true ;
            } else {
            	strcpy(UI->message, "You got nothing!") ;
                UI->startTime = SDL_GetTicks() ;
                UI->notiBox = true ;
			}

            // Xóa hộp sau khi nhặt
            it = itemProcessor->boxList.erase(it);
        } 
        else {
            ++it;
        }
    }
}

void CollisionDetection::BulletBossAndPlayer() {
	if(player->currentMap == 1) {
	    // Duyệt từng viên đạn trong danh sách đạn của boss
	    for (auto bulletIt = bulletProcessor->bulletsBoss.begin(); bulletIt != bulletProcessor->bulletsBoss.end(); ) {
	        // Tạo hình chữ nhật đại diện cho viên đạn
	        SDL_Rect bulletRect = { bulletIt->x, bulletIt->y, sizeBulletBossX, sizeBulletBossY };
	        SDL_Rect playerRect = { player->x, player->y, sizePlayerX, sizePlayerY };
	
	        // Kiểm tra va chạm giữa viên đạn và người chơi
	        if (checkCollision(bulletRect, playerRect)) {
	        	player->hp -= boss->dame ;
	        	
	            // Nếu có va chạm, xóa viên đạn
	            bulletIt = bulletProcessor->bulletsBoss.erase(bulletIt);
	        } else {
	            // Nếu không xóa viên đạn, tiếp tục tăng iterator
	            ++bulletIt;
	        }
	    }
	}
}

void CollisionDetection::BulletPlayerAndBoss() {
	if(player->currentMap == 1) {
	    // Duyệt từng viên đạn trong danh sách đạn của người chơi
	    for (auto bulletIt = bulletProcessor->bulletsPlayer.begin(); bulletIt != bulletProcessor->bulletsPlayer.end(); ) {
	        // Tạo hình chữ nhật đại diện cho viên đạn
	        SDL_Rect bulletRect = { bulletIt->x, bulletIt->y, sizeBulletX, sizeBulletY };
	        SDL_Rect bossRect = { boss->x, boss->y, sizeBodyBossX, sizeBodyBossY };  // Hình chữ nhật của Boss
	
	        // Kiểm tra va chạm giữa viên đạn và Boss
	        if (checkCollision(bulletRect, bossRect)) {
	            boss->hp -= player->dame;  
	            if(boss->hp - player->dame <= 0) {
	            	boss->hp = 0 ;
	            	player->scores += 20 ;
	            	player->HandleHighScore() ;
	            }	else boss->hp -= player->dame ;
	            // Xóa viên đạn khỏi danh sách
	            bulletIt = bulletProcessor->bulletsPlayer.erase(bulletIt);
	        } else {
	            // Nếu không xóa viên đạn, tiếp tục tăng iterator
	            ++bulletIt;
	        }
	    }
	}
}


