#include "../include/BulletProcessing.h" 

BulletProcessing :: BulletProcessing(Player* player, Monster* MonsterOop, Mix_Music* shotMusic)  
	: player(player), MonsterOop(MonsterOop), shotMusic(shotMusic) 
	{
}

//*************** Player ***************//

void BulletProcessing :: ShotByPlayer(SDL_Event event) {
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		const int gunLength = 35;  // Điều chỉnh tùy theo súng dài hay ngắn
		Uint32 currentTime = SDL_GetTicks() ; //lấy thời gian
		if(currentTime - player->lastTimeShot >= player->speedShot) {  //kiểm tra xem đã bắn được chưa
			player->isAttacking = true ;
			
			// Tọa độ trung tâm xe tăng
			int centerX = player->x + sizePlayerX / 2;
			int centerY = player->y + sizePlayerY / 2;
			
			// Tọa độ đầu nòng súng
			int bulletStartX = centerX + gunLength * sin(player->angleWeapon * PI / 180) - 3 ;
			int bulletStartY = centerY - gunLength * cos(player->angleWeapon * PI / 180) - 3 ;
			
			// Tạo viên đạn tại đầu nòng súng
			bulletsPlayer.push_back({bulletStartX , bulletStartY , player->angleWeapon, 5 + player->level, player->dame});
			Mix_PlayMusic(shotMusic, 0);
	//		printf("Bullet shot from (%d, %d) at angle %f\n", bulletStartX, bulletStartY, player->angleWeapon);
			player->lastTimeShot = currentTime ;
		}	
	}
}

void BulletProcessing :: UpdatePositionBulletPlayer() {
//	printf("Number of bullets: %lu\n", bulletsPlayer.size());
	for(size_t i=0 ; i < bulletsPlayer.size() ; i++) {
		bulletsPlayer[i].Update() ;
	}
}

// **************** Monster ****************//

void BulletProcessing :: ShotByMonster() {
	const int gunLength = 35;  // Điều chỉnh tùy theo súng dài hay ngắn
	for(auto &monster : MonsterOop->monsters) {
		if(monster.isAttacking) {
			int centerX = monster.x + sizePlayerX / 2;
			int centerY = monster.y + sizePlayerY / 2;
				
			// Tọa độ đầu nòng súng
			int bulletStartX = centerX + gunLength * sin(monster.angleWeapon * PI / 180) - 3 ;
			int bulletStartY = centerY - gunLength * cos(monster.angleWeapon * PI / 180) - 3 ;
			
			// Tạo viên đạn tại đầu nòng súng
			bulletsMonster.push_back({bulletStartX , bulletStartY , monster.angleWeapon, 5 + player->level, monster.dame});
			Mix_PlayMusic(shotMusic, 0);
			monster.isShotting = true ;
		}
	}
}

void BulletProcessing :: UpdatePositionBulletMonster() {
	for(size_t i=0 ; i < bulletsMonster.size() ; i++) bulletsMonster[i].Update() ;
}

void BulletProcessing :: Reset() {
	bulletsMonster.clear() ; //xóa hết đạn của quái vật
	bulletsPlayer.clear() ; //xóa hết đạn của người chơi
}
