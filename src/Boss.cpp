#include "../include/Boss.h"
#include <cmath>

Boss :: Boss(Player* player) 
	: hp(5000), maxHp(5000), dame(75), speed(3), speedBullet(8), speedShot(1000), angleWeapon(0), angleBody(0),
	x(448), y(100), changeDirection(false), isShot(false), lastTimeShot(0),
	player(player) 
	{
}

void Boss :: updateAngle() {
	if(player->currentMap == 1) {
		Uint32 currentTime = SDL_GetTicks(); // Lấy thời gian hiện tại
	    if (currentTime - lastChangeTime >= 5000 || changeDirection) {
	        // Đổi hướng ngẫu nhiên +90 hoặc -90
	        if (rand() % 2 == 0) {
	            targetAngle = fmod(targetAngle + 90, 360);
	        } else {
	            targetAngle = fmod(targetAngle - 90 + 360, 360);
	        }
	
	        lastChangeTime = currentTime;
	        changeDirection = false;  // Đặt lại cờ sau khi thay đổi hướng
	    }
	
	    // Tính góc quay ngắn nhất từ góc hiện tại đến góc mục tiêu
	    float optimalAngle = fmod(targetAngle - angleBody + 360, 360);
	    if (optimalAngle > 180) {
	        optimalAngle -= 360;  // Chuyển góc về phạm vi [-180, 180]
	    }
	
	    // Dùng lerp để chuyển dần góc
	    angleBody = lerp(angleBody, angleBody + optimalAngle, 0.2f);  // Điều chỉnh tốc độ quay (0.2f có thể thay đổi)
	
	    // Nếu góc quay đã đủ gần góc mục tiêu, làm tròn góc về 0, 90, 180, 270
	    if (fabs(angleBody - targetAngle) < 1.0f) {
	        angleBody = round(angleBody / 90) * 90;
	    }
	
	    //Duy trì góc trong phạm vi [0, 360]
	    angleBody = fmod(angleBody + 360, 360);
	
	    int centerX = x + sizeBodyBossX / 2;  // Tọa độ tâm Boss
	    int centerY = y + sizeBodyBossY / 2;
	
	    int playerX = player->x + sizePlayerX / 2;  // Tọa độ tâm Player
	    int playerY = player->y + sizePlayerY / 2;
	
	    // Tính góc từ Boss đến Player
	    float angleRad = atan2(centerY - player->y, centerX - player->x) ; // Góc tính bằng radian
	    angleWeapon = angleRad * 180 / M_PI - 90; // Chuyển đổi radian -> độ
    }
}

void Boss :: move() {
	if(player->currentMap == 1) {
		angleBody = fmod(angleBody + 360, 360);  // Đảm bảo góc trong phạm vi [0, 360]
		int oldX = x ;
		int oldY = y ;
	    // Di chuyển Boss theo góc
	    switch (int(angleBody)) {
	        case 0:   // Di chuyển lên trên
	            y -= speed;
	            break;
	        case 90:  // Di chuyển sang phải
	            x += speed;
	            break;
	        case 180: // Di chuyển xuống dưới
	            y += speed;
	            break;
	        case 270: // Di chuyển sang trái
	            x -= speed;
	            break;
	    }
	    
	    if(x < 64 || x > 832 || y < 64 || y > 384) {
	    	changeDirection = true ;
	    	x = oldX ;
	    	y = oldY ;
		}
	}
}

void Boss::Reset() {
	hp = 3000 ;
	x = 448 ;
	y = 100 ;
}