#include "../include/Player.h"
#include "../include/Monster.h"
#include "../include/BulletProcessing.h" 
#include "../include/Boss.h"
#include "../include/UIManager.h"

Player :: Player(Item* itemProcessor) 
	: level(1),scores(0), highScore(0), dame(25), hp(200), exp(0), maxExpLevel(3), maxHp(200), 
	x(446), y(434), speed(2), speedShot(1600), lastTimeShot(0),
	isMovingUp(false), isMovingDown(false), isMovingLeft(false), isMovingRight(false),
	angleWeapon(0), anglePlayer(0),
	currentMap(0),
	isAttacking(false), keyBoss(false),
	itemProcessor(itemProcessor)
	   {
	}


void Player::UpdateAngleWeapon(int mouseX, int mouseY) {
    // Xác định tâm xe tăng
    int centerX = x + sizePlayerX / 2;
    int centerY = y + sizePlayerY / 2;

    // Tính góc giữa trung tâm xe và con trỏ chuột
    double targetAngleWeapon = atan2(mouseY - centerY, mouseX - centerX) * (180.0 / PI) + 90.0 ;
//    std :: cout << targetAngleWeapon << std :: endl ;
   	if(targetAngleWeapon == 0 || targetAngleWeapon == 90 || targetAngleWeapon == 180 || targetAngleWeapon == 270) angleWeapon = targetAngleWeapon ;
   		else angleWeapon = targetAngleWeapon + 2 ;
   	
//   	std :: cout << angleWeapon << std :: endl;
}

void Player::UpdateAnglePlayer() {
    int targetAnglePlayer = anglePlayer ;

    // Xác định góc đích
    if (isMovingUp && !isMovingDown && isMovingLeft && !isMovingRight) targetAnglePlayer = -45;
    else if (isMovingUp && !isMovingDown && !isMovingLeft && isMovingRight) targetAnglePlayer = 45;
    else if (!isMovingUp && isMovingDown && isMovingLeft && !isMovingRight) targetAnglePlayer = -135;
    else if (!isMovingUp && isMovingDown && !isMovingLeft && isMovingRight) targetAnglePlayer = 135;
    else if (isMovingUp && !isMovingDown && !isMovingLeft && !isMovingRight) targetAnglePlayer = 0;
    else if (!isMovingUp && isMovingDown && !isMovingLeft && !isMovingRight) targetAnglePlayer = 180;
    else if (!isMovingUp && !isMovingDown && isMovingLeft && !isMovingRight) targetAnglePlayer = -90;
    else if (!isMovingUp && !isMovingDown && !isMovingLeft && isMovingRight) targetAnglePlayer = 90;

    // Tính góc quay ngắn nhất
    float optimalAngle = shortestRotation(anglePlayer, targetAnglePlayer);

    // Dùng lerp để chuyển dần
    anglePlayer = lerp(anglePlayer, optimalAngle, 0.1f);
}

void Player::UpdatePosition(int mouseX, int mouseY, Monster* MonstersOop, Boss* boss, UIManager* UI) {
    int dx = 0, dy = 0;
//    std :: cout << dame << std :: endl ;
    if (isMovingUp) dy -= 1;
    if (isMovingDown) dy += 1;
    if (isMovingLeft) dx -= 1;
    if (isMovingRight) dx += 1;

    int oldX = x, oldY = y;

    if (dx != 0 && dy != 0) {
        x += dx * speed / sqrt(2);
        y += dy * speed / sqrt(2);
    } else {
        x += dx * speed;
        y += dy * speed;
    }

	if(currentMap == 0 && !keyBoss && y <= 0 ) {
		x = oldX ;
		y = oldY ;
		strcpy(UI->message, "You need a Boss Key to enter the map!") ;
        UI->startTime = SDL_GetTicks() ;
        UI->notiBox = true ;
	}
	
    SDL_Rect playerRect = {x, y, sizePlayerX - 10, sizePlayerY - 10};

    
    std::vector<SDL_Rect>* currentWalls = nullptr;
    switch (currentMap) {
        case 0: currentWalls = &wallMap0; break;
        case 1: currentWalls = &wallMap1; break;
        case 2: currentWalls = &wallMap2; break;
        case 3: currentWalls = &wallMap3; break;
    }

    if (currentWalls) {
        for (auto& wall : *currentWalls) {
            if (checkCollision(playerRect, wall)) {
                x = oldX;
                y = oldY;
                break;
            }
        }
    }
	
	if(currentMap == 1 && y >= 512) {
		x = oldX ;
		y = oldY ;
	} 

    if (currentMap != 1) {  
        std::vector<Monsters>* currentMonsters = nullptr;
        switch (currentMap) {
            case 0: currentMonsters = &MonstersOop->m0monsters; break;
            case 2: currentMonsters = &MonstersOop->m2monsters; break;
            case 3: currentMonsters = &MonstersOop->m3monsters; break;
        }

        if (currentMonsters) {
            for (auto& monster : *currentMonsters) {
                SDL_Rect monsterRect = {monster.x, monster.y, sizePlayerX - 10, sizePlayerY - 10};
                if (checkCollision(playerRect, monsterRect)) {
                    x = oldX;
                    y = oldY;
                    break;
                }
            }
        }
    }

    
    if (currentMap == 1) { 
        SDL_Rect bossRect = {boss->x, boss->y, sizeBodyBossX, sizeBodyBossY};
        if (checkCollision(playerRect, bossRect)) {
            x = oldX;
            y = oldY;
        }
    }
}



