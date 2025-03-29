#ifndef BULLETPROCESSING_H
#define BULLETPROCESSING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_mixer.h>
#include "Player.h"
#include "Constants.h"
#include <vector>
#include <cmath>
#include "Monster.h"
#include <ctime>

struct Bullet {
	int x, y, speed, dame;
	double angle;
	
	Bullet(int _x,int _y,double _angle,int _speed, int _dame) {
		x = _x ;
		y = _y ;
		speed = _speed  ;
		angle = _angle - 90;
		dame = _dame ;
	}
	
	void Update() {
		if(angle == 0 || angle == 90 || angle == 270) {
			x += speed * cos(angle * PI / 180) ;
			y += speed * sin(angle * PI / 180) ;
		} else {
			x += speed * (cos(angle * PI / 180) + 0.05 ) ;
			y += speed * (sin(angle * PI / 180) + 0.05 ) ;
		} 
	}
};

class BulletProcessing {
public :
	BulletProcessing(Player* player, Monster* MonsterOop, Mix_Music* shotMusic) ;  
	std :: vector<Bullet> bulletsPlayer ; //vector chứa đạn được bắn ra bởi người chơi
	std :: vector<Bullet> bulletsMonster ; //vector chứa đạn được bắn ra bởi quái vật
	void ShotByPlayer(SDL_Event	event) ; //xử lí sự kiện bắn đạn
	void UpdatePositionBulletPlayer() ; //cập nhật vị trí đạn của người chơi
	void UpdatePositionBulletMonster() ; //cập nhật vị trí đạn của quái vật
	void ShotByMonster() ; //xử lí sự kiện bắn đạn của quái vật
	void Reset() ; //đặt lại đạn
	Player* player ;
	Monster* MonsterOop ;
	Mix_Music* shotMusic ;
	
};
#endif 