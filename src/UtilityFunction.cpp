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
	return x<0 || y<0 || x>1024 || y>576 ;
}

bool checkTankOutOfMap(SDL_Rect a) {
	return a.x < 32 || a.y < 32 || a.x > 910 || a.y > 460 ;
}

//kiểm tra xem có bấm vào đúng nút hay không
bool isMouseInside(SDL_Rect button, int mouseX, int mouseY) {
	return (mouseX > button.x && mouseX < button.x + button.w && mouseY > button.y && mouseY < button.y + button.h);
}

////đọc file
//int readFile(std :: string filePath) {
//	std::ifstream file(filePath);
//    if (!file) {
//        std::cout << "Không thể mở file!\n";
//        return 0; // Trả về 0 nếu file không mở được
//    }
//
//    int scoreMax = 0; //khởi tạo giá trị mặc định
//    file >> scoreMax;
//    file.close();
//    
//    return scoreMax;
//}
//
//void writeFile(std :: string filePath, int score) {
//	int scoreMax = readFile(filePath);
//    
//    if (scoreMax < score) {
//        std::ofstream file(filePath, std::ios::trunc); //xóa nội dung cũ
//        if (!file) {
//            std::cout << "Không thể mở file để ghi!\n";
//            return;
//        }
//        file << score;
//        file.close();
//    }
//}