void Player :: UpdatePower() {
	maxHp = 150 + level * 70 ;
	dame = 15 + level*7 ;
	if(speedShot > 400) speedShot = 1400 - level * 200 ;
}

void Player::UpdateMap(BulletProcessing* bulletProcessor) {
//	std :: cout << currentMap << std :: endl;
	switch (currentMap) {
		case 0 :
			if(x < -5) {
				currentMap = 2 ;
				x = 1015 ;
				y = 270 ;
				bulletProcessor->bulletsMonster.clear() ;
				bulletProcessor->bulletsPlayer.clear() ;
				itemProcessor->hpList.clear() ;
				itemProcessor->boxList.clear() ;
				itemProcessor->expList.clear() ;
			}
			if(x > 1020) {
				currentMap = 3 ;
				x = -3 ;
				bulletProcessor->bulletsMonster.clear() ;
				bulletProcessor->bulletsPlayer.clear() ;
				itemProcessor->hpList.clear() ;
				itemProcessor->expList.clear() ;
				itemProcessor->boxList.clear() ;
			}
			
			if(y < -5) {
				currentMap = 1 ;
				y = 513 ;
				bulletProcessor->bulletsMonster.clear() ;
				bulletProcessor->bulletsPlayer.clear() ;
				itemProcessor->hpList.clear() ;
				itemProcessor->expList.clear() ;
				itemProcessor->boxList.clear() ;
			}
			break ;
//		case 1 :
//			
//			break ;
		case 2 :
			if(x > 1020) {
				currentMap = 0 ;
				x = 10 ;
				y = 270 ;
				bulletProcessor->bulletsMonster.clear() ;
				bulletProcessor->bulletsPlayer.clear() ;
				itemProcessor->hpList.clear() ;
				itemProcessor->expList.clear() ;
				itemProcessor->boxList.clear() ;
			}
			break ;
		case 3 :
			if(x < -5) {
				currentMap = 0 ;
				x = 1010 ;
				y = 270 ;
				bulletProcessor->bulletsMonster.clear() ;
				bulletProcessor->bulletsPlayer.clear() ;
				itemProcessor->hpList.clear() ;
				itemProcessor->expList.clear() ;
				itemProcessor->boxList.clear() ;
			}
			break ;
	}
}

void Player :: HandleHighScore() {
	// Nếu điểm mới cao hơn thì lưu lại
    if (scores > highScore) {
        std::ofstream outFile("highscore.txt");
        if (outFile) {
            outFile << scores;
        }
        outFile.close();
    }
	// Đọc điểm cao từ file
    std::ifstream inFile("highscore.txt");
    if (inFile) {
        inFile >> highScore;
    }
    inFile.close();
} 

void Player :: Reset() {
	level = 1;
	scores = 0 ;
	dame = 20 ;
	hp = 200 ;
	exp = 0 ;
	maxExpLevel = 3;
	maxHp = 200 ; 
	x = 446 ; 
	y = 434 ; 
	speed = 2 ;
	speedShot = 1400 ; 
	isMovingUp = false ; 
	isMovingDown = false ;
	isMovingLeft = false ;
	isMovingRight = false ;
	angleWeapon = 0 ;
	anglePlayer = 0 ;
	isAttacking = false ;
	currentMap = 0 ;
	keyBoss = false ;
}