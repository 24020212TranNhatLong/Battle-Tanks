#include "../include/UtilityFunction.h"

//nội suy tuyến tính
float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

//hàm tính góc quy ngắn nhất
float shortestRotation(float currentAngle, float targetAngle) {
    float diff = fmod(targetAngle - currentAngle + 180, 360) - 180;
    return currentAngle + diff;
}

//kiểm tra va chạm bằng hàm trong SDL2
bool checkCollision(SDL_Rect a, SDL_Rect b) {
	return SDL_HasIntersection(&a, &b);
}

//kiểm tra ra khỏi màn hình
bool checkBulletOutOfScreen(int x, int y) {
	return (x<0 || y<0 || x>1024 || y>576) ;
}


double Distance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool checkTankOutOfMap(SDL_Rect a) {
	return a.x < 35 || a.y < 35 || a.x > 910 || a.y > 460 ;
}

//kiểm tra xem có bấm vào đúng nút hay không
bool isMouseInside(SDL_Rect button, int mouseX, int mouseY) {
	return (mouseX > button.x && mouseX < button.x + button.w && mouseY > button.y && mouseY < button.y + button.h);
}



