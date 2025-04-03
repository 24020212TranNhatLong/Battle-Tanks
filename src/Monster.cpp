#include "../include/Monster.h"
#include "../include/BulletProcessing.h"
#include <cstdlib>
#include <ctime>

Monster::Monster(Player* player) 
    : player(player) {
    srand(time(0)); // Chỉ gọi một lần khi tạo quái
}

// Hàm kiểm tra xem có va chạm không
bool Monster::isValidSpawn(int x, int y, std::vector<SDL_Rect>& walls, std::vector<Monsters>& monsters) {
    SDL_Rect monsterRect = {x, y, sizePlayerX, sizePlayerY};

    // Kiểm tra va chạm với player
    SDL_Rect playerRect = {player->x, player->y, sizePlayerX, sizePlayerY};
    if (checkCollision(monsterRect, playerRect)) return false;

    // Kiểm tra va chạm với tường
    for (int i = 0; i < walls.size(); i++) {
        if (checkCollision(monsterRect, walls[i])) return false;
    }

    // Kiểm tra va chạm với quái khác
    for (int i = 0; i < monsters.size(); i++) {
        SDL_Rect other = {monsters[i].x, monsters[i].y, sizePlayerX, sizePlayerY};
        if (checkCollision(monsterRect, other)) return false;
    }

    return true; // Nếu không va chạm, vị trí hợp lệ
}

// Hàm tìm vị trí spawn hợp lệ
void Monster::findSpawnPosition(int& x, int& y, std::vector<SDL_Rect>& walls, std::vector<Monsters>& monsters) {
    int attempts = 50;
    do {
        x = rand() % 820 + 64; 
        y = rand() % 380 + 64;
    } while (--attempts > 0 && !isValidSpawn(x, y, walls, monsters));
}

// Hàm spawn quái
void Monster::spawnMonster() {
	if(player->currentMap != 1) {
	    int x, y;
	
	    if (m0monsters.empty()) {
	        findSpawnPosition(x, y, wallMap0, m0monsters);
	        m0monsters.push_back(Monsters(x, y, player));
	    }	    
	    if (m2monsters.empty()) {
	        findSpawnPosition(x, y, wallMap2, m2monsters);
	        m2monsters.push_back(Monsters(x, y, player));
	
	        findSpawnPosition(x, y, wallMap2, m2monsters);
	        m2monsters.push_back(Monsters(x, y, player));
	    }
	
	    if (m3monsters.empty()) {
	        findSpawnPosition(x, y, wallMap3, m3monsters);
	        m3monsters.push_back(Monsters(x, y, player));
	
	        findSpawnPosition(x, y, wallMap3, m3monsters);
	        m3monsters.push_back(Monsters(x, y, player));
	
	        findSpawnPosition(x, y, wallMap3, m3monsters);
	        m3monsters.push_back(Monsters(x, y, player));
	    }
	}
}

void Monster :: updateAngleTank() {
	if(player->currentMap == 1) return ;
	
		Uint32 currentTime = SDL_GetTicks() ; //lấy thời gian
		std :: vector<Monsters>* currentMonster = NULL ;
		switch(player->currentMap) {
			case 0 :
				currentMonster = &m0monsters ;
				break ;
			case 2 :
				currentMonster = &m2monsters ;
				break ;
			case 3 :
				currentMonster = &m3monsters ;
				break ;
		}
			
		//duyệt từng quái vật
		for(auto &monster : *currentMonster) {
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
	if(player->currentMap == 1) return ;
	
		std :: vector<Monsters>* currentMonster = NULL ;
		switch(player->currentMap) {
			case 0 :
				currentMonster = &m0monsters ;
				break ;
			case 2 :
				currentMonster = &m2monsters ;
				break ;
			case 3 :
				currentMonster = &m3monsters ;
				break ;
		}
	    for (auto &monster : *currentMonster) {
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
	        SDL_Rect monsterRect = {monster.x, monster.y, sizePlayerX - 10, sizePlayerY - 10};
	        SDL_Rect playerRect = {player->x, player->y, sizePlayerX - 10, sizePlayerY - 10} ;
	        
	        if(checkCollision(monsterRect, playerRect)) collision = true ;
	        //kiểm tra va chạm
	        if(checkTankOutOfMap(monsterRect))  collision = true ;
	       	std::vector<SDL_Rect>* currentWalls = nullptr;
    		switch (player->currentMap) {
       		 	case 0: currentWalls = &wallMap0; break;
        		case 2: currentWalls = &wallMap2; break;
        		case 3: currentWalls = &wallMap3; break;
    		}
    		
    		if (currentWalls) {
	        for (auto& wall : *currentWalls) {
	            if (checkCollision(monsterRect, wall)) {
	                collision = true ;
	                break;
	            }
	    	}
				
	        for(auto &other : *currentMonster) {
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
}

void Monster::attackPlayer() { 
	if(player->currentMap == 1) return ;
    // Xác định danh sách quái theo bản đồ hiện tại

    	std::vector<Monsters>* currentMonster = nullptr;
	    switch (player->currentMap) {
	        case 0:
	            currentMonster = &m0monsters;
	            break;
	        case 2:
	            currentMonster = &m2monsters;
	            break;
	        case 3:
	            currentMonster = &m3monsters;
	            break;
	        default:
	            return; // Tránh lỗi nếu map không hợp lệ
	    }

	    Uint32 currentTime = SDL_GetTicks();
	
	    // Duyệt từng quái vật
	    for (auto& monster : *currentMonster) {
	        int centerX = monster.x;
	        int centerY = monster.y;
	
	        // Tính khoảng cách bình phương để tối ưu hiệu suất
	        int dx = player->x - centerX;
	        int dy = player->y - centerY;
	        int distanceSquared = dx * dx + dy * dy;
	        int attackRangeSquared = monster.attackRange * monster.attackRange;
	
	        // Kiểm tra nếu quái trong phạm vi tấn công và đủ thời gian bắn
	        if (distanceSquared <= attackRangeSquared && (currentTime - monster.lastTimeAttack >= monster.speedShot)) {
	            monster.isAttacking = true;
	        } else {
	            monster.isAttacking = false;
	        }
	
	        // Nếu quái trong phạm vi tấn công, tính toán góc bắn
	        if (distanceSquared <= attackRangeSquared) {
	            monster.angleWeapon = atan2(dy, dx) * (180.0 / PI) + 90.0;
	        }
	    }
	
}


void Monster :: Reset() {
	m0monsters.clear() ;
	m2monsters.clear() ;
	m3monsters.clear() ;
}