#include "../include/Player.h"
#include "../include/Monster.h"

Player :: Player() 
	: level(1),scores(0), dame(20), hp(200), exp(0), maxExpLevel(3), maxHp(200), 
	x(446), y(434), speed(2), speedShot(1400), lastTimeShot(0),
	isMovingUp(false), isMovingDown(false), isMovingLeft(false), isMovingRight(false),
	angleWeapon(0), anglePlayer(0),
	isAttacking(false) 
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


void Player :: UpdatePosition(int mouseX, int mouseY, Monster* MonstersOop) {
	int dx = 0 , dy = 0 ;
	if(isMovingUp) dy -= 1 ;
	if(isMovingDown) dy += 1 ;
	if(isMovingLeft) dx -= 1 ;
	if(isMovingRight) dx += 1 ;
	
	int oldX = x ;
	int oldY = y ;
	if(dx != 0 && dy != 0) {
		if(dx == 1 && dy == 1) {
			x += dx * speed / sqrt(4) ;
			y += dy * speed / sqrt(4) ;
		}
		else {
			x += dx * speed / sqrt(2) ;
			y += dy * speed / sqrt(2) ;
		}
	} else {
		x += dx * speed ;
		y += dy * speed ;
	}
	
	SDL_Rect playerRect = {x, y, sizePlayerX - 10, sizePlayerY - 10} ;
	
	//kiểm tra va chạm với map
	if(checkTankOutOfMap(playerRect) || checkCollision(playerRect, wall1) ||
			checkCollision(playerRect, wall1) || checkCollision(playerRect, wall2) ||
			checkCollision(playerRect, wall3) || checkCollision(playerRect, wall4)) {
		x = oldX;
		y = oldY;
	}
	
	//kiểm tra va chạm giữa monster và player
	for(auto& monster : MonstersOop->monsters) {
		SDL_Rect monsterRect = {monster.x, monster.y, sizePlayerX-10, sizePlayerY-10} ;
		if(checkCollision(playerRect, monsterRect)) {
			x = oldX;
			y = oldY;
		}
	}
}

void Player :: UpdatePower() {
	maxHp = 150 + level * 50 ;
	dame = 18 + level * 5 ;
	if(speedShot > 400) speedShot = 1400 - level * 200 ;
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
}